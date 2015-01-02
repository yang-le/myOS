#ifndef __TYPES_H__
#define __TYPES_H__

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;

typedef signed char int8;
typedef signed short int16;
typedef signed int int32;

typedef uint8 bool;
typedef uint32 far_ptr;

#define true 1
#define false 0
#define null (void*)0

#define __PACKED__ __attribute__ ((gcc_struct, packed))

#define _STR(x) #x
#define STR(x) _STR(x)

#endif