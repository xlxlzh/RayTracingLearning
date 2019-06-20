#ifndef _UTILITIES_H_
#define _UTILITIES_H_

#include <ctime>
#include <random>

#include "Vector3.h"

namespace rt
{
    Vector3 Reflect(const Vector3& v, const Vector3& n)
    {
        return v - 2.0 * Dot(v, n) * n;
    }

    bool Refract(const Vector3& v, const Vector3& n, float niOverNt, Vector3& refracted)
    {
        Vector3 uv = MakeUnit(v);
        float dt = Dot(uv, n);
        float discriminant = 1.0 - niOverNt * niOverNt * (1.0 - dt * dt);
        if (discriminant > 0)
        {
            refracted = niOverNt * (uv - n * dt) - n * sqrt(discriminant);
            return true;
        }
        else
        {
            return false;
        }
    }

    float Schlick(float cosine, float refIdx)
    {
        float r0 = (1.0 - refIdx) / (1.0 + refIdx);
        r0 = r0 * r0;
        return r0 + (1.0 - r0) * pow(1.0 - cosine, 5);
    }

    std::default_random_engine random(time(nullptr));

    float Random021()
    {
        std::uniform_real_distribution<double> dis(0.0, 1.0);
        return dis(random);
    }

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

    rt::Vector3 RandomInUnitDisk()
    {
        std::uniform_real_distribution<double> dis(0.0, 1.0);

        rt::Vector3 p;
        do
        {
            p = 2.0 * rt::Vector3(dis(random), dis(random), 0.0) - rt::Vector3(1.0, 1.0, 0.0);
        } while (Dot(p, p) >= 1.0);

        return p;
    }
}

#endif
