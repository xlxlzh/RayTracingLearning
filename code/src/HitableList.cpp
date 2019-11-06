#include "../include/HitableList.h"
#include "../include/AABB.h"

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

    bool HitableList::boundingBox(float t0, float t1, AABB& box)
    {
        if (_size < 1)
        {
            return false;
        }

        AABB tmpBox;
        bool bRet = _list[0]->boundingBox(t0, t1, tmpBox);
        if (!bRet)
        {
            return false;
        }
        else
        {
            box = tmpBox;
        }

        for (int i = 0; i < _size; ++i)
        {
            if (_list[i]->boundingBox(t0, t1, tmpBox))
            {
                box = SurroundingBox(tmpBox, box);
            }
            else
            {
                return false;
            }
        }

        return true;
    }
}