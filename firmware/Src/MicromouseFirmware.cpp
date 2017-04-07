#include <stm32l4xx_hal.h>

#ifdef __cplusplus
extern "C" {
    #include "main.h"
}
#endif

#include <functional>
#include <algorithm>    

#include "stm32l4xx_hal.h"
#include "GPIO.h"
#include "TIM.h"
#include "I2C.h"
#include "Motor.h"
#include "Robot.h"
#include "IMU.h"
#include "ADC.h"
#include "Reflectance.h"
#include "Distance.h"

int main(void) {
     
    CMain();
    printf("!STARTED PROGRAM!\n");

    pal::Adc adc1(hadc1, 2);
    pal::Adc adc2(hadc2, 3);
    pal::Adc adc3(hadc3, 1);
    phil::Distance distA(adc1, 5, 0);
    phil::Distance distB(adc2, 6, 0);
    phil::Reflectance reflA(adc1, 7, 1);
    phil::Reflectance reflB(adc2, 8, 1);
    phil::Reflectance reflC(adc3, 4, 0);
    printf("Entered main program loop\n");
    while (1) {
        float distA_out = distA.GetDistance(); // RIGHT
        //float distB_out = distB.GetDistance(); // LEFT
        //float reflA_out = reflA.GetDistance(); // LEFT
        //float reflB_out = reflB.GetDistance(); // RIGHT
        //float reflC_out = reflC.GetDistance(); // CENTER
    }
  }
