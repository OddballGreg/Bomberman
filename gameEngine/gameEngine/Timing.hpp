#pragma once_flag

namespace gameEngine {

    class FpsLimiter {

        public:
            FpsLimiter();
            
            void            setMaxFPS(float maxFPS);
            void            init(float maxFPS);
            void            beginFrame();
            float           end();

        private:
            void            calculateFPS();

            float           _maxFPS;
            unsigned int    _startTicks;
            float           _fps;
            float           _frameTime;
    };
}