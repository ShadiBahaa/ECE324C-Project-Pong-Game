#include "UART_Config.h"
#include "UART_Interface.h"
#include "UART_Private.h"

UART_CallBack_t Reciever_Interrupt_CallBacks[UARTS_UNITS_COUNT];

unsigned char to_send;
unsigned char to_recieve;

void UART_VoidInit(UART_Config_t *UART_Config)
{
    UARTS_e Current_UART;
    for (Current_UART = UART_0; Current_UART <= UART_7; ++Current_UART)
    {
        UART_Clock_Status_e UART_Clock_Status = UART_Config->UARTS[Current_UART].UART_Clock_Status;
        if (UART_Clock_Status == UART_CLOCK_DISABLED)
        {
            continue;
        }
        UART_VoidSetUARTClockStatus(Current_UART, UART_Clock_Status);
        UART_VoidSetUARTEnableStatus(Current_UART, UART_DISABLED);
        UART_VoidSetBaudRate(Current_UART, UART_Config->UARTS[Current_UART].UART_Integer_Baud_Rate_Divisor, UART_Config->UARTS[Current_UART].UART_Fractional_Baud_Rate_Divisor);
        UART_VoidSetUARTStickyParityBitStatus(Current_UART, UART_Config->UARTS[Current_UART].UART_Sticky_Parity_Bit_Status);
        UART_VoidSetUARTEvenParityBitStatus(Current_UART, UART_Config->UARTS[Current_UART].UART_Even_Parity_Bit_Status);
        UART_VoidSetParityEnableStatus(Current_UART, UART_Config->UARTS[Current_UART].UART_Parity_Enable_Status);
        UART_VoidSetUARTWordLength(Current_UART, UART_Config->UARTS[Current_UART].UART_Word_Length);
        UART_VoidSetFIFOEnableStatus(Current_UART, UART_Config->UARTS[Current_UART].UART_FIFO_Enable_Status);
        UART_VoidSetStopBitsStatus(Current_UART, UART_Config->UARTS[Current_UART].UART_Stop_Bits_Status);
        UART_VoidSetRecieverEnableStatus(Current_UART, UART_Config->UARTS[Current_UART].UART_Receive_Enable_Status);
        UART_VoidSetTransmitterEnableStatus(Current_UART, UART_Config->UARTS[Current_UART].UART_Transmit_Enable_Status);
        UART_VoidSetTrasmitIntStatus(Current_UART, UART_Config->UARTS[Current_UART].UART_Transmit_Interrupt_Status);
        UART_VoidSetRecieveIntStatus(Current_UART, UART_Config->UARTS[Current_UART].UART_Reciever_Interrupt_Status);
        UART_VoidSetUARTSpeedStatus(Current_UART, UART_Config->UARTS[Current_UART].UART_Speed_Status);
        UART_VoidClearTransmitIntFlag(Current_UART);
        UART_VoidClearRecieveIntFlag(Current_UART);
        UART_VoidSetUARTEnableStatus(Current_UART, UART_Config->UARTS[Current_UART].UART_Enable_Status);
    }
}
void UART_VoidSetUARTClockStatus(UARTS_e UART_Unit, UART_Clock_Status_e UART_Clock_Status)
{
    if (UART_Clock_Status == UART_CLOCK_DISABLED)
    {
        SYSCTL_RCGCUART_R &= ~(1 << UART_Unit);
    }
    else
    {
        SYSCTL_RCGCUART_R |= (1 << UART_Unit);
    }
}
void UART_VoidSetUARTEnableStatus(UARTS_e UART_Unit, UART_Enable_Status_e UART_Enable_Status)
{
    if (UART_Enable_Status == UART_DISABLED)
    {
        UARTS[UART_Unit]->CTL &= ~(1 << 0);
    }
    else
    {
        UARTS[UART_Unit]->CTL |= (1 << 0);
    }
}
void UART_VoidSetUARTStickyParityBitStatus(UARTS_e UART_Unit, UART_Sticky_Parity_Bit_Status_e UART_Sticky_Parity_Bit_Status)
{
    if (UART_Sticky_Parity_Bit_Status == UART_STICKY_PARITY_BIT_DISABLED)
    {
        UARTS[UART_Unit]->LCRH &= ~(1 << 7);
    }
    else
    {
        UARTS[UART_Unit]->LCRH |= (1 << 7);
    }
}
void UART_VoidSetUARTEvenParityBitStatus(UARTS_e UART_Unit, UART_Even_Parity_Bit_Status_e UART_Even_Parity_Bit_Status)
{
    if (UART_Even_Parity_Bit_Status == UART_EVEN_PARITY_BIT_DISABLED)
    {
        UARTS[UART_Unit]->LCRH &= ~(1 << 2);
    }
    else
    {
        UARTS[UART_Unit]->LCRH |= (1 << 2);
    }
}
void UART_VoidSetParityEnableStatus(UARTS_e UART_Unit, UART_Parity_Enable_Status_e UART_Parity_Enable_Status)
{
    if (UART_Parity_Enable_Status == UART_PARITY_DISABLED)
    {
        UARTS[UART_Unit]->LCRH &= ~(1 << 1);
    }
    else
    {
        UARTS[UART_Unit]->LCRH |= (1 << 1);
    }
}
void UART_VoidSetRecieverEnableStatus(UARTS_e UART_Unit, UART_Receive_Enable_Status_e UART_Receive_Enable_Status)
{
    if (UART_Receive_Enable_Status == UART_RECIEVE_DISABLED)
    {
        UARTS[UART_Unit]->CTL &= ~(1 << 9);
    }
    else
    {
        UARTS[UART_Unit]->CTL |= (1 << 9);
    }
}
void UART_VoidSetTransmitterEnableStatus(UARTS_e UART_Unit, UART_Transmit_Enable_Status_e UART_Transmit_Enable_Status)
{
    if (UART_Transmit_Enable_Status == UART_TRANSMIT_DISABLED)
    {
        UARTS[UART_Unit]->CTL &= ~(1 << 8);
    }
    else
    {
        UARTS[UART_Unit]->CTL |= (1 << 8);
    }
}
void UART_VoidSetUARTSpeedStatus(UARTS_e UART_Unit, UART_Speed_Status_e UART_Speed_Status)
{
    if (UART_Speed_Status == SYSTEM_CLOCK_DIV_BY_16)
    {
        UARTS[UART_Unit]->CTL &= ~(1 << 5);
    }
    else
    {
        UARTS[UART_Unit]->CTL |= (1 << 5);
    }
}
void UART_VoidSetUARTWordLength(UARTS_e UART_Unit, UART_Word_Length_e UART_Word_Length)
{
    UARTS[UART_Unit]->LCRH &= ~(3 << 5);
    UARTS[UART_Unit]->LCRH |= (UART_Word_Length << 5);
}
void UART_VoidSetFIFOEnableStatus(UARTS_e UART_Unit, UART_FIFO_Enable_Status_e UART_FIFO_Enable_Status)
{
    if (UART_FIFO_Enable_Status == UART_FIFO_DISABLED)
    {
        UARTS[UART_Unit]->LCRH &= ~(1 << 4);
    }
    else
    {
        UARTS[UART_Unit]->LCRH |= (1 << 4);
    }
}
void UART_VoidSetStopBitsStatus(UARTS_e UART_Unit, UART_Stop_Bits_Status_e UART_Stop_Bits_Status)
{
    if (UART_Stop_Bits_Status == ONE_STOP_BIT)
    {
        UARTS[UART_Unit]->LCRH &= ~(1 << 3);
    }
    else
    {
        UARTS[UART_Unit]->LCRH |= (1 << 3);
    }
}
void UART_VoidSetTrasmitIntStatus(UARTS_e UART_Unit, UART_Transmit_Interrupt_Status_e UART_Transmit_Interrupt_Status)
{
    if (UART_Transmit_Interrupt_Status == UART_TRANS_INT_DISABLED)
    {
        UARTS[UART_Unit]->IM &= ~(1 << 5);
    }
    else
    {
        UARTS[UART_Unit]->IM |= (1 << 5);
    }
}
void UART_VoidSetRecieveIntStatus(UARTS_e UART_Unit, UART_Reciever_Interrupt_Status_e UART_Reciever_Interrupt_Status)
{
    if (UART_Reciever_Interrupt_Status == UART_RECIEVER_INT_DISABLED)
    {
        UARTS[UART_Unit]->IM &= ~(1 << 4);
    }
    else
    {
        UARTS[UART_Unit]->IM |= (1 << 4);
    }
}
void UART_VoidClearRecieveIntFlag(UARTS_e UART_Unit)
{
    UARTS[UART_Unit]->ICR |= (1 << 4);
}
void UART_VoidClearTransmitIntFlag(UARTS_e UART_Unit)
{
    UARTS[UART_Unit]->ICR |= (1 << 5);
}
void UART_VoidSetBaudRate(UARTS_e UART_Unit, UART_Integer_Baud_Rate_Divisor_t UART_Integer_Baud_Rate_Divisor, UART_Fractional_Baud_Rate_Divisor_t UART_Fractional_Baud_Rate_Divisor)
{
    UARTS[UART_Unit]->IBRD = UART_Integer_Baud_Rate_Divisor;
    UARTS[UART_Unit]->FBRD = UART_Fractional_Baud_Rate_Divisor;
}
UART_Message_t UART_UnsignedCharGetDataBlocking(UARTS_e UART_Unit)
{
    while ((UARTS[UART_Unit]->FR & (1 << 4)) != 0)
        ;
    return ((UART_Message_t)(UARTS[UART_Unit]->DR & 0xFF));
}
UART_Message_t UART_UnsignedCharGetDataNonBlocking(UARTS_e UART_Unit)
{
    return ((UART_Message_t)(UARTS[UART_Unit]->DR & 0xFF));
}
void UART_VoidSendDataBlocking(UARTS_e UART_Unit, UART_Message_t Data)
{
    while ((UARTS[UART_Unit]->FR & (1 << 5)) != 0)
        ;
    UARTS[UART_Unit]->DR = Data;
}
void UART_VoidSendDataNonBlocking(UARTS_e UART_Unit, UART_Message_t Data)
{
    UARTS[UART_Unit]->DR = Data;
}
void UART_VoidSendStringBlocking(UARTS_e UART_Unit, UART_Message_t *Data_String)
{
    while (*Data_String != '\0')
    {
        UART_VoidSendDataBlocking(UART_Unit, *Data_String);
        Data_String++;
    }
}
void UART_VoidSetUARTInterruptCallBack(UARTS_e UART_Unit, UART_CallBack_t Ptr_To_Function)
{
    Reciever_Interrupt_CallBacks[UART_Unit] = Ptr_To_Function;
}

