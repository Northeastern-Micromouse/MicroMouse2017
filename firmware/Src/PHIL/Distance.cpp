#include "Distance.h"

#include <algorithm>

namespace {
    const int LSB_OFFSET = 27;
    const int LOOKUP_SIZE = 2087;
}

namespace phil {
    Distance::Distance(pal::Adc& adc, int chan, int pos)
        : adc_(adc)
        , chan_(chan)
        , pos_(pos)
    {
        adc_.RegisterChannel(chan_, pos_);
    }
    
    float Distance::GetDistance() {
        uint16_t adc_data = adc_.GetData(chan_);
        int index = std::max(LSB_OFFSET,
            std::min(static_cast<int>(adc_data),
                LSB_OFFSET + LOOKUP_SIZE));
        return DISTANCE_LOOKUP[index - LSB_OFFSET];
    }
}