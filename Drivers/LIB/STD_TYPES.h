#ifndef LIB_STD_TYPES_H_
#define LIB_STD_TYPES_H_

typedef unsigned char u8 ;
typedef unsigned short int u16 ;
typedef unsigned long int u32 ;
typedef signed char s8 ;
typedef signed short int s16 ;
typedef signed long int s32 ;
typedef float f32;
typedef double f64;

typedef enum {
	STD_NOK = 0,
	STD_OK  = 1,
} enuErrorState_t;

#define NULL ((void*)0)

#endif /* LIB_STD_TYPES_H_ */
