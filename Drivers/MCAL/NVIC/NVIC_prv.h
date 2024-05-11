#ifndef MCAL_NVIC_NVIC_PRV_H_
#define MCAL_NVIC_NVIC_PRV_H_

/*base address of NVIC  page 193 in programming manual (core peripherals)*/

//NVIC register Map
typedef struct
{
  volatile u32 EN[5];
	volatile u8 RESERVED0[108];
  volatile u32 DIS[5];
	volatile u8 RESERVED1[108];
  volatile u32 PEND[5];
	volatile u8 RESERVED2[108];
  volatile u32 UNPEND[5];
	volatile u8 RESERVED3[108];
  volatile u32 ACTIVE[5];
	volatile u8 RESERVED4[236];
  volatile u32 PRI[35];
}NVIC_MemMap_t;
#define  NVIC_BASE_ADDRESS       0xE000E100
#define   NVIC  ((volatile NVIC_MemMap_t*)(NVIC_BASE_ADDRESS))
	
#endif /* MCAL_NVIC_NVIC_PRV_H_ */
