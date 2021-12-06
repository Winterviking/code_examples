
//
// Задаём константные данные в PROGMEM
// таблица соответствия и русский шрифт
//


#include "display_array_rus.h"


const def_letter rus_alphabet[RUSSIAN_ALPHABET_LETTER_COUNT] PROGMEM = {
  0,           0,             (uint8_t)192,      (uint8_t)224,        'A',        'a',        1040,         1072,         //'А',      'а'
  rus_B,       rus_b,         (uint8_t)193,      (uint8_t)225,        0,          0,          1041,         1073,         //'Б',      'б'
  0,           rus_v,         (uint8_t)194,      (uint8_t)226,        'B',        0,          1042,         1074,         //'В',      'в'
  rus_G,       rus_g,         (uint8_t)195,      (uint8_t)227,        0,          0,          1043,         1075,         //'Г',      'г'
  rus_D,       rus_d,         (uint8_t)196,      (uint8_t)228,        0,          0,          1044,         1076,         //'Д',      'д'
  0,           0,             (uint8_t)197,      (uint8_t)229,        'E',        'e',        1045,         1077,         //'Е',      'е'
  rus_ZH,      rus_zh,        (uint8_t)198,      (uint8_t)230,        0,          0,          1046,         1078,         //'Ж',      'ж'
  rus_Z,       rus_z,         (uint8_t)199,      (uint8_t)231,        0,          0,          1047,         1079,         //'З',      'з'
  rus_I,       rus_i,         (uint8_t)200,      (uint8_t)232,        0,          0,          1048,         1080,         //'И',      'и'
  rus_II,      rus_ii,        (uint8_t)201,      (uint8_t)233,        0,          0,          1049,         1081,         //'Й',      'й'
  0,           rus_k,         (uint8_t)202,      (uint8_t)234,        'K',        0,          1050,         1082,         //'К',      'к'
  rus_L,       rus_l,         (uint8_t)203,      (uint8_t)235,        0,          0,          1051,         1083,         //'Л',      'л'
  0,           rus_m,         (uint8_t)204,      (uint8_t)236,        'M',        0,          1052,         1084,         //'М',      'м'
  0,           rus_n,         (uint8_t)205,      (uint8_t)237,        'H',        0,          1053,         1085,         //'Н',      'н'
  0,           0,             (uint8_t)206,      (uint8_t)238,        'O',        'o',        1054,         1086,         //'О',      'о'
  rus_P,       rus_p,         (uint8_t)207,      (uint8_t)239,        0,          0,          1055,         1087,         //'П',      'п'
  0,           0,             (uint8_t)208,      (uint8_t)240,        'P',        'p',        1056,         1088,         //'Р',      'р'
  0,           0,             (uint8_t)209,      (uint8_t)241,        'C',        'c',        1057,         1089,         //'С',      'с'
  0,           rus_t,         (uint8_t)210,      (uint8_t)242,        'T',        0,          1058,         1090,         //'Т',      'т'
  rus_U,       0,             (uint8_t)211,      (uint8_t)243,        0,          'y',        1059,         1091,         //'У',      'у'
  rus_F,       rus_f,         (uint8_t)212,      (uint8_t)244,        0,          0,          1060,         1092,         //'Ф',      'ф'
  0,           0,             (uint8_t)213,      (uint8_t)245,        'X',        'x',        1061,         1093,         //'Х',      'х'
  rus_TS,      rus_ts,        (uint8_t)214,      (uint8_t)246,        0,          0,          1062,         1094,         //'Ц',      'ц'
  rus_CH,      rus_ch,        (uint8_t)215,      (uint8_t)247,        0,          0,          1063,         1095,         //'Ч',      'ч'
  rus_SH,      rus_sh,        (uint8_t)216,      (uint8_t)248,        0,          0,          1064,         1096,         //'Ш',      'ш'
  rus_SCH,     rus_sch,       (uint8_t)217,      (uint8_t)249,        0,          0,          1065,         1097,         //'Щ',      'щ'
  rus_tverd,   rus_tverd_mal, (uint8_t)218,      (uint8_t)250,        0,          0,          1066,         1098,         //'Ъ',      'ъ'
  rus_Y,       rus_y,         (uint8_t)219,      (uint8_t)251,        0,          0,          1067,         1099,         //'Ы',      'ы'
  rus_myagk,   rus_myagk_mal, (uint8_t)220,      (uint8_t)252,        0,          0,          1068,         1100,         //'Ь',      'ь'
  rus_EE,      rus_ee,        (uint8_t)221,      (uint8_t)253,        0,          0,          1069,         1101,         //'Э',      'э'
  rus_YU,      rus_yu,        (uint8_t)222,      (uint8_t)254,        0,          0,          1070,         1102,         //'Ю',      'ю'
  rus_YA,      rus_ya,        (uint8_t)223,      (uint8_t)255,        0,          0,          1071,         1103,         //'Я',      'я'
  rus_YO,      rus_yo,        (uint8_t)168,      (uint8_t)184,        0,          0,          1025,         1105          //'Ё',      'ё'
};







