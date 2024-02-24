#ifndef TIMER_H
#define TIMER_H

#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL.h>

#define startInLapse(counter, lapse, dt) static float counter = 0.0; \
                                    counter += dt; \
                                    if( lapse == 0.0 || counter >= lapse ){
#define endInLapse(counter,lapse) counter = lapse > 0? counter - lapse : 0; }

class Timer
{
public:
    static float getDeltaTime(){
        return Timer::deltaTime;
    }

    static void tickUpdate()
    {
        static Uint64 lastTime = SDL_GetPerformanceCounter();
        const Uint64 currentTime = SDL_GetPerformanceCounter();

        Timer::deltaTime = static_cast<double>(currentTime - lastTime) / static_cast<double>(SDL_GetPerformanceFrequency());
        lastTime = currentTime;
    }
private:
    static inline float deltaTime = 0.0;
};

#endif // TIMER_H 
