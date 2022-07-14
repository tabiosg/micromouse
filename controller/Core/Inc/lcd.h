/*
 * lcd.h
 *
 *  Created on: Apr 8, 2022
 *      Author: alan1
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_

  void lcdClearScreen();
  void lcdSetCursor(int row, int col);
  void lcdWrite(uint8_t* word, uint8_t len);
  void lcdDrawMenu();
  void lcdSetBrightness(uint8_t brightness);



#endif /* INC_LCD_H_ */
