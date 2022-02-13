#include "algorithm.h"

uint8_t determine_algorithm()
{
	// TODO - fix once begin implementing different algorithms
	uint8_t determined_algorithm = is_switch_on();

	switch (determined_algorithm)
	{
	case 0:
		return Hug_Left_Algo;
	case 1:
		return Flood_Fill_Algo;
	}  // switch()

	return -1;
}

void do_search_algorithm(algorithm_type algo)
{
	//  Turn Blue LED on to indicate searching for a path.
	turn_LEDs_all(Off);
	turn_LED(Red, On);
	turn_LED(Blue, On);

	switch (algo)
	{
	case Hug_Left_Algo:
		do_hug_left_algorithm();
		return;
	case Flood_Fill_Algo:
		return; // TODO
	}  // switch()

}

void complete_search_algorithm()
{
	//  Turn Green LED to indicate when done searching for a path or solving a maze
	turn_LEDs_all(Off);
	turn_LED(Red, On);
	turn_LED(Green, On);

}
