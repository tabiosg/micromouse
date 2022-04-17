#include "algorithm.h"

uint8_t determine_algorithm()
{
	// TODO - fix once begin implementing different algorithms

	uint8_t determined_algorithm = is_switch_on();
	determined_algorithm = Flood_Fill_Algo;  // TODO - Flood_Fill_Algo when not testing, Test_Algo when testing

	switch(determined_algorithm)
	{
	case 0:
		return Hug_Left_Algo;
	case 1:
		return Flood_Fill_Algo;
	case 2:
		return Test_Algo;
	}  // switch()

	return -1;
}  // determine_algorithm()

uint8_t do_search_algorithm(algorithm_type algo)
{
	//  Turn Blue LED on to indicate searching for a path.
	turn_LEDs_all(Off);
	turn_LED(Red, On);
	turn_LED(Blue, On);

	switch(algo)
	{
	case Hug_Left_Algo:
		do_hug_left_algorithm();
		return 0;
	case Flood_Fill_Algo:
		return do_flood_fill_algorithm();
	case Test_Algo:
		do_test_algorithm();
		return 0;
	}  // switch(algo)
}  // uint8_t do_search_algorithm(algorithm_type algo)

void complete_search_algorithm()
{
	//  Turn Green LED to indicate when done searching for a path or solving a maze
	turn_LEDs_all(Off);
	turn_LED(Red, On);
	turn_LED(Green, On);
}  // complete_search_algorithm()
