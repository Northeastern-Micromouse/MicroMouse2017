#ifndef TIM_H
#define TIM_H

#include "stm32l4xx_hal.h"
#include <functional>

namespace pal {
    
    class Tim {
        
    private:
        TIM_HandleTypeDef* tim_;
        std::function<void()> callback_;
        
    public:
        static Tim* registry[];
        static void DelayUs(uint32_t us);
        
        Tim(TIM_HandleTypeDef* tim);
        HAL_StatusTypeDef SetTiming(uint16_t prescaler, uint16_t period);
        void Enable();
        void Disable();
        void SetCount(uint32_t count);
        uint32_t GetCount();
        bool GetUpdateFlag();
        void ClearUpdateFlag();
        
        void EnableWithInt();
        void DisableWithInt();
        void SetISR(std::function<void()> callback);
        void ISR();
        TIM_HandleTypeDef* GetHandle();
    };
    
}

//void TIM1_UP_TIM16_IRQHandler(void);

#endif
