#ifndef _HITABLE_LIST_H_
#define _HITABLE_LIST_H_

#include "Hitable.h"

namespace rt
{
    class HitableList : public Hitable
    {
    public:
        HitableList() = default;
        HitableList(Hitable** l, int size) : _list(l), _size(size) { }

        virtual bool rayCast(const Ray& ray, float tMin, float tMax, HitRecord& rec) const override;

        Hitable** _list;
        int _size;
    };
}

#endif
