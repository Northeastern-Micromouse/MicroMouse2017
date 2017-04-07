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
    pal::I2C i2c(&hi2c1, 10000);
    pal::Gpio left_step = pal::Gpio(S_MOTOR_B_STEP_GPIO_Port, S_MOTOR_B_STEP_Pin);
    pal::Gpio left_dir = pal::Gpio(S_MOTOR_B_DIR_GPIO_Port, S_MOTOR_B_DIR_Pin);
    pal::Gpio right_step = pal::Gpio(S_MOTOR_A_STEP_GPIO_Port, S_MOTOR_A_STEP_Pin);
    pal::Gpio right_dir = pal::Gpio(S_MOTOR_A_DIR_GPIO_Port, S_MOTOR_A_DIR_Pin);
    pal::Tim drive_tick = pal::Tim(&htim1);
    
    phil::Distance distA(adc1, 5, 0);
    phil::Distance distB(adc2, 6, 0);
    phil::Reflectance reflA(adc1, 7, 1, 0);
    phil::Reflectance reflB(adc2, 8, 1, 1);
    phil::Reflectance reflC(adc3, 4, 0, 2);
    phil::IMU imu(&i2c, BNO055_ADDRESS_A);
    imu.Initialize();
    phil::DriveSystem drive_system(&left_step, &left_dir, &right_step, &right_dir, &drive_tick, 1, 1, 1);
    
    al::Robot robot(&drive_system, &imu, &distB, &distA, &reflA, &reflB, &reflC);
    
    printf("Entered main program loop\n");
    while (1) {
        //float offset_h = robot.GetHorizontalLocation(true, true);
        //float offset_v = robot.GetVerticalLocation();
        //float dist = reflC.GetDistance();
        float left_dist = distB.GetDistance();
        float right_dist = distA.GetDistance();
    }
  }
