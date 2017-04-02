#ifndef IMU_H
#define IMU_H

#ifdef __cplusplus
extern "C" {
    #include "stm32l4xx_hal.h"
}
#endif

#include "I2C.h"

// Some BNO055 Constants
#define BNO055_ADDRESS_A (0x28 << 1)
#define BNO055_ADDRESS_B (0x29 << 1)
#define BNO055_ID        (0xA0)
#define BNO055_I2C_TIMEOUT	10000

// BNO055 Register Addresses (taken from Adafruit_BNO055.h)

/* Page id register definition */
#define BNO055_PAGE_ID_ADDR                   0x07

/* PAGE0 REGISTER DEFINITION START*/
#define BNO055_CHIP_ID_ADDR                   0x00
#define BNO055_ACCEL_REV_ID_ADDR              0x01
#define BNO055_MAG_REV_ID_ADDR                0x02
#define BNO055_GYRO_REV_ID_ADDR               0x03
#define BNO055_SW_REV_ID_LSB_ADDR             0x04
#define BNO055_SW_REV_ID_MSB_ADDR             0x05
#define BNO055_BL_REV_ID_ADDR                 0x06

/* Accel data register */
#define BNO055_ACCEL_DATA_X_LSB_ADDR          0x08
#define BNO055_ACCEL_DATA_X_MSB_ADDR          0x09
#define BNO055_ACCEL_DATA_Y_LSB_ADDR          0x0A
#define BNO055_ACCEL_DATA_Y_MSB_ADDR          0x0B
#define BNO055_ACCEL_DATA_Z_LSB_ADDR          0x0C
#define BNO055_ACCEL_DATA_Z_MSB_ADDR          0x0D

/* Mag data register */
#define BNO055_MAG_DATA_X_LSB_ADDR            0x0E
#define BNO055_MAG_DATA_X_MSB_ADDR            0x0F
#define BNO055_MAG_DATA_Y_LSB_ADDR            0x10
#define BNO055_MAG_DATA_Y_MSB_ADDR            0x11
#define BNO055_MAG_DATA_Z_LSB_ADDR            0x12
#define BNO055_MAG_DATA_Z_MSB_ADDR            0x13

/* Gyro data registers */
#define BNO055_GYRO_DATA_X_LSB_ADDR           0x14
#define BNO055_GYRO_DATA_X_MSB_ADDR           0x15
#define BNO055_GYRO_DATA_Y_LSB_ADDR           0x16
#define BNO055_GYRO_DATA_Y_MSB_ADDR           0x17
#define BNO055_GYRO_DATA_Z_LSB_ADDR           0x18
#define BNO055_GYRO_DATA_Z_MSB_ADDR           0x19

/* Euler data registers */
#define BNO055_EULER_H_LSB_ADDR               0x1A
#define BNO055_EULER_H_MSB_ADDR               0x1B
#define BNO055_EULER_R_LSB_ADDR               0x1C
#define BNO055_EULER_R_MSB_ADDR               0x1D
#define BNO055_EULER_P_LSB_ADDR               0x1E
#define BNO055_EULER_P_MSB_ADDR               0x1F

/* Quaternion data registers */
#define BNO055_QUATERNION_DATA_W_LSB_ADDR     0x20
#define BNO055_QUATERNION_DATA_W_MSB_ADDR     0x21
#define BNO055_QUATERNION_DATA_X_LSB_ADDR     0x22
#define BNO055_QUATERNION_DATA_X_MSB_ADDR     0x23
#define BNO055_QUATERNION_DATA_Y_LSB_ADDR     0x24
#define BNO055_QUATERNION_DATA_Y_MSB_ADDR     0x25
#define BNO055_QUATERNION_DATA_Z_LSB_ADDR     0x26
#define BNO055_QUATERNION_DATA_Z_MSB_ADDR     0x27

/* Linear acceleration data registers */
#define BNO055_LINEAR_ACCEL_DATA_X_LSB_ADDR   0x28
#define BNO055_LINEAR_ACCEL_DATA_X_MSB_ADDR   0x29
#define BNO055_LINEAR_ACCEL_DATA_Y_LSB_ADDR   0x2A
#define BNO055_LINEAR_ACCEL_DATA_Y_MSB_ADDR   0x2B
#define BNO055_LINEAR_ACCEL_DATA_Z_LSB_ADDR   0x2C
#define BNO055_LINEAR_ACCEL_DATA_Z_MSB_ADDR   0x2D

/* Gravity data registers */
#define BNO055_GRAVITY_DATA_X_LSB_ADDR        0x2E
#define BNO055_GRAVITY_DATA_X_MSB_ADDR        0x2F
#define BNO055_GRAVITY_DATA_Y_LSB_ADDR        0x30
#define BNO055_GRAVITY_DATA_Y_MSB_ADDR        0x31
#define BNO055_GRAVITY_DATA_Z_LSB_ADDR        0x32
#define BNO055_GRAVITY_DATA_Z_MSB_ADDR        0x33

/* Temperature data register */
#define BNO055_TEMP_ADDR					  0x34

