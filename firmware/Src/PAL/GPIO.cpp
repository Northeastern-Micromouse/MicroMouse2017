#include "GPIO.h"

pal::Gpio::Gpio(GPIO_TypeDef* port, uint16_t pin) {
	// Remember that CubeMX takes care of initializing clocks and configuring
	// the pins, so all we need to do is set local variables
	port_ = port;
	pin_ = pin;
}

void pal::Gpio::Set(bool value) const {
	HAL_GPIO_WritePin(port_, pin_, (value ? GPIO_PIN_SET : GPIO_PIN_RESET));
}

bool pal::Gpio::Get() const {
	return HAL_GPIO_ReadPin(port_, pin_) == GPIO_PIN_SET;
}

void pal::Gpio::Toggle() const {
	HAL_GPIO_TogglePin(port_, pin_);
}
