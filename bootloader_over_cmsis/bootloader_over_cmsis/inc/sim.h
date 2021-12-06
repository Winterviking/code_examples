#ifndef __SIM_H_INCLUDED__
#define __SIM_H_INCLUDED__

#include "includer_hw.h"





void radio_reset(bool reset);
void radio_boot(bool boot);

void radio_init();
void radio_deinit();
void radio_wake();




#endif /* __SIM_H_INCLUDED__ */
