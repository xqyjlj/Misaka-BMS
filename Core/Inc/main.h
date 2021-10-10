/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

#include "stm32f1xx_ll_adc.h"
#include "stm32f1xx_ll_dma.h"
#include "stm32f1xx_ll_iwdg.h"
#include "stm32f1xx_ll_rcc.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_system.h"
#include "stm32f1xx_ll_exti.h"
#include "stm32f1xx_ll_cortex.h"
#include "stm32f1xx_ll_utils.h"
#include "stm32f1xx_ll_pwr.h"
#include "stm32f1xx_ll_spi.h"
#include "stm32f1xx_ll_tim.h"
#include "stm32f1xx_ll_usart.h"
#include "stm32f1xx_ll_gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define RGB_R_Pin LL_GPIO_PIN_13
#define RGB_R_GPIO_Port GPIOC
#define RGB_G_Pin LL_GPIO_PIN_14
#define RGB_G_GPIO_Port GPIOC
#define RGB_B_Pin LL_GPIO_PIN_15
#define RGB_B_GPIO_Port GPIOC
#define CHARGE_SIGNAL_Pin LL_GPIO_PIN_2
#define CHARGE_SIGNAL_GPIO_Port GPIOB
#define ERROR_SIGNAL_Pin LL_GPIO_PIN_12
#define ERROR_SIGNAL_GPIO_Port GPIOB
#define UNLOCK_SIGNAL_Pin LL_GPIO_PIN_13
#define UNLOCK_SIGNAL_GPIO_Port GPIOB
#define CH443K_SEL_Pin LL_GPIO_PIN_14
#define CH443K_SEL_GPIO_Port GPIOB
#define CH444G_IN0_Pin LL_GPIO_PIN_15
#define CH444G_IN0_GPIO_Port GPIOB
#define CH444G_IN1_Pin LL_GPIO_PIN_8
#define CH444G_IN1_GPIO_Port GPIOA
#define LTC6811_CS_Pin LL_GPIO_PIN_15
#define LTC6811_CS_GPIO_Port GPIOA
#define I2C_SCL_Pin LL_GPIO_PIN_6
#define I2C_SCL_GPIO_Port GPIOB
#define I2C_SDA_Pin LL_GPIO_PIN_7
#define I2C_SDA_GPIO_Port GPIOB
#define BEEP_Pin LL_GPIO_PIN_8
#define BEEP_GPIO_Port GPIOB
#define DISCHARGE_SIGNAL_Pin LL_GPIO_PIN_9
#define DISCHARGE_SIGNAL_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
