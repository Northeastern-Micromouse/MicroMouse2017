#ifndef MICROMOUSE_HARDWARE_HARDWARE_H_
#define MICROMOUSE_HARDWARE_HARDWARE_H_

typedef enum SensorResult {
	VALID,
	INVALID
} SR;

SR * PollSensors();

#endif  // MICROMOUSE_HARDWARE_HARDWARE_H_