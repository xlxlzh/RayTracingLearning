#include <iostream>
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "include/stb/stb_image_write.h"
#include "include/Ray.h"

using namespace rt;

rt::Vector3 Color(const rt::Ray& ray)
{
  rt::Vector3 dir = rt::makeUnit(ray.getDirection());
  float t = 0.5 * (dir._y + 1.0);
  return (1.0 - t) * rt::Vector3(1.0, 1.0, 1.0) + t * rt::Vector3(0.5, 0.7, 1.0);
}

unsigned makeColor(const rt::Vector3& col)
{
  unsigned r = col._x * 255;
  unsigned g = col._y * 255;
  unsigned b = col._z * 255;
  unsigned a = 255;

  g = g << 8;
  b = b << 16;
  a = a << 24;

  return r | g | b | a;
}

int main()
{
  int width = 200;
  int height = 100;

  unsigned images[200][100] = { 0 };

  rt::Vector3 leftCorner(-2.0, -1.0, -1.0);
  rt::Vector3 horizontal(4.0, 0.0, 0.0);
  rt::Vector3 vertical(0.0, 2.0, 0.0);
  rt::Vector3 origin(0.0, 0.0, 0.0);

  for (int j = height - 1; j >= 0; --j)
  {
    for (int i = 0; i < width; ++i)
    {
      float u = float(i) / float(width);
      float v = float(j) / float(height);

      rt::Ray ray(origin, leftCorner + u * horizontal + v * vertical);
      rt::Vector3 col = Color(ray);
      images[i][j] = makeColor(col);
    }
  }

  stbi_write_png("test.png", width, height, 4, images, width * 4);
}