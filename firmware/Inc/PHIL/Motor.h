#ifndef MOTOR_H
#define MOTOR_H

#include "GPIO.h"
#include "TIM.h"

#define TICK_PRESCALER 80

namespace phil
{

	class Motor
	{
	private:
    	pal::Gpio* step_;
        pal::Gpio* dir_;
		pal::Tim* tick_;
		int steps_;
    	
	public:
    	enum class Direction {
    	    CW, CCW
    	};
    	
		Motor(pal::Gpio* step, pal::Gpio* dir, pal::Tim* tick);
    	
    	// Returns the current number of steps taken by the motor since the
    	// last call to resetSteps() or initialization.
		int getSteps() const;
    	
    	// Resets the motor's step count
    	void resetSteps();
    	
    	// Sets the direction of the motor
    	void SetDirection(Direction d);
    	
    	// Steps the motor one step. Note: blocks for 1ms
    	void Step();
    	
    	// Sets the angular velocity of the motor given the angular velocity
    	// (w) and the radians per step of this motor
    	void SetAngularVelocity(float w, float radPerStep);
    	
    	// If "on" is true, the motor will turn on, otherwise the motor will
    	// turn off
    	void SetMotion(bool on);
	};
	
}

#endif