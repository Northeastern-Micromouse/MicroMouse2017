#include <stm32l4xx_hal.h>

#ifdef __cplusplus
extern "C" {
    #include "main.h"
}
#endif

#include <functional>
    
#include "stm32l4xx_hal.h"
#include "GPIO.h"
#include "TIM.h"
#include "I2C.h"
#include "Motor.h"
#include "Robot.h"
#include "IMU.h"

int main(void) {
    
    CMain();
    
    pal::Gpio leftMotorStep = 
        pal::Gpio(S_MOTOR_A_STEP_GPIO_Port, S_MOTOR_A_STEP_Pin);
    
    pal::Gpio leftMotorDir = 
        pal::Gpio(S_MOTOR_A_DIR_GPIO_Port, S_MOTOR_A_DIR_Pin);
    
    pal::Tim leftMotorTick = pal::Tim(getTIM1Handle());
    
    phil::Motor leftMotor = 
        phil::Motor(&leftMotorStep, &leftMotorDir, &leftMotorTick);
    
    pal::Gpio rightMotorStep = 
        pal::Gpio(S_MOTOR_B_STEP_GPIO_Port, S_MOTOR_B_STEP_Pin);
    
    pal::Gpio rightMotorDir = 
        pal::Gpio(S_MOTOR_B_DIR_GPIO_Port, S_MOTOR_B_DIR_Pin);
    
    pal::Tim rightMotorTick = pal::Tim(getTIM2Handle());
    
    phil::Motor rightMotor = 
        phil::Motor(&rightMotorStep, &rightMotorDir, &rightMotorTick);
    
    pal::Gpio driverRst = pal::Gpio(DRIVER_RSTn_GPIO_Port, DRIVER_RSTn_Pin);
    driverRst.Set(true);
    
    //pal::Gpio led = pal::Gpio(DC_M1_IN1_GPIO_Port, DC_M1_IN1_Pin);
    //pal::Tim timer = pal::Tim(TIM2);
    //leftMotorTick.SetTiming(40000, 500);
    //leftMotorTick.SetISR(std::bind<void>(&phil::Motor::Step, leftMotor));
    //leftMotorTick.Enable();
    
    //al::Robot micromouse = al::Robot(leftMotor, rightMotor);
    
    //leftMotor.SetAngularVelocity(M_PI/4, 2.0 * M_PI / 200.0);
    //leftMotor.SetMotion(true);
    
    leftMotor.SetDirection(phil::Motor::Direction::CCW);
    rightMotor.SetDirection(phil::Motor::Direction::CW);
    
    while (1) {
        //HAL_Delay(3000);
        //micromouse.Drive(1, 2*M_PI, al::Robot::DriveMethod::SIMPLE);
        HAL_Delay(1);
        leftMotor.Step();
        rightMotor.Step();
    }
    
    //pal::Gpio led = pal::Gpio(GPIOB, GPIO_PIN_15);
    
    //led.Set(true);
    
    /*
    while (1) {
        led.Toggle();
        HAL_Delay(1000);
    }
    */
    /*
    pal::I2C imuI2C = pal::I2C(getI2C1Handle(), 10000);
    phil::IMU imu = phil::IMU(&imuI2C, BNO055_ADDRESS_A);
    HAL_StatusTypeDef error = imu.Initialize();
    
    uint8_t data;
    imuI2C.Read(BNO055_ADDRESS_A, BNO055_CHIP_ID_ADDR, &data);
    
    while (1) {
        float roll = 0, pitch = 0, heading = 0;
        imu.GetRoll(roll);
        imu.GetPitch(pitch);
        imu.GetHeading(heading);
        HAL_Delay(10);
    }
    */
}
