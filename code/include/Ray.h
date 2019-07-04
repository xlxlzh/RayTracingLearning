#ifndef _RAY_H_
#define _RAY_H_

#include "Vector3.h"

namespace rt
{
  class Ray
  {
  public:
    Ray() = default;
    Ray(const Vector3& origin, const Vector3& dir, float ti = 0.0) : _origin(origin), _dir(dir), _time(ti) { }

    Vector3 getOrigin() const { return _origin; }
    Vector3 getDirection() const { return _dir; }

    Vector3 rayCast(float t) const { return _origin + _dir * t; }

    float time() const { return _time; }

  public:
    Vector3 _origin;
    Vector3 _dir;

    float _time;
  };
}

#endif
