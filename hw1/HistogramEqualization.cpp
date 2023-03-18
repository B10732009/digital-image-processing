#include <cmath>
#include <iostream>
#include <vector>

#define PYBIND11

#ifdef PYBIND11
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#endif

typedef std::vector<std::vector<int>> img_t;

img_t histogramEqualization(img_t img, std::size_t height, std::size_t width)
{
  // input error, return empty image
  if (height <= 0 || width <= 0)
    return {{}};

  // build a pixel table
  std::vector<int> hist(256, 0);

  // count the probability distribution
  for (std::size_t i = 0; i < height; i++)
  {
    for (std::size_t j = 0; j < width; j++)
      hist[img[i][j]]++;
  }

  // transform to cumulative distribution
  for (std::size_t i = 0; i < hist.size() - 1; i++)
    hist[i + 1] += hist[i];

  // scale to 0~255
  for (std::size_t i = 0; i < hist.size(); i++)
    hist[i] = (int)std::round(hist[i] * 255 / (height * width));

  // set every pixel to new value
  for (std::size_t i = 0; i < height; i++)
  {
    for (std::size_t j = 0; j < width; j++)
      img[i][j] = hist[img[i][j]];
  }

  return img;
}

#ifdef PYBIND11
PYBIND11_MODULE(HistogramEqualization, m)
{
  m.def("histogramEqualization", &histogramEqualization, "A function which implements histogram equalization.");
}
#endif
