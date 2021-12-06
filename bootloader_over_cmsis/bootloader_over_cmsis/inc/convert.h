#ifndef __CONVERT_H_INCLUDED__
#define __CONVERT_H_INCLUDED__

//
// Ёлементы отладочной инфраструктуры
// набор функций дл€ принудительного преобразовани€ ..
// общий printf лучше .. .. ..
// тем не менее .. этот код сыграл свою роль в отладке
//
// плюс, это был такой эксперимент с "метапрограммированием" на си
//

#include "includer.h"

#define _itoa2name_(_type) itoa2##_type
#define _itoa2_(type,anyint) char* _itoa2name_(type)(anyint num, char* str, BYTE base, BYTE shift)



_itoa2_(_int16, signed short);
_itoa2_(_int32, signed int);
_itoa2_(_uint32, unsigned int);


#define int_to_hex(num) _itoa2name_(_int32)(num, convert_str, 16, 4)
#define int_to_oct(num) _itoa2name_(_int32)(num, convert_str, 8, 3)
#define int_to_bin(num) _itoa2name_(_int32)(num, convert_str, 2, 1)

#define int16_to_hex(num) _itoa2name_(_int16)(num, convert_str, 16, 4)
#define int16_to_oct(num) _itoa2name_(_int16)(num, convert_str, 8, 3)
#define int16_to_bin(num) _itoa2name_(_int16)(num, convert_str, 2, 1)

#define uint_to_hex(num) _itoa2name_(_uint32)(num, convert_str, 16, 4)
#define uint_to_oct(num) _itoa2name_(_uint32)(num, convert_str, 8, 3)
#define uint_to_bin(num) _itoa2name_(_uint32)(num, convert_str, 2, 1)














extern char convert_str[MAX_CONVERT_STRING_SIZE];
extern BYTE convert_strlen;






#endif /* __CONVERT_H_INCLUDED__ */
