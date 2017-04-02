#ifndef I2C_H
#define I2C_H

#ifdef __cplusplus
extern "C" {
    #include "stm32l4xx_hal.h"
}
#endif

namespace pal {
    
    class I2C {
    
    private:
        I2C_HandleTypeDef* i2c_;
        uint32_t timeout_;
        
    public:
        I2C(I2C_HandleTypeDef* i2c, uint32_t timeout);
        HAL_StatusTypeDef Write(uint8_t device, uint8_t address, uint8_t data);
        HAL_StatusTypeDef Write(uint8_t device, uint8_t address, uint8_t* data, uint16_t size);
        HAL_StatusTypeDef Read(uint8_t device, uint8_t address, uint8_t* data);
        HAL_StatusTypeDef Read(uint8_t device, uint8_t address, uint8_t* data, uint16_t size);
    };
    
}

#endif