#ifndef _HITABLE_H_
#define _HITABLE_H_

#include "Ray.h"

namespace rt
{
    class Material;

    struct HitRecord
    {
        float t;
        Vector3 p;
        Vector3 normal;
        Material* mat;
    };

    class Hitable
    {
    public:
        virtual bool rayCast(const Ray& ray, float tMin, float tMax, HitRecord& rec) const = 0;
    };
}

#endif
