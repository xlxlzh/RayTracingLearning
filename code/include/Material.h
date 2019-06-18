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

    class Dielectric : public Material
    {
    public:
        Dielectric(float ri) : _refIndex(ri) { }

        virtual bool scatter(const Ray& rayIn, const HitRecord& rec, Vector3& attenuation, Ray& scattered) override
        {
            Vector3 outwardNormal;
            Vector3 reflected = Reflect(rayIn.getDirection(), rec.normal);
            float niOverHt = 0.0f;
            attenuation = Vector3(1.0, 1.0, 1.0);

            float reflectProb;
            float cosine;
            Vector3 refracted;
            if (Dot(rayIn.getDirection(), rec.normal) > 0)
            {
                outwardNormal = -rec.normal;
                niOverHt = _refIndex;
                cosine = _refIndex * Dot(rayIn.getDirection(), rec.normal) / rayIn.getDirection().length();
            }
            else
            {
                outwardNormal = rec.normal;
                niOverHt = 1.0 / _refIndex;
                cosine = -Dot(rayIn.getDirection(), rec.normal) / rayIn.getDirection().length();
            }

            if (Refract(rayIn.getDirection(), outwardNormal, niOverHt, refracted))
            {
                reflectProb = Schlick(cosine, _refIndex);
            }
            else
            {
                scattered = Ray(rec.p, reflected);
                reflectProb = 1.0;
            }

            if (Random021() < reflectProb)
            {
                scattered = Ray(rec.p, reflected);
            }
            else
            {
                scattered = Ray(rec.p, refracted);
            }

            return true;
        }

        float _refIndex;
    };
}

#endif
