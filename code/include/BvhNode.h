#ifndef _BVHNODE_H_
#define _BVHNODE_H_

#include "Hitable.h"
#include "AABB.h"

namespace rt
{
    class BvhNode : public Hitable
    {
    public:
        BvhNode() = default;

        BvhNode(Hitable** l, int n, float t0, float t1);

        virtual bool rayCast(const Ray& ray, float tMin, float tMax, HitRecord& rec) const override;
        virtual bool boundingBox(float t0, float t1, AABB& box) override;

        Hitable* _left;
        Hitable* _right;
        AABB _box;
    };
}

#endif
