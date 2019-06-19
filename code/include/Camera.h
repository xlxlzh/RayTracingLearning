#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Ray.h"

#define RT_PI 3.14159265358979323846

namespace rt
{
    class Camera
    {
    public:
        Camera(Vector3 lookFrom, Vector3 lookAt, Vector3 up, float fov, float aspect)
        {
            float theta = fov * RT_PI / 180;
            float halfHeight = tan(theta / 2.0);
            float halfWidth = aspect * halfHeight;

            _origin = lookFrom;

            Vector3 u, v, w;
            w = MakeUnit(lookFrom - lookAt);
            u = MakeUnit(Cross(up, w));
            v = Cross(w, u);

            _leftCorner = _origin - halfWidth * u - halfHeight * v - w;

            _horizontal = 2.0 * halfWidth * u;
            _vertical = 2.0 * halfHeight * v;
        }

        Ray getRay(float u, float v) { return Ray(_origin, _leftCorner + u * _horizontal + v * _vertical - _origin); }

    public:
        Vector3 _origin;
        Vector3 _leftCorner;
        Vector3 _horizontal;
        Vector3 _vertical;
    };
}

#endif