//Б
const byte rus_B[8] PROGMEM = {
  0b11111,
  0b10000,
  0b10000,
  0b11110,
  0b10001,
  0b10001,
  0b11110,
  0b00000
};
//Г
const byte rus_G[8] PROGMEM = {
  0b11111,
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b00000
};
//Д
const byte rus_D[8] PROGMEM = {
  0b00110,
  0b01010,
  0b01010,
  0b01010,
  0b01010,
  0b01010,
  0b11111,
  0b10001
};
//Ё
const byte rus_YO[8] PROGMEM = {
  0b01010,
  0b00000,
  0b11111,
  0b10000,
  0b11111,
  0b10000,
  0b10000,
  0b11111
};
//Ж
const byte rus_ZH[8] PROGMEM = {
  0b10101,
  0b10101,
  0b10101,
  0b01110,
  0b10101,
  0b10101,
  0b10101,
  0b00000
};
//З
const byte rus_Z[8] PROGMEM = {
  0b01110,
  0b10001,
  0b00001,
  0b00110,
  0b00001,
  0b10001,
  0b01110,
  0b00000
};
//И
const byte rus_I[8] PROGMEM = {
  0b00000,
  0b10001,
  0b10001,
  0b10001,
  0b10011,
  0b10101,
  0b11001,
  0b10001
};
//Й
const byte rus_II[8] PROGMEM = {
  0b00100,
  0b10001,
  0b10001,
  0b10001,
  0b10011,
  0b10101,
  0b11001,
  0b10001
};
//Л
const byte rus_L[8] PROGMEM = {
  0b00111,
  0b01001,
  0b01001,
  0b01001,
  0b01001,
  0b01001,
  0b10001,
  0b00000
};
//П
const byte rus_P[8] PROGMEM = {
  0b11111,
  0b10001,
  0b10001,
  0b10001,
  0b10001,
  0b10001,
  0b10001,
  0b00000
};
//У
const byte rus_U[8] PROGMEM = {
  0b10001,
  0b10001,
  0b10001,
  0b01111,
  0b00001,
  0b10001,
  0b01110,
  0b00000
};
//Ф
const byte rus_F[8] PROGMEM = {
  0b00100,
  0b01110,
  0b10101,
  0b10101,
  0b10101,
  0b01110,
  0b00100,
  0b00000
};
//Ц
const byte rus_TS[8] PROGMEM = {
  0b10010,
  0b10010,
  0b10010,
  0b10010,
  0b10010,
  0b10010,
  0b11111,
  0b00001
};
//Ч
const byte rus_CH[8] PROGMEM = {
  0b10001,
  0b10001,
  0b10001,
  0b01111,
  0b00001,
  0b00001,
  0b00001,
  0b00000
};
//Ш
const byte rus_SH[8] PROGMEM = {
  0b10001,
  0b10001,
  0b10001,
  0b10101,
  0b10101,
  0b10101,
  0b11111,
  0b00000
};
//Щ
const byte rus_SCH[8] PROGMEM = {
  0b10001,
  0b10001,
  0b10001,
  0b10101,
  0b10101,
  0b10101,
  0b11111,
  0b00001
};
//Ъ
const byte rus_tverd[8] PROGMEM = {
  0b11000,
  0b01000,
  0b01000,
  0b01110,
  0b01001,
  0b01001,
  0b01110,
  0b00000
};
//Ы
const byte rus_Y[8] PROGMEM = {
  0b10001,
  0b10001,
  0b10001,
  0b11101,
  0b10011,
  0b10011,
  0b11101,
  0b00000
};
//Ь
const byte rus_myagk[8] PROGMEM = {
  0b10000,
  0b10000,
  0b10000,
  0b11110,
  0b10001,
  0b10001,
  0b11110,
  0b00000
};
//Э
const byte rus_EE[8] PROGMEM = {
  0b01110,
  0b10001,
  0b00001,
  0b00111,
  0b00001,
  0b10001,
  0b01110,
  0b00000
};
//Ю
const byte rus_YU[8] PROGMEM = {
  0b10010,
  0b10101,
  0b10101,
  0b11101,
  0b10101,
  0b10101,
  0b10010,
  0b00000
};
//Я
const byte rus_YA[8] PROGMEM = {
  0b01111,
  0b10001,
  0b10001,
  0b01111,
  0b00101,
  0b01001,
  0b10001,
  0b00000
};
const byte rus_b[8] PROGMEM = {
  0b00011,
  0b01100,
  0b10000,
  0b11110,
  0b10001,
  0b10001,
  0b01110,
  0b00000
};//б
const byte rus_v[8] PROGMEM = {
  0b00000,
  0b00000,
  0b11110,
  0b10001,
  0b11110,
  0b10001,
  0b11110,
  0b00000
};//в
const byte rus_g[8] PROGMEM = {
  0b00000,
  0b00000,
  0b11110,
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b00000
};//г
const byte rus_d[8] PROGMEM = {
  0b00000,
  0b00000,
  0b00110,
  0b01010,
  0b01010,
  0b01010,
  0b11111,
  0b10001
};//д
const byte rus_yo[8] PROGMEM = {
  0b01010,
  0b00000,
  0b01110,
  0b10001,
  0b11111,
  0b10000,
  0b01111,
  0b00000
};//ё
const byte rus_zh[8] PROGMEM = {
  0b00000,
  0b00000,
  0b10101,
  0b10101,
  0b01110,
  0b10101,
  0b10101,
  0b00000
};//ж
const byte rus_z[8] PROGMEM = {
  0b00000,
  0b00000,
  0b01110,
  0b10001,
  0b00110,
  0b10001,
  0b01110,
  0b00000
};//з
const byte rus_i[8] PROGMEM = {
  0b00000,
  0b00000,
  0b10001,
  0b10011,
  0b10101,
  0b11001,
  0b10001,
  0b00000
};//и
const byte rus_ii[8] PROGMEM = {
  0b01010,
  0b00100,
  0b10001,
  0b10011,
  0b10101,
  0b11001,
  0b10001,
  0b00000
};//й
const byte rus_k[8] PROGMEM = {
  0b00000,
  0b00000,
  0b10010,
  0b10100,
  0b11000,
  0b10100,
  0b10010,
  0b00000
};//к
const byte rus_l[8] PROGMEM = {
  0b00000,
  0b00000,
  0b00111,
  0b01001,
  0b01001,
  0b01001,
  0b10001,
  0b00000
};//л
const byte rus_m[8] PROGMEM = {
  0b00000,
  0b00000,
  0b10001,
  0b11011,
  0b10101,
  0b10001,
  0b10001,
  0b00000
};//м
const byte rus_n[8] PROGMEM = {
  0b00000,
  0b00000,
  0b10001,
  0b10001,
  0b11111,
  0b10001,
  0b10001,
  0b00000
};//н
const byte rus_p[8] PROGMEM = {
  0b00000,
  0b00000,
  0b11111,
  0b10001,
  0b10001,
  0b10001,
  0b10001,
  0b00000
};//п
const byte rus_t[8] PROGMEM = {
  0b00000,
  0b00000,
  0b11111,
  0b00100,
  0b00100,
  0b00100,
  0b00100,
  0b00000
};//т
const byte rus_f[8] PROGMEM = {
  0b00000,
  0b00000,
  0b00100,
  0b01110,
  0b10101,
  0b01110,
  0b00100,
  0b00000
};//ф
const byte rus_ts[8] PROGMEM = {
  0b00000,
  0b00000,
  0b10010,
  0b10010,
  0b10010,
  0b10010,
  0b11111,
  0b00001
};//ц
const byte rus_ch[8] PROGMEM = {
  0b00000,
  0b00000,
  0b10001,
  0b10001,
  0b01111,
  0b00001,
  0b00001,
  0b00000
};//ч
const byte rus_sh[8] PROGMEM = {
  0b00000,
  0b00000,
  0b10101,
  0b10101,
  0b10101,
  0b10101,
  0b11111,
  0b00000
};//ш
const byte rus_sch[8] PROGMEM = {
  0b00000,
  0b00000,
  0b10101,
  0b10101,
  0b10101,
  0b10101,
  0b11111,
  0b00001
};//щ
const byte rus_tverd_mal[8] PROGMEM = {
  0b00000,
  0b00000,
  0b11000,
  0b01000,
  0b01110,
  0b01001,
  0b01110,
  0b00000
};//ъ
const byte rus_y[8] PROGMEM = {
  0b00000,
  0b00000,
  0b10001,
  0b10001,
  0b11101,
  0b10011,
  0b11101,
  0b00000
};//ы
const byte rus_myagk_mal[8] PROGMEM = {
  0b00000,
  0b00000,
  0b10000,
  0b10000,
  0b11110,
  0b10001,
  0b11110,
  0b00000
};//ь
const byte rus_ee[8] PROGMEM = {
  0b00000,
  0b00000,
  0b01110,
  0b10001,
  0b00111,
  0b10001,
  0b01110,
  0b00000
};//э
const byte rus_yu[8] PROGMEM = {
  0b00000,
  0b00000,
  0b10010,
  0b10101,
  0b11101,
  0b10101,
  0b10010,
  0b00000
};//ю
const byte rus_ya[8] PROGMEM = {
  0b00000,
  0b00000,
  0b01111,
  0b10001,
  0b01111,
  0b00101,
  0b01001,
  0b00000
};//я

wchar_t *char_utf8 = L" ";

