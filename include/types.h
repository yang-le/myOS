#ifndef __TYPES_H__
#define __TYPES_H__

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;

typedef uint8 bool;
#define true 1
#define false 0

#define __PACKED__ __attribute__ ((gcc_struct, packed))

#define _STR(x) #x
#define STR(x) _STR(x)

#endif