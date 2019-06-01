#include "../include/HitableList.h"

namespace rt
{
    bool HitableList::rayCast(const Ray& ray, float tMin, float tMax, HitRecord& rec) const
    {
        HitRecord tmpRec;
        bool hitAnything = false;
        double closest = tMax;

        for (int i = 0; i < _size; i++)
        {
            if (_list[i]->rayCast(ray, tMin, closest, tmpRec))
            {
                hitAnything = true;
                closest = tmpRec.t;
                rec = tmpRec;
            }
        }

        return hitAnything;
    }
}