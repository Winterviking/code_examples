//
// Atmega162.h >> >> >> >> 
// atmeg <= подробный заголовочный файл для избранной периферии 
// 
//
//


#ifndef __ATMEGA162_H_INCLUDED__
#define __ATMEGA162_H_INCLUDED__

//
// TIMER PRESCALER
//


#define TCCR0_CS_TIMER_DISABLED           					0b000
#define TCCR0_CS_TIMER_DIV_1              					0b001
#define TCCR0_CS_TIMER_DIV_8              					0b010
#define TCCR0_CS_TIMER_DIV_64             					0b011
#define TCCR0_CS_TIMER_DIV_256            					0b100
#define TCCR0_CS_TIMER_DIV_1024           					0b101
#define TCCR0_CS_TIMER_EXT_FALLING_EDGE   					0b110
#define TCCR0_CS_TIMER_EXT_RISING_EDGE    					0b111

#define TCCR0_FOC0_ON                     					0b10000000
#define TCCR0_FOC0_OFF                    					0b00000000
#define TCCR0_FOC0_DEFAULT                					0b00000000

#define TCCR0_WGM0_NORMAL                 					0b00000000
#define TCCR0_WGM0_PWM_PHASE_CORRECT      					0b01000000
#define TCCR0_WGM0_CTC                    					0b00001000
#define TCCR0_WGM0_FAST_PWM               					0b01001000

#define TCCR0_COM0_NON_PWM_NORMAL_OPERATION     			0b00000000
#define TCCR0_COM0_NON_PWM_TOGGLE_OC0_ON_CM     			0b00010000
#define TCCR0_COM0_NON_PWM_CLEAR_OC0_ON_CM      			0b00100000
#define TCCR0_COM0_NON_PWM_SET_OC0_ON_CM        			0b00110000

#define TCCR0_COM0_FAST_PWM_NORMAL_OPERATION    			0b00000000
#define TCCR0_COM0_FAST_PWM_RESERVED            			0b00010000
#define TCCR0_COM0_FAST_PWM_CLEAR_OC0_ON_CM     			0b00100000
#define TCCR0_COM0_FAST_PWM_SET_OC0_ON_CM       			0b00110000

#define TCCR0_COM0_PHASE_CORRECT_PWM_NORMAL_OPERATION    	0b00000000
#define TCCR0_COM0_PHASE_CORRECT_PWM_RESERVED            	0b00010000
#define TCCR0_COM0_PHASE_CORRECT_PWM_CLEAR_OC0_ON_CM     	0b00100000
#define TCCR0_COM0_PHASE_CORRECT_PWM_SET_OC0_ON_CM       	0b00110000

//
// TIMSK
//
#define TIMSK_MASK_OCIE0      								0b00000001
#define TIMSK_MASK_TOIE0      								0b00000010
#define TIMSK_MASK_TOIE2      								0b00000100
#define TIMSK_MASK_TICIE1     								0b00001000
#define TIMSK_MASK_OCIE2      								0b00010000
#define TIMSK_MASK_OCIE1B     								0b00100000
#define TIMSK_MASK_OCIE1A     								0b01000000
#define TIMSK_MASK_TOIE1      								0b10000000






//
// TIMER 16
//



//#define TIMSK_TC_IE_MASK_TOIE     						0b000001
//#define TIMSK_TC_IE_MASK_OCIEA    						0b000010
//#define TIMSK_TC_IE_MASK_OCIEB    						0b000100
//#define TIMSK_TC_IE_MASK_ICFIE    						0b100000


// TCNT0
// OCR0A
// OCR0B
// TIFR0

#define WGM_TIMER16_MODE_NORMAL                 			0b00
#define WGM_TIMER16_MODE_PWM_PC_08BIT           			0b01
#define WGM_TIMER16_MODE_PWM_PC_09BIT           			0b10
#define WGM_TIMER16_MODE_PWM_PC_10BIT           			0b11
#define WGM_TIMER16_MODE_CTC_OCR                			0b00
#define WGM_TIMER16_MODE_FAST_PWM_08BIT         			0b01
#define WGM_TIMER16_MODE_FAST_PWM_09BIT         			0b10
#define WGM_TIMER16_MODE_FAST_PWM_10BIT         			0b11
#define WGM_TIMER16_MODE_PWM_PFC_ICR            			0b00
#define WGM_TIMER16_MODE_PWM_PFC_OCR            			0b01
#define WGM_TIMER16_MODE_PWM_PC_ICR             			0b10
#define WGM_TIMER16_MODE_PWM_PC_OCR             			0b11
#define WGM_TIMER16_MODE_CTC_ICR                			0b00
#define WGM_TIMER16_MODE_RESERVED               			0b01
#define WGM_TIMER16_MODE_FAST_PWM_ICR           			0b10
#define WGM_TIMER16_MODE_FAST_PWM_OCR           			0b11

#define WGM_TIMER16_COMMON        							0b00000
#define WGM_TIMER16_FAST_PWM      							0b01000
#define WGM_TIMER16_PWM_PC_PFC    							0b10000
#define WGM_TIMER16_FAST_PWM_ADD  							0b11000












#endif // End of __ATMEGA162_H_INCLUDED__








