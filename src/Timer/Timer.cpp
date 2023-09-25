#include "Timer.h"
#include <SDL2/SDL_timer.h>

Timer *Timer::instance = nullptr;

Timer::Timer()
{       
    performanceFrequency = SDL_GetPerformanceFrequency();
    maxFps = 0;
    targetFrameTime = 1.0 / static_cast<double>(maxFps);

    lastTime = SDL_GetPerformanceCounter();
}

void Timer::tickUpdate()
{
    Uint64 currentTime = SDL_GetPerformanceCounter();
    deltaTime = static_cast<double>(currentTime - lastTime) / static_cast<double>(performanceFrequency);
    lastTime = currentTime;
    
}
