/**
  ******************************************************************************
  * File Name          : main.h
  * Description        : This file contains the common defines of the application
  ******************************************************************************
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H
  /* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define OSC32_IN_Pin GPIO_PIN_14
#define OSC32_IN_GPIO_Port GPIOC
#define OSC32_OUT_Pin GPIO_PIN_15
#define OSC32_OUT_GPIO_Port GPIOC
#define S_MOTOR_A_DIR_Pin GPIO_PIN_0
#define S_MOTOR_A_DIR_GPIO_Port GPIOC
#define S_MOTOR_A_STEP_Pin GPIO_PIN_1
#define S_MOTOR_A_STEP_GPIO_Port GPIOC
#define DRIVER_RSTn_Pin GPIO_PIN_2
#define DRIVER_RSTn_GPIO_Port GPIOC
#define REFL_DIST_C_OUT_Pin GPIO_PIN_3
#define REFL_DIST_C_OUT_GPIO_Port GPIOC
#define GP2Y_DIST_A_OUT_Pin GPIO_PIN_0
#define GP2Y_DIST_A_OUT_GPIO_Port GPIOA
#define GP2Y_DIST_B_OUT_Pin GPIO_PIN_1
#define GP2Y_DIST_B_OUT_GPIO_Port GPIOA
#define REFL_DIST_A_OUT_Pin GPIO_PIN_2
#define REFL_DIST_A_OUT_GPIO_Port GPIOA
#define REFL_DIST_B_OUT_Pin GPIO_PIN_3
#define REFL_DIST_B_OUT_GPIO_Port GPIOA
#define REFL_DIST_D_OUT_Pin GPIO_PIN_4
#define REFL_DIST_D_OUT_GPIO_Port GPIOC
#define DC_M2_IN1_Pin GPIO_PIN_5
#define DC_M2_IN1_GPIO_Port GPIOC
#define S_MOTOR_B_DIR_Pin GPIO_PIN_0
#define S_MOTOR_B_DIR_GPIO_Port GPIOB
#define S_MOTOR_B_STEP_Pin GPIO_PIN_1
#define S_MOTOR_B_STEP_GPIO_Port GPIOB
#define DIST_INT2_Pin GPIO_PIN_2
#define DIST_INT2_GPIO_Port GPIOB
#define BNO_RSTn_Pin GPIO_PIN_13
#define BNO_RSTn_GPIO_Port GPIOB
#define DIST_INT1_Pin GPIO_PIN_14
#define DIST_INT1_GPIO_Port GPIOB
#define DC_M2_IN2_Pin GPIO_PIN_6
#define DC_M2_IN2_GPIO_Port GPIOC
#define DC_M1_IN1_Pin GPIO_PIN_7
#define DC_M1_IN1_GPIO_Port GPIOC
#define SD_DAT0_Pin GPIO_PIN_8
#define SD_DAT0_GPIO_Port GPIOC
#define SD_DAT1_Pin GPIO_PIN_9
#define SD_DAT1_GPIO_Port GPIOC
#define SD_CARD_DETECT_Pin GPIO_PIN_8
#define SD_CARD_DETECT_GPIO_Port GPIOA
#define IMU_INTn_Pin GPIO_PIN_9
#define IMU_INTn_GPIO_Port GPIOA
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define SD_DAT2_Pin GPIO_PIN_10
#define SD_DAT2_GPIO_Port GPIOC
#define SD_DAT3_Pin GPIO_PIN_11
#define SD_DAT3_GPIO_Port GPIOC
#define SD_CLOCK_Pin GPIO_PIN_12
#define SD_CLOCK_GPIO_Port GPIOC
#define SD_CMD_Pin GPIO_PIN_2
#define SD_CMD_GPIO_Port GPIOD
#define ENCODER2_OUT_A_Pin GPIO_PIN_4
#define ENCODER2_OUT_A_GPIO_Port GPIOB
#define ENCODER2_OUT_B_Pin GPIO_PIN_5
#define ENCODER2_OUT_B_GPIO_Port GPIOB
#define ENCODER1_OUT_A_Pin GPIO_PIN_6
#define ENCODER1_OUT_A_GPIO_Port GPIOB
#define ENCODER1_OUT_B_Pin GPIO_PIN_7
#define ENCODER1_OUT_B_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */
int firmware_init(void);
/* USER CODE END Private defines */

/**
  * @}
  */ 

/**
  * @}
*/ 

#endif /* __MAIN_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
