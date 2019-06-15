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
}

#endif
