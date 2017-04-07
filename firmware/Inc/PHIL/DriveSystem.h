#ifndef DRIVESYSTEM_H
#define DRIVESYSTEM_H

#include <cmath>
#include "GPIO.h"
#include "TIM.h"

#define STEPPER_MOTOR_STEP_TIME 5 //Step pulse width in us

namespace phil {
    
    class DriveSystem {
    
    private:
      
        // The distance between the wheels in mm
        const float WIDTH;
    	
        // The diameter of the wheels in mm
        const float WHEEL_RADIUS;
    	
        // Radians/step of the motors
        const float RADIANS_PER_STEP;
    	
        // The distance taken by one step 
        const float DISTANCE_PER_STEP = WHEEL_RADIUS * RADIANS_PER_STEP;
    	
        // The distance the left and right motors must travel to rotate the bot
        // by one degree
        // = (mm/rad_of_bot_rotation) * (rad/deg) = cm/deg
        const float ARC_LENGTH_PER_DEGREE = (WIDTH / 2.0) * (M_PI / 180.0);
        
        pal::Gpio* left_step_;
        pal::Gpio* left_dir_;
        pal::Gpio* right_step_;
        pal::Gpio* right_dir_;
        pal::Tim* us_tick_;
        
        uint32_t left_step_count_ = 0;
        uint32_t right_step_count_ = 0;
        
        void DriveEquidistant(float distance, float velocity);
        
    public:
        
        enum class Direction {
            CW,
            CCW
        };
        
        // Initializes the DriveSystem with the necessary parameters.
        // us_tick will be configured for a 1us tick inside this function
        DriveSystem(pal::Gpio* left_step, pal::Gpio* left_dir, 
                    pal::Gpio* right_step, pal::Gpio* right_dir,
                    pal::Tim* us_tick,
                    float width, float wheel_radius, float radians_per_step);
        
        // Simply drives the robot straight at the given velocity
        void DriveStraight(float distance, float velocity);
        
        // Drives the robot enforcing relative velocity between wheels such
        // that the left wheel will drive left_distance in the same amount of
        // time as the right wheel will drive right_distance, with the velocity
        // centered at average_velocity
        void DriveRelative(
            float left_distance, 
            float right_distance, 
            float average_velocity);
        
        // Drives the robot along an arc of given radius for the given arc
        // length at the given velocity. A positive radius means a clockwise
        // arc, while a negative radius means a counterclockwise arc.
        void DriveRadius(float arc_length, float radius, float velocity);
        
        // Turns the robot in place at the given angular velocity (radians/s)
        void Turn(float degrees, float angularVelocity);
        
        uint32_t GetLeftStepCount() const;
        uint32_t GetRightStepCount() const;
        void ResetLeftStepCount();
        void ResetRightStepCount();
        
        float GetWidth() const;
        float GetWheelRadius() const;
        
    };
    
}

#endif
