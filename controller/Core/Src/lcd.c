/*
 * lcd.c
 *
 *  Created on: Apr 8, 2022
 *      Author: alan1
 */
#include "main.h"
#include "stdint.h"
#include "string.h"
#define LCD_ADDR 0x50
 extern I2C_HandleTypeDef hi2c2;
// LCD screen API

  // Set Cursor - 0xFE 0x45
  // row 0: 0x00 - 0x13 Mode: Manual/Autonomous
  // row 1: 0x40 - 0x53 Direction: F/L/R/B/S
  // row 2: 0x14 - 0x27
  // row 3: 0x54 - 0x67 Location: (x, y), N/E/S/W
  void lcdSetCursor(int row, int col){
	  uint8_t cmd_buf[3];
	  cmd_buf[0] = 0xFE;
	  cmd_buf[1] = 0x45;
	  switch(row){
	  case 0:
		  cmd_buf[2] = 0x00 + col;
		  HAL_I2C_Master_Transmit(&hi2c2, LCD_ADDR, cmd_buf, sizeof(cmd_buf), 2000);
		  break;

	  case 1:
	  		  cmd_buf[2] = 0x40 + col;
	  		  HAL_I2C_Master_Transmit(&hi2c2, LCD_ADDR, cmd_buf, sizeof(cmd_buf), 1000);
	  		  break;

	  case 2:
	  		  cmd_buf[2] = 0x14 + col;
	  		  HAL_I2C_Master_Transmit(&hi2c2, LCD_ADDR, cmd_buf, sizeof(cmd_buf), 1000);
	  		  break;

	  case 3:
	  		  cmd_buf[2] = 0x54 + col;
	  		  HAL_I2C_Master_Transmit(&hi2c2, LCD_ADDR, cmd_buf, sizeof(cmd_buf), 1000);
	  		  break;

		  break;
	  }
  }

  // Takes in character array
  void lcdWrite(uint8_t* word, uint8_t len){
	  HAL_I2C_Master_Transmit(&hi2c2, LCD_ADDR, word, len, 2000);
  }

  // Clear Screen - 0xFE 0x51
  void lcdClearScreen(){
	  uint8_t cmd_buf[2];
		cmd_buf[0] = 0xFE;
		cmd_buf[1] = 0x51;
		HAL_I2C_Master_Transmit(&hi2c2, LCD_ADDR, cmd_buf, sizeof(cmd_buf), 1000);
  }

  // Creates custom lcd menu
  void lcdDrawMenu(){
	  lcdClearScreen();
	  uint8_t mode[] = {'M', 'O', 'D', 'E', ':'};
	  uint8_t direction[] = {'D', 'I', 'R', 'E', 'C', 'T', 'I', 'O', 'N', ':'};
	  uint8_t location[] = {'L', 'O', 'C', 'A', 'T', 'I', 'O', 'N', ':'};

	  HAL_Delay(100);
	  lcdSetCursor(0, 0);
	  lcdWrite(&mode, sizeof(mode));
//	  lcdWrite(&(mode[4]));

	  lcdSetCursor(1, 0);
	  lcdWrite(&direction, sizeof(direction));

	  lcdSetCursor(2, 0);
	  lcdWrite(&location, sizeof(location));

  }

// backlight brightness - 0xFE 0x53
  // inputs are values 1-8, 8 being brightest
  void lcdSetBrightness(uint8_t brightness){
	  uint8_t cmd_buf[3];
	  cmd_buf[0] = 0xFE;
	  cmd_buf[1] = 0x53;
	  cmd_buf[2] = brightness;
	  HAL_I2C_Master_Transmit(&hi2c2, LCD_ADDR, cmd_buf, sizeof(cmd_buf), 1000);
  }
