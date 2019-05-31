#include "../include/Sphere.h"

namespace rt
{
    bool Sphere::rayCast(const Ray& ray, float tMin, float tMax, HitRecord& rec) const
    {
        Vector3 oc = ray.getDirection() - _center;
        float a = Dot(ray.getDirection(), ray.getDirection());
        float b = Dot(oc, ray.getDirection());
        float c = Dot(oc, oc) - _radius * _radius;
        float dis = b * b - 4 * a * c;
        if (dis > 0)
        {
            float temp = (-b - sqrt(b * b - a * c)) / a;
            if (temp < tMax && temp > tMin)
            {
                rec.t = temp;
                rec.p = ray.rayCast(rec.t);
                rec.normal = (rec.p - _center) / _radius;
                return true;
            }

            temp = (-b + sqrt(b * b - a * c)) / a;
            if (temp < tMax && temp > tMin)
            {
                rec.t = temp;
                rec.p = ray.rayCast(rec.t);
                rec.normal = (rec.p - _center) / _radius;
                return true;
            }
        }
        
        return false;
    }
}