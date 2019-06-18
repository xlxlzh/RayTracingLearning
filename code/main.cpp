#include <iostream>
#include <fstream>
#include <cfloat>
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "include/stb/stb_image_write.h"
#include "include/Ray.h"
#include "include/HitableList.h"
#include "include/Sphere.h"
#include "include/Camera.h"
#include "include/Utilities.h"
#include "include/Material.h"

using namespace rt;

const int WIDTH = 400;
const int HEIGHT = 200;


Vector3 Color(const Ray& ray, const Hitable* world, int depth)
{
    HitRecord rec;
    if (world->rayCast(ray, 0.001, FLT_MAX, rec))
    {
        Ray scattered;
        Vector3 attenuation;
        if (depth < 50 && rec.mat->scatter(ray, rec, attenuation, scattered))
        {
            return attenuation * Color(scattered, world, depth + 1);
        }
        else
        {
            return Vector3(0.0, 0.0, 0.0);
        }
    }
    else
    {
        Vector3 dir = MakeUnit(ray.getDirection());
        float t = 0.5 * (dir._y + 1.0);
        return (1.0 - t) * Vector3(1.0, 1.0, 1.0) + t * Vector3(0.5, 0.7, 1.0);
    }
}

Vector3 GammaCorrection(const Vector3 col)
{
    return Vector3(sqrt(col.r()), sqrt(col.g()), sqrt(col.b()));
}

int main()
{
    unsigned char images[HEIGHT][WIDTH * 4] = { 0 };

    Vector3 leftCorner(-2.0, -1.0, -1.0);
    Vector3 horizontal(4.0, 0.0, 0.0);
    Vector3 vertical(0.0, 2.0, 0.0);
    Vector3 origin(0.0, 0.0, 0.0);

    std::ofstream imageOutput;
    imageOutput.open("image_debug.ppm");
    imageOutput << "P3\n" << WIDTH << " " << HEIGHT << "\n255\n";

    Hitable* list[5] = { nullptr };
    list[0] = new Sphere(Vector3(0.0, 0.0, -1.0), 0.5, new Lambertian(Vector3(0.1, 0.2, 0.5)));
    list[1] = new Sphere(Vector3(0.0, -100.5, -1.0), 100, new Lambertian(Vector3(0.8, 0.8, 0.0)));
    list[2] = new Sphere(Vector3(1.0, 0.0, -1.0), 0.5, new Metal(Vector3(0.8, 0.6, 0.2), 0.3));
    list[3] = new Sphere(Vector3(-1.0, 0.0, -1.0), 0.5, new Dielectric(1.5));
    list[4] = new Sphere(Vector3(-1.0, 0.0, -1.0), -0.45, new Dielectric(1.5));

    Hitable* world = new HitableList(list, 5);
    Camera mainCamera;

    std::uniform_real_distribution<double> dis(0.0, 1.0);
    int sampleCount = 100;
    for (int j = HEIGHT - 1; j >= 0; --j)
    {
        for (int i = 0; i < WIDTH; ++i)
        {
            Vector3 col(0.0, 0.0, 0.);
            for (int s = 0; s < sampleCount; ++s)
            {
                float u = float(i + dis(random)) / float(WIDTH);
                float v = float(j + dis(random)) / float(HEIGHT);
                Ray ray = mainCamera.getRay(u, v);
                col += Color(ray, world, 0);
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