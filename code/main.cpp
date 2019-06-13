#include <iostream>
#include <fstream>
#include <cfloat>
#include <random>
#include <ctime>
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "include/stb/stb_image_write.h"
#include "include/Ray.h"
#include "include/HitableList.h"
#include "include/Sphere.h"
#include "include/Camera.h"

const int WIDTH = 400;
const int HEIGHT = 200;

std::default_random_engine random(time(nullptr));

rt::Vector3 RandomInUnitSphere()
{
    std::uniform_real_distribution<double> dis(0.0, 1.0);

    rt::Vector3 p;
    do
    {
        p = 2.0 * rt::Vector3(dis(random), dis(random), dis(random)) - rt::Vector3(1.0, 1.0, 1.0);
    } while (p.squaredLength() >= 1.0);

    return p;
}

rt::Vector3 Color(const rt::Ray& ray, const rt::Hitable* world)
{
    rt::HitRecord rec;
    if (world->rayCast(ray, 0.001, FLT_MAX, rec))
    {
        rt::Vector3 target = rec.p + rec.normal + RandomInUnitSphere();
        return 0.5 * Color(rt::Ray(rec.p, target - rec.p), world);
    }
    else
    {
        rt::Vector3 dir = rt::MakeUnit(ray.getDirection());
        float t = 0.5 * (dir._y + 1.0);
        return (1.0 - t) * rt::Vector3(1.0, 1.0, 1.0) + t * rt::Vector3(0.5, 0.7, 1.0);
    }
}

rt::Vector3 GammaCorrection(const rt::Vector3 col)
{
    return rt::Vector3(sqrt(col.r()), sqrt(col.g()), sqrt(col.b()));
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

    rt::Hitable* list[2] = { nullptr };
    list[0] = new rt::Sphere(rt::Vector3(0.0, 0.0, -1.0), 0.5);
    list[1] = new rt::Sphere(rt::Vector3(0.0, -100.5, -1.0), 100);

    rt::Hitable* world = new rt::HitableList(list, 2);
    rt::Camera mainCamera;

    std::uniform_real_distribution<double> dis(0.0, 1.0);
    int sampleCount = 100;
    for (int j = HEIGHT - 1; j >= 0; --j)
    {
        for (int i = 0; i < WIDTH; ++i)
        {
            rt::Vector3 col(0.0, 0.0, 0.);
            for (int s = 0; s < sampleCount; ++s)
            {
                float u = float(i + dis(random)) / float(WIDTH);
                float v = float(j + dis(random)) / float(HEIGHT);
                rt::Ray ray = mainCamera.getRay(u, v);
                col += Color(ray, world);
            }

            col /= float(sampleCount);
            col = GammaCorrection(col);
            col *= 255;

            int rowIndex = HEIGHT - 1 - j;
            images[rowIndex][i * 4] = int(col.r());
            images[rowIndex][i * 4 + 1] = int(col.g());
            images[rowIndex][i * 4 + 2] = int(col.b());
            images[rowIndex][i * 4 + 3] = 255;
            imageOutput << int(col._x) << " " << int(col._y) << " " << int(col._z) << "\n";
        }
    }

    imageOutput.close();
    stbi_write_png("image.png", WIDTH, HEIGHT, 4, images, 0);

    return 0;
}