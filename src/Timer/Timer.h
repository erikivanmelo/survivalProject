#ifndef TIMER_H
#define TIMER_H

#include <SDL2/SDL_stdinc.h>

class Timer
{
public:

    void clean(){
        delete instance;
    }

    void tickUpdate();
    
    int getFPS() const { 
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

    inline float getDeltaTime(){ 
        return deltaTime; 
    }

    inline static Timer* getInstance(){ return instance = (instance == nullptr)? new Timer() : instance; }

private:
    Timer();
    ~Timer(){}
    static Timer *instance;
    
    float deltaTime;
    Uint64 lastTime;
    Uint64 performanceFrequency;

    int maxFps;

    double targetFrameTime;

};

#endif // TIMER_H 
