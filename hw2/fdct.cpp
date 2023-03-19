#include <cmath>
#include <ctime>
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
inline double C(int i, int j, int n)
{
  return (i == 0 ? std::sqrt(1.0 / n) : (std::sqrt(2.0 / n) * COS(j, i, n)));
}

// support function
inline double CT(int i, int j, int n)
{
  return C(j, i, n);
}

img_t fdct(img_t input, int n)
{
  std::clock_t start, end;
  start = std::clock();

  img_t output = input;
  std::vector<std::vector<double>> temp(n, std::vector<double>(n));

  // implement input * Ct
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      temp[i][j] = 0.0;
      for (int k = 0; k < n; k++)
        temp[i][j] += input[i][k] * CT(k, j, n);
    }
  }

  // implement C * (input * Ct)
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      double temp2 = 0.0;
      for (int k = 0; k < n; k++)
        temp2 += C(i, k, n) * temp[k][j];
      output[i][j] = (int)std::round(temp2);
    }
  }

  end = std::clock();
  std::cout << "finishing FDCT of " << n << "*" << n << " image in " << (double)(end - start) / CLOCKS_PER_SEC
            << " second(s).\n";
  return output;
}

img_t fidct(img_t input, int n)
{
  std::clock_t start, end;
  start = std::clock();

  img_t output = input;
  std::vector<std::vector<double>> temp(n, std::vector<double>(n));

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      temp[i][j] = 0.0;
      for (int k = 0; k < n; k++)
        temp[i][j] += input[i][k] * C(k, j, n);
    }
  }

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      double temp2 = 0.0;
      for (int k = 0; k < n; k++)
        temp2 += CT(i, k, n) * temp[k][j];

      // force the point value in 0~255
      if (temp2 < 0.0)
        temp2 = 0.0;
      else if (temp2 > 255.0)
        temp2 = 255.0;

      output[i][j] = (int)std::round(temp2);
    }
  }

  end = std::clock();
  std::cout << "finishing FIDCT of " << n << "*" << n << " image in " << (double)(end - start) / CLOCKS_PER_SEC
            << " second(s).\n";
  return output;
}

#ifdef PYBIND11
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
PYBIND11_MODULE(fdct, m)
{
  m.def("fdct", &fdct, "A function which implements FDCT.");
  m.def("fidct", &fidct, "A function which implements FIDCT.");
}
#endif
