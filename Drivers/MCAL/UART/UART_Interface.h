#ifndef _UART_INTERFACE_H_

#define _UART_INTERFACE_H_

// For each unit

typedef enum{
    UART_0,
    UART_1,
    UART_2,
    UART_3,
    UART_4,
    UART_5,
    UART_6,
    UART_7,
}UARTS_e;

typedef enum
{
    UART_CLOCK_DISABLED,
    UART_CLOCK_ENABLED,
} UART_Clock_Status_e;

typedef enum
{
    UART_DISABLED,
    UART_ENABLED
} UART_Enable_Status_e;

typedef enum
{
    UART_STICKY_PARITY_BIT_DISABLED,
    UART_STICKY_PARITY_BIT_ENABLED
} UART_Sticky_Parity_Bit_Status_e;

typedef enum
{
    UART_EVEN_PARITY_BIT_DISABLED,
    UART_EVEN_PARITY_BIT_ENABLED
} UART_Even_Parity_Bit_Status_e;

typedef enum
{
    UART_PARITY_DISABLED,
    UART_PARITY_ENABLED,
} UART_Parity_Enable_Status_e;
typedef enum
{
    UART_RECIEVE_DISABLED,
    UART_RECIEVE_ENABLED
} UART_Receive_Enable_Status_e;
typedef enum
{
    UART_TRANSMIT_DISABLED,
    UART_TRANSMIT_ENABLED
} UART_Transmit_Enable_Status_e;
typedef enum
{
    SYSTEM_CLOCK_DIV_BY_16,
    SYSTEM_CLOCK_DIV_BY_8,
} UART_Speed_Status_e;
typedef enum
{
    FIVE_BITS,
    SEX_BITS,
    SEVEN_BITS,
    EIGHT_BITS
} UART_Word_Length_e;

typedef enum
{
    UART_FIFO_DISABLED,
    UART_FIFO_ENABLED
} UART_FIFO_Enable_Status_e;

typedef enum
{
    ONE_STOP_BIT,
    TWO_STOP_BITS
} UART_Stop_Bits_Status_e;

typedef enum
{
    UART_TRANS_INT_DISABLED,
    UART_TRANS_INT_ENABLED,
} UART_Transmit_Interrupt_Status_e;

typedef enum
{
    UART_RECIEVER_INT_DISABLED,
    UART_RECIEVER_INT_ENABLED,
} UART_Reciever_Interrupt_Status_e;

typedef unsigned long int UART_Integer_Baud_Rate_Divisor_t;
typedef unsigned long int UART_Fractional_Baud_Rate_Divisor_t;
typedef void (*UART_CallBack_t)(void);

typedef struct
{
    UART_Clock_Status_e UART_Clock_Status;
    UART_Enable_Status_e UART_Enable_Status;
    UART_Sticky_Parity_Bit_Status_e UART_Sticky_Parity_Bit_Status;
    UART_Even_Parity_Bit_Status_e UART_Even_Parity_Bit_Status;
    UART_Parity_Enable_Status_e UART_Parity_Enable_Status;
    UART_Receive_Enable_Status_e UART_Receive_Enable_Status;
    UART_Transmit_Enable_Status_e UART_Transmit_Enable_Status;
    UART_Speed_Status_e UART_Speed_Status;
    UART_Word_Length_e UART_Word_Length;
    UART_FIFO_Enable_Status_e UART_FIFO_Enable_Status;
    UART_Stop_Bits_Status_e UART_Stop_Bits_Status;
    UART_Transmit_Interrupt_Status_e UART_Transmit_Interrupt_Status;
    UART_Reciever_Interrupt_Status_e UART_Reciever_Interrupt_Status;
    UART_Integer_Baud_Rate_Divisor_t UART_Integer_Baud_Rate_Divisor;
    UART_Fractional_Baud_Rate_Divisor_t UART_Fractional_Baud_Rate_Divisor;
} UART_Unit_Config_t;

typedef struct
{
    UART_Unit_Config_t UARTS[UARTS_UNITS_COUNT];
} UART_Config_t;

typedef unsigned char UART_Message_t;

void UART_VoidInit(UART_Config_t * UART_Config);
void UART_VoidSetUARTClockStatus(UARTS_e UART_Unit, UART_Clock_Status_e UART_Clock_Status);
void UART_VoidSetUARTEnableStatus(UARTS_e UART_Unit, UART_Enable_Status_e UART_Enable_Status);
void UART_VoidSetUARTStickyParityBitStatus(UARTS_e UART_Unit, UART_Sticky_Parity_Bit_Status_e UART_Sticky_Parity_Bit_Status);
void UART_VoidSetUARTEvenParityBitStatus(UARTS_e UART_Unit,UART_Even_Parity_Bit_Status_e UART_Even_Parity_Bit_Status);
void UART_VoidSetParityEnableStatus(UARTS_e UART_Unit,UART_Parity_Enable_Status_e UART_Parity_Enable_Status);
void UART_VoidSetRecieverEnableStatus(UARTS_e UART_Unit,UART_Receive_Enable_Status_e UART_Receive_Enable_Status);
void UART_VoidSetTransmitterEnableStatus(UARTS_e UART_Unit,UART_Transmit_Enable_Status_e UART_Transmit_Enable_Status);
void UART_VoidSetUARTSpeedStatus(UARTS_e UART_Unit,UART_Speed_Status_e UART_Speed_Status);
void UART_VoidSetUARTWordLength(UARTS_e UART_Unit,UART_Word_Length_e UART_Word_Length);
void UART_VoidSetFIFOEnableStatus(UARTS_e UART_Unit,UART_FIFO_Enable_Status_e UART_FIFO_Enable_Status);
void UART_VoidSetStopBitsStatus(UARTS_e UART_Unit,UART_Stop_Bits_Status_e UART_Stop_Bits_Status);
void UART_VoidSetTrasmitIntStatus(UARTS_e UART_Unit,UART_Transmit_Interrupt_Status_e UART_Transmit_Interrupt_Status);
void UART_VoidSetRecieveIntStatus(UARTS_e UART_Unit,UART_Reciever_Interrupt_Status_e UART_Reciever_Interrupt_Status);
void UART_VoidSetBaudRate(UARTS_e UART_Unit,UART_Integer_Baud_Rate_Divisor_t UART_Integer_Baud_Rate_Divisor,UART_Fractional_Baud_Rate_Divisor_t UART_Fractional_Baud_Rate_Divisor);
UART_Message_t UART_UnsignedCharGetDataBlocking(UARTS_e UART_Unit);
UART_Message_t UART_UnsignedCharGetDataNonBlocking(UARTS_e UART_Unit);
void UART_VoidSendDataBlocking(UARTS_e UART_Unit, UART_Message_t Data);
void UART_VoidSendDataNonBlocking(UARTS_e UART_Unit ,UART_Message_t Data);
void UART_VoidSendStringBlocking(UARTS_e UART_Unit,UART_Message_t *Data_String);
void UART_VoidSendStringNonBlocking(UARTS_e UART_Unit,UART_Message_t *Data_String);
void UART_VoidSetUARTInterruptCallBack(UARTS_e UART_Unit, UART_CallBack_t Ptr_To_Function);
void UART_VoidClearRecieveIntFlag(UARTS_e UART_Unit);
void UART_VoidClearTransmitIntFlag(UARTS_e UART_Unit);
#endif