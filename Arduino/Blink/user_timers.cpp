
#include "user_timers.h"


//uint16_t gen_loop_counter;
//uint16_t independent_counter;
//uint16_t independent_counter_multiplier;
//uint16_t independent_counter2;
//uint16_t independent_counter_multiplier2;

inline void init_counters(){
	reset_gen_loop_counter();
	reset_independent_counter();
	reset_independent_counter_multiplier();
	reset_independent_counter2();
	reset_independent_counter_multiplier2();
}
	

void init_usertimer_system(){
	init_timer0();
	init_counters();
}