/* Status registers */
#define BNO055_CALIB_STAT_ADDR                0x35
#define BNO055_SELFTEST_RESULT_ADDR           0x36
#define BNO055_INTR_STAT_ADDR                 0x37

#define BNO055_SYS_CLK_STAT_ADDR              0x38
#define BNO055_SYS_STAT_ADDR                  0x39
#define BNO055_SYS_ERR_ADDR0x3A

/* Unit selection register */
#define BNO055_UNIT_SEL_ADDR                  0x3B
#define BNO055_DATA_SELECT_ADDR               0x3C

/* Mode registers */
#define BNO055_OPR_MODE_ADDR                  0x3D
#define BNO055_PWR_MODE_ADDR                  0x3E

#define BNO055_SYS_TRIGGER_ADDR               0x3F
#define BNO055_TEMP_SOURCE_ADDR               0x40

/* Axis remap registers */
#define BNO055_AXIS_MAP_CONFIG_ADDR           0x41
#define BNO055_AXIS_MAP_SIGN_ADDR             0x42

/* SIC registers */
#define BNO055_SIC_MATRIX_0_LSB_ADDR          0x43
#define BNO055_SIC_MATRIX_0_MSB_ADDR          0x44
#define BNO055_SIC_MATRIX_1_LSB_ADDR          0x45
#define BNO055_SIC_MATRIX_1_MSB_ADDR          0x46
#define BNO055_SIC_MATRIX_2_LSB_ADDR          0x47
#define BNO055_SIC_MATRIX_2_MSB_ADDR          0x48
#define BNO055_SIC_MATRIX_3_LSB_ADDR          0x49
#define BNO055_SIC_MATRIX_3_MSB_ADDR          0x4A
#define BNO055_SIC_MATRIX_4_LSB_ADDR          0x4B
#define BNO055_SIC_MATRIX_4_MSB_ADDR          0x4C
#define BNO055_SIC_MATRIX_5_LSB_ADDR          0x4D
#define BNO055_SIC_MATRIX_5_MSB_ADDR          0x4E
#define BNO055_SIC_MATRIX_6_LSB_ADDR          0x4F
#define BNO055_SIC_MATRIX_6_MSB_ADDR          0x50
#define BNO055_SIC_MATRIX_6_MSB_ADDR          0x50
#define BNO055_SIC_MATRIX_7_LSB_ADDR          0x51
#define BNO055_SIC_MATRIX_7_MSB_ADDR          0x52
#define BNO055_SIC_MATRIX_8_LSB_ADDR          0x53
#define BNO055_SIC_MATRIX_8_MSB_ADDR          0x54

/* Accelerometer Offset registers */
#define BNO055_ACCEL_OFFSET_X_LSB_ADDR               0x55
#define BNO055_ACCEL_OFFSET_X_MSB_ADDR               0x56
#define BNO055_ACCEL_OFFSET_Y_LSB_ADDR               0x57
#define BNO055_ACCEL_OFFSET_Y_MSB_ADDR               0x58
#define BNO055_ACCEL_OFFSET_Z_LSB_ADDR               0x59
#define BNO055_ACCEL_OFFSET_Z_MSB_ADDR               0x5A

/* Magnetometer Offset registers */
#define BNO055_MAG_OFFSET_X_LSB_ADDR                 0x5B
#define BNO055_MAG_OFFSET_X_MSB_ADDR                 0x5C
#define BNO055_MAG_OFFSET_Y_LSB_ADDR                 0x5D
#define BNO055_MAG_OFFSET_Y_MSB_ADDR                 0x5E
#define BNO055_MAG_OFFSET_Z_LSB_ADDR                 0x5F
#define BNO055_MAG_OFFSET_Z_MSB_ADDR                 0x60

/* Gyroscope Offset Registers*/
#define BNO055_GYRO_OFFSET_X_LSB_ADDR                0x61
#define BNO055_GYRO_OFFSET_X_MSB_ADDR                0x62
#define BNO055_GYRO_OFFSET_Y_LSB_ADDR                0x63
#define BNO055_GYRO_OFFSET_Y_MSB_ADDR                0x64
#define BNO055_GYRO_OFFSET_Z_LSB_ADDR                0x65
#define BNO055_GYRO_OFFSET_Z_MSB_ADDR                0x66

/* Radius registers */
#define BNO055_ACCEL_RADIUS_LSB_ADDR                 0x67
#define BNO055_ACCEL_RADIUS_MSB_ADDR                 0x68
#define BNO055_MAG_RADIUS_LSB_ADDR                   0x69
#define BNO055_MAG_RADIUS_MSB_ADDR                   0x6A

// Power Modes
#define BNO055_POWER_MODE_NORMAL                     0x00
#define BNO055_POWER_MODE_LOWPOWER                   0x01
#define BNO055_POWER_MODE_SUSPEND                    0x02

