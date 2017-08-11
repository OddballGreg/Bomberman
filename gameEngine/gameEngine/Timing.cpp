#include "Timing.hpp"

#include <GL/glew.h>
#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>
#include <SDL2/SDL.h>

gameEngine::FpsLimiter::FpsLimiter() {

}
void gameEngine::FpsLimiter::setMaxFPS(float maxFPS) {
    _maxFPS = maxFPS;
}

void gameEngine::FpsLimiter::init(float maxFPS) {
    setMaxFPS(maxFPS);
}

void gameEngine::FpsLimiter::beginFrame() {
   //  _startTicks = SDL_GetTicks();
   _startTicks = glfwGetTime();
}

float gameEngine::FpsLimiter::end() {
    calculateFPS();

    float frameTicks = glfwGetTime() - _startTicks;
        if (1.0f / _maxFPS > frameTicks) {
            // usleep(1.0f / _maxFPS - frameTicks);
            SDL_Delay((Uint32)(1000.0f / _maxFPS - frameTicks));
        }
    return _fps;
}

void    gameEngine::FpsLimiter::calculateFPS() {
    // Log log("mainGame", "calculateFPS", CRITICAL);
    static const int NUM_SAMPLES = 100;
    static float frameTimes[NUM_SAMPLES];
    static int currentFrame = 0;

    static float prevTicks = glfwGetTime();
    float currentTicks;

    currentTicks = glfwGetTime();

    _frameTime = currentTicks - prevTicks;
    frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;

    prevTicks = currentTicks;

    int count;

    currentFrame++;

    if (currentFrame < NUM_SAMPLES) {
        count = currentFrame;
    }
    else
        count = NUM_SAMPLES;
    
    float frameTimeAverage = 0;
    
    for (int i = 0; i < count; i++) {
        frameTimeAverage += frameTimes[i];
    }

    frameTimeAverage /= count;
    if (frameTimeAverage > 0) {
        _fps = 1.0f / frameTimeAverage;
    }
    else {
        _fps = 60;
    }
}