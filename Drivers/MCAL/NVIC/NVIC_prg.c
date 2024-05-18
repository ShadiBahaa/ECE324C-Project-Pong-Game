#include "../../LIB/STD_TYPES.h"

#include "../../LIB/BIT_MATH.h"
#include "NVIC_prv.h"
#include "NVIC_int.h"

/*INVIC enable peripheral INT */

void MNVIC_vEnableINTPeripheral(NVIC_IntID_t A_u8IntId)
{
//A_u8INTID / 32  to get the number of register
//A_u8INTID % 32  to get the number of bit
	NVIC->EN[A_u8IntId / 32] |= 1<< (A_u8IntId % 32);//set bit

}
void MNVIC_vDisableINTPeripheral(NVIC_IntID_t A_u8IntId)
{
NVIC->DIS[A_u8IntId / 32] |= 1<< (A_u8IntId % 32);//CLEAR BIT
}

//Function to test
void MNVIC_vSetPending(NVIC_IntID_t A_u8IntId)
{
NVIC->PEND[A_u8IntId / 32] |= 1 << (A_u8IntId % 32); // change interrupt state to pending
}
void MNVIC_vClearPending(NVIC_IntID_t A_u8IntId)
{
NVIC->UNPEND [A_u8IntId / 32] |= 1<< (A_u8IntId % 32);//1: Removes the pending state of an interrupt
}
//to check
u8 MNVIC_u8GetActive(NVIC_IntID_t A_u8IntId)
{
 u8 L_u8IntActive = GET_BIT(NVIC->ACTIVE[A_u8IntId / 32],(A_u8IntId % 32) );
return L_u8IntActive;
}

void MNVIC_vSetpriority(NVIC_IntID_t A_u8IntId , u8 A_u8IntPri)
{
	NVIC->PRI[A_u8IntId / 4] &= ~0x7 <<(((A_u8IntId % 4) * 8)+5);
	NVIC->PRI[A_u8IntId / 4] |= A_u8IntPri<< (((A_u8IntId % 4) * 8)+5);
}

