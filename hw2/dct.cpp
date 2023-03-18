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

img_t dct(img_t input, int n)
{
  img_t output = input;
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      // for each point, use the formula to calculate the D(i, j),
      // and store into output image
      double temp = 0.0;
      for (int x = 0; x < n; x++)
      {
        for (int y = 0; y < n; y++)
          temp += COS(x, i, n) * COS(y, j, n) * input[x][y];
      }
      temp *= (2.0 / n) * C(i) * C(j);

      // force the point value in 0~255
      //   if (temp < 0.0)
      //     temp = 0.0;
      //   else if (temp > 255.0)
      //     temp = 255.0;

      output[i][j] = std::round(temp);
    }
  }
  return output;
}

img_t idct(img_t input, int n)
{
  img_t output = input;
  for (int x = 0; x < n; x++)
  {
    for (int y = 0; y < n; y++)
    {
      // for each point, use the formula to calculate the f(x, y),
      // and store into output image
      double temp = 0.0;
      for (int i = 0; i < n; i++)
      {
        for (int j = 0; j < n; j++)
          temp += C(i) * C(j) * COS(x, i, n) * COS(y, j, n) * input[i][j];
      }

      temp *= (2.0 / n);

      // force the point value in 0~255
      if (temp < 0.0)
        temp = 0.0;
      else if (temp > 255.0)
        temp = 255.0;

      output[x][y] = std::round(temp);
    }
  }
  return output;
}

#ifdef PYBIND11
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
PYBIND11_MODULE(dct, m)
{
  m.def("dct", &dct, "A function which implements DCT.");
  m.def("idct", &idct, "A function which implements IDCT.");
}
#endif
