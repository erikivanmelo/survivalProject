#include "Timer.h"
#include <SDL2/SDL_timer.h>

Timer *Timer::instance = nullptr;

Timer::Timer()
{       
    performanceFrequency = SDL_GetPerformanceFrequency();
    maxFps = 0;
    targetFrameTime = 1.0 / static_cast<double>(maxFps);

    lastTime = SDL_GetPerformanceCounter();
    frameCount = 0;
    fpsTimer = 0.0;
    currentFPS = 0;
}

void Timer::tickUpdate()
{
    Uint64 currentTime = SDL_GetPerformanceCounter();
    deltaTime = static_cast<double>(currentTime - lastTime) / static_cast<double>(performanceFrequency);
    lastTime = currentTime;

    // Limitar el FPS
    if(maxFps > 0){
        if (deltaTime < targetFrameTime) {
            double delayTime = targetFrameTime - deltaTime;
            uint32_t delayMilliseconds = static_cast<uint32_t>(delayTime * 1000.0);
            SDL_Delay(delayMilliseconds);

            // Actualizar el deltaTime después del retraso
            currentTime = SDL_GetPerformanceCounter();
            deltaTime = static_cast<double>(currentTime - lastTime) / static_cast<double>(performanceFrequency);
            lastTime = currentTime;
        }
    }
    
    // Actualizar el contador de cuadros y el temporizador de FPS
    frameCount++;
    fpsTimer += deltaTime;
    if (fpsTimer >= 1.0) { // Si ha pasado 1 segundo
        // Calcular los FPS actuales
        currentFPS = static_cast<double>(frameCount) / fpsTimer;

        // Reiniciar el contador de cuadros y el temporizador de FPS
        frameCount = 0;
        fpsTimer = 0.0;
    }
}
