#ifndef MOTOR_H
#define MOTOR_H

namespace phil
{

	class Motor
	{
	private:
		pal::GPIO a, b;
		pal::TIM tick;
	public:
		Motor(pal::GPIO& a, pal::GPIO& b, pal::TIM& tick);
	};
	
}

#endif