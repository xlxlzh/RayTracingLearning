#include "MovingSphere.h"

namespace rt
{
    Vector3 MovingSphere::center(float time) const
    {
        return _center0 + ((time - _t0) / (_t1 - _t0)) * (_center1 - _center0);
    }

    bool MovingSphere::rayCast(const Ray& ray, float tMin, float tMax, HitRecord& rec) const
    {
        Vector3 oc = ray.getOrigin() - center(ray.time());
        float a = Dot(ray.getDirection(), ray.getDirection());
        float b = Dot(oc, ray.getDirection());
        float c = Dot(oc, oc) - _radius * _radius;
        float dis = b * b - a * c;
        if (dis > 0)
        {
            float temp = (-b - sqrt(b * b - a * c)) / a;
            if (temp < tMax && temp > tMin)
            {
                rec.t = temp;
                rec.p = ray.rayCast(rec.t);
                rec.normal = (rec.p - center(ray.time())) / _radius;
                rec.mat = _material;
                return true;
            }

            temp = (-b + sqrt(b * b - a * c)) / a;
            if (temp < tMax && temp > tMin)
            {
                rec.t = temp;
                rec.p = ray.rayCast(rec.t);
                rec.normal = (rec.p - center(ray.time())) / _radius;
                rec.mat = _material;
                return true;
            }
        }

        return false;
    }
}