#include <cmath>
#include <iostream>
#include <vector>

#define PYBIND11
#define PI 3.14159265359

typedef std::vector<std::vector<int>> img_t;

// support function
inline double COS(int x, int i, int n)
{
  return std::cos((2 * x + 1) * i * PI / (2.0 * n));
}

// support function
inline double C(int i)
{
  return (i == 0 ? std::sqrt(0.5) : 1.0);
}

img_t dwt(img_t input, int n)
{
  img_t output = input;
  std::vector<std::vector<double>> temp(n, std::vector<double>(n));

  // horizontal transformation
  for (int i = 0; i < n; i++)
  {
    int k = 0;
    for (int j = 0; j < n; j += 2)
    {
      int a = input[i][j];
      int b = input[i][j + 1];
      temp[i][k] = (a + b);
      temp[i][k + n / 2] = (a - b);
      k++;
    }
  }

  // vertical transformation
  for (int j = 0; j < n; j++)
  {
    int k = 0;
    for (int i = 0; i < n; i += 2)
    {
      int a = temp[i][j];
      int b = temp[i + 1][j];
      output[k][j] = (a + b);
      output[k + n / 2][j] = (a - b);
      k++;
    }
  }

  return output;
}

img_t idwt(img_t input, int n)
{
  img_t output = input;
  std::vector<std::vector<double>> temp(n, std::vector<double>(n));

  // vertical transformation
  for (int j = 0; j < n; j++)
  {
    int k = 0;
    for (int i = 0; i < n / 2; i++)
    {
      int sum = input[i][j];
      int diff = input[i + n / 2][j];
      temp[k][j] = (sum + diff) / 2;
      temp[k + 1][j] = (sum - diff) / 2;
      k += 2;
    }
  }

  // horizontal transformation
  for (int i = 0; i < n; i++)
  {
    int k = 0;
    for (int j = 0; j < n / 2; j++)
    {
      int sum = temp[i][j];
      int diff = temp[i][j + n / 2];
      output[i][k] = (sum + diff) / 2;
      output[i][k + 1] = (sum - diff) / 2;
      k += 2;
    }
  }

  return output;
}

#ifdef PYBIND11
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
PYBIND11_MODULE(dwt, m)
{
  m.def("dwt", &dwt, "A function which implements DWT.");
  m.def("idwt", &idwt, "A function which implements IDWT.");
}
#endif
