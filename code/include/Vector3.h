#ifndef _VECTOR3_H_
#define _VECTOR3_H_

#include <cmath>

namespace rt
{
    class Vector3
    {
    public:

        Vector3() = default;

        Vector3(float x, float y, float z) : _x(x), _y(y), _z(z) { }

        float x() const { return _x; }
        float y() const { return _y; }
        float z() const { return _z; }
        float r() const { return _x; }
        float g() const { return _y; }
        float b() const { return _z; }

        const Vector3& operator + () const { return *this; }
        Vector3 operator - () const { return Vector3(-_x, -_y, -_z); }
        float operator [] (int index) const { return values[index]; }
        float& operator [] (int index) { return values[index]; }

        Vector3& operator += (const Vector3& rhs);
        Vector3& operator -= (const Vector3& rhs);
        Vector3& operator *= (const Vector3& rhs);
        Vector3& operator /= (const Vector3& rhs);
        Vector3& operator *= (const float t);
        Vector3& operator /= (const float t);

        Vector3 operator + (const Vector3& rhs) const;
        Vector3 operator + (const float t) const;
        Vector3 operator - (const Vector3& rhs) const;
        Vector3 operator * (const Vector3& rhs) const;
        Vector3 operator * (const float t) const;
        Vector3 operator / (const Vector3& rhs) const;
        Vector3 operator / (const float t) const;

        float length() const { return sqrt(_x * _x + _y * _y + _z * _z); }
        float squaredLength() const { return _x * _x + _y * _y + _z * _z; }
        Vector3& normalize();

        union
        {
            struct
            {
                float _x;
                float _y;
                float _z;
            };

            float values[3];
        };
    };

    inline Vector3 operator * (const float t, const Vector3& rhs)
    {
        return Vector3(t * rhs._x, t * rhs._y, t * rhs._z);
    }

    inline float Dot(const Vector3& lhs, const Vector3& rhs)
    {
        return lhs._x * rhs._x + lhs._y * rhs._y + lhs._z * rhs._z;
    }

    inline Vector3 Cross(const Vector3& lhs, const Vector3& rhs)
    {
        return Vector3(lhs._y * rhs._z - lhs._z * rhs._y,
            lhs._z * rhs._x - lhs._x * rhs._z,
            lhs._x * rhs._y - lhs._y * rhs._x);
    }

    inline Vector3 MakeUnit(const Vector3& vec)
    {
        return vec / vec.length();
    }
}

#endif