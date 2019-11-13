#ifndef _PERLIN_H_
#define _PERLIN_H_

#include "Vector3.h"
#include "Utilities.h"

namespace rt
{
    class Perlin
    {
    public:
        float noise(const Vector3& p) const
        {

        }

    public:
        static float* _ranfloat;
        static int* _permX;
        static int* _permY;
        static int* _permZ;
    };



    static float* PerlinGenerate()
    {
        float* p = new float[256];
        for (int i = 0; i < 256; i++)
        {
            p[i] = Random021();
        }

        return p;
    }

    void Permute(int* p, int n)
    {
        for (int i = n - 1; i > 0; --i)
        {
            int target = static_cast<int>(Random021() * (i + 1));
            int tmp = p[i];
            p[i] = target;
            p[target] = i;
        }
    }

    static int* PerlinGeneratePerm()
    {
        int* p = new int[256];
        for (int i = 0; i < 256; i++)
        {
            p[i] = i;
        }

        Permute(p, 256);

        return p;
    }

    float* Perlin::_ranfloat = PerlinGenerate();
    int* Perlin::_permX = PerlinGeneratePerm();
    int* Perlin::_permY = PerlinGeneratePerm();
    int* Perlin::_permZ = PerlinGeneratePerm();
}

#endif // !_PERLIN_H_
