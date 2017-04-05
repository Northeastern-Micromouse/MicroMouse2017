#pragma once

#include "stm32l4xx_hal_adc.h"

namespace pal {
    
    class Adc {
    public:
        explicit Adc(ADC_HandleTypeDef adc_handle, size_t num_channels);
        ~Adc();
        uint16_t GetData(int channel);
        void RegisterChannel(int channel, int pos);
    private:
        uint16_t* p_data_;
        int p_chan_registry_[16];
        ADC_HandleTypeDef adc_handle_;
    };

}