#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../tm4c123gh6pm.h"
#include "ADC.h"

//AIN2 PE1 ADC0 seq3
volatile u16 G_u16ADCvalue = 0;

void MADC_vInit(void){
  volatile unsigned long delay;
  SYSCTL_RCGCADC_R |= (1<<ADC_RCG_BIT);
  delay = SYSCTL_RCGCADC_R;
  ADC0_ACTSS_R &= ~(1<<ADC_SEQ3_BIT);
  ADC0_EMUX_R  =  (ADC_MANUAL_TRIGGER<<ADC_EMUX_BIT);
  ADC0_SSMUX3_R = ADC_CHANNEL_VAL;
  ADC0_SSCTL3_R |= (1<<ADC_INT_BIT)|(1<<ADC_END_BIT);
	ADC0_ISC_R = (1<<ADC_SEQ3_BIT);
  ADC0_ACTSS_R |= (1<<ADC_SEQ3_BIT);
}
void MADC_vStartSampling(void){
	ADC0_PSSI_R |= (1<<ADC_SEQ3_BIT);
}

u16 MADC_u16GetVal(void){
	return ADC0_SSFIFO3_R;
}

void ADC0Seq3_Handler(void){
		if((ADC0_RIS_R&(1<<ADC_SEQ3_BIT))==(1<<ADC_SEQ3_BIT)){
			ADC0_ISC_R |= (1<<ADC_SEQ3_BIT);      // acknowledge flag4
			G_u16ADCvalue = ADC0_SSFIFO3_R;	// get the ADC value
		}
}
