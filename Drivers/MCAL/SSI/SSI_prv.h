#ifndef MCAL_SPI_SPI_PRV_H_
#define MCAL_SPI_SPI_PRV_H_

typedef enum SSI_STATE_e{
	SSI_LOW,
	SSI_HIGH
}SSI_STATE_t;


#define SSI_CR0_FRF_bit												4
#define SSI_CR0_SCR_bit												8

#define SSI_CR0_SPO_bit												6
#define SSI_CR0_SPH_bit												7
#define SSI_CR1_SSE_bit												1
#define SSI_SR_RNE_bit												2
#define SSI_SR_TNF_bit												1
#define SSI_SR_BSY_bit												4
#define SYSCTL_RCGC1_SSI0_bit						      4


#define SSI_MS_MODE_MASK											0x0000000C
#define SSI_CLK_SOURCE_MASK										0x0000000F
#define SSI_SERIAL_CLOCK_MASK									0x0000FF00
#define SSI_PRESCALLER_DIVISOR_MASK						0x000000FF
#define SSI_FRAME_FORMAT_MASK									0x00000030
#define SSI_DATA_SIZE_MASK										0x0000000F





#define	SSI_MODE_MASTER												0x00000000
#define	SSI_MODE_SLAVE_OUTPUT_ENABLED 				0x00000004
#define	SSI_MODE_MASTER_OUTPUT_DISABLED 			0x0000000C


#define SSI_SYS_CLK 													0x00000000
#define	SSI_PIOSC 														0x00000005


#define SSI_PRESCALLER_DIV(N) ((N) >= 2 && (N) <= 254 && (N) % 2 == 0) ? (N):2


#define SSI_SERIAL_CLOCK(N) ((N) >= 0 && (N) <= 255) ? (N):0


#define	SSI_FRAME_FORMAT_FREESCALE						0x00000000
#define	SSI_FRAME_FORMAT_TEXAS_INSTRUMENTS		0x00000001
#define	SSI_FRAME_FORMAT_MICROWIRE						0x00000002


#define	SSI_POLARITY_SELECT_LOW 							SSI_LOW
#define	SSI_POLARITY_SELECT_HIGH 							SSI_HIGH


#define	SSI_PHASE_SELECT_LOW 									SSI_LOW
#define	SSI_PHASE_SELECT_HIGH 								SSI_HIGH


#define SSI_DATA_BIT_SIZE(N) ((N) >= 3 && (N) <= 15) ? (N-1):7


#endif /* MCAL_SPI_SPI_PRV_H_ */
