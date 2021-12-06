#ifndef __USB_CDC_H_INCLUDED__
#define __USB_CDC_H_INCLUDED__

#include "includer_hw.h"

// импользуем EP0 > EP1 вспомогательный протокол

void EP1_SETUP(void);
void EP2_SETUP(void);
void EP3_SETUP(void);

void EP1_OUT(void);
void EP2_OUT(void);
void EP3_OUT(void);

void EP1_IN(void);
void EP2_IN(void);
void EP3_IN(void);





extern volatile bool EP1_busy;

volatile DWORD ep1_busy_timer;








#endif // End of __USB_CDC_H_INCLUDED__
