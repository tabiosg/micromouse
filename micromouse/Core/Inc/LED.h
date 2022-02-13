#ifndef INC_LED_H_
#define INC_LED_H_

typedef enum
{
	Red, Blue, Green, Yellow
} LED_color;

typedef enum
{
	Off, On
} LED_state;

void turn_LEDs_all(LED_state state);

void turn_LED(LED_color col, LED_state state);

void turn_off_LED_color(LED_color col);

void turn_on_LED_color(LED_color col);

#endif /* INC_MOUSE_H_ */
