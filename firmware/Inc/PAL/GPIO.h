#ifndef GPIO_H
#define GPIO_H

#include "stm32l4xx_hal.h"

namespace pal {
    
	class Gpio {
	
	private:
		GPIO_TypeDef* port_;
		uint16_t pin_;
		
	public:
		Gpio(GPIO_TypeDef* port, uint16_t pin);
		void Set(bool value) const;
		bool Get() const;
		void Toggle() const;
	};
	
}

#endif