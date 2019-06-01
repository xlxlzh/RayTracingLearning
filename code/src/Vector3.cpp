#include "../include/Vector3.h"

namespace rt
{
    Vector3& Vector3::operator+=(const Vector3& rhs)
    {
        _x += rhs._x;
        _y += rhs._y;
        _z += rhs._z;

        return *this;
    }

    Vector3& Vector3::operator-=(const Vector3 & rhs)
    {
        _x -= rhs._x;
        _y -= rhs._y;
        _z -= rhs._z;

        return *this;
    }

    Vector3& Vector3::operator*=(const Vector3 & rhs)
    {
        _x *= rhs._x;
        _y *= rhs._y;
        _z *= rhs._z;

        return *this;
    }

    Vector3& Vector3::operator/=(const Vector3 & rhs)
    {
        _x /= rhs._x;
        _y /= rhs._y;
        _z /= rhs._z;

        return *this;
    }

    Vector3& Vector3::operator*=(const float t)
    {
        _x *= t;
        _y *= t;
        _z *= t;

        return *this;
    }

    Vector3& Vector3::operator/=(const float t)
    {
        _x /= t;
        _y /= t;
        _z /= t;

        return *this;
    }

    Vector3 Vector3::operator + (const Vector3 & rhs) const
    {
        return Vector3(_x + rhs._x, _y + rhs._y, _z + rhs._z);
    }

    Vector3 Vector3::operator + (const float t) const
    {
        return Vector3(_x + t, _y + t, _z + t);
    }

    Vector3 Vector3::operator - (const Vector3 & rhs) const
    {
        return Vector3(_x - rhs._x, _y - rhs._y, _z - rhs._z);
    }

    Vector3 Vector3::operator * (const Vector3 & rhs) const
    {
        return Vector3(_x * rhs._x, _y * rhs._y, _z * rhs._z);
    }

    Vector3 Vector3::operator * (const float t) const
    {
        return Vector3(_x * t, _y * t, _z * t);
    }

    Vector3 Vector3::operator / (const Vector3 & rhs) const
    {
        return Vector3(_x / rhs._x, _y / rhs._y, _z / rhs._z);
    }

    Vector3 Vector3::operator/(const float t) const
    {
        return Vector3(_x / t, _y / t, _z / t);
    }

    Vector3& Vector3::normalize()
    {
        *this /= length();
        return *this;
    }
}