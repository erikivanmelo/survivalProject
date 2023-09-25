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
    
    inline int getFPS() const { 
        return currentFPS; 
    }

    inline void setMaxFps(int maxFps){ 
        this->maxFps = maxFps; 
        targetFrameTime = 1.0 / static_cast<double>(maxFps); 
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
    
    int frameCount;
    double fpsTimer;
    int currentFPS;

    int maxFps;
    float frameDuration;

    double targetFrameTime;
};

#endif // TIMER_H 
