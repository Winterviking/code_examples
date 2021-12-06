#ifndef __TYPES_H_INCLUDED__
#define __TYPES_H_INCLUDED__


#include <stdint.h>
#include <stdbool.h>
//
// API ����� :: ��� unsigned ����� ���������� ������� ����, ������� ������� ��� ��������-������������ ����� ���������
//
typedef uint8_t     BYTE;
typedef uint16_t    WORD;
typedef uint32_t    DWORD;
typedef uint64_t    QWORD;

//
// ����� ������ �����
//#define bool    BYTE
//#define true 1
//#define false 0


//
//
#define LOBYTE(x) (x&0xFF)
#define HIBYTE(x) ((x>>8)&0xFF)

#endif // End of __TYPES_H_INCLUDED__
