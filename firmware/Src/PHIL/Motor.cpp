#include "Motor.h"

phil::Motor::Motor(pal::Gpio* step, pal::Gpio* dir, pal::Tim* tick) {
    step_ = step;
    dir_ = dir;
    tick_ = tick;
    tick->SetISR(std::bind<void>(&phil::Motor::Step, *this));
}

int phil::Motor::getSteps() const {
    return steps_;
}

void phil::Motor::SetDirection(phil::Motor::Direction d) {
    dir_->Set(d == phil::Motor::Direction::CCW);
}

void phil::Motor::Step() {
    step_->Set(true);
    HAL_Delay(1);
    step_->Set(false);
    steps_++;
}

void phil::Motor::resetSteps() {
    steps_ = 0;
}

void phil::Motor::SetAngularVelocity(float w, float radPerStep) {
    // (rad/step) / (rad/s) = (s/step)
    float periodUs = radPerStep / w * 1000000.0;
    // max period of 65ms, min period of 5us
    tick_->SetTiming(TICK_PRESCALER, (uint16_t)periodUs);
}

void phil::Motor::SetMotion(bool on) {
    if (on) {
        tick_->Enable();
    }
    else {
        tick_->Disable();
    }
}
