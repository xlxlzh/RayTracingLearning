#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "Vector3.h"
#include "Perlin.h"

namespace rt
{
    class Texture
    {
    public:
        virtual Vector3 value(float u, float v, const Vector3& p) const = 0;
    };


    class ConstTexture : public Texture
    {
    public:
        ConstTexture() = default;

        ConstTexture(Vector3 c) : _color(c) { }

        virtual Vector3 value(float u, float v, const Vector3& p) const override
        {
            return _color;
        }

    public:
        Vector3 _color;
    };

    class CheckerTexture : public Texture
    {
    public:
        CheckerTexture() = default;

        CheckerTexture(Texture* t0, Texture* t1) : _odd(t0), _even(t1) { }

        virtual Vector3 value(float u, float v, const Vector3& p) const override
        {
            float sines = sin(10.0f * p._x) * sin(10.0f * p._y) * sin(10.0f * p._z);
            if (sines < 0.0)
            {
                return _odd->value(u, v, p);
            }
            else
            {
                return _even->value(u, v, p);
            }
        }

    public:
        Texture* _odd;
        Texture* _even;
    };

    class NoiseTexture : public Texture
    {
    public:
        NoiseTexture() = default;

        virtual Vector3 value(float u, float v, const Vector3& p) const override
        {
            return Vector3(1.0f, 1.0f, 1.0f) * _noise.noise(p);
        }

    public:
        Perlin _noise;
    };
}

#endif
