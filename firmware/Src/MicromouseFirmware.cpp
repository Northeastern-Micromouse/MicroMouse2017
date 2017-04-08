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
#include "DriveSystem.h"
#include "Distance.h"
#include "Algo/robot/impl/RobotImpl.h"

int main(void) {
    CMain();

    pal::Adc adc1(hadc1, 2);
    pal::Adc adc2(hadc2, 3);
    pal::Adc adc3(hadc3, 1);
    pal::I2C i2c(&hi2c1, 10000);
    pal::Gpio left_step = pal::Gpio(S_MOTOR_B_STEP_GPIO_Port, S_MOTOR_B_STEP_Pin);
    pal::Gpio left_dir = pal::Gpio(S_MOTOR_B_DIR_GPIO_Port, S_MOTOR_B_DIR_Pin);
    pal::Gpio right_step = pal::Gpio(S_MOTOR_A_STEP_GPIO_Port, S_MOTOR_A_STEP_Pin);
    pal::Gpio right_dir = pal::Gpio(S_MOTOR_A_DIR_GPIO_Port, S_MOTOR_A_DIR_Pin);
    pal::Gpio driver_rst = pal::Gpio(DRIVER_RSTn_GPIO_Port, DRIVER_RSTn_Pin);
    pal::Tim drive_tick = pal::Tim(&htim1);

    phil::Distance distA(adc1, 5, 0);
    phil::Distance distB(adc2, 6, 0);
    phil::Reflectance reflA(adc1, 7, 1, 0);
    phil::Reflectance reflB(adc2, 8, 1, 1);
    phil::Reflectance reflC(adc3, 4, 0, 2);
    phil::IMU imu(&i2c, BNO055_ADDRESS_A);
    imu.Initialize();
    phil::DriveSystem drive_system(&left_step, &left_dir, &right_step, &right_dir, &drive_tick, 106, 30, M_PI/(100*16));
    
    robot.CorrectiveDrive(180, 350);
    while (1) {
        robot.Turn(90, 2*M_PI);
        robot.CorrectiveDrive(360, 350);
    }
    

  //  al::Robot winslow_ = al::Robot(&drive_system, &imu, &distB, &distA, &reflA, &reflB, &reflC);
  //  AlgoRobot* winslow = new robot::impl::RobotImpl(winslow_, true);
  //  winslow->StartExploration();
  //  winslow->ComputeFastestPath();
  //  winslow->GoToGoal();
  //  delete winslow;
}
