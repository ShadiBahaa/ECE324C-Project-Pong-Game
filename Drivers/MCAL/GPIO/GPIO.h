#ifndef GPIO_H
#define GPIO_H

#include "GPIO_Cfg.h"

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;

// Return type for the GPIO functions
typedef enum GPIO_Ret_e
{
	GPIO_RET_OK,
	GPIO_RET_ERROR
} GPIO_Ret_t;

// GPIO port enumeration
typedef enum GPIO_Port_e
{
	GPIO_PORT_A,
	GPIO_PORT_B,
	GPIO_PORT_C,
	GPIO_PORT_D,
	GPIO_PORT_E,
	GPIO_PORT_F
} GPIO_Port_t;

// GPIO pin enumeration
typedef enum GPIO_Pin_e
{
	GPIO_PIN_0,
	GPIO_PIN_1,
	GPIO_PIN_2,
	GPIO_PIN_3,
	GPIO_PIN_4,
	GPIO_PIN_5,
	GPIO_PIN_6,
	GPIO_PIN_7
} GPIO_Pin_t;

// GPIO pin status
typedef enum GPIO_PinStatus_e
{
	GPIO_LOW,
	GPIO_HIGH
} GPIO_PinStatus_t;

// GPIO port state enumeration
typedef enum GPIO_PortState_e
{
	GPIO_PORT_DISABLE,
	GPIO_PORT_ENABLE
} GPIO_PortState_t;

// GPIO pin state enumeration
typedef enum GPIO_PinState_e
{
	GPIO_PIN_DISABLE,
	GPIO_PIN_ENABLE
} GPIO_PinState_t;

// GPIO direction enumeration
typedef enum GPIO_Dir_e
{
	GPIO_DIR_INPUT,
	GPIO_DIR_OUTPUT
} GPIO_Dir_t;

// GPIO function enumeration
typedef enum GPIO_Function_e
{
	GPIO_FUNCTION_GPIO,
	GPIO_FUNCTION_TIMER = PCTL_TIMER,
	GPIO_FUNCTION_UART = PCTL_UART,
	GPIO_FUNCTION_SSI = PCTL_SSI,
	GPIO_FUNCTION_ADC = PCTL_ADC
} GPIO_Function_t;

// GPIO pad configuration enumeration
typedef enum GPIO_PadConfig_e
{
	GPIO_PAD_CONFIG_STANDARD,
	GPIO_PAD_CONFIG_WEAK_PULL_UP,
	GPIO_PAD_CONFIG_WEAK_PULL_DOWN,
	GPIO_PAD_CONFIG_OPEN_DRAIN
} GPIO_PadConfig_t;

// GPIO strength enumeration
typedef enum GPIO_Strength_e
{
	GPIO_STRENGTH_2MA,
	GPIO_STRENGTH_4MA,
	GPIO_STRENGTH_8MA
} GPIO_Strength_t;

// GPIO digital/analog select enumeration
typedef enum GPIO_DigitalAnalogSelect_e
{
	GPIO_MODE_DIGITAL,
	GPIO_MODE_ANALOG
} GPIO_DigitalAnalogSelect_t;

// GPIO Interrupt event enumeration
typedef enum GPIO_InterruptEvent_e
{
	GPIO_INTERRUPT_EVENT_NONE, // Disable the interrupt
	GPIO_INTERRUPT_EVENT_FALLING_EDGE,
	GPIO_INTERRUPT_EVENT_RISING_EDGE,
	GPIO_INTERRUPT_EVENT_BOTH_EDGES,
	GPIO_INTERRUPT_EVENT_LOW_LEVEL,
	GPIO_INTERRUPT_EVENT_HIGH_LEVEL
} GPIO_InterruptEvent_t;

// GPIO Interrupt status enumeration
typedef enum GPIO_InterruptStatus_e
{
	GPIO_INTERRUPT_STATUS_NONE,
	GPIO_INTERRUPT_STATUS_OCCURRED
} GPIO_InterruptStatus_t;

// GPIO pin configurations structure
typedef struct GPIO_PinConfigurations_s
{
	GPIO_PinState_t pinState;
	GPIO_Dir_t pinDirection;
	GPIO_Function_t pinFunction;
	GPIO_Strength_t pinStrength;
	GPIO_PadConfig_t padConfig;
	GPIO_DigitalAnalogSelect_t digitalAnalogSelect;
	GPIO_InterruptEvent_t interruptEvent;

} GPIO_PinConfigurations_t;