// Operation Modes
#define BNO055_OPERATION_MODE_CONFIG                 0x00
#define BNO055_OPERATION_MODE_ACCONLY                0x01
#define BNO055_OPERATION_MODE_MAGONLY                0x02
#define BNO055_OPERATION_MODE_GYRONLY                0x03
#define BNO055_OPERATION_MODE_ACCMAG                 0x04
#define BNO055_OPERATION_MODE_ACCGYRO                0x05
#define BNO055_OPERATION_MODE_MAGGYRO                0x06
#define BNO055_OPERATION_MODE_AMG                    0x07
#define BNO055_OPERATION_MODE_IMUPLUS                0x08
#define BNO055_OPERATION_MODE_COMPASS                0x09
#define BNO055_OPERATION_MODE_M4G                    0x0A
#define BNO055_OPERATION_MODE_NDOF_FMC_OFF           0x0B
#define BNO055_OPERATION_MODE_NDOF                   0x0C

// Axis Remap Configurations

#define BNO055_REMAP_CONFIG_P0                       0x21
#define BNO055_REMAP_CONFIG_P1                       0x24 // default
#define BNO055_REMAP_CONFIG_P2                       0x24
#define BNO055_REMAP_CONFIG_P3                       0x21
#define BNO055_REMAP_CONFIG_P4                       0x24
#define BNO055_REMAP_CONFIG_P5                       0x21
#define BNO055_REMAP_CONFIG_P6                       0x21
#define BNO055_REMAP_CONFIG_P7                       0x24

// Axis Remap Sign Configurations

#define BNO055_REMAP_SIGN_P0                         0x04
#define BNO055_REMAP_SIGN_P1                         0x00 // default
#define BNO055_REMAP_SIGN_P2                         0x06
#define BNO055_REMAP_SIGN_P3                         0x02
#define BNO055_REMAP_SIGN_P4                         0x03
#define BNO055_REMAP_SIGN_P5                         0x01
#define BNO055_REMAP_SIGN_P6                         0x07
#define BNO055_REMAP_SIGN_P7                         0x05

// Scale Factors for Physical Readings
#define BNO055_MAG_SCALE_FACTOR                      (1.0 / 16.0)
#define BNO055_GYRO_SCALE_FACTOR                     (1.0 / 900.0)
#define BNO055_EULER_SCALE_FACTOR                    (1.0 / 16.0)
#define BNO055_ACCEL_SCALE_FACTOR                    (1.0 / 100.0)
#define BNO055_GRAVITY_SCALE_FACTOR                  (1.0 / 100.0)
#define BNO055_LINEAR_ACCEL_SCALE_FACTOR             (1.0 / 100.0)
#define BNO055_QUATERNION_SCALE_FACTOR               (1.0 / (1 << 14))

namespace phil {
    
    class IMU {
    
    private:
        pal::I2C* i2c_;
        uint8_t address_;
        
        // Reads three sequential 16-bit values from the IMU and scales them by
        // the given scale factor
        HAL_StatusTypeDef ReadThreeAxisData(uint8_t baseAddress,
                                            float scaleFactor,
                                            float& x,
                                            float& y,
                                            float& z);
        
    public:
        IMU(pal::I2C* i2c, uint8_t address);
        
        // Runs the IMU initialization sequence
        HAL_StatusTypeDef Initialize();
        
        /** RAW DATA COLLECTION **/
        
        // Reads the temperature. Returns generated HAL error code
        HAL_StatusTypeDef GetTemperature(uint8_t* temperature);
        
        // Reads the magnetometer in uT. Returns generated HAL error code
        HAL_StatusTypeDef GetMagnetometerData(float& x, float& y, float& z);
        
        // Reads the gyroscope in rps. Returns generated HAL error code
        HAL_StatusTypeDef GetGyroscopeData(float& x, float& y, float& z);
        
        // Reads the accelerometer in m/s^2. Returns generated HAL error code
        HAL_StatusTypeDef GetAccelerationData(float& x, float& y, float& z);
        
        // Reads the gravity sensor in m/s^2. Returns generated HAL error code
        HAL_StatusTypeDef GetGravityData(float& x, float& y, float& z);
        
        // Reads the linear accelerometer in m/s^2. Returns generated HAL error
        // code
        HAL_StatusTypeDef GetLinearAccelerationData(float& x,
                                                    float& y,
                                                    float& z);
        
        /** MATHEMATICAL ENTITIES **/
        
        // Note that even though the Euler angles could be considered a three-
        // axis quantity, we often only need one axis and so it would allow for
        // faster code to only read the axis we need instead of all three every
        // time.
        
        // It is also worth noting that even though this format of orientation
        // is referred to by the IMU and its documentation as Euler angles,
        // they are actually the Tait-Bryan angles, a convention of expressing
        // the Euler angles.
        
        // Reads the Euler angle associated with roll. Returns generated HAL
        // error code
        HAL_StatusTypeDef GetRoll(float& roll);
        
        // Reads the Euler angle associated with pitch. Returns generated HAL
        // error code
        HAL_StatusTypeDef GetPitch(float& pitch);
        
        // Reads the Euler angle associated with heading. Returns generated HAL
        // error code
        HAL_StatusTypeDef GetHeading(float& heading);
        
        // Reads the current orientation as a quaternion. Returns the generated
        // HAL error code
        HAL_StatusTypeDef GetQuaternion(float& w,
                                        float& x,
                                        float& y,
                                        float& z);
    };
    
}

#endif
