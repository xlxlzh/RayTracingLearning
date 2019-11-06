#ifndef _AABB_H_
#define _AABB_H_

#include "Vector3.h"

namespace rt
{
    inline float ffmin(float a, float b) { return a < b ? a : b; }
    inline float ffmax(float a, float b) { return a > b ? a : b; }

    class Ray;

    class AABB
    {
    public:
        AABB() = default;

        AABB(const Vector3& a, const Vector3& b) : _min(a), _max(b) { }

        Vector3 min() const { return _min; }
        Vector3 max() const { return _max; }

        bool hit(const Ray& ray, float tmin, float tmax) const;

    private:
        Vector3 _min;
        Vector3 _max;
    };

    static AABB SurroundingBox(AABB box0, AABB box1)
    {
        Vector3 small(ffmin(box0.min()._x, box1.min()._x),
            ffmin(box0.min()._y, box1.min()._y),
            ffmin(box0.min()._z, box1.min()._z));

        Vector3 big(ffmax(box0.min()._x, box1.min()._x),
            ffmax(box0.min()._y, box1.min()._y),
            ffmax(box0.min()._z, box1.min()._z));

        return AABB(small, big);
    }
}


#endif
