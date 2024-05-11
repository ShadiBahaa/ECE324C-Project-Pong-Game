#ifndef MCAL_SPI_SPI_INT_H_
#define MCAL_SPI_SPI_INT_H_

void MSSI_vInit(void);
void MSSI_vTransmit_single(u16 A_u16Data);
void MSSI_vTransmit_continuous(u16 A_u16Data);
u16 MSSI_u16Recieve_single(void);
u16 MSSI_u16Recieve_continuous(void);
u8 MSSI_u8Check_Busy(void);
u8 MSSI_u8Check_NotEmpty(void);
#endif /* MCAL_SPI_SPI_INT_H_ */
