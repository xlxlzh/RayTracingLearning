#include <iostream>
#include <fstream>
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "include/stb/stb_image_write.h"
#include "include/Ray.h"

const int WIDTH = 400;
const int HEIGHT = 200;

float HitSphere(const rt::Vector3& center, float radius, const rt::Ray& ray)
{
  rt::Vector3 oc = ray.getOrigin() - center;
  float a = rt::Dot(ray.getDirection(), ray.getDirection());
  float b = 2.0 * rt::Dot(oc, ray.getDirection());
  float c = rt::Dot(oc, oc) - radius * radius;
  float d = b * b - 4 * a * c;

  if (d < 0)
  {
    return -1.0;
  }
  else
  {
    return (-b - sqrt(d)) / (2.0 * a);
  }
}

rt::Vector3 Color(const rt::Ray& ray)
{
  float value = HitSphere(rt::Vector3(0.0, 0.0, -1.0), 0.5, ray);
  if (value > 0.0)
  {
    rt::Vector3 normal = rt::MakeUnit(ray.rayCast(value) - rt::Vector3(0.0, 0.0, -1.0));
    return 0.5 * (normal + 1.0);
  }

  rt::Vector3 dir = rt::MakeUnit(ray.getDirection());
  float t = 0.5 * (dir._y + 1.0);
  return (1.0 - t) * rt::Vector3(1.0, 1.0, 1.0) + t * rt::Vector3(0.5, 0.7, 1.0);
}

int main()
{
  unsigned char images[HEIGHT][WIDTH * 4] = { 0 };
  
  rt::Vector3 leftCorner(-2.0, -1.0, -1.0);
  rt::Vector3 horizontal(4.0, 0.0, 0.0);
  rt::Vector3 vertical(0.0, 2.0, 0.0);
  rt::Vector3 origin(0.0, 0.0, 0.0);

  std::ofstream imageOutput;
  imageOutput.open("image_debug.ppm");
  imageOutput << "P3\n" << WIDTH << " " << HEIGHT << "\n255\n";
  
  for (int j = HEIGHT - 1; j >= 0; --j)
  {
    for (int i = 0; i < WIDTH; ++i)
    {
      float u = float(i) / float(WIDTH);
      float v = float(j) / float(HEIGHT);
  
      rt::Ray ray(origin, leftCorner + u * horizontal + v * vertical);
      rt::Vector3 col = Color(ray);

      int rowIndex = HEIGHT - 1 - j;
      images[rowIndex][i * 4] = int(col.r() * 255);
      images[rowIndex][i * 4 + 1] = int(col.g() * 255);
      images[rowIndex][i * 4 + 2] = int(col.b() * 255);
      images[rowIndex][i * 4 + 3] = 255;
      imageOutput << int(255.99 * col._x) << " " << int(255.99 * col._y) << " " << int(255.99 * col._z) << "\n";
    }
  }

  imageOutput.close();
  stbi_write_png("image.png", WIDTH, HEIGHT, 4, images, 0);

  return 0;
}