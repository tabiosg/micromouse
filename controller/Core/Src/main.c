/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#define LCD_ADDR 0x50
#define UART_buffer_size 20

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
 I2C_HandleTypeDef hi2c2;

UART_HandleTypeDef huart2;
UART_HandleTypeDef huart6;

/* USER CODE BEGIN PV */
uint8_t UART6_rxBuffer[UART_buffer_size] = {0};
uint8_t received_data[UART_buffer_size];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_I2C2_Init(void);
static void MX_USART6_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	// received_data[0] = UART6_rxBuffer[0];
	memcpy(received_data, UART6_rxBuffer, UART_buffer_size);
    HAL_UART_Receive_IT(&huart6, UART6_rxBuffer, UART_buffer_size);
}


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_I2C2_Init();
  MX_USART6_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_UART_Receive_IT(&huart6, UART6_rxBuffer, UART_buffer_size);

  lcdSetBrightness(5);
  lcdDrawMenu();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  uint8_t forward[] = {'F', 'O', 'R', 'W', 'A', 'R', 'D', ' '};
  uint8_t backward[] = {'B', 'A', 'C', 'K', 'W', 'A', 'R', 'D'};
  uint8_t left[] = {'L', 'E', 'F', 'T', ' ', ' ', ' ', ' '};
  uint8_t right[] = {'R', 'I', 'G', 'H', 'T', ' ', ' ', ' '};
  uint8_t stopped[] = {'S', 'T', 'O', 'P', 'P', 'E', 'D', ' '};

  uint8_t manual[] = {'M', 'A', 'N', 'U', 'A', 'L', ' ', ' ', ' ', ' '};
  uint8_t autonomous[] = {'A', 'U', 'T', 'O', 'N', 'O', 'M', 'O', 'U', 'S'};
  uint8_t completed[] = {'C', 'O', 'M', 'P', 'L', 'E', 'T', 'E', 'D', ' '};

  uint8_t blankline[] = {' ', ' ', ' ', ' ', ' ', ' ', ' '};

  uint32_t row_ports[] = {ROW0_GPIO_Port, ROW1_GPIO_Port, ROW2_GPIO_Port, ROW3_GPIO_Port};
  uint32_t row_pins[] = {ROW0_Pin, ROW1_Pin, ROW2_Pin, ROW3_Pin};

  uint32_t col_ports[] = {COL0_GPIO_Port, COL1_GPIO_Port, COL2_GPIO_Port, COL3_GPIO_Port};
  uint32_t col_pins[] = {COL0_Pin, COL1_Pin, COL2_Pin, COL3_Pin};

  uint8_t button = '*';

  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	  // NOTE: With this method, you cannot press the same button twice.
	  // keypad loop

	  // steady state
	  for(uint8_t i = 0; i < 4; i++){
		  HAL_GPIO_WritePin(col_ports[i], col_pins[i], GPIO_PIN_SET);
	  }
	  // read if any input pins are high
	  uint8_t active_row = 5;
	  for(uint8_t i = 0; i < 4; i++){
		  if(HAL_GPIO_ReadPin(row_ports[i], row_pins[i])){
			  active_row = i;
		  }
	  }

	  // only continue if a button is pressed
	  if(active_row < 5){
		  // read and check activated rows
		  // do this by outputting 1-hot on col pins
		  uint8_t active_col = 5;
		  for(uint8_t i = 0; i < 4; i++){
			  // set all col pins to 0
			  for(int j = 0; j < 4; j++){
				  HAL_GPIO_WritePin(col_ports[j], col_pins[j], GPIO_PIN_RESET);
			  }
			  HAL_GPIO_WritePin(col_ports[i], col_pins[i], GPIO_PIN_SET);

			  // if corresponding column is pressed, the active row will be active again
			  uint8_t col = HAL_GPIO_ReadPin(row_ports[active_row], row_pins[active_row]);
			  if(col){
				  active_col = i;
			  }
		  }

		  // now we have the active row and column, we know the button pressed.
		  uint8_t buttons[4][4] = {{'1', '2', '3', 'A'}, {'4', '5', '6', 'B'}, {'7', '8', '9', 'C'}, {'*', '0', '#', 'D'}};
		  uint8_t new_button = buttons[active_row][active_col];
		  if(new_button != button){
			  HAL_UART_Transmit(&huart6, &new_button, sizeof(new_button), 200);
			  button = new_button;
		  }

	  }
	  // end keypad loop


	  char tag = received_data[0];

	  switch(tag){

	  	  // Handle Direction line
	  	  case '$':
	  		  lcdSetCursor(1, 11);
	  		  char direction = received_data[1];

	  		  if(direction == 'L'){
	  			lcdWrite(&left, sizeof(left));
	  		  }
	  	  	  else if(direction == 'R'){
	  	  		lcdWrite(&right, sizeof(right));
	  	  	  }
	  		  else if(direction == 'F'){
	  			lcdWrite(&forward, sizeof(forward));
	  		  }
	  		  else if(direction == 'B'){
	  			lcdWrite(&backward, sizeof(backward));
	  		  }
	  		  else if(direction == 'S'){
	  			lcdWrite(&stopped, sizeof(stopped));
	   		  }
	  		  break;

	  	  // Handle Mode line
	  	  case '&':
	  		  	 lcdSetCursor(0,7);
	  		  	 char mode = received_data[1];

	  		  	 if(mode == 'M'){
	  		  		 lcdWrite(&manual, sizeof(manual));
	  		  		 // Clear location
	  		  		 lcdSetCursor(2, 10);
	  		  		 lcdWrite(&blankline, sizeof(blankline));
	  		  	 }
	  		  	 else if(mode == 'A'){
	  		  		 lcdWrite(&autonomous, sizeof(autonomous));
	  		  	 }
	  		  	 else if(mode == 'C'){
	  		  		 lcdWrite(&completed, sizeof(completed));
	  		  	 }
	  		  break;

	  	  // Handle Location line
	  	  case '@':
	  		  lcdSetCursor(2, 10);
	  		  uint8_t buf[20];
	  		  memcpy(buf, received_data, sizeof(received_data));
	  		  uint8_t x = buf[1];
	  		  uint8_t y = buf[3];
	  		  uint8_t facing = buf[5];
	  		  uint8_t dir[4] = {'N', 'E', 'S', 'W'};
	  		  int index = facing - '0';
	  		  uint8_t location[] = {'(', x, ',', y, ')', ' ', dir[index]};
	  		  lcdWrite(&location, sizeof(location));
	  		  break;

	  	  // Handle wall detection line
	  	  case '%': ; //empty statement
	  		char d = received_data[1];
	  		char di[] = {received_data[6]};
	  		  if(d == 'L'){
	  			lcdSetCursor(3,4);
	  			lcdWrite(&di, sizeof(di));
	  		  }
	  		  else if(d == 'F'){
	  			lcdSetCursor(3,11);
	  			di[0] = received_data[7];
	  			lcdWrite(&di, sizeof(di));
	  		  }
	  		  else if(d == 'R'){
	  			lcdSetCursor(3,18);
	  			di[0] = received_data[7];
	  			lcdWrite(&di, sizeof(di));
	  		  }
	  		  break;

	  	  default:
	  		  break;

	  }

	  // 50Hz
	  HAL_Delay(20);


  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C2_Init(void)
{

  /* USER CODE BEGIN I2C2_Init 0 */

  /* USER CODE END I2C2_Init 0 */

  /* USER CODE BEGIN I2C2_Init 1 */

  /* USER CODE END I2C2_Init 1 */
  hi2c2.Instance = I2C2;
  hi2c2.Init.ClockSpeed = 30000;
  hi2c2.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c2.Init.OwnAddress1 = 0;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C2_Init 2 */

  /* USER CODE END I2C2_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief USART6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART6_UART_Init(void)
{

  /* USER CODE BEGIN USART6_Init 0 */

  /* USER CODE END USART6_Init 0 */

  /* USER CODE BEGIN USART6_Init 1 */

  /* USER CODE END USART6_Init 1 */
  huart6.Instance = USART6;
  huart6.Init.BaudRate = 9600;
  huart6.Init.WordLength = UART_WORDLENGTH_8B;
  huart6.Init.StopBits = UART_STOPBITS_1;
  huart6.Init.Parity = UART_PARITY_NONE;
  huart6.Init.Mode = UART_MODE_TX_RX;
  huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart6.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart6) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART6_Init 2 */

  /* USER CODE END USART6_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LD2_Pin|COL0_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, COL1_Pin|COL2_Pin|COL3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : ROW0_Pin ROW1_Pin ROW2_Pin ROW3_Pin */
  GPIO_InitStruct.Pin = ROW0_Pin|ROW1_Pin|ROW2_Pin|ROW3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : LD2_Pin COL0_Pin */
  GPIO_InitStruct.Pin = LD2_Pin|COL0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : COL1_Pin COL2_Pin COL3_Pin */
  GPIO_InitStruct.Pin = COL1_Pin|COL2_Pin|COL3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
