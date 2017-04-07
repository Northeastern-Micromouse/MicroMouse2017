#ifndef UTIL_H
#define UTIL_H

#include <cmath>

namespace util {
    
    class PID {
        
    private:
        float kp_ = 0;
        float ki_ = 0;
        float kd_ = 0;
        float setpoint_ = 0;
        float previous_error_ = 0;
        float integral_ = 0;
        
    public:
        PID(float kp, float ki, float kd);
        float Set(float setpoint);
        float Update(float process, float dt);
        void ResetIntegral();
    };
    
    float HermiteSplinePointDistance(
        float starting_x, 
        float offset,
        float t0,
        float t1); 
    
    float HermiteSplineArcLength(
        float starting_x,
        float offset,
        float t0,
        float t1,
        int segments);
    
    float DeltaAngle(float current, float target);
    
}

#endif
