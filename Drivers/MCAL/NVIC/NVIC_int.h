#ifndef MCAL_NVIC_NVIC_INT_H_
#define MCAL_NVIC_NVIC_INT_H_

typedef enum {
  NVIC_GPIOA                    =   0,              
  NVIC_GPIOB                    =   1,              
  NVIC_GPIOC                    =   2,              
  NVIC_GPIOD                    =   3,              
  NVIC_GPIOE                    =   4,              
  NVIC_UART0                    =   5,              
  NVIC_UART1                    =   6,              
  NVIC_SSI0                     =   7,              
  NVIC_I2C0                     =   8,              
  NVIC_PWM0_FAULT               =   9,              
  NVIC_PWM0_0                   =  10,              
  NVIC_PWM0_1                   =  11,              
  NVIC_PWM0_2                   =  12,              
  NVIC_QEI0                     =  13,              
  NVIC_ADC0SS0                  =  14,              
  NVIC_ADC0SS1                  =  15,              
  NVIC_ADC0SS2                  =  16,              
  NVIC_ADC0SS3                  =  17,              
  NVIC_WATCHDOG0                =  18,              
  NVIC_TIMER0A                  =  19,              
  NVIC_TIMER0B                  =  20,              
  NVIC_TIMER1A                  =  21,              
  NVIC_TIMER1B                  =  22,              
  NVIC_TIMER2A                  =  23,              
  NVIC_TIMER2B                  =  24,              
  NVIC_COMP0                    =  25,              
  NVIC_COMP1                    =  26,              
  NVIC_SYSCTL                   =  28,              
  NVIC_FLASH_CTRL               =  29,              
  NVIC_GPIOF                    =  30,              
  NVIC_UART2                    =  33,              
  NVIC_SSI1                     =  34,              
  NVIC_TIMER3A                  =  35,              
  NVIC_TIMER3B                  =  36,              
  NVIC_I2C1                     =  37,              
  NVIC_QEI1                     =  38,              
  NVIC_CAN0                     =  39,              
  NVIC_CAN1                     =  40,              
  NVIC_HIB                      =  43,              
  NVIC_USB0                     =  44,              
  NVIC_PWM0_3                   =  45,              
  NVIC_UDMA                     =  46,              
  NVIC_UDMAERR                  =  47,              
  NVIC_ADC1SS0                  =  48,              
  NVIC_ADC1SS1                  =  49,              
  NVIC_ADC1SS2                  =  50,              
  NVIC_ADC1SS3                  =  51,              
  NVIC_SSI2                     =  57,              
  NVIC_SSI3                     =  58,              
  NVIC_UART3                    =  59,              
  NVIC_UART4                    =  60,              
  NVIC_UART5                    =  61,              
  NVIC_UART6                    =  62,              
  NVIC_UART7                    =  63,              
  NVIC_I2C2                     =  68,              
  NVIC_I2C3                     =  69,              
  NVIC_TIMER4A                  =  70,              
  NVIC_TIMER4B                  =  71,              
  NVIC_TIMER5A                  =  92,              
  NVIC_TIMER5B                  =  93,              
  NVIC_WTIMER0A                 =  94,              
  NVIC_WTIMER0B                 =  95,              
  NVIC_WTIMER1A                 =  96,              
  NVIC_WTIMER1B                 =  97,              
  NVIC_WTIMER2A                 =  98,              
  NVIC_WTIMER2B                 =  99,              
  NVIC_WTIMER3A                 = 100,              
  NVIC_WTIMER3B                 = 101,              
  NVIC_WTIMER4A                 = 102,              
  NVIC_WTIMER4B                 = 103,              
  NVIC_WTIMER5A                 = 104,              
  NVIC_WTIMER5B                 = 105,              
  NVIC_SYSEXC                   = 106,              
  NVIC_PWM1_0                   = 134,              
  NVIC_PWM1_1                   = 135,              
  NVIC_PWM1_2                   = 136,              
  NVIC_PWM1_3                   = 137,              
  NVIC_PWM1_FAULT               = 138               
} NVIC_IntID_t;


void MNVIC_vEnableINTPeripheral(NVIC_IntID_t A_u8INTID);
void MNVIC_vDisableINTPeripheral(NVIC_IntID_t A_u8INTID);
//Function to test
void MNVIC_vSetPending(NVIC_IntID_t A_u8INTID);
void MNVIC_vClearPending(NVIC_IntID_t A_u8INTID);
//to check
u8 MNVIC_u8GetActive(NVIC_IntID_t A_u8INTID);
//priority
void MNVIC_vSetpriority(NVIC_IntID_t A_u8IntId , u8 A_u8IntPri);

#endif /* MCAL_NVIC_NVIC_INT_H_ */
