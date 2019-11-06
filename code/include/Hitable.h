#ifndef _HITABLE_H_
#define _HITABLE_H_

#include "Ray.h"

namespace rt
{
    class Material;
    class AABB;

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
        virtual bool boundingBox(float t0, float t1, AABB& box) = 0;
    };
}

#endif
