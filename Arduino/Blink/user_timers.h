//
//
// module for working with user timers based on hw timer
//


#ifndef __USER_TIMERS_H_INCLUDED__
#define __USER_TIMERS_H_INCLUDED__

#include <stdint.h>
#include "timers.h"

#define MAKE_TIMER(name)	static uint16_t name;					\
							inline void reset_##name(){name = 0;}	\
							inline void inc_##name(){name++;}

MAKE_TIMER(gen_loop_counter)
MAKE_TIMER(independent_counter)
MAKE_TIMER(independent_counter_multiplier)
MAKE_TIMER(independent_counter2)
MAKE_TIMER(independent_counter_multiplier2)


void init_usertimer_system();





#endif // End of __USER_TIMERS_H_INCLUDED__
