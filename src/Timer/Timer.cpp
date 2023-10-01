#include "Timer.h"
#include <SDL2/SDL_timer.h>

Timer *Timer::instance = nullptr;

Timer::Timer()
{       
    deltaTime = 0;
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
int Timer::getFPS() { 
    static const int numSamples = 60; // Número de muestras para calcular el promedio de FPS.
    static double frameTimes[numSamples];
    static int currentFrame = 0;

    frameTimes[currentFrame] = deltaTime;
    currentFrame = (currentFrame + 1) % numSamples;

    double totalTime = 0.0;
    for (int i = 0; i < numSamples; ++i)
    {
        totalTime += frameTimes[i];
    }

    return static_cast<int>(1.0 / (totalTime / numSamples));
}
