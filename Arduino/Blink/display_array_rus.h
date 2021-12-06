//
//
// Кеш шрифта для "неанглийских" русских букв в PROGMEM 
// таблица в PROGMEM, хранящая числовые значения в кодировках и задающая соответствие между русскими и английскими буквами
// возможно, "ближняя" экстренная подстановка не обеспечивается (нно и не надо, надо нормальные надписи делать)
//
//
//

#ifndef __DISPLAY_ARRAY_RUS_H_INCLUDED__
#define __DISPLAY_ARRAY_RUS_H_INCLUDED__

#include <stdint.h>
#include <avr/pgmspace.h>

#define byte uint8_t

#define RUSSIAN_ALPHABET_LETTER_COUNT 33


//
// Базовые и специальные константы кодировок
//
#define CAPITAL_A_ASCII     (uint8_t)192
#define SMALL_A_ASCII       (uint8_t)224
#define CAPITAL_YA_ASCII    (uint8_t)223
#define SMALL_YA_ASCII      (uint8_t)255

#define CAPITAL_YO_ASCII    (uint8_t)168
#define SMALL_YO_ASCII      (uint8_t)184

#define CAPITAL_A_UNICODE   1040
#define SMALL_A_UNICODE     1072
#define CAPITAL_YA_UNICODE  1071
#define SMALL_YA_UNICODE    1103

#define CAPITAL_YO_UNICODE  1025
#define SMALL_YO_UNICODE    1105

#define YO_LETTER_POSITION  33


//
// полное описание буквы для установления однозначного соответствия
// технически, английский шрифт поддерживается дисплеем, а значит, нам нужно по кодировке иметь русский шрифт
typedef struct {
  const byte* capital;
  const byte* small;
  unsigned char rus_code_ascii_capital;
  unsigned char rus_code_ascii_small;
  unsigned char eng_code_ascii_capital;
  unsigned char eng_code_ascii_small;
  wchar_t rus_code_unicode_capital;
  wchar_t rus_code_unicode_small;
} def_letter;







//
// кеш русских букв - шрифт 8х8
// алфавит по кодировке даёт взаимно-однозначное соответствие

extern const byte rus_B[8];
extern const byte rus_G[8];
extern const byte rus_D[8];
extern const byte rus_ZH[8];
extern const byte rus_Z[8];
extern const byte rus_I[8];
extern const byte rus_II[8];
extern const byte rus_L[8];
extern const byte rus_P[8];
extern const byte rus_U[8];
extern const byte rus_F[8];
extern const byte rus_TS[8];
extern const byte rus_CH[8];
extern const byte rus_SH[8];
extern const byte rus_SCH[8];
extern const byte rus_tverd[8];
extern const byte rus_Y[8];
extern const byte rus_myagk[8];
extern const byte rus_EE[8];
extern const byte rus_YU[8];
extern const byte rus_YA[8];

extern const byte rus_YO[8];


extern const byte rus_b[8];
extern const byte rus_v[8];
extern const byte rus_g[8];
extern const byte rus_d[8];
extern const byte rus_zh[8];
extern const byte rus_z[8];
extern const byte rus_i[8];
extern const byte rus_ii[8];
extern const byte rus_k[8];
extern const byte rus_l[8];
extern const byte rus_m[8];
extern const byte rus_n[8];
extern const byte rus_p[8];
extern const byte rus_t[8];
extern const byte rus_f[8];
extern const byte rus_ts[8];
extern const byte rus_ch[8];
extern const byte rus_sh[8];
extern const byte rus_sch[8];
extern const byte rus_tverd_mal[8];
extern const byte rus_y[8];
extern const byte rus_myagk_mal[8];
extern const byte rus_ee[8];
extern const byte rus_yu[8];
extern const byte rus_ya[8];

extern const byte rus_yo[8];



extern const def_letter rus_alphabet[RUSSIAN_ALPHABET_LETTER_COUNT];




#endif // End of __DISPLAY_ARRAY_RUS_H_INCLUDED__


