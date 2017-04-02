#include "I2C.h"

pal::I2C::I2C(I2C_HandleTypeDef* i2c, uint32_t timeout) {
    i2c_ = i2c;
    timeout_ = timeout;
}

HAL_StatusTypeDef pal::I2C::Write(uint8_t device,
                                    uint8_t address,
                                    uint8_t data) {
    return Write(device, address, &data, 1);
}

HAL_StatusTypeDef pal::I2C::Write(uint8_t device,
                                    uint8_t address,
                                    uint8_t* data,
                                    uint16_t size) {
    return HAL_I2C_Mem_Write(i2c_, device,
                             address, I2C_MEMADD_SIZE_8BIT,
                             data, size,
                             timeout_);
}

HAL_StatusTypeDef pal::I2C::Read(uint8_t device,
                                    uint8_t address,
                                    uint8_t* data) {
    return Read(device, address, data, 1);
}

HAL_StatusTypeDef pal::I2C::Read(uint8_t device,
                                    uint8_t address,
                                    uint8_t* data,
                                    uint16_t size) {
    return HAL_I2C_Mem_Read(i2c_, device,
                            address, I2C_MEMADD_SIZE_8BIT,
                            data, size,
                            timeout_);
}
