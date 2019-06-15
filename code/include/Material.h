#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "Hitable.h"
#include "Utilities.h"

namespace rt
{
    class Material
    {
    public:
        virtual bool scatter(const Ray& rayIn, const HitRecord& rec, Vector3& attenuation, Ray& scattered) = 0;
    };

    class Lambertian : public Material
    {
    public:
        Lambertian(const Vector3& albedo) : _albedo(albedo) { }

        virtual bool scatter(const Ray& rayIn, const HitRecord& rec, Vector3& attenuation, Ray& scattered) override
        {
            Vector3 target = rec.p + rec.normal + RandomInUnitSphere();
            scattered = Ray(rec.p, target - rec.p);
            attenuation = _albedo;
            return true;
        }

        Vector3 _albedo;
    };

    class Metal : public Material
    {
    public:
        Metal(const Vector3& albedo, float f) : _albedo(albedo)
        { 
            _fuzz = f < 1.0 ? f : 1.0;
        }

        virtual bool scatter(const Ray& rayIn, const HitRecord& rec, Vector3& attenuation, Ray& scattered) override
        {
            Vector3 reflected = Reflect(MakeUnit(rayIn.getDirection()), rec.normal);
            scattered = Ray(rec.p, reflected + _fuzz * RandomInUnitSphere());
            attenuation = _albedo;
            return Dot(scattered.getDirection(), rec.normal) > 0;
        }

        Vector3 _albedo;
        float _fuzz;
    };
}

#endif
