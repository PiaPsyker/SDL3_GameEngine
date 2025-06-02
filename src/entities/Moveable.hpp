//---------------------------------------------------------//
//
// Prototype Code for SDL3 - DO NOT USE FOR PROD
//
// PiaPsyker - 2025
//
//---------------------------------------------------------//
/* Library Loading */
//---------------------------------------------------------//

#ifndef MOVEABLE_H
#define MOVEABLE_H

//---------------------------------------------------------//
/* Class Prototype */
//---------------------------------------------------------//

class Moveable {

    public:

        virtual void move(int x, int y, int z) {};
        virtual void setPosition(int x, int y, int z) {};

};

#endif