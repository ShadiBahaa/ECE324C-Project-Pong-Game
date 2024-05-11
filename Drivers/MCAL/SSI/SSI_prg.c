#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../../tm4c123gh6pm.h"
#include "SSI_prv.h"
#include "SSI_cfg.h"
#include "SSI_int.h"


void MSSI_vInit(void){
	volatile u32 delay;
	SET_BIT(SYSCTL_RCGC1_R,SYSCTL_RCGC1_SSI0_bit); //enble SSI Clock
	delay = SYSCTL_RCGC1_R;
	CLR_BIT(SSI0_CR1_R,SSI_CR1_SSE_bit); //disable SSI
	SSI0_CR1_R = (SSI0_CR1_R&~SSI_MS_MODE_MASK) | SSI_MS_MODE;	//select mode
	SSI0_CC_R = (SSI0_CC_R&~SSI_CLK_SOURCE_MASK) | SSI_CLK_SOURCE; //select clock source
	// SysClk/(CPSDVSR*(1+SCR))
	SSI0_CPSR_R = (SSI0_CPSR_R&~SSI_PRESCALLER_DIVISOR_MASK) | SSI_PRESCALLER_DIVISOR; //set prescaller divisor
	SSI0_CR0_R = (SSI0_CR0_R&~SSI_SERIAL_CLOCK_MASK) | SSI_SERIAL_CLOCK_RATE<<SSI_CR0_SCR_bit; //set serial clock rate
	WRT_BIT(SSI0_CR0_R,SSI_CR0_SPO_bit,SSI_POLARITY_SELECT); //select polarity
	WRT_BIT(SSI0_CR0_R,SSI_CR0_SPH_bit,SSI_PHASE_SELECT); //select phase
	SSI0_CR0_R = (SSI0_CR0_R&~SSI_FRAME_FORMAT_MASK) | SSI_FRAME_FORMAT<<SSI_CR0_FRF_bit; //select frame format
	SSI0_CR0_R = (SSI0_CR0_R&~SSI_DATA_SIZE_MASK) | SSI_DATA_SIZE; //select data size
	SET_BIT(SSI0_CR1_R,SSI_CR1_SSE_bit); //enable SSI
	
}
void MSSI_vTransmit_single(u16 A_u16Data){
	  while(GET_BIT(SSI0_SR_R,SSI_SR_BSY_bit)==SSI_HIGH){}; //wait for busy bit
    SSI0_DR_R = A_u16Data;	//send data
    while(GET_BIT(SSI0_SR_R,SSI_SR_BSY_bit)==SSI_HIGH){};	//wait for busy bit
}
void MSSI_vTransmit_continuous(u16 A_u16Data){
	  while(GET_BIT(SSI0_SR_R,SSI_SR_TNF_bit)==SSI_LOW){}; //wait until transmit not full
    SSI0_DR_R = A_u16Data;	//send data
}
u16 MSSI_u16Recieve_single(void){
		while(GET_BIT(SSI0_SR_R,SSI_SR_BSY_bit)==SSI_HIGH){}; //wait for busy bit
    return SSI0_DR_R;	//recieve data
}
u16 MSSI_u16Recieve_continuous(void){
		while(GET_BIT(SSI0_SR_R,SSI_SR_RNE_bit)==SSI_LOW){}; //wait until recieve not empty
    return SSI0_DR_R; //recieve data
}

u8 MSSI_u8Check_Busy(void){
	return GET_BIT(SSI0_SR_R,SSI_SR_BSY_bit);
}
u8 MSSI_u8Check_NotEmpty(void){
	return GET_BIT(SSI0_SR_R,SSI_SR_TNF_bit);
}