// GPIO port configurations structure
typedef struct GPIO_PortConfigurations_s
{
	GPIO_PortState_t portState;
	GPIO_PinConfigurations_t pinsCfgs[MAX_PIN_NUMBER];

} GPIO_PortConfigurations_t;

// GPIO configurations structure
typedef struct GPIO_Configurations_s
{
	GPIO_PortConfigurations_t portsCfgs[MAX_PORT_NUMBER];
} GPIO_Configurations_t;

// GPIO interrupt handler function pointer
typedef void (*GPIO_CallBack_t)(void);

// Function prototypes
// Initialize the GPIO module
GPIO_Ret_t GPIO_Init(void);

// Enable/Disable the port
GPIO_Ret_t GPIO_EnablePort(GPIO_Port_t portNum);
GPIO_Ret_t GPIO_DisablePort(GPIO_Port_t portNum);

// Enable/Disable the pin
GPIO_Ret_t GPIO_EnablePin(GPIO_Port_t portNum, GPIO_Pin_t pinNum);
GPIO_Ret_t GPIO_DisablePin(GPIO_Port_t portNum, GPIO_Pin_t pinNum);

// Set/Get the direction of the pin
GPIO_Ret_t GPIO_SetDirection(GPIO_Port_t portNum, GPIO_Pin_t pinNum, GPIO_Dir_t direction);
GPIO_Dir_t GPIO_GetDirection(GPIO_Port_t portNum, GPIO_Pin_t pinNum);

// Set/Get the function of the pin
GPIO_Ret_t GPIO_SetFunction(GPIO_Port_t portNum, GPIO_Pin_t pinNum, GPIO_Function_t function);
GPIO_Function_t GPIO_GetFunction(GPIO_Port_t portNum, GPIO_Pin_t pinNum);

// Set/Get the digital/analog select of the pin
GPIO_Ret_t GPIO_SetDigitalAnalogSelect(GPIO_Port_t portNum, GPIO_Pin_t pinNum, GPIO_DigitalAnalogSelect_t digitalAnalogSelect);
GPIO_DigitalAnalogSelect_t GPIO_GetDigitalAnalogSelect(GPIO_Port_t portNum, GPIO_Pin_t pinNum);

// Set/Get the strength of the pin
GPIO_Ret_t GPIO_SetStrength(GPIO_Port_t portNum, GPIO_Pin_t pinNum, GPIO_Strength_t strength);
GPIO_Strength_t GPIO_GetStrength(GPIO_Port_t portNum, GPIO_Pin_t pinNum);

// Set/Get the pad configuration of the pin
GPIO_Ret_t GPIO_SetPadConfig(GPIO_Port_t portNum, GPIO_Pin_t pinNum, GPIO_PadConfig_t padConfig);
GPIO_PadConfig_t GPIO_GetPadConfig(GPIO_Port_t portNum, GPIO_Pin_t pinNum);

// Enable/Disable the interrupt of the pin
GPIO_Ret_t GPIO_EnableInterrupt(GPIO_Port_t portNum, GPIO_Pin_t pinNum);
GPIO_Ret_t GPIO_DisableInterrupt(GPIO_Port_t portNum, GPIO_Pin_t pinNum);

// Set/Get the interrupt event of the pin
GPIO_Ret_t GPIO_SetInterruptEvent(GPIO_Port_t portNum, GPIO_Pin_t pinNum, GPIO_InterruptEvent_t interruptEvent);
GPIO_InterruptEvent_t GPIO_GetInterruptEvent(GPIO_Port_t portNum, GPIO_Pin_t pinNum);

// Clear the interrupt of the pin (Acknowledge the interrupt)
GPIO_Ret_t GPIO_ClearInterrupt(GPIO_Port_t portNum, GPIO_Pin_t pinNum);

// Get the interrupt status of the pin
GPIO_InterruptStatus_t GPIO_GetInterruptStatus(GPIO_Port_t portNum, GPIO_Pin_t pinNum, uint8_t masked);

// Register the interrupt handler
GPIO_Ret_t GPIO_RegisterInterruptHandler(GPIO_Port_t portNum, GPIO_Pin_t pinNum, void (*handler)(void));

// Unregister the interrupt handler
GPIO_Ret_t GPIO_UnregisterInterruptHandler(GPIO_Port_t portNum, GPIO_Pin_t pinNum);

// Write/Read the pin
void GPIO_WritePin(GPIO_Port_t portNum, GPIO_Pin_t pinNum, GPIO_PinStatus_t status);
GPIO_PinStatus_t GPIO_ReadPin(GPIO_Port_t portNum, GPIO_Pin_t pinNum);

#endif // GPIO_H
