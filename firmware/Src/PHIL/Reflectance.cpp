#include "Reflectance.h"

#include <algorithm>

namespace {
    int LSB_OFFSET[3] = { 3204, 2850, 3155 };
    int LOOKUP_SIZE[3] = { 767, 1109, 826 };
}

namespace phil {
    Reflectance::Reflectance(pal::Adc& adc, int chan, int pos, int lookup) :
        adc_(adc), chan_(chan), pos_(pos), lookup_(lookup)
    {
        adc_.RegisterChannel(chan_, pos_);
    }
    
    /*Reflectance::Reflectance(pal::Adc&& adc, int chan, int pos)
        : adc_(std::move(adc))
        , chan_(chan)
        , pos_(pos) {}
    */
    
    float Reflectance::GetDistance(bool* max) {
        uint16_t adc_data = adc_.GetData(chan_);
        int index = std::max(LSB_OFFSET[lookup_], std::min(static_cast<int>(adc_data),
            LSB_OFFSET[lookup_] + LOOKUP_SIZE[lookup_]));
        if (index == LSB_OFFSET[lookup_] + LOOKUP_SIZE[lookup_]) {
            *max = true;
        }
        switch (lookup_) {
        case 0:
            return REFLECTANCE_LOOKUP_LEFT[index - LSB_OFFSET[lookup_]];
        case 1:
            return REFLECTANCE_LOOKUP_RIGHT[index - LSB_OFFSET[lookup_]];
        case 2:
            return REFLECTANCE_LOOKUP_FRONT[index - LSB_OFFSET[lookup_]];
        default:
            return -1;
        }
    }
}