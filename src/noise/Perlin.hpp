//---------------------------------------------------------//
//
// Prototype Code for SDL3 - DO NOT USE FOR PROD
//
// PiaPsyker - 2025
//
//---------------------------------------------------------//
/* Library Loading */
//---------------------------------------------------------//

#ifndef PERLIN_H
#define PERLIN_H

#include <cstdlib>
#include <ctime>
#include <cmath>

//---------------------------------------------------------//
/* Class Prototype */
//---------------------------------------------------------//

class Perlin {

    public:
        Perlin();
        
        float noise(float sample_x, float sample_y, float sample_z);

    private:
        int *p;

        float *Gx;
        float *Gy;
        float *Gz;

};

#endif