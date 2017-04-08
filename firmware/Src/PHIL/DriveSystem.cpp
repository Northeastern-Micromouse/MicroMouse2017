#include "DriveSystem.h"

phil::DriveSystem::DriveSystem(
    pal::Gpio* left_step, 
    pal::Gpio* left_dir, 
    pal::Gpio* right_step, 
    pal::Gpio* right_dir,
    pal::Tim* us_tick,
    float width, 
    float wheel_radius,
    float radians_per_step): 
    WIDTH(width), 
    WHEEL_RADIUS(wheel_radius), 
    RADIANS_PER_STEP(radians_per_step), 
    left_step_(left_step),
    left_dir_(left_dir),
    right_step_(right_step),
    right_dir_(right_dir),
    us_tick_(us_tick) {
     
    
    // Configure the timer to tick every us
    us_tick_->SetTiming(1, 80000000 / 8000000);  
}

void phil::DriveSystem::DriveEquidistant(float distance, float velocity) {
    // Calculate us per step
    // (rad/step) / (rad/s) = (s/step)
    // Also calculate required angular velocity
    // v = rw -> w = v/r
    uint32_t period_us = (uint32_t)(RADIANS_PER_STEP / 
                    (velocity / WHEEL_RADIUS) * 1000000.0);
    
    // now figure out how long the whole move should take in us
    //uint32_t time = distance / velocity * 1000000;
    
    // now figure out how many steps should be taken
    // steps = desiredDistance / (distance / step) 
    //       = desiredDistance / (radius * radians/step)
    uint32_t steps = distance / (WHEEL_RADIUS * RADIANS_PER_STEP);
    
    // now actually drive, stopping when time is up
    us_tick_->SetCount(0);
    us_tick_->Enable();
    
    ResetLeftStepCount();
    ResetRightStepCount();
    
    uint32_t us = 0;
    uint32_t period_start = 0;
    
    while (left_step_count_ < steps && right_step_count_ < steps) {
        
        // first, update our us count using the timer count
        if (us_tick_->GetUpdateFlag()) {
            us++;
            us_tick_->ClearUpdateFlag();
        }
        
        if (us % period_us == 0) {
            // Time to raise the step pin
            left_step_->Set(true);
            right_step_->Set(true);
            period_start = us;
        }
        
        else if (us == (period_start + STEPPER_MOTOR_STEP_TIME)) {
            left_step_->Set(false);
            right_step_->Set(false);
            left_step_count_++;
            right_step_count_++;
        }
    }
    
    us_tick_->Disable();
}
        
void phil::DriveSystem::DriveStraight(float distance, float velocity) {
    // Set both motors forward and drive an equal distance on each wheel
    left_dir_->Set(false);
    right_dir_->Set(true);
    DriveEquidistant(distance, velocity);
}

void phil::DriveSystem::DriveRelative(
    float left_distance, 
    float right_distance, 
    float average_velocity) {
        
    left_dir_->Set(false);
    right_dir_->Set(true);
        
    // First, figure out how much time the entire operation will take using the
    // given average velocity
    float time = ((left_distance + right_distance) / 2.0) / average_velocity;
    
    // Now compute the left and right velocities, and accordingly the time per
    // step of the left and right wheels
    float left_velocity = left_distance / time;
    float right_velocity = right_distance / time;
        
    // (rad/step) / (rad/s) = (s/step)
    // Also calculate required angular velocity
    // v = rw -> w = r/v
    uint32_t left_period = (uint32_t)(RADIANS_PER_STEP / 
                            (left_velocity / WHEEL_RADIUS) * 1000000.0);
    uint32_t right_period = (uint32_t)(RADIANS_PER_STEP / 
                            (right_velocity / WHEEL_RADIUS) * 1000000.0);
        
    uint32_t left_steps = left_distance / (WHEEL_RADIUS * RADIANS_PER_STEP);
    uint32_t right_steps = right_distance / (WHEEL_RADIUS * RADIANS_PER_STEP);
        
    ResetLeftStepCount();
    ResetRightStepCount();
        
    // Now use the tick to drive the wheels with the appropriate timing
    us_tick_->SetCount(0);
    us_tick_->Enable();
        
    uint32_t us = 0;
    uint32_t left_period_start = 0;
    uint32_t right_period_start = 0;
    
    while (left_step_count_ < left_steps && right_step_count_ < right_steps) {
        
        // first, update our us count using the timer count
        if (us_tick_->GetUpdateFlag()) {
            us++;
            us_tick_->ClearUpdateFlag();
        }
        
        if (us % left_period == 0) {
            // Time to raise the step pin
            left_step_->Set(true);
            left_period_start = us;
        }
        
        else if (us == (left_period_start + STEPPER_MOTOR_STEP_TIME)) {
            left_step_->Set(false);
            left_step_count_++;
        }
        
        if (us % right_period == 0) {
            // Time to raise the step pin
            right_step_->Set(true);
            right_period_start = us;
        }
        
        else if (us == (right_period_start + STEPPER_MOTOR_STEP_TIME)) {
            right_step_->Set(false);
            right_step_count_++;
        }
    }
}

void phil::DriveSystem::DriveRadius(
    float arc_length,
    float radius,
    float velocity) {
        
    // We are basically driving each wheel along two different arcs, each at a
    // slightly different radius based on the width of the robot. We can just
    // compute the length of these arcs and call DriveRelative:
    float angle = arc_length / fabs(radius);
    float left_radius = fabs(radius) + 
            (radius > 0 ? 1.0 : -1.0) * WIDTH / 2.0;
    float right_radius = fabs(radius) - 
            (radius > 0 ? 1.0 : -1.0) * WIDTH / 2.0;
    
    DriveRelative(left_radius * angle, right_radius * angle, velocity);
}

void phil::DriveSystem::Turn(float radians, float angularVelocity) {
    // Set motors in opposite directions and drive an equal distance on each
    // wheel. Positive values for radians means a clockwise turn, negative
    // means counter clockwise
    left_dir_->Set(radians < 0);
    right_dir_->Set(radians < 0);
    
    // Calculate the distance each wheel needs to drive
    // This is the arc length around the circle formed with the center being
    // the midpoint of the bot and the radius being half the width of the drive
    // system
    // s = r*theta
    float distance = (WIDTH / 2.0) * radians;
    
    // Convert the angular velocity into linear velocity (being the linear
    // velocity of the wheels travelling along the arc) by computing the time
    // taken to travel the given number of degrees and dividing the computed
    // arc length by this time
    float time = radians / angularVelocity;
    
    // Now simply drive the wheels
    DriveEquidistant(distance, distance / time); 
    
}

uint32_t phil::DriveSystem::GetLeftStepCount() const {
    return left_step_count_;
}

uint32_t phil::DriveSystem::GetRightStepCount() const {
    return right_step_count_;
}

void phil::DriveSystem::ResetLeftStepCount() {
    left_step_count_ = 0;
}

void phil::DriveSystem::ResetRightStepCount() {
    right_step_count_ = 0;
}

float phil::DriveSystem::GetWidth() const {
    return WIDTH;
}

float phil::DriveSystem::GetWheelRadius() const {
    return WHEEL_RADIUS;
}
