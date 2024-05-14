#include "GPTM_Config.h"
#include "GPTM_Private.h"
#include "GPTM_Interface.h"

#define NULL ((void *)0)

TIMER_CallBack_t Raw_Interrupt_CallBacks[TIMERS_BLOCKS_COUNT][COUNTERS_PER_TIMER];

void GPTM_VoidInit(GPTM_Config_t *GPTM_Config)
{
    TIMERS_e Current_Timer;

    for (Current_Timer = TIMER_0; Current_Timer <= TIMER_5; Current_Timer++)
    {
        TIMER_Clock_Status_e TIMER_Clock_Status;
        TIMER_Clock_Status = GPTM_Config->TIMER_Blocks[Current_Timer].TIMER_Clock_Status;
        if (TIMER_Clock_Status == TIMER_CLOCK_DISABLED)
            continue;
        GPTM_VoidSetTimerClockStatus(TIMER_Clock_Status, Current_Timer);
        GPTM_VoidSetTimerMode(GPTM_Config->TIMER_Blocks[Current_Timer].TIMER_Mode, Current_Timer);
        TIMER_Counters_e Current_Counter;
        for (Current_Counter = COUNTER_A; Current_Counter <= COUNTER_B; Current_Counter++)
        {
            GPTM_VoidSetTimerStatus(TIMER_DISABLED, Current_Timer, Current_Counter);
            GPTM_VoidSetTimerPeriodicity(GPTM_Config->TIMER_Blocks[Current_Timer].Timers[Current_Counter].TIMER_Periodicity, Current_Timer, Current_Counter);
            GPTM_VoidSetTimerCountingDirection(GPTM_Config->TIMER_Blocks[Current_Timer].Timers[Current_Counter].TIMER_Counting_Direction, Current_Timer, Current_Counter);
            GPTM_VoidSetTimerReloadValue(Current_Timer, Current_Counter, GPTM_Config->TIMER_Blocks[Current_Timer].Timers[Current_Counter].TIMER_Period);
            GPTM_VoidSetTimerPrescalarValue(Current_Timer, Current_Counter, GPTM_Config->TIMER_Blocks[Current_Timer].Timers[Current_Counter].TIMER_Prescalar);
            GPTM_VoidClearTimerTimeOutRawInterrupt(Current_Timer, Current_Counter);
            GPTM_VoidSetTimerTimeOutRawInterruptStatus(Current_Timer, Current_Counter, GPTM_Config->TIMER_Blocks[Current_Timer].Timers[Current_Counter].TIMER_Time_Out_Interrupt_Status);
            GPTM_VoidSetTimerStatus(TIMER_ENABLED, Current_Timer, Current_Counter);
        }
    }
}
void GPTM_VoidSetTimerClockStatus(TIMER_Clock_Status_e TIMER_Clock_Status, TIMERS_e Timer)
{

    if (TIMER_Clock_Status == TIMER_CLOCK_DISABLED)
    {
        SYSCTL_RCGCTIMER_R &= ~(1 << Timer);
    }
    else
    {
        SYSCTL_RCGCTIMER_R |= (1 << Timer);
    }
    SYSCTL_RCGCTIMER_R = SYSCTL_RCGCTIMER_R;
}
void GPTM_VoidSetTimerStatus(TIMER_Status_e TIMER_Status, TIMERS_e Timer, TIMER_Counters_e Timer_Counter)
{
    if (TIMER_Status == TIMER_ENABLED)
    {
        GPTMS[Timer]->CTL |= (1 << (Timer_Counter * 8));
    }
    else
    {
        GPTMS[Timer]->CTL &= ~(1 << (Timer_Counter * 8));
    }
}
void GPTM_VoidSetTimerMode(TIMER_Mode_e TIMER_Mode, TIMERS_e Timer)
{
    GPTMS[Timer]->CFG = TIMER_Mode;
}
void GPTM_VoidSetTimerPeriodicity(TIMER_Periodicity_e TIMER_Periodicity, TIMERS_e Timer, TIMER_Counters_e Timer_Counter)
{
    if (Timer_Counter == COUNTER_A)
    {
        GPTMS[Timer]->TAMR &= ~0x3;
        GPTMS[Timer]->TAMR |= TIMER_Periodicity;
    }
    else
    {
        GPTMS[Timer]->TBMR &= ~0x3;
        GPTMS[Timer]->TBMR |= TIMER_Periodicity;
    }
}
void GPTM_VoidSetTimerCountingDirection(TIMER_Counting_Direction_e TIMER_Counting_Direction, TIMERS_e Timer, TIMER_Counters_e Timer_Counter)
{
    if (Timer_Counter == COUNTER_A)
    {
        if (TIMER_Counting_Direction == TIMER_COUNTING_DOWN)
        {
            GPTMS[Timer]->TAMR &= ~(1 << 4);
        }
        else
        {
            GPTMS[Timer]->TAMR |= (1 << 4);
        }
    }
    else
    {
        if (TIMER_Counting_Direction == TIMER_COUNTING_DOWN)
        {
            GPTMS[Timer]->TBMR &= ~(1 << 4);
        }
        else
        {
            GPTMS[Timer]->TBMR |= (1 << 4);
        }
    }
}
void GPTM_VoidSetTimerReloadValue(TIMERS_e Timer, TIMER_Counters_e Timer_Counter, TIMER_Period_t Period)
{
    if (Timer_Counter == COUNTER_A)
        GPTMS[Timer]->TAILR = Period - 1;
    else
    {
        GPTMS[Timer]->TBILR = Period - 1;
    }
}
void GPTM_VoidSetTimerPrescalarValue(TIMERS_e Timer, TIMER_Counters_e Timer_Counter, TIMER_Prescalar_t Prescalar)
{
    if (Timer_Counter == COUNTER_A)
        GPTMS[Timer]->TAPR = Prescalar;
    else
    {
        GPTMS[Timer]->TBPR = Prescalar;
    }
}
void GPTM_VoidClearTimerTimeOutRawInterrupt(TIMERS_e Timer, TIMER_Counters_e Timer_Counter)
{
    GPTMS[Timer]->ICR |= (1 << (Timer_Counter * 8));
}
void GPTM_VoidSetTimerTimeOutRawInterruptStatus(TIMERS_e Timer, TIMER_Counters_e Timer_Counter, TIMER_Time_Out_Interrupt_Status_e TIMER_Time_Out_Interrupt_Status)
{
    if (TIMER_Time_Out_Interrupt_Status == TIME_OUT_INT_DISABLED)
    {
        GPTMS[Timer]->IMR &= ~(1 << (Timer_Counter * 8));
    }
    else
    {
        GPTMS[Timer]->IMR |= (1 << (Timer_Counter * 8));
    }
}
void GPTM_VoidSetTimeOutRawInterruptCallBack(TIMERS_e Timer, TIMER_Counters_e Timer_Counter, TIMER_CallBack_t Ptr_To_Function)
{
    Raw_Interrupt_CallBacks[Timer][Timer_Counter] = Ptr_To_Function;
}
void GPTM_VoidSetBusyWaitinMS(TIMERS_e Timer, TIMER_Counters_e Timer_Counter, TIMER_time_t Time_In_MS)
{
    GPTM_VoidSetTimerStatus(TIMER_DISABLED, Timer, Timer_Counter);
    TIMER_Period_t TIMER_Period = TICKS_PER_SECOND * Time_In_MS / 1000 - 1;
    GPTM_VoidSetTimerReloadValue(Timer, Timer_Counter, TIMER_Period);
    GPTM_VoidSetTimerStatus(TIMER_ENABLED, Timer, Timer_Counter);
    while ((GPTMS[Timer]->RIS & (1 << (Timer_Counter * 8))) == 0)
        ;
    GPTM_VoidClearTimerTimeOutRawInterrupt(Timer, Timer_Counter);
}
void Timer0A_Handler(void)
{
    GPTM_VoidClearTimerTimeOutRawInterrupt(TIMER_0, COUNTER_A);

    if (Raw_Interrupt_CallBacks[TIMER_0][COUNTER_A] != NULL)
    {
        Raw_Interrupt_CallBacks[TIMER_0][COUNTER_A]();
    }
}
void Timer0B_Handler(void)
{
    GPTM_VoidClearTimerTimeOutRawInterrupt(TIMER_0, COUNTER_B);
    if (Raw_Interrupt_CallBacks[TIMER_0][COUNTER_B] != NULL)
    {
        Raw_Interrupt_CallBacks[TIMER_0][COUNTER_B]();
    }
}
void Timer1A_Handler(void)
{
    GPTM_VoidClearTimerTimeOutRawInterrupt(TIMER_1, COUNTER_A);

    if (Raw_Interrupt_CallBacks[TIMER_1][COUNTER_A] != NULL)
    {
        Raw_Interrupt_CallBacks[TIMER_1][COUNTER_A]();
    }
}
void Timer1B_Handler(void)
{
    GPTM_VoidClearTimerTimeOutRawInterrupt(TIMER_1, COUNTER_B);

    if (Raw_Interrupt_CallBacks[TIMER_1][COUNTER_B] != NULL)
    {
        Raw_Interrupt_CallBacks[TIMER_1][COUNTER_B]();
    }
}
void Timer2A_Handler(void)
{
    GPTM_VoidClearTimerTimeOutRawInterrupt(TIMER_2, COUNTER_A);

    if (Raw_Interrupt_CallBacks[TIMER_2][COUNTER_A] != NULL)
    {
        Raw_Interrupt_CallBacks[TIMER_2][COUNTER_A]();
    }
}
void Timer2B_Handler(void)
{
    GPTM_VoidClearTimerTimeOutRawInterrupt(TIMER_2, COUNTER_B);

    if (Raw_Interrupt_CallBacks[TIMER_2][COUNTER_B] != NULL)
    {
        Raw_Interrupt_CallBacks[TIMER_2][COUNTER_B]();
    }
}
void Timer3A_Handler(void)
{
    GPTM_VoidClearTimerTimeOutRawInterrupt(TIMER_3, COUNTER_A);

    if (Raw_Interrupt_CallBacks[TIMER_3][COUNTER_A] != NULL)
    {
        Raw_Interrupt_CallBacks[TIMER_3][COUNTER_A]();
    }
}
void Timer3B_Handler(void)
{
    GPTM_VoidClearTimerTimeOutRawInterrupt(TIMER_3, COUNTER_B);

    if (Raw_Interrupt_CallBacks[TIMER_3][COUNTER_B] != NULL)
    {
        Raw_Interrupt_CallBacks[TIMER_3][COUNTER_B]();
    }
}
void Timer4A_Handler(void)
{
    GPTM_VoidClearTimerTimeOutRawInterrupt(TIMER_4, COUNTER_A);

    if (Raw_Interrupt_CallBacks[TIMER_4][COUNTER_A] != NULL)
    {
        Raw_Interrupt_CallBacks[TIMER_4][COUNTER_A]();
    }
}
void Timer4B_Handler(void)
{
    GPTM_VoidClearTimerTimeOutRawInterrupt(TIMER_4, COUNTER_B);

    if (Raw_Interrupt_CallBacks[TIMER_4][COUNTER_B] != NULL)
    {
        Raw_Interrupt_CallBacks[TIMER_4][COUNTER_B]();
    }
}
void Timer5A_Handler(void)
{
    GPTM_VoidClearTimerTimeOutRawInterrupt(TIMER_5, COUNTER_A);

    if (Raw_Interrupt_CallBacks[TIMER_5][COUNTER_A] != NULL)
    {
        Raw_Interrupt_CallBacks[TIMER_5][COUNTER_A]();
    }
}
void Timer5B_Handler(void)
{
    GPTM_VoidClearTimerTimeOutRawInterrupt(TIMER_5, COUNTER_B);

    if (Raw_Interrupt_CallBacks[TIMER_5][COUNTER_B] != NULL)
    {
        Raw_Interrupt_CallBacks[TIMER_5][COUNTER_B]();
    }
}