//---------------------------------------------------------//
//
// Prototype Code for SDL3 - DO NOT USE FOR PROD
//
// PiaPsyker - 2025
//
//---------------------------------------------------------//
/* Library Loading */
//---------------------------------------------------------//

#ifndef TIMER_H
#define TIMER_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3_image/SDL_image.h>

//---------------------------------------------------------//
/* Class Prototype */
//---------------------------------------------------------//

class Timer {

    public:

        Timer();

        void start();
        void stop();
        void pause();
        void unpause();

        Uint64 getTicksNS();

        bool isStarted();
        bool isPaused();

    private:

        Uint64 startTicks;
        Uint64 pausedTicks;

        bool paused;
        bool started;

};

#endif