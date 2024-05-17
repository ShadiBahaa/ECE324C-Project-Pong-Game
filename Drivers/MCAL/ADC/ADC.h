#ifndef MCAL_ADC_ADC_PRV_H_
#define MCAL_ADC_ADC_PRV_H_


#define ADC_SEQ3_BIT 3
#define ADC_RCG_BIT 0
#define ADC_EMUX_BIT 12
#define ADC_INT_BIT 2
#define ADC_END_BIT 1
#define ADC_CHANNEL_VAL 2
#define ADC_MANUAL_TRIGGER 0x0

void MADC_vInit(void);
u16 MADC_u16GetVal(void);
void MADC_vStartSampling(void);

#endif /* MCAL_ADC_ADC_PRV_H_ */
