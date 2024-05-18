
#include "UART_Config.h"
#include "UART_Interface.h"

UART_Config_t UART_Config = {
    .UARTS[2] = {
        .UART_Clock_Status = UART_CLOCK_ENABLED,
        .UART_Enable_Status = UART_ENABLED,
        .UART_Integer_Baud_Rate_Divisor = 104,
        .UART_Fractional_Baud_Rate_Divisor = 11,
        .UART_Word_Length = EIGHT_BITS,
        .UART_Parity_Enable_Status = UART_PARITY_DISABLED,
        .UART_Stop_Bits_Status = ONE_STOP_BIT,
				.UART_Receive_Enable_Status = UART_RECIEVE_ENABLED,
        .UART_Transmit_Enable_Status = UART_TRANSMIT_ENABLED,
				.UART_Reciever_Interrupt_Status = UART_RECIEVER_INT_ENABLED
    }
};