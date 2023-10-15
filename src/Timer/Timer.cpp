#include "Timer.h"
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>

Timer *Timer::instance = nullptr;

Timer::Timer() : 
    deltaTime(0.0), 
    currentFPS(0)
{}

void Timer::tickUpdate()
{
    const double performanceFrequency = static_cast<double>(SDL_GetPerformanceFrequency());
    static int frameCount = 0;
    static double fpsTimer = 0.0;
    static Uint64 lastTime = SDL_GetPerformanceCounter();
    Uint64 currentTime = SDL_GetPerformanceCounter();

    deltaTime = static_cast<double>(currentTime - lastTime) / performanceFrequency;
    lastTime = currentTime;

    frameCount++;
    // Actualizar el contador de cuadros y el temporizador de FPS
    if ( (fpsTimer += deltaTime) >= 1.0 ) { // Si ha pasado 1 segundo
        // Calcular los FPS actuales
        currentFPS = static_cast<double>(frameCount) / fpsTimer;

        // Reiniciar el contador de cuadros y el temporizador de FPS
        frameCount = 0;
        fpsTimer = 0.0;
    }

}
