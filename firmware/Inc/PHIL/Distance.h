#pragma once
#include "SensorLookupTables.h"
#include "ADC.h"

namespace phil {
    class Distance {
    public:
        Distance(pal::Adc& adc, int chan, int pos);
        float GetDistance();
    private:
        pal::Adc& adc_;
        int chan_, pos_;
    };
}