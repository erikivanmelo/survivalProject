#ifndef TIMER_H
#define TIMER_H

#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL.h>

#define startInLapse(counter,lapse) static float counter = 0.0; \
                                    counter += Timer::getDeltaTime(); \
                                    if( lapse == 0.0 || counter >= lapse ){
#define endInLapse(counter,lapse) counter = lapse? counter - lapse : 0; }

class Timer
{
public:
    static float getDeltaTime(){
        return Timer::deltaTime;
    }

    static void tickUpdate()
    {
        static Uint64 lastTime = SDL_GetPerformanceCounter();
        const double performanceFrequency = static_cast<double>(SDL_GetPerformanceFrequency());
        const Uint64 currentTime = SDL_GetPerformanceCounter();

        Timer::deltaTime = static_cast<double>(currentTime - lastTime) / performanceFrequency;
        lastTime = currentTime;
    }
private:
    static inline float deltaTime = 0.0;
};

#endif // TIMER_H 
