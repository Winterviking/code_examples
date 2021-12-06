#ifndef __DRV_CLOCK_H_INCLUDED__
#define __DRV_CLOCK_H_INCLUDED__

#include "includer_hw.h"

//
//
// ������� ������� ��������, ���������� �� sysclk (1ms timer hw)
// ����� ���������� ����� ����� ��������
//
//

extern volatile DWORD SYSCLK_1MS;

#define TIMER(p) (SYSCLK_1MS-(p))
#define CLEAR_TIMER(p) p=SYSCLK_1MS
#define WAIT(p) {DWORD tmr;CLEAR_TIMER(tmr);while(TIMER(tmr)<p);}

void drv_clock_config_lp(void); // low power config >>
void drv_clock_config(void);

void drv_clock_deinit();


#endif // End of __DRV_CLOCK_H_INCLUDED__
