#pragma once
#include "SensorLookupTables.h"
#include "ADC.h"

namespace phil {
    class Reflectance {
    public:
        Reflectance(pal::Adc& adc, int chan, int pos, int lookup);
        //Reflectance(pal::Adc&& adc, int chan, int pos);
        float GetDistance(bool* max);
    private:
        pal::Adc& adc_;
        int chan_, pos_;
        int lookup_;
    };
}