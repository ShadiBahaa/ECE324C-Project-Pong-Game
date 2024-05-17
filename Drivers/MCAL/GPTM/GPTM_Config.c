#include "GPTM_Config.h"
#include "GPTM_Interface.h"

GPTM_Config_t GPTM_Config = {
    .TIMER_Blocks[2] = {
        .TIMER_Clock_Status = TIMER_CLOCK_ENABLED,
        .TIMER_Mode = TIMER_32_64_BIT_MODE,
        .Timers[0] = {
            .TIMER_Status = TIMER_ENABLED,
            .TIMER_Periodicity = TIMER_PERIODIC_MODE,
            .TIMER_Counting_Direction = TIMER_COUNTING_DOWN,
            .TIMER_Period = 800000*3/2 -1,
            .TIMER_Prescalar = 0,
            .TIMER_Time_Out_Interrupt_Status = TIME_OUT_INT_ENABLED,
        }},
    .TIMER_Blocks[1] = {.TIMER_Clock_Status = TIMER_CLOCK_ENABLED, .TIMER_Mode = TIMER_32_64_BIT_MODE, .Timers[0] = {
                                                                                                           .TIMER_Status = TIMER_ENABLED,
                                                                                                           .TIMER_Periodicity = TIMER_PERIODIC_MODE,
                                                                                                           .TIMER_Counting_Direction = TIMER_COUNTING_DOWN,
                                                                                                       }}};
