#ifndef INC_ALGORITHM_H_
#define INC_ALGORITHM_H_

#include "hugger.h"
#include "flood_fill.h"
#include "switch.h"
#include "LED.h"
#include "test.h"

typedef enum
{
	Hug_Left_Algo, Flood_Fill_Algo, Test_Algo
} algorithm_type;

uint8_t determine_algorithm();

void do_search_algorithm(algorithm_type algo);

void complete_search_algorithm();

#endif /* INC_ALGORITHM_H_ */
