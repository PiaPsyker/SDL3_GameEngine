#include "Timer.hpp"
#include <SDL3/SDL_timer.h>


//---------------------------------------------------------//
/* Class Implementation */
//---------------------------------------------------------//

Timer::Timer():

    startTicks{0},
    pausedTicks{0},
    paused{false},
    started{false}

{



}

void Timer::start() {

    started = true;
    paused = false;

    startTicks = SDL_GetTicksNS();
    pausedTicks = 0;

}

void Timer::stop() {

    started = false;
    paused = false;

    startTicks = 0;
    pausedTicks = 0;

}

void Timer::pause() {

    if(started && !paused) {

        paused = true;

        pausedTicks = SDL_GetTicksNS() - startTicks;
        startTicks = 0;

    }
}

void Timer::unpause() {

    if(started && paused) {

        paused = false;

        startTicks = SDL_GetTicksNS() - pausedTicks;
        pausedTicks = 0;

    }
}

Uint64 Timer::getTicksNS() {

    Uint64 time = 0;

    if(started) {

        if(paused) {

            time = pausedTicks;

        } else {

            time = SDL_GetTicksNS() - startTicks;

        }
    }

    return time;

}