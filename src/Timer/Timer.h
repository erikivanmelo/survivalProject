#ifndef TIMER_H
#define TIMER_H

#include <SDL2/SDL_stdinc.h>

class Timer
{
public:

    void tickUpdate();
    
    inline int getFPS() const { 
        return currentFPS; 
    }

    inline float getDeltaTime() const { 
        return deltaTime; 
    }

    inline static Timer* getInstance(){ return instance = (instance == nullptr)? new Timer() : instance; }
    inline static void clean(){ delete instance; }

private:
    ~Timer(){}
    Timer();
    static Timer *instance;
    
    float deltaTime;
    Uint64 lastTime;
    Uint64 performanceFrequency;

    int frameCount;
    double fpsTimer;
    int currentFPS;

    double targetFrameTime;

};

#endif // TIMER_H 
