#include <iostream>
#include "../include/BvhNode.h"
#include "../include/Utilities.h"

namespace rt
{
    int BoxXCompare(const void* a, const void* b)
    {
        AABB boxLeft, boxRight;
        Hitable* ah = *(Hitable**)a;
        Hitable* bh = *(Hitable**)b;

        if (!ah->boundingBox(0, 0, boxLeft) || !bh->boundingBox(0, 0, boxRight))
            std::cerr << "error \n";

        if (boxLeft.min()._x - boxRight.min()._x < 0.0)
        {
            return -1;
        }
        else
        {
            return 1;
        }
    }

    int BoxYCompare(const void* a, const void* b)
    {
        AABB boxLeft, boxRight;
        Hitable* ah = *(Hitable**)a;
        Hitable* bh = *(Hitable**)b;

        if (!ah->boundingBox(0, 0, boxLeft) || !bh->boundingBox(0, 0, boxRight))
            std::cerr << "error \n";

        if (boxLeft.min()._y - boxRight.min()._y < 0.0)
        {
            return -1;
        }
        else
        {
            return 1;
        }
    }

    int BoxZCompare(const void* a, const void* b)
    {
        AABB boxLeft, boxRight;
        Hitable* ah = *(Hitable**)a;
        Hitable* bh = *(Hitable**)b;

        if (!ah->boundingBox(0, 0, boxLeft) || !bh->boundingBox(0, 0, boxRight))
            std::cerr << "error \n";

        if (boxLeft.min()._z - boxRight.min()._z < 0.0)
        {
            return -1;
        }
        else
        {
            return 1;
        }
    }
    
    BvhNode::BvhNode(Hitable** l, int n, float t0, float t1)
    {
        int axis = static_cast<int>(Random021() * 3.0f);
        if (axis == 0)
        {
            qsort(l, n, sizeof(Hitable*), BoxXCompare);
        }
        else if (axis == 1)
        {
            qsort(l, n, sizeof(Hitable*), BoxYCompare);
        }
        else
        {
            qsort(l, n, sizeof(Hitable*), BoxZCompare);
        }

        if (n == 1)
        {
            _left = _right = l[0];
        }
        else if (n == 2)
        {
            _left = l[0];
            _right = l[1];
        }
        else
        {
            _left = new BvhNode(l, n / 2, t0, t1);
            _right = new BvhNode(l + n / 2, n - n / 2, t0, t1);
        }

        AABB boxLeft, boxRight;
        if (!_left->boundingBox(t0, t1, boxLeft) || !_right->boundingBox(t0, t1, boxRight))
            std::cerr << "error \n";

        _box = SurroundingBox(boxLeft, boxRight);
    }

    bool BvhNode::rayCast(const Ray& ray, float tMin, float tMax, HitRecord& rec) const
    {
        if (_box.hit(ray, tMin, tMax))
        {
            HitRecord leftRec, rightRec;
            bool hitLeft = _left->rayCast(ray, tMin, tMax, leftRec);
            bool hitRight = _right->rayCast(ray, tMin, tMax, rightRec);

            if (hitLeft && hitRight)
            {
                if (leftRec.t < rightRec.t)
                {
                    rec = leftRec;
                }
                else
                {
                    rec = rightRec;
                }

                return true;
            }
            else if (hitLeft)
            {
                rec = leftRec;
                return true;
            }
            else if (hitRight)
            {
                rec = rightRec;
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }

    bool BvhNode::boundingBox(float t0, float t1, AABB& box)
    {
        box = _box;
        return true;
    }
}