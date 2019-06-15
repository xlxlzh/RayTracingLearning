#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "Hitable.h"

namespace rt
{
    class Sphere : public Hitable
    {
    public:
        Sphere() = default;
        Sphere(const Vector3& c, float radius, Material* mat) : _center(c), _radius(radius), _material(mat) { }

        bool rayCast(const Ray& ray, float tMin, float tMax, HitRecord& rec) const override;

    private:
        Vector3 _center;
        float _radius;
        Material* _material;
    };
}

#endif