void UART0_Handler(void)
{
    UART_VoidClearRecieveIntFlag(UART_0);
    if (Reciever_Interrupt_CallBacks[UART_0])
    {
        Reciever_Interrupt_CallBacks[UART_0]();
    }
}
void UART1_Handler(void)
{
    UART_VoidClearRecieveIntFlag(UART_1);
    if (Reciever_Interrupt_CallBacks[UART_1])
    {
        Reciever_Interrupt_CallBacks[UART_1]();
    }
}
void UART2_Handler(void)
{
    UART_VoidClearRecieveIntFlag(UART_2);
    if (Reciever_Interrupt_CallBacks[UART_2])
    {
        Reciever_Interrupt_CallBacks[UART_2]();
    }
}
void UART3_Handler(void)
{
    UART_VoidClearRecieveIntFlag(UART_3);
    if (Reciever_Interrupt_CallBacks[UART_3])
    {
        Reciever_Interrupt_CallBacks[UART_3]();
    }
}
void UART4_Handler(void)
{
    UART_VoidClearRecieveIntFlag(UART_4);
    if (Reciever_Interrupt_CallBacks[UART_4])
    {
        Reciever_Interrupt_CallBacks[UART_4]();
    }
}
void UART5_Handler(void)
{
    UART_VoidClearRecieveIntFlag(UART_5);
    if (Reciever_Interrupt_CallBacks[UART_5])
    {
        Reciever_Interrupt_CallBacks[UART_5]();
    }
}
void UART6_Handler(void)
{
    UART_VoidClearRecieveIntFlag(UART_6);
    if (Reciever_Interrupt_CallBacks[UART_6])
    {
        Reciever_Interrupt_CallBacks[UART_6]();
    }
}
void UART7_Handler(void)
{
    UART_VoidClearRecieveIntFlag(UART_7);
    if (Reciever_Interrupt_CallBacks[UART_7])
    {
        Reciever_Interrupt_CallBacks[UART_7]();
    }
}