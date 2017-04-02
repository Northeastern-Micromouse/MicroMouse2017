#include "IMU.h"

phil::IMU::IMU(pal::I2C* i2c, uint8_t address) {
    i2c_ = i2c;
    address_ = address;
}

HAL_StatusTypeDef phil::IMU::ReadThreeAxisData(
    uint8_t baseAddress, 
    float scaleFactor,
    float& x,
    float& y,
    float& z) {
        
    uint8_t data[6];
    HAL_StatusTypeDef error = i2c_->Read(address_, 
                                         baseAddress, 
                                         data, 
                                         6*sizeof(uint8_t));
                                                     
    if (error) {
        return error;
    }
       
    x = ((data[1] << 8) | data[0]) * scaleFactor;
    y = ((data[3] << 8) | data[2]) * scaleFactor;
    z = ((data[5] << 8) | data[4]) * scaleFactor;
        
    return HAL_OK;
}
        

HAL_StatusTypeDef phil::IMU::Initialize() {
    
    HAL_StatusTypeDef error;
    
    // First, set the operating mode to configuration
    error = i2c_->Write(address_, 
                        BNO055_OPR_MODE_ADDR, 
                        BNO055_OPERATION_MODE_CONFIG);
    if (error) {
        return error;
    }
    
    // Reset the chip
    error = i2c_->Write(address_, BNO055_SYS_TRIGGER_ADDR, 0x20);
    
    if (error) {
        return error;
    }
    
    // Wait for it to come back online
    uint8_t response;
    
    do {
        
        HAL_Delay(100);
		
        error = i2c_->Read(address_, BNO055_CHIP_ID_ADDR, &response);
        
        // we don't want to return based on error here since the chip will
		// return an error if we try to read from it before it's ready
        
    } while (response != BNO055_ID);
	
    HAL_Delay(50);
    
    // Set power mode to normal
    error = i2c_->Write(address_,
                        BNO055_PWR_MODE_ADDR,
                        BNO055_POWER_MODE_NORMAL);
    
    if (error) {
        return error;
    }
    
    HAL_Delay(10);
    
    // Write 0 to page ID
    
    error = i2c_->Write(address_, BNO055_PAGE_ID_ADDR, 0x00);
    
    if (error) {
        return error;
    }
    
    // Write 0 to system trigger
    
    error = i2c_->Write(address_, BNO055_SYS_TRIGGER_ADDR, 0x00);
    
    if (error) {
        return error;
    }
    
    HAL_Delay(10);
    
    // Set mode to NDOF
    error = i2c_->Write(address_,
                        BNO055_OPR_MODE_ADDR,
                        BNO055_OPERATION_MODE_NDOF);
    
    if (error) {
        return error;
    }
    
    HAL_Delay(20);
    
    return HAL_OK;
}

HAL_StatusTypeDef phil::IMU::GetTemperature(uint8_t* temperature) {
    return i2c_->Read(address_, BNO055_TEMP_ADDR, temperature);
}

HAL_StatusTypeDef phil::IMU::GetMagnetometerData(
    float& x,
    float& y,
    float& z) {
  
    return ReadThreeAxisData(BNO055_MAG_DATA_X_LSB_ADDR,
                             BNO055_MAG_SCALE_FACTOR,
                             x, y, z);
}

HAL_StatusTypeDef phil::IMU::GetGyroscopeData(float& x, float& y, float& z) {
    
    return ReadThreeAxisData(BNO055_GYRO_DATA_X_LSB_ADDR,
                             BNO055_GYRO_SCALE_FACTOR,
                             x, y, z);
}

HAL_StatusTypeDef phil::IMU::GetAccelerationData(
    float& x,
    float& y,
    float& z) {
    
    return ReadThreeAxisData(BNO055_ACCEL_DATA_X_LSB_ADDR,
                             BNO055_ACCEL_SCALE_FACTOR,
                             x, y, z);
}

HAL_StatusTypeDef phil::IMU::GetGravityData(float& x, float& y, float& z) {
    
    return ReadThreeAxisData(BNO055_GRAVITY_DATA_X_LSB_ADDR,
                             BNO055_GRAVITY_SCALE_FACTOR,
                             x, y, z);
}

HAL_StatusTypeDef phil::IMU::GetLinearAccelerationData(
    float& x,
    float& y,
    float& z) {
        
    return ReadThreeAxisData(BNO055_LINEAR_ACCEL_DATA_X_LSB_ADDR,
                             BNO055_LINEAR_ACCEL_SCALE_FACTOR,
                             x, y, z);
}

HAL_StatusTypeDef phil::IMU::GetRoll(float& roll) {
    
    uint8_t data[2];
    HAL_StatusTypeDef error = i2c_->Read(address_, 
                                         BNO055_EULER_R_LSB_ADDR, 
                                         data, 
                                         2);
    
    if (error) {
        return error;
    }
    
    roll = ((data[1] << 8) | data[0]) * BNO055_EULER_SCALE_FACTOR;
    
    return HAL_OK;
}

HAL_StatusTypeDef phil::IMU::GetPitch(float& pitch) {
    
    uint8_t data[2];
    HAL_StatusTypeDef error = i2c_->Read(address_, 
                                         BNO055_EULER_P_LSB_ADDR, 
                                         data, 
                                         2);
    
    if (error) {
        return error;
    }
    
    pitch = ((data[1] << 8) | data[0]) * BNO055_EULER_SCALE_FACTOR;
    
    return HAL_OK;
}

HAL_StatusTypeDef phil::IMU::GetHeading(float& heading) {
    uint8_t data[2];
    HAL_StatusTypeDef error = i2c_->Read(address_, 
                                         BNO055_EULER_H_LSB_ADDR, 
                                         data, 
                                         2);
    
    if (error) {
        return error;
    }
    
    heading = ((data[1] << 8) | data[0]) * BNO055_EULER_SCALE_FACTOR;
    
    return HAL_OK;
}

HAL_StatusTypeDef phil::IMU::GetQuaternion(
    float& w,
    float& x,
    float& y,
    float& z) {
        
    uint8_t data[8];
    HAL_StatusTypeDef error = i2c_->Read(address_, 
                                         BNO055_QUATERNION_DATA_W_LSB_ADDR, 
                                         data, 
                                         8);
    
    if (error) {
        return error;
    }
    
    w = ((data[1] << 8) | data[0]) * BNO055_QUATERNION_SCALE_FACTOR;
    x = ((data[3] << 8) | data[2]) * BNO055_QUATERNION_SCALE_FACTOR;
    y = ((data[5] << 8) | data[4]) * BNO055_QUATERNION_SCALE_FACTOR;
    z = ((data[7] << 8) | data[6]) * BNO055_QUATERNION_SCALE_FACTOR;
    
    return HAL_OK;
}
