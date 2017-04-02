#include "TIM.h"

pal::Tim* pal::Tim::registry[] = { };

void pal::Tim::DelayUs(uint32_t us) {
    // Thanks to:
    // https://stm32f4-discovery.net/2015/07/hal-library-3-delay-for-stm32fxxx/
    uint32_t start = DWT->CYCCNT;
    
    /* Go to number of cycles for system */
    us *= (HAL_RCC_GetHCLKFreq() / 1000000);
    
    /* Delay till end */
    while ((DWT->CYCCNT - start) < us);
}

pal::Tim::Tim(TIM_HandleTypeDef* tim) {
    tim_ = tim;
    
    Disable();
    
    // Enter the object into the class' registry
    if (tim->Instance == TIM1) {
        pal::Tim::registry[0] = this;
    }
    
    else if (tim->Instance == TIM2) {
        pal::Tim::registry[1] = this;
    }
    
    else if (tim->Instance == TIM3) {
        pal::Tim::registry[2] = this;
    }
    
    else if (tim->Instance == TIM4) {
        pal::Tim::registry[3] = this;
    }
    
    else if (tim->Instance == TIM5) {
        pal::Tim::registry[4] = this;
    }
    
    else if (tim->Instance == TIM6) {
        pal::Tim::registry[5] = this;
    }
    else if (tim->Instance == TIM7) {
        pal::Tim::registry[6] = this;
    }
    
    else if (tim->Instance == TIM8) {
        pal::Tim::registry[7] = this;
    }
    
    else if (tim->Instance == TIM15) {
        pal::Tim::registry[8] = this;
    }
    
    else if (tim->Instance == TIM16) {
        pal::Tim::registry[9] = this;
    }
    
    else if (tim->Instance == TIM17) {
        pal::Tim::registry[10] = this;
    }
}

HAL_StatusTypeDef pal::Tim::SetTiming(uint16_t prescaler, uint16_t period) {
    tim_->Init.Prescaler = prescaler;
    tim_->Init.Period = period;
    return HAL_TIM_Base_Init(tim_);
}

void pal::Tim::Enable() {
    HAL_TIM_Base_Start_IT(tim_);
}

void pal::Tim::Disable() {
    HAL_TIM_Base_Stop_IT(tim_);
}

void pal::Tim::SetISR(std::function<void()> callback) {
    callback_ = callback;
}

void pal::Tim::ISR() {
    callback_();
}

TIM_HandleTypeDef* pal::Tim::GetHandle() {
    return tim_;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM1) {
        pal::Tim::registry[0]->ISR();
    }
    
    else if (htim->Instance == TIM2) {
        pal::Tim::registry[1]->ISR();
    }
    
    else if (htim->Instance == TIM3) {
        pal::Tim::registry[2]->ISR();
    }
    
    else if (htim->Instance == TIM4) {
        pal::Tim::registry[3]->ISR();
    }
    
    else if (htim->Instance == TIM5) {
        pal::Tim::registry[4]->ISR();
    }
    
    else if (htim->Instance == TIM6) {
        pal::Tim::registry[5]->ISR();
    }
    
    else if (htim->Instance == TIM7) {
        pal::Tim::registry[6]->ISR();
    }
    
    else if (htim->Instance == TIM8) {
        pal::Tim::registry[7]->ISR();
    }
    
    else if (htim->Instance == TIM15) {
        pal::Tim::registry[8]->ISR();
    }
    
    else if (htim->Instance == TIM16) {
        pal::Tim::registry[9]->ISR();
    }
    
    else if (htim->Instance == TIM17) {
        pal::Tim::registry[10]->ISR();
    }
}
