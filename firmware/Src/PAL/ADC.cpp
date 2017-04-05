#include "ADC.h"

#include <cstdint>

namespace {
    uint32_t ADC_DATA_SIZE = 16;
}

namespace pal {
    
    Adc::Adc(ADC_HandleTypeDef adc_handle, size_t num_channels) {
        adc_handle_ = adc_handle;
        p_data_ = new uint16_t[num_channels];
        HAL_ADC_Start_DMA(&adc_handle_, reinterpret_cast<uint32_t*>(p_data_), ADC_DATA_SIZE);
    }
 
    Adc::~Adc() {
        HAL_ADC_Stop_DMA(&adc_handle_);
    }
 
    uint16_t Adc::GetData(int channel) {
        return p_data_[p_chan_registry_[channel]];
    }
    
    void Adc::RegisterChannel(int channel, int pos) {
        p_chan_registry_[channel] = pos;
    }
}