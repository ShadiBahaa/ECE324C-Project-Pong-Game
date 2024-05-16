#ifndef _GPTM_INTERFACE_H_
#define _GPTM_INTERFACE_H_

typedef enum
{
    TIMER_0,
    TIMER_1,
    TIMER_2,
    TIMER_3,
    TIMER_4,
    TIMER_5,
} TIMERS_e;
typedef enum
{
    COUNTER_A,
    COUNTER_B
} TIMER_Counters_e;
typedef enum
{
    TIMER_CLOCK_DISABLED,
    TIMER_CLOCK_ENABLED
} TIMER_Clock_Status_e;
typedef enum
{
    TIMER_32_64_BIT_MODE,
    TIMER_32_64_RTC_BIT_MODE,
    TIMER_16_32_BIT_MODE = 4
} TIMER_Mode_e;
typedef enum
{
    UPDATE_ERROR_INT_DISABLED,
    UPDATE_ERROR_INT_ENABLED
} TIMER_Update_Error_Interrupt_Status_e;

typedef enum
{
    TIMER_DISABLED,
    TIMER_ENABLED
} TIMER_Status_e;
typedef enum
{
    CCP_LOW,
    CCP_HIGH
} TIMER_PWM_Legacy_Op_Status_e;

typedef enum
{
    ON_THE_NEXT_CYCLE,
    ON_THE_NEXT_TIMEOUT
} TIMER_Match_Register_Update_Status_e;

typedef enum
{
    CEI_INTERRUPT_DISABLED,
    CEI_INTERRUPT_ENABLED,
} TIMER_PWM_Interrupt_Status_e;

typedef enum
{
    UPDATE_ON_THE_NEXT_CYCLE,
    UPDATE_ON_THE_NEXT_TIMEOUT
} TIMER_Interval_Load_Write_Status_e;
typedef enum
{
    TIMER_SNAP_SHOT_DISABLE,
    TIMER_SNAP_SHOT_ENABLED
} TIMER_Snap_Shot_Mode_e;
typedef enum
{
    COUTING_ON_ENABLE,
    COUTING_ON_TRIGGER
} TIMER_Wait_On_Trigger_Status_e;
typedef enum
{
    MATCH_INTERRUPT_DISABLED,
    MATCH_INTERRUPT_ENABLED,
} TIMER_Match_Interrupt_Status_e;

typedef enum
{
    TIMER_COUNTING_DOWN,
    TIMER_COUNTING_UP,
} TIMER_Counting_Direction_e;

typedef enum
{
    CAPTURE_COMPARE_MODE,
    PWM_MODE,
} TIMER_Alternate_Mode_e;
typedef enum
{
    EDGE_COUNT_MODE,
    EDGE_TIME_MODE,
} TIMER_Capture_Mode_e;

typedef enum
{
    TIMER_ONE_SHOT_MODE = 1,
    TIMER_PERIODIC_MODE,
    TIMER_CAPTURE_MODE
} TIMER_Periodicity_e;

typedef enum
{
    OUTPUT_UNAFFECTED,
    OUTPUT_INVERTED
} TIMER_PWM_Output_Level_e;

typedef enum
{
    ADC_TRIGGER_DISABLED,
    ADC_TRIGGER_ENABLED
} TIMER_Output_Trigger_Status_e;

typedef enum
{
    POSITIVE_EDGE,
    NEGATIVE_EDGE,
    BOTH_EDGES = 3
} TIMER_Event_Mode_e;

typedef enum
{
    CONTINUE_WHILE_HALTING,
    FREEZING_WHILE_HALTING
} TIMER_Stall_Status_e;

typedef enum
{
    CAPTURE_MODE_EVENT_INT_DISABLED,
    CAPTURE_MODE_EVENT_INT_ENABLED
} TIMER_Capture_Mode_Event_Interrupt_Status_e;

typedef enum
{
    CAPTURE_MODE_MATCH_INT_DISABLED,
    CAPTURE_MODE_MATCH_INT_ENABLED
} TIMER_Capture_Mode_Match_Interrupt_Status_e;

typedef enum
{
    TIME_OUT_INT_DISABLED,
    TIME_OUT_INT_ENABLED
} TIMER_Time_Out_Interrupt_Status_e;

typedef unsigned long int TIMER_Period_t;
typedef unsigned long int TIMER_time_t;
typedef unsigned long int TIMER_Prescalar_t;
typedef void (*TIMER_CallBack_t)(void);

typedef struct
{
    TIMER_Status_e TIMER_Status;
    TIMER_Periodicity_e TIMER_Periodicity;
    TIMER_PWM_Legacy_Op_Status_e TIMER_PWM_Legacy_Op_Status;
    TIMER_Match_Register_Update_Status_e TIMER_Match_Register_Update_Status;
    TIMER_PWM_Interrupt_Status_e TIMER_PWM_Interrupt_Status;
    TIMER_Interval_Load_Write_Status_e TIMER_Interval_Load_Write_Status;
    TIMER_Snap_Shot_Mode_e TIMER_Snap_Shot_Mode;
    TIMER_Wait_On_Trigger_Status_e TIMER_Wait_On_Trigger_Status;
    TIMER_Match_Interrupt_Status_e TIMER_Match_Interrupt_Status;
    TIMER_Counting_Direction_e TIMER_Counting_Direction;
    TIMER_Alternate_Mode_e TIMER_Alternate_Mode;
    TIMER_Capture_Mode_e TIMER_Capture_Mode;
    TIMER_PWM_Output_Level_e TIMER_PWM_Output_Level;
    TIMER_Output_Trigger_Status_e TIMER_Output_Trigger_Status;
    TIMER_Event_Mode_e TIMER_Event_Mode;
    TIMER_Stall_Status_e TIMER_Stall_Status;
    TIMER_Capture_Mode_Event_Interrupt_Status_e TIMER_Capture_Mode_Event_Interrupt_Status;
    TIMER_Capture_Mode_Match_Interrupt_Status_e TIMER_Capture_Mode_Match_Interrupt_Status;
    TIMER_Time_Out_Interrupt_Status_e TIMER_Time_Out_Interrupt_Status;
    TIMER_Period_t TIMER_Period;
    TIMER_Prescalar_t TIMER_Prescalar;
} TIMER_Config_t;

typedef struct
{
    TIMER_Config_t Timers[2];
    TIMER_Clock_Status_e TIMER_Clock_Status;
    TIMER_Mode_e TIMER_Mode;
    TIMER_Update_Error_Interrupt_Status_e TIMER_Update_Error_Interrupt_Status;
} TIMER_Block_Config_t;

typedef struct
{
    TIMER_Block_Config_t TIMER_Blocks[TIMERS_BLOCKS_COUNT];
} GPTM_Config_t;

void GPTM_VoidInit(GPTM_Config_t *GPTM_Config);
void GPTM_VoidSetTimerStatus(TIMER_Status_e TIMER_Status, TIMERS_e Timer, TIMER_Counters_e Timer_Counter);
void GPTM_VoidSetTimerClockStatus(TIMER_Clock_Status_e TIMER_Clock_Status, TIMERS_e Timer);
void GPTM_VoidSetTimerMode(TIMER_Mode_e TIMER_Mode, TIMERS_e Timer);
void GPTM_VoidSetTimerPeriodicity(TIMER_Periodicity_e TIMER_Periodicity, TIMERS_e Timer, TIMER_Counters_e Timer_Counter);
void GPTM_VoidSetTimerCountingDirection(TIMER_Counting_Direction_e TIMER_Counting_Direction, TIMERS_e Timer, TIMER_Counters_e Timer_Counter);
void GPTM_VoidSetTimerReloadValue(TIMERS_e Timer, TIMER_Counters_e Timer_Counter, TIMER_Period_t Period);
void GPTM_VoidSetTimerPrescalarValue(TIMERS_e Timer, TIMER_Counters_e Timer_Counter, TIMER_Prescalar_t Prescalar);
void GPTM_VoidClearTimerTimeOutRawInterrupt(TIMERS_e Timer, TIMER_Counters_e Timer_Counter);
void GPTM_VoidSetTimerTimeOutRawInterruptStatus(TIMERS_e Timer, TIMER_Counters_e Timer_Counter, TIMER_Time_Out_Interrupt_Status_e TIMER_Time_Out_Interrupt_Status);
void GPTM_VoidSetTimeOutRawInterruptCallBack(TIMERS_e Timer, TIMER_Counters_e Timer_Counter, TIMER_CallBack_t Ptr_To_Function);
void GPTM_VoidSetBusyWaitinMS(TIMERS_e Timer, TIMER_Counters_e Timer_Counter, TIMER_time_t Time_In_MS);
#endif