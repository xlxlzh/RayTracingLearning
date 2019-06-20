#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Ray.h"
#include "Utilities.h"

#define RT_PI 3.14159265358979323846

namespace rt
{
    class Camera
    {
    public:
        Camera(Vector3 lookFrom, Vector3 lookAt, Vector3 up, float fov, float aspect, float aperture, float focusDist)
        {
            _lensRadius = aperture / 2.0;
            float theta = fov * RT_PI / 180;
            float halfHeight = tan(theta / 2.0);
            float halfWidth = aspect * halfHeight;

            _origin = lookFrom;

            _w = MakeUnit(lookFrom - lookAt);
            _u = MakeUnit(Cross(up, _w));
            _v = Cross(_w, _u);

            _leftCorner = _origin - halfWidth * _u * focusDist - halfHeight * _v * focusDist - _w * focusDist;

            _horizontal = 2.0 * halfWidth * _u * focusDist;
            _vertical = 2.0 * halfHeight * _v * focusDist;
        }

        Ray getRay(float s, float t) 
        { 
            Vector3 rd = _lensRadius * RandomInUnitDisk();
            Vector3 offset = _u * rd._x + _v * rd._y;
            return Ray(_origin + offset, _leftCorner + s * _horizontal + t * _vertical - _origin - offset);
        }

    public:
        Vector3 _origin;
        Vector3 _leftCorner;
        Vector3 _horizontal;
        Vector3 _vertical;
        Vector3 _u, _v, _w;

        float _lensRadius;
    };
}

#endif
