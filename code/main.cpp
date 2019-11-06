#include <iostream>
#include <fstream>
#include <cfloat>
#include <thread>
#include <memory>
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "include/stb/stb_image_write.h"
#include "include/Ray.h"
#include "include/HitableList.h"
#include "include/Sphere.h"
#include "include/Camera.h"
#include "include/Utilities.h"
#include "include/Material.h"
#include "include/Texture.h"
#include "include/BvhNode.h"

using namespace rt;

const int WIDTH = 4096;
const int HEIGHT = 2160;


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

Hitable* RandomScene()
{
    int n = 500;
    Hitable** list = new Hitable*[n + 1];
    list[0] = new Sphere(Vector3(0.0, -1000.0, 0.0), 1000.0,
        new Lambertian(new CheckerTexture(new ConstTexture(Vector3(0.2, 0.3, 0.1)), new ConstTexture(Vector3(0.9, 0.9, 0.9)))));
    int i = 1;
    for (int a = -11; a < 11; ++a)
    {
        for (int b = -11; b < 11; ++b)
        {
            float chooseMat = Random021();
            Vector3 center(a + 0.9 * Random021(), 0.2, b + 0.9 * Random021());
            if ((center - Vector3(4.0, 0.2, 0.0)).length() > 0.9)
            {
                if (chooseMat < 0.8)
                {
                    list[i++] = new Sphere(center, 0.2, new Lambertian(new ConstTexture(Vector3(Random021() * Random021(), Random021() * Random021(), Random021() * Random021()))));
                }
                else if (chooseMat < 0.95)
                {
                    list[i++] = new Sphere(center, 0.2, new Metal(Vector3(0.5 * (1.0 + Random021()), 0.5 * (1.0 + Random021()), 0.5 * (1.0 + Random021())), 0.5 * Random021()));
                }
                else
                {
                    list[i++] = new Sphere(center, 0.2, new Dielectric(1.5));
                }
            }
        }
    }

    list[i++] = new Sphere(Vector3(0.0, 1.0, 0.0), 1.0, new Dielectric(1.5));
    list[i++] = new Sphere(Vector3(-4.0, 1.0, 0.0), 1.0, new Lambertian(new ConstTexture(Vector3(0.4, 0.2, 0.1))));
    list[i++] = new Sphere(Vector3(4.0, 1.0, 0.0), 1.0, new Metal(Vector3(0.7, 0.6, 0.5), 0.0));

    return new BvhNode(list, i, 0.0, 1.0);
}

unsigned char images[HEIGHT][WIDTH * 4] = { 0 };
int sampleCount = 100;

void RendererPatch(int from, int to, Camera& mainCamera, Hitable* world)
{
    for (int j = from; j >= to; --j)
    {
        for (int i = 0; i < WIDTH; ++i)
        {
            Vector3 col(0.0, 0.0, 0.);
            for (int s = 0; s < sampleCount; ++s)
            {
                float u = float(i + Random021()) / float(WIDTH);
                float v = float(j + Random021()) / float(HEIGHT);
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
        }
    }
}

const int MAX_THREAD = 12;

using ThreadPtr = std::shared_ptr<std::thread>;

int main()
{
    Hitable* world = RandomScene();

    Vector3 lookFrom(13.0, 2.0, 3.0);
    Vector3 lookAt(0.0, 0.0, 0.0);
    float distFocus = 10.0;
    float aperture = 0.1;

    Camera mainCamera(lookFrom, lookAt, Vector3(0.0, 1.0, 0.0), 20.0, (float)WIDTH / (float)HEIGHT, aperture, distFocus, 0.0, 1.0);

    std::vector<ThreadPtr> threadArr;

    int heightPreThread = HEIGHT / MAX_THREAD;
    for (int i = 0; i < MAX_THREAD; ++i)
    {
        ThreadPtr ptr = ThreadPtr(new std::thread(RendererPatch, heightPreThread * (i + 1) - 1, heightPreThread * i, mainCamera, world));
        threadArr.push_back(ptr);
    }

    for (auto patch : threadArr)
    {
        patch->join();
    }

    stbi_write_png("image.png", WIDTH, HEIGHT, 4, images, 0);

    system("pause");

    return 0;
}