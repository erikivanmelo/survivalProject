#include "Timer.h"
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>

Timer *Timer::instance = nullptr;

Timer::Timer()
{       
    deltaTime = 0;
    performanceFrequency = SDL_GetPerformanceFrequency();
    targetFrameTime = 1.0 / 60;

    lastTime = SDL_GetPerformanceCounter();
}

void Timer::tickUpdate()
{
    Uint64 currentTime = SDL_GetPerformanceCounter();
    deltaTime = static_cast<double>(currentTime - lastTime) / static_cast<double>(performanceFrequency);
    lastTime = currentTime;
    frameCount++;
    fpsTimer += deltaTime;

    // Actualizar el contador de cuadros y el temporizador de FPS
    if (fpsTimer >= 1.0) { // Si ha pasado 1 segundo
        // Calcular los FPS actuales
        currentFPS = static_cast<double>(frameCount) / fpsTimer;

        // Reiniciar el contador de cuadros y el temporizador de FPS
        frameCount = 0;
        fpsTimer = 0.0;
    }

}
