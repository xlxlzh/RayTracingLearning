#include <algorithm>
#include "../include/AABB.h"
#include "../include/Ray.h"

namespace rt
{
    bool AABB::hit(const Ray& ray, float tmin, float tmax) const
    {
        for (int i = 0; i < 3; i++)
        {
            float invD = 1.0f / ray.getDirection()[i];
            float t0 = (_min[i] - ray.getOrigin()[i]) * invD;
            float t1 = (_max[i] - ray.getOrigin()[i]) * invD;

            if (invD < 0.0f)
            {
                std::swap(t0, t1);
            }

            tmin = t0 > tmin ? t0 : tmin;
            tmax = t1 < tmax ? t1 : tmax;

            if (tmax <= tmin)
                return false;

        }

        return true;
    }
}