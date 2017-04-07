#ifndef UTIL_H
#define UTIL_H

#include <cmath>

namespace util {
    
    class PID {
        
        float kp;
        float ki;
        float kd;
        
        
    
    };
    
    float HermiteSplinePointDistance(
        float starting_x, 
        float offset,
        float t0,
        float t1) {
        
        // Calculate the distance between two points on the Hermite spline
        return sqrt((pow(-0.5 * (3 * pow(t0, 2) - 2 * pow(t0, 3)) - 
                starting_x * (1 - 3 * pow(t0, 2) + 2 * pow(t0, 3)) - 
                offset / sqrt(1 + pow(0.5 * (6 * t0 - 6 * pow(t0, 2)) + 
                starting_x * (-6 * t0 + 6 * pow(t0, 2)),
                2)) + 0.5 * (3 * pow(t1, 2) - 2 * pow(t1, 3)) + 
                starting_x * (1 - 3 * pow(t1, 2) + 2 * pow(t1, 3)) + offset /
                sqrt(1 + pow((0.5 * (6 * t1 - 6 * pow(t1, 2)) + 
                starting_x * (-6 * t1 + 6 * pow(t1, 2))),
                2)), 2) + 
                pow(-t0 - (offset * (-0.5 * (6 * t0 - 6 * pow(t0, 2)) - 
                starting_x * (-6 * t0 + 6 * pow(t0, 2)))) / 
                sqrt(1 + pow((0.5 * (6 * t0 - 6 * pow(t0, 2)) + 
                starting_x * (-6 * t0 + 6 * pow(t0, 2))),
                2)) + t1 + (offset * (-0.5 * (6 * t1 - 6 * pow(t1, 2)) - 
                starting_x * (-6 * t1 + 6 * pow(t1, 2)))) / 
                sqrt(1 + pow(0.5 * (6 * t1 - 6 * pow(t1, 2)) + 
                starting_x * (-6 * t1 + 6 * pow(t1, 2)),
                2)), 2)));
    }

    float HermiteSplineArcLength(
        float starting_x,
        float offset,
        float t0,
        float t1,
        int segments) {
        
        // Normally, the equation for the Hermite Spline can be quite long, but 
        // here we will simplify the equation by utilizing the fact that the
        // tangent at both points will be (0,1), the final point will always be
        // (0.5, 1), and the y-coordinate of the starting point is always 0.
        // We will take the offset of this curve (using 0 to represent the regular
        // curve) and calculate the arc length between t0 and t1.
        
        // Begin by first dividing the spline segment into a number of its own
        // discrete segments
        float arc_step = (t1 - t0) / segments;                           

            // Now sum the length of each arc segment
        float length = 0;
        for (int i = 0; i < segments; i++) {
            length += HermiteSplinePointDistance(starting_x, offset, t0 + i*arc_step, t0 + (i + 1)*arc_step);
        }
        
        return length;
    }
    
    float DeltaAngle(float current, float target) {
        if (fabs(target - current) > 180) {
            return (360 - fabs(target - current))*
                        (target - current > 0 ? 1 : -1);
        }
        return target - current;
    }
    
}

#endif
