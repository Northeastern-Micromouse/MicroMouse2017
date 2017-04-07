#include "Reflectance.h"

#include <algorithm>

namespace {
    const int LSB_OFFSET = 3179;
    const int LOOKUP_SIZE = 801;
}

namespace phil {
    Reflectance::Reflectance(pal::Adc& adc, int chan, int pos) :
        adc_(adc), chan_(chan), pos_(pos)
    {
        adc_.RegisterChannel(chan_, pos_);
    }
    
    /*Reflectance::Reflectance(pal::Adc&& adc, int chan, int pos)
        : adc_(std::move(adc))
        , chan_(chan)
        , pos_(pos) {}
    */
    
    float Reflectance::GetDistance() {
        uint16_t adc_data = adc_.GetData(chan_);
        int index = std::max(LSB_OFFSET, std::min(static_cast<int>(adc_data),
            LSB_OFFSET + LOOKUP_SIZE));
        return REFLECTANCE_LOOKUP[index - LSB_OFFSET];
    }
}