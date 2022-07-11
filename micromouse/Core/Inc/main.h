/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
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
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

#define UART_buffer_size 1


extern uint8_t UART6_rxBuffer[];
extern char current_manual_command;
extern char requested_manual_command;

extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart6;

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SONIC_ECHO_Pin GPIO_PIN_1
#define SONIC_ECHO_GPIO_Port GPIOA
#define UART_PRINT_USB_Pin GPIO_PIN_2
#define UART_PRINT_USB_GPIO_Port GPIOA
#define YELLOW_LED_Pin GPIO_PIN_5
#define YELLOW_LED_GPIO_Port GPIOA
#define PUSH_BUTTON_Pin GPIO_PIN_6
#define PUSH_BUTTON_GPIO_Port GPIOA
#define RIGHT_PWM_Pin GPIO_PIN_7
#define RIGHT_PWM_GPIO_Port GPIOC
#define RIGHT_DIR_Pin GPIO_PIN_8
#define RIGHT_DIR_GPIO_Port GPIOA
#define LEFT_DIR_Pin GPIO_PIN_9
#define LEFT_DIR_GPIO_Port GPIOA
#define SERVO_PWM_Pin GPIO_PIN_15
#define SERVO_PWM_GPIO_Port GPIOA
#define LEFT_PWM_Pin GPIO_PIN_6
#define LEFT_PWM_GPIO_Port GPIOB
#define SONIC_TRIGGER_Pin GPIO_PIN_8
#define SONIC_TRIGGER_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

extern TIM_HandleTypeDef htim5;

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
