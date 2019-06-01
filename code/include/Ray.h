#ifndef _RAY_H_
#define _RAY_H_

#include "Vector3.h"

namespace rt
{
  class Ray
  {
  public:
    Ray() = default;
    Ray(const Vector3& origin, const Vector3& dir) : _origin(origin), _dir(dir) { }

    Vector3 getOrigin() const { return _origin; }
    Vector3 getDirection() const { return _dir; }

    Vector3 rayCast(float t) const { return _origin + _dir * t; }

  public:
    Vector3 _origin;
    Vector3 _dir;
  };
}

#endif
