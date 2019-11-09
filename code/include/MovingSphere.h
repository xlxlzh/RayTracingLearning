#ifndef _MOVINGSPHERE_H_
#define _MOVINGSPHERE_H_

#include "Hitable.h"

namespace rt
{
    class MovingSphere : public Hitable
    {
    public:
        MovingSphere() = default;
        MovingSphere(const Vector3& c0, const Vector3& c1, float t0, float t1, float radius, Material* mat) : _center0(c0), _center1(c1), _t0(t0), _t1(t1), _radius(radius), _material(mat) { }

        bool rayCast(const Ray& ray, float tMin, float tMax, HitRecord& rec) const override;

        Vector3 center(float time) const;

    private:
        Vector3 _center0;
        Vector3 _center1;

        float _radius;
        float _t0, _t1;

        Material* _material;
    };
}

#endif
