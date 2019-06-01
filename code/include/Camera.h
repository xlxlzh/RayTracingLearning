#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Ray.h"

namespace rt
{
    class Camera
    {
    public:
        Camera()
        {
            _leftCorner = Vector3(-2.0, -1.0, -1.0);
            _horizontal = Vector3(4.0, 0.0, 0.0);
            _vertical = Vector3(0.0, 2.0, 0.0);
            _origin = Vector3(0.0, 0.0, 0.0);
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
