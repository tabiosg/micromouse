#include "LED.h"

void turn_LEDs_all(LED_state state)
{
	LED_color color_first = Red;
	LED_color color_last = Yellow;

	for(int led_col = color_first; led_col <= color_last; ++led_col)
	{
		turn_LED(led_col, state);
	}  // for()
}  // turn_LEDs_all(LED_state state)

void turn_LED(LED_color col, LED_state state)
{
	switch(state)
	{
	case Off:
		turn_off_LED_color(col);
		return;
	case On:
		turn_on_LED_color(col);
	}
}  // turn_LED(LED_color col, LED_state state)

void turn_off_LED_color(LED_color col)
{
	// TODO - turn off LED_color
	switch(col)
	{
	case Red:
		return;
	case Blue:
		return;
	case Green:
		return;
	case Yellow:
		HAL_GPIO_WritePin(YELLOW_LED_GPIO_Port, YELLOW_LED_Pin, GPIO_PIN_SET);
		return;
	}  // switch(col)
}  // turn_off_LED_color(LED_color col)

void turn_on_LED_color(LED_color col)
{
	// TODO - turn off LED_color
	switch(col)
	{
	case Red:
		return;
	case Blue:
		return;
	case Green:
		return;
	case Yellow:
		HAL_GPIO_WritePin(YELLOW_LED_GPIO_Port, YELLOW_LED_Pin, GPIO_PIN_RESET);
		return;
	}  // switch(col)
}  // turn_on_LED_color(LED_color col)
