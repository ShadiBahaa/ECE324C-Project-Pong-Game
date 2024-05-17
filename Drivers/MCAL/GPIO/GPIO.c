#include "GPIO.h"
#include "../../LIB/STD_TYPES.h"
#include "../../TM4C123GH6PMn.h"

GPIOA_Type *GPIO_PORTS[] = {
	GPIOA,
	GPIOB,
	GPIOC,
	GPIOD,
	GPIOE,
	GPIOF};

extern GPIO_Configurations_t *GPIOCfgs;

GPIO_CallBack_t InterruptHandlers[MAX_PORT_NUMBER][MAX_PIN_NUMBER];

GPIO_Ret_t GPIO_Init()
{
	volatile unsigned long delay;
	int portNum, pinNum;
	for (portNum = 0; portNum < MAX_PORT_NUMBER; ++portNum)
	{
		if (GPIOCfgs->portsCfgs[portNum].portState == GPIO_PORT_ENABLE)
		{
			// enable clock to the port
			SYSCTL->RCGC2 |= (1 << portNum);
			delay = SYSCTL->RCGC2;

			// configure pins
			for (pinNum = 0; pinNum < MAX_PIN_NUMBER; ++pinNum)
			{
				if (GPIOCfgs->portsCfgs[portNum].pinsCfgs[pinNum].pinState == GPIO_PIN_ENABLE)
				{

					// unlock the pin
					GPIO_PORTS[portNum]->LOCK = 0x4C4F434B;
					GPIO_PORTS[portNum]->CR |= (1 << pinNum);

					// set direction
					if (GPIOCfgs->portsCfgs[portNum].pinsCfgs[pinNum].pinDirection == GPIO_DIR_INPUT)
					{
						GPIO_PORTS[portNum]->DIR &= ~(1 << pinNum);
					}
					else
					{
						GPIO_PORTS[portNum]->DIR |= (1 << pinNum);
					}

					// set the function of the pin
					if (GPIOCfgs->portsCfgs[portNum].pinsCfgs[pinNum].pinFunction == GPIO_FUNCTION_GPIO)
					{
						GPIO_PORTS[portNum]->AFSEL &= ~(1 << pinNum);
						GPIO_PORTS[portNum]->PCTL &= ~(0xF << (pinNum * 4));
					}
					else
					{
						GPIO_PORTS[portNum]->AFSEL |= (1 << pinNum);
						GPIO_PORTS[portNum]->PCTL = (GPIO_PORTS[portNum]->PCTL & ~(0xF << (pinNum * 4))) | (GPIOCfgs->portsCfgs[portNum].pinsCfgs[pinNum].pinFunction << (pinNum * 4));
					}

					// set the pin strength
					if (GPIOCfgs->portsCfgs[portNum].pinsCfgs[pinNum].pinStrength == GPIO_STRENGTH_2MA)
					{
						GPIO_PORTS[portNum]->DR2R |= (1 << pinNum);
					}
					else if (GPIOCfgs->portsCfgs[portNum].pinsCfgs[pinNum].pinStrength == GPIO_STRENGTH_4MA)
					{
						GPIO_PORTS[portNum]->DR4R |= (1 << pinNum);
					}
					else if (GPIOCfgs->portsCfgs[portNum].pinsCfgs[pinNum].pinStrength == GPIO_STRENGTH_8MA)
					{
						GPIO_PORTS[portNum]->DR8R |= (1 << pinNum);
					}

					// set the pad configuration
					if (GPIOCfgs->portsCfgs[portNum].pinsCfgs[pinNum].padConfig == GPIO_PAD_CONFIG_WEAK_PULL_UP)
					{
						GPIO_PORTS[portNum]->PUR |= (1 << pinNum);
					}
					else if (GPIOCfgs->portsCfgs[portNum].pinsCfgs[pinNum].padConfig == GPIO_PAD_CONFIG_WEAK_PULL_DOWN)
					{
						GPIO_PORTS[portNum]->PDR |= (1 << pinNum);
					}
					else if (GPIOCfgs->portsCfgs[portNum].pinsCfgs[pinNum].padConfig == GPIO_PAD_CONFIG_OPEN_DRAIN)
					{
						GPIO_PORTS[portNum]->ODR |= (1 << pinNum);
					}

					// set the digital/analog mode
					if (GPIOCfgs->portsCfgs[portNum].pinsCfgs[pinNum].digitalAnalogSelect == GPIO_MODE_DIGITAL)
					{
						GPIO_PORTS[portNum]->DEN |= (1 << pinNum);
						GPIO_PORTS[portNum]->AMSEL &= ~(1 << pinNum);
					}
					else
					{
						GPIO_PORTS[portNum]->AMSEL |= (1 << pinNum);
						GPIO_PORTS[portNum]->DEN &= ~(1 << pinNum);
					}

					// set the interrupt event
					if (GPIOCfgs->portsCfgs[portNum].pinsCfgs[pinNum].interruptEvent != GPIO_INTERRUPT_EVENT_NONE)
					{
						// disable the interrupt
						GPIO_PORTS[portNum]->IM &= ~(1 << pinNum);

						if (GPIOCfgs->portsCfgs[portNum].pinsCfgs[pinNum].interruptEvent == GPIO_INTERRUPT_EVENT_FALLING_EDGE)
						{
							GPIO_PORTS[portNum]->IS &= ~(1 << pinNum);
							GPIO_PORTS[portNum]->IBE &= ~(1 << pinNum);
							GPIO_PORTS[portNum]->IEV &= ~(1 << pinNum);
						}
						else if (GPIOCfgs->portsCfgs[portNum].pinsCfgs[pinNum].interruptEvent == GPIO_INTERRUPT_EVENT_RISING_EDGE)
						{
							GPIO_PORTS[portNum]->IS &= ~(1 << pinNum);
							GPIO_PORTS[portNum]->IBE &= ~(1 << pinNum);
							GPIO_PORTS[portNum]->IEV |= (1 << pinNum);
						}
						else if (GPIOCfgs->portsCfgs[portNum].pinsCfgs[pinNum].interruptEvent == GPIO_INTERRUPT_EVENT_BOTH_EDGES)
						{
							GPIO_PORTS[portNum]->IS &= ~(1 << pinNum);
							GPIO_PORTS[portNum]->IBE |= (1 << pinNum);
						}
						else if (GPIOCfgs->portsCfgs[portNum].pinsCfgs[pinNum].interruptEvent == GPIO_INTERRUPT_EVENT_LOW_LEVEL)
						{
							GPIO_PORTS[portNum]->IS |= (1 << pinNum);
							GPIO_PORTS[portNum]->IEV &= ~(1 << pinNum);
						}
						else if (GPIOCfgs->portsCfgs[portNum].pinsCfgs[pinNum].interruptEvent == GPIO_INTERRUPT_EVENT_HIGH_LEVEL)
						{
							GPIO_PORTS[portNum]->IS |= (1 << pinNum);
							GPIO_PORTS[portNum]->IEV |= (1 << pinNum);
						}

						// clear the interrupt flag and enable the interrupt
						GPIO_PORTS[portNum]->ICR |= (1 << pinNum);
						GPIO_PORTS[portNum]->IM |= (1 << pinNum);
					}
				}
			}
		}
	}

	return GPIO_RET_OK;
}

GPIO_Ret_t GPIO_EnablePort(GPIO_Port_t portNum)
{
	if (GPIOCfgs->portsCfgs[portNum].portState == GPIO_PORT_DISABLE)
	{
		GPIOCfgs->portsCfgs[portNum].portState = GPIO_PORT_ENABLE;
		// enable clock to the port
		SYSCTL->RCGC2 |= (1 << portNum);
		volatile unsigned long delay = SYSCTL->RCGC2;
		return GPIO_RET_OK;
	}
	return GPIO_RET_ERROR;
}

GPIO_Ret_t GPIO_DisablePort(GPIO_Port_t portNum)
{
	if (GPIOCfgs->portsCfgs[portNum].portState == GPIO_PORT_ENABLE)
	{
		GPIOCfgs->portsCfgs[portNum].portState = GPIO_PORT_DISABLE;
		// disable clock to the port
		SYSCTL->RCGC2 &= ~(1 << portNum);
		return GPIO_RET_OK;
	}
	return GPIO_RET_ERROR;
}

GPIO_Ret_t GPIO_EnablePin(GPIO_Port_t portNum, GPIO_Pin_t pinNum)
{
	if (GPIOCfgs->portsCfgs[portNum].portState == GPIO_PORT_DISABLE)
	{
		return GPIO_RET_ERROR;
	}
	GPIOCfgs->portsCfgs[portNum].pinsCfgs[pinNum].pinState = GPIO_PIN_ENABLE;

	// unlock the pin
	GPIO_PORTS[portNum]->LOCK = 0x4C4F434B;
	GPIO_PORTS[portNum]->CR |= (1 << pinNum);
	return GPIO_RET_OK;
}

GPIO_Ret_t GPIO_DisablePin(GPIO_Port_t portNum, GPIO_Pin_t pinNum)
{
	if (GPIOCfgs->portsCfgs[portNum].portState == GPIO_PORT_DISABLE)
	{
		return GPIO_RET_ERROR;
	}
	GPIOCfgs->portsCfgs[portNum].pinsCfgs[pinNum].pinState = GPIO_PIN_DISABLE;
	return GPIO_RET_OK;
}

GPIO_Ret_t GPIO_SetDirection(GPIO_Port_t portNum, GPIO_Pin_t pinNum, GPIO_Dir_t direction)
{
	if (GPIOCfgs->portsCfgs[portNum].portState == GPIO_PORT_DISABLE)
	{
		return GPIO_RET_ERROR;
	}
	if (GPIOCfgs->portsCfgs[portNum].pinsCfgs[pinNum].pinState == GPIO_PIN_DISABLE)
	{
		return GPIO_RET_ERROR;
	}
	if (direction == GPIO_DIR_INPUT)
	{
		GPIO_PORTS[portNum]->DIR &= ~(1 << pinNum);
	}
	else
	{
		GPIO_PORTS[portNum]->DIR |= (1 << pinNum);
	}
	return GPIO_RET_OK;
}

GPIO_Dir_t GPIO_GetDirection(GPIO_Port_t portNum, GPIO_Pin_t pinNum)
{
	if (GPIO_PORTS[portNum]->DIR & (1 << pinNum))
	{
		return GPIO_DIR_OUTPUT;
	}
	return GPIO_DIR_INPUT;
}

GPIO_Ret_t GPIO_SetFunction(GPIO_Port_t portNum, GPIO_Pin_t pinNum, GPIO_Function_t function)
{
	if (GPIOCfgs->portsCfgs[portNum].portState == GPIO_PORT_DISABLE)
	{
		return GPIO_RET_ERROR;
	}
	if (GPIOCfgs->portsCfgs[portNum].pinsCfgs[pinNum].pinState == GPIO_PIN_DISABLE)
	{
		return GPIO_RET_ERROR;
	}
	if (function == GPIO_FUNCTION_GPIO)
	{
		GPIO_PORTS[portNum]->AFSEL &= ~(1 << pinNum);
		GPIO_PORTS[portNum]->PCTL &= ~(0xF << (pinNum * 4));
	}
	else
	{
		GPIO_PORTS[portNum]->AFSEL |= (1 << pinNum);
		GPIO_PORTS[portNum]->PCTL = (GPIO_PORTS[portNum]->PCTL & ~(0xF << (pinNum * 4))) | (function << (pinNum * 4));
	}
	return GPIO_RET_OK;
}

GPIO_Function_t GPIO_GetFunction(GPIO_Port_t portNum, GPIO_Pin_t pinNum)
{
	if (GPIO_PORTS[portNum]->AFSEL & (1 << pinNum))
	{
		return (GPIO_Function_t)((GPIO_PORTS[portNum]->PCTL & (0xF << (pinNum * 4))) >> (pinNum * 4));
	}
	return GPIO_FUNCTION_GPIO;
}

GPIO_Ret_t GPIO_SetStrength(GPIO_Port_t portNum, GPIO_Pin_t pinNum, GPIO_Strength_t strength)
{
	if (GPIOCfgs->portsCfgs[portNum].portState == GPIO_PORT_DISABLE)
	{
		return GPIO_RET_ERROR;
	}
	if (GPIOCfgs->portsCfgs[portNum].pinsCfgs[pinNum].pinState == GPIO_PIN_DISABLE)
	{
		return GPIO_RET_ERROR;
	}
	if (strength == GPIO_STRENGTH_2MA)
	{
		GPIO_PORTS[portNum]->DR2R |= (1 << pinNum);
	}
	else if (strength == GPIO_STRENGTH_4MA)
	{
		GPIO_PORTS[portNum]->DR4R |= (1 << pinNum);
	}
	else if (strength == GPIO_STRENGTH_8MA)
	{
		GPIO_PORTS[portNum]->DR8R |= (1 << pinNum);
	}
	return GPIO_RET_OK;
}

GPIO_Strength_t GPIO_GetStrength(GPIO_Port_t portNum, GPIO_Pin_t pinNum)
{
	if (GPIO_PORTS[portNum]->DR2R & (1 << pinNum))
	{
		return GPIO_STRENGTH_2MA;
	}
	else if (GPIO_PORTS[portNum]->DR4R & (1 << pinNum))
	{
		return GPIO_STRENGTH_4MA;
	}
	else
	{
		return GPIO_STRENGTH_8MA;
	}
}

GPIO_Ret_t GPIO_SetPadConfig(GPIO_Port_t portNum, GPIO_Pin_t pinNum, GPIO_PadConfig_t padConfig)
{
	if (GPIOCfgs->portsCfgs[portNum].portState == GPIO_PORT_DISABLE)
	{
		return GPIO_RET_ERROR;
	}
	if (GPIOCfgs->portsCfgs[portNum].pinsCfgs[pinNum].pinState == GPIO_PIN_DISABLE)
	{
		return GPIO_RET_ERROR;
	}
	if (padConfig == GPIO_PAD_CONFIG_WEAK_PULL_UP)
	{
		GPIO_PORTS[portNum]->PUR |= (1 << pinNum);
	}
	else if (padConfig == GPIO_PAD_CONFIG_WEAK_PULL_DOWN)
	{
		GPIO_PORTS[portNum]->PDR |= (1 << pinNum);
	}
	else if (padConfig == GPIO_PAD_CONFIG_OPEN_DRAIN)
	{
		GPIO_PORTS[portNum]->ODR |= (1 << pinNum);
	}
	return GPIO_RET_OK;
}

GPIO_PadConfig_t GPIO_GetPadConfig(GPIO_Port_t portNum, GPIO_Pin_t pinNum)
{
	if (GPIO_PORTS[portNum]->PUR & (1 << pinNum))
	{
		return GPIO_PAD_CONFIG_WEAK_PULL_UP;
	}
	else if (GPIO_PORTS[portNum]->PDR & (1 << pinNum))
	{
		return GPIO_PAD_CONFIG_WEAK_PULL_DOWN;
	}
	else if (GPIO_PORTS[portNum]->ODR & (1 << pinNum))
	{
		return GPIO_PAD_CONFIG_OPEN_DRAIN;
	}
	return GPIO_PAD_CONFIG_STANDARD;
}

GPIO_Ret_t GPIO_SetDigitalAnalogSelect(GPIO_Port_t portNum, GPIO_Pin_t pinNum, GPIO_DigitalAnalogSelect_t digitalAnalogSelect)
{
	if (GPIOCfgs->portsCfgs[portNum].portState == GPIO_PORT_DISABLE)
	{
		return GPIO_RET_ERROR;
	}
	if (GPIOCfgs->portsCfgs[portNum].pinsCfgs[pinNum].pinState == GPIO_PIN_DISABLE)
	{
		return GPIO_RET_ERROR;
	}
	if (digitalAnalogSelect == GPIO_MODE_DIGITAL)
	{
		GPIO_PORTS[portNum]->DEN |= (1 << pinNum);
		GPIO_PORTS[portNum]->AMSEL &= ~(1 << pinNum);
	}
	else
	{
		GPIO_PORTS[portNum]->AMSEL |= (1 << pinNum);
		GPIO_PORTS[portNum]->DEN &= ~(1 << pinNum);
	}
	return GPIO_RET_OK;
}

GPIO_DigitalAnalogSelect_t GPIO_GetDigitalAnalogSelect(GPIO_Port_t portNum, GPIO_Pin_t pinNum)
{
	if (GPIO_PORTS[portNum]->DEN & (1 << pinNum))
	{
		return GPIO_MODE_DIGITAL;
	}
	return GPIO_MODE_ANALOG;
}

GPIO_Ret_t GPIO_SetInterruptEvent(GPIO_Port_t portNum, GPIO_Pin_t pinNum, GPIO_InterruptEvent_t event)
{
	if (GPIOCfgs->portsCfgs[portNum].portState == GPIO_PORT_DISABLE)
	{
		return GPIO_RET_ERROR;
	}
	if (GPIOCfgs->portsCfgs[portNum].pinsCfgs[pinNum].pinState == GPIO_PIN_DISABLE)
	{
		return GPIO_RET_ERROR;
	}
	// disable the interrupt
	GPIO_PORTS[portNum]->IM &= ~(1 << pinNum);

	if (event == GPIO_INTERRUPT_EVENT_NONE)
	{
		return GPIO_RET_OK;
	}
	else if (event == GPIO_INTERRUPT_EVENT_FALLING_EDGE)
	{
		GPIO_PORTS[portNum]->IS &= ~(1 << pinNum);
		GPIO_PORTS[portNum]->IBE &= ~(1 << pinNum);
		GPIO_PORTS[portNum]->IEV &= ~(1 << pinNum);
	}
	else if (event == GPIO_INTERRUPT_EVENT_RISING_EDGE)
	{
		GPIO_PORTS[portNum]->IS &= ~(1 << pinNum);
		GPIO_PORTS[portNum]->IBE &= ~(1 << pinNum);
		GPIO_PORTS[portNum]->IEV |= (1 << pinNum);
	}
	else if (event == GPIO_INTERRUPT_EVENT_BOTH_EDGES)
	{
		GPIO_PORTS[portNum]->IS &= ~(1 << pinNum);
		GPIO_PORTS[portNum]->IBE |= (1 << pinNum);
	}
	else if (event == GPIO_INTERRUPT_EVENT_LOW_LEVEL)
	{
		GPIO_PORTS[portNum]->IS |= (1 << pinNum);
		GPIO_PORTS[portNum]->IEV &= ~(1 << pinNum);
	}
	else if (event == GPIO_INTERRUPT_EVENT_HIGH_LEVEL)
	{
		GPIO_PORTS[portNum]->IS |= (1 << pinNum);
		GPIO_PORTS[portNum]->IEV |= (1 << pinNum);
	}

	// clear the interrupt flag and enable the interrupt
	GPIO_PORTS[portNum]->ICR |= (1 << pinNum);
	GPIO_PORTS[portNum]->IM |= (1 << pinNum);
	return GPIO_RET_OK;
}

GPIO_InterruptEvent_t GPIO_GetInterruptEvent(GPIO_Port_t portNum, GPIO_Pin_t pinNum)
{
	if (GPIO_PORTS[portNum]->IM & (1 << pinNum))
	{
		if (GPIO_PORTS[portNum]->IS & (1 << pinNum))
		{
			if (GPIO_PORTS[portNum]->IEV & (1 << pinNum))
			{
				return GPIO_INTERRUPT_EVENT_HIGH_LEVEL;
			}
			return GPIO_INTERRUPT_EVENT_LOW_LEVEL;
		}
		if (GPIO_PORTS[portNum]->IBE & (1 << pinNum))
		{
			return GPIO_INTERRUPT_EVENT_BOTH_EDGES;
		}
		if (GPIO_PORTS[portNum]->IEV & (1 << pinNum))
		{
			return GPIO_INTERRUPT_EVENT_RISING_EDGE;
		}
		return GPIO_INTERRUPT_EVENT_FALLING_EDGE;
	}
	return GPIO_INTERRUPT_EVENT_NONE;
}

GPIO_InterruptStatus_t GPIO_GetInterruptStatus(GPIO_Port_t portNum, GPIO_Pin_t pinNum, uint8_t masked)
{
	if (masked)
	{
		if (GPIO_PORTS[portNum]->MIS & (1 << pinNum))
		{
			return GPIO_INTERRUPT_STATUS_OCCURRED;
		}
	}
	else
	{
		if (GPIO_PORTS[portNum]->RIS & (1 << pinNum))
		{
			return GPIO_INTERRUPT_STATUS_OCCURRED;
		}
	}
	return GPIO_INTERRUPT_STATUS_NONE;
}

GPIO_Ret_t GPIO_ClearInterrupt(GPIO_Port_t portNum, GPIO_Pin_t pinNum)
{
	if (GPIOCfgs->portsCfgs[portNum].portState == GPIO_PORT_DISABLE)
	{
		return GPIO_RET_ERROR;
	}
	if (GPIOCfgs->portsCfgs[portNum].pinsCfgs[pinNum].pinState == GPIO_PIN_DISABLE)
	{
		return GPIO_RET_ERROR;
	}
	GPIO_PORTS[portNum]->ICR |= (1 << pinNum);
	return GPIO_RET_OK;
}

GPIO_Ret_t GPIO_EnableInterrupt(GPIO_Port_t portNum, GPIO_Pin_t pinNum)
{
	if (GPIOCfgs->portsCfgs[portNum].portState == GPIO_PORT_DISABLE)
	{
		return GPIO_RET_ERROR;
	}
	if (GPIOCfgs->portsCfgs[portNum].pinsCfgs[pinNum].pinState == GPIO_PIN_DISABLE)
	{
		return GPIO_RET_ERROR;
	}
	GPIO_PORTS[portNum]->IM |= (1 << pinNum);
	return GPIO_RET_OK;
}

GPIO_Ret_t GPIO_DisableInterrupt(GPIO_Port_t portNum, GPIO_Pin_t pinNum)
{
	if (GPIOCfgs->portsCfgs[portNum].portState == GPIO_PORT_DISABLE)
	{
		return GPIO_RET_ERROR;
	}
	if (GPIOCfgs->portsCfgs[portNum].pinsCfgs[pinNum].pinState == GPIO_PIN_DISABLE)
	{
		return GPIO_RET_ERROR;
	}
	GPIO_PORTS[portNum]->IM &= ~(1 << pinNum);
	return GPIO_RET_OK;
}

GPIO_Ret_t GPIO_RegisterInterruptHandler(GPIO_Port_t portNum, GPIO_Pin_t pinNum, void (*handler)(void))
{
	if (GPIOCfgs->portsCfgs[portNum].portState == GPIO_PORT_DISABLE)
	{
		return GPIO_RET_ERROR;
	}
	if (GPIOCfgs->portsCfgs[portNum].pinsCfgs[pinNum].pinState == GPIO_PIN_DISABLE)
	{
		return GPIO_RET_ERROR;
	}
	// register the interrupt handler
	InterruptHandlers[portNum][pinNum] = handler;
	return GPIO_RET_OK;
}

void GPIOPortA_Handler(void)
{
	if (GPIO_GetInterruptStatus(GPIO_PORT_A, GPIO_PIN_0, 1) == GPIO_INTERRUPT_STATUS_OCCURRED)
	{
		GPIO_ClearInterrupt(GPIO_PORT_A, GPIO_PIN_0);
		if (InterruptHandlers[GPIO_PORT_A][GPIO_PIN_0] != NULL)
		{
			InterruptHandlers[GPIO_PORT_A][GPIO_PIN_0]();
		}
	}
	if (GPIO_GetInterruptStatus(GPIO_PORT_A, GPIO_PIN_1, 1) == GPIO_INTERRUPT_STATUS_OCCURRED)
	{
		GPIO_ClearInterrupt(GPIO_PORT_A, GPIO_PIN_1);
		if (InterruptHandlers[GPIO_PORT_A][GPIO_PIN_1] != NULL)
		{
			InterruptHandlers[GPIO_PORT_A][GPIO_PIN_1]();
		}
	}
	if (GPIO_GetInterruptStatus(GPIO_PORT_A, GPIO_PIN_2, 1) == GPIO_INTERRUPT_STATUS_OCCURRED)
	{
		GPIO_ClearInterrupt(GPIO_PORT_A, GPIO_PIN_2);
		if (InterruptHandlers[GPIO_PORT_A][GPIO_PIN_2] != NULL)
		{
			InterruptHandlers[GPIO_PORT_A][GPIO_PIN_2]();
		}
	}
	if (GPIO_GetInterruptStatus(GPIO_PORT_A, GPIO_PIN_3, 1) == GPIO_INTERRUPT_STATUS_OCCURRED)
	{
		GPIO_ClearInterrupt(GPIO_PORT_A, GPIO_PIN_3);
		if (InterruptHandlers[GPIO_PORT_A][GPIO_PIN_3] != NULL)
		{
			InterruptHandlers[GPIO_PORT_A][GPIO_PIN_3]();
		}
	}
	if (GPIO_GetInterruptStatus(GPIO_PORT_A, GPIO_PIN_4, 1) == GPIO_INTERRUPT_STATUS_OCCURRED)
	{
		GPIO_ClearInterrupt(GPIO_PORT_A, GPIO_PIN_4);
		if (InterruptHandlers[GPIO_PORT_A][GPIO_PIN_4] != NULL)
		{
			InterruptHandlers[GPIO_PORT_A][GPIO_PIN_4]();
		}
	}
	if (GPIO_GetInterruptStatus(GPIO_PORT_A, GPIO_PIN_5, 1) == GPIO_INTERRUPT_STATUS_OCCURRED)
	{
		GPIO_ClearInterrupt(GPIO_PORT_A, GPIO_PIN_5);
		if (InterruptHandlers[GPIO_PORT_A][GPIO_PIN_5] != NULL)
		{
			InterruptHandlers[GPIO_PORT_A][GPIO_PIN_5]();
		}
	}
	if (GPIO_GetInterruptStatus(GPIO_PORT_A, GPIO_PIN_6, 1) == GPIO_INTERRUPT_STATUS_OCCURRED)
	{
		GPIO_ClearInterrupt(GPIO_PORT_A, GPIO_PIN_6);
		if (InterruptHandlers[GPIO_PORT_A][GPIO_PIN_6] != NULL)
		{
			InterruptHandlers[GPIO_PORT_A][GPIO_PIN_6]();
		}
	}
	if (GPIO_GetInterruptStatus(GPIO_PORT_A, GPIO_PIN_7, 1) == GPIO_INTERRUPT_STATUS_OCCURRED)
	{
		GPIO_ClearInterrupt(GPIO_PORT_A, GPIO_PIN_7);
		if (InterruptHandlers[GPIO_PORT_A][GPIO_PIN_7] != NULL)
		{
			InterruptHandlers[GPIO_PORT_A][GPIO_PIN_7]();
		}
	}
}

void GPIOPortB_Handler(void)
{
	if (GPIO_GetInterruptStatus(GPIO_PORT_B, GPIO_PIN_0, 1) == GPIO_INTERRUPT_STATUS_OCCURRED)
	{
		GPIO_ClearInterrupt(GPIO_PORT_B, GPIO_PIN_0);
		if (InterruptHandlers[GPIO_PORT_B][GPIO_PIN_0] != NULL)
		{
			InterruptHandlers[GPIO_PORT_B][GPIO_PIN_0]();
		}
	}
	if (GPIO_GetInterruptStatus(GPIO_PORT_B, GPIO_PIN_1, 1) == GPIO_INTERRUPT_STATUS_OCCURRED)
	{
		GPIO_ClearInterrupt(GPIO_PORT_B, GPIO_PIN_1);
		if (InterruptHandlers[GPIO_PORT_B][GPIO_PIN_1] != NULL)
		{
			InterruptHandlers[GPIO_PORT_B][GPIO_PIN_1]();
		}
	}
	if (GPIO_GetInterruptStatus(GPIO_PORT_B, GPIO_PIN_2, 1) == GPIO_INTERRUPT_STATUS_OCCURRED)
	{
		GPIO_ClearInterrupt(GPIO_PORT_B, GPIO_PIN_2);
		if (InterruptHandlers[GPIO_PORT_B][GPIO_PIN_2] != NULL)
		{
			InterruptHandlers[GPIO_PORT_B][GPIO_PIN_2]();
		}
	}
	if (GPIO_GetInterruptStatus(GPIO_PORT_B, GPIO_PIN_3, 1) == GPIO_INTERRUPT_STATUS_OCCURRED)
	{
		GPIO_ClearInterrupt(GPIO_PORT_B, GPIO_PIN_3);
		if (InterruptHandlers[GPIO_PORT_B][GPIO_PIN_3] != NULL)
		{
			InterruptHandlers[GPIO_PORT_B][GPIO_PIN_3]();
		}
	}
	if (GPIO_GetInterruptStatus(GPIO_PORT_B, GPIO_PIN_4, 1) == GPIO_INTERRUPT_STATUS_OCCURRED)
	{
		GPIO_ClearInterrupt(GPIO_PORT_B, GPIO_PIN_4);
		if (InterruptHandlers[GPIO_PORT_B][GPIO_PIN_4] != NULL)
		{
			InterruptHandlers[GPIO_PORT_B][GPIO_PIN_4]();
		}
	}
	if (GPIO_GetInterruptStatus(GPIO_PORT_B, GPIO_PIN_5, 1) == GPIO_INTERRUPT_STATUS_OCCURRED)
	{
		GPIO_ClearInterrupt(GPIO_PORT_B, GPIO_PIN_5);
		if (InterruptHandlers[GPIO_PORT_B][GPIO_PIN_5] != NULL)
		{
			InterruptHandlers[GPIO_PORT_B][GPIO_PIN_5]();
		}
	}
	if (GPIO_GetInterruptStatus(GPIO_PORT_B, GPIO_PIN_6, 1) == GPIO_INTERRUPT_STATUS_OCCURRED)
	{
		GPIO_ClearInterrupt(GPIO_PORT_B, GPIO_PIN_6);
		if (InterruptHandlers[GPIO_PORT_B][GPIO_PIN_6] != NULL)
		{
			InterruptHandlers[GPIO_PORT_B][GPIO_PIN_6]();
		}
	}
	if (GPIO_GetInterruptStatus(GPIO_PORT_B, GPIO_PIN_7, 1) == GPIO_INTERRUPT_STATUS_OCCURRED)
	{
		GPIO_ClearInterrupt(GPIO_PORT_B, GPIO_PIN_7);
		if (InterruptHandlers[GPIO_PORT_B][GPIO_PIN_7] != NULL)
		{
			InterruptHandlers[GPIO_PORT_B][GPIO_PIN_7]();
		}
	}
}
void GPIOPortC_Handler(void)
{
	if (GPIO_GetInterruptStatus(GPIO_PORT_C, GPIO_PIN_0, 1) == GPIO_INTERRUPT_STATUS_OCCURRED)
	{
		GPIO_ClearInterrupt(GPIO_PORT_C, GPIO_PIN_0);
		if (InterruptHandlers[GPIO_PORT_C][GPIO_PIN_0] != NULL)
		{
			InterruptHandlers[GPIO_PORT_C][GPIO_PIN_0]();
		}
	}
	if (GPIO_GetInterruptStatus(GPIO_PORT_C, GPIO_PIN_1, 1) == GPIO_INTERRUPT_STATUS_OCCURRED)
	{
		GPIO_ClearInterrupt(GPIO_PORT_C, GPIO_PIN_1);
		if (InterruptHandlers[GPIO_PORT_C][GPIO_PIN_1] != NULL)
		{
			InterruptHandlers[GPIO_PORT_C][GPIO_PIN_1]();
		}
	}
	if (GPIO_GetInterruptStatus(GPIO_PORT_C, GPIO_PIN_2, 1) == GPIO_INTERRUPT_STATUS_OCCURRED)
	{
		GPIO_ClearInterrupt(GPIO_PORT_C, GPIO_PIN_2);
		if (InterruptHandlers[GPIO_PORT_C][GPIO_PIN_2] != NULL)
		{
			InterruptHandlers[GPIO_PORT_C][GPIO_PIN_2]();
		}
	}
	if (GPIO_GetInterruptStatus(GPIO_PORT_C, GPIO_PIN_3, 1) == GPIO_INTERRUPT_STATUS_OCCURRED)
	{
		GPIO_ClearInterrupt(GPIO_PORT_C, GPIO_PIN_3);
		if (InterruptHandlers[GPIO_PORT_C][GPIO_PIN_3] != NULL)
		{
			InterruptHandlers[GPIO_PORT_C][GPIO_PIN_3]();
		}
	}
	if (GPIO_GetInterruptStatus(GPIO_PORT_C, GPIO_PIN_4, 1) == GPIO_INTERRUPT_STATUS_OCCURRED)
	{
		GPIO_ClearInterrupt(GPIO_PORT_C, GPIO_PIN_4);
		if (InterruptHandlers[GPIO_PORT_C][GPIO_PIN_4] != NULL)
		{
			InterruptHandlers[GPIO_PORT_C][GPIO_PIN_4]();
		}
	}
	if (GPIO_GetInterruptStatus(GPIO_PORT_C, GPIO_PIN_5, 1) == GPIO_INTERRUPT_STATUS_OCCURRED)
	{
		GPIO_ClearInterrupt(GPIO_PORT_C, GPIO_PIN_5);
		if (InterruptHandlers[GPIO_PORT_C][GPIO_PIN_5] != NULL)
		{
			InterruptHandlers[GPIO_PORT_C][GPIO_PIN_5]();
		}
	}
	if (GPIO_GetInterruptStatus(GPIO_PORT_C, GPIO_PIN_6, 1) == GPIO_INTERRUPT_STATUS_OCCURRED)
	{
		GPIO_ClearInterrupt(GPIO_PORT_C, GPIO_PIN_6);
		if (InterruptHandlers[GPIO_PORT_C][GPIO_PIN_6] != NULL)
		{
			InterruptHandlers[GPIO_PORT_C][GPIO_PIN_6]();
		}
	}
	if (GPIO_GetInterruptStatus(GPIO_PORT_C, GPIO_PIN_7, 1) == GPIO_INTERRUPT_STATUS_OCCURRED)
	{
		GPIO_ClearInterrupt(GPIO_PORT_C, GPIO_PIN_7);
		if (InterruptHandlers[GPIO_PORT_C][GPIO_PIN_7] != NULL)
		{
			InterruptHandlers[GPIO_PORT_C][GPIO_PIN_7]();
		}
	}
}
void GPIOPortD_Handler(void)
{
	if (GPIO_GetInterruptStatus(GPIO_PORT_D, GPIO_PIN_0, 1) == GPIO_INTERRUPT_STATUS_OCCURRED)
	{
		GPIO_ClearInterrupt(GPIO_PORT_D, GPIO_PIN_0);
		if (InterruptHandlers[GPIO_PORT_D][GPIO_PIN_0] != NULL)
		{
			InterruptHandlers[GPIO_PORT_D][GPIO_PIN_0]();
		}
	}
	if (GPIO_GetInterruptStatus(GPIO_PORT_D, GPIO_PIN_1, 1) == GPIO_INTERRUPT_STATUS_OCCURRED)
	{
		GPIO_ClearInterrupt(GPIO_PORT_D, GPIO_PIN_1);
		if (InterruptHandlers[GPIO_PORT_D][GPIO_PIN_1] != NULL)
		{
			InterruptHandlers[GPIO_PORT_D][GPIO_PIN_1]();
		}
	}
	if (GPIO_GetInterruptStatus(GPIO_PORT_D, GPIO_PIN_2, 1) == GPIO_INTERRUPT_STATUS_OCCURRED)
	{
		GPIO_ClearInterrupt(GPIO_PORT_D, GPIO_PIN_2);
		if (InterruptHandlers[GPIO_PORT_D][GPIO_PIN_2] != NULL)
		{
			InterruptHandlers[GPIO_PORT_D][GPIO_PIN_2]();
		}
	}
	if (GPIO_GetInterruptStatus(GPIO_PORT_D, GPIO_PIN_3, 1) == GPIO_INTERRUPT_STATUS_OCCURRED)
	{
		GPIO_ClearInterrupt(GPIO_PORT_D, GPIO_PIN_3);
		if (InterruptHandlers[GPIO_PORT_D][GPIO_PIN_3] != NULL)
		{
			InterruptHandlers[GPIO_PORT_D][GPIO_PIN_3]();
		}
	}
	if (GPIO_GetInterruptStatus(GPIO_PORT_D, GPIO_PIN_4, 1) == GPIO_INTERRUPT_STATUS_OCCURRED)
	{
		GPIO_ClearInterrupt(GPIO_PORT_D, GPIO_PIN_4);
		if (InterruptHandlers[GPIO_PORT_D][GPIO_PIN_4] != NULL)
		{
			InterruptHandlers[GPIO_PORT_D][GPIO_PIN_4]();
		}
	}
	if (GPIO_GetInterruptStatus(GPIO_PORT_D, GPIO_PIN_5, 1) == GPIO_INTERRUPT_STATUS_OCCURRED)
	{
		GPIO_ClearInterrupt(GPIO_PORT_D, GPIO_PIN_5);
		if (InterruptHandlers[GPIO_PORT_D][GPIO_PIN_5] != NULL)
		{
			InterruptHandlers[GPIO_PORT_D][GPIO_PIN_5]();
		}
	}
	if (GPIO_GetInterruptStatus(GPIO_PORT_D, GPIO_PIN_6, 1) == GPIO_INTERRUPT_STATUS_OCCURRED)
	{
		GPIO_ClearInterrupt(GPIO_PORT_D, GPIO_PIN_6);
		if (InterruptHandlers[GPIO_PORT_D][GPIO_PIN_6] != NULL)
		{
			InterruptHandlers[GPIO_PORT_D][GPIO_PIN_6]();
		}
	}
	if (GPIO_GetInterruptStatus(GPIO_PORT_D, GPIO_PIN_7, 1) == GPIO_INTERRUPT_STATUS_OCCURRED)
	{
		GPIO_ClearInterrupt(GPIO_PORT_D, GPIO_PIN_7);
		if (InterruptHandlers[GPIO_PORT_D][GPIO_PIN_7] != NULL)
		{
			InterruptHandlers[GPIO_PORT_D][GPIO_PIN_7]();
		}
	}
}
void GPIOPortE_Handler(void)
{
	if (GPIO_GetInterruptStatus(GPIO_PORT_E, GPIO_PIN_0, 1) == GPIO_INTERRUPT_STATUS_OCCURRED)
	{
		GPIO_ClearInterrupt(GPIO_PORT_E, GPIO_PIN_0);
		if (InterruptHandlers[GPIO_PORT_E][GPIO_PIN_0] != NULL)
		{
			InterruptHandlers[GPIO_PORT_E][GPIO_PIN_0]();
		}
	}
	if (GPIO_GetInterruptStatus(GPIO_PORT_E, GPIO_PIN_1, 1) == GPIO_INTERRUPT_STATUS_OCCURRED)
	{
		GPIO_ClearInterrupt(GPIO_PORT_E, GPIO_PIN_1);
		if (InterruptHandlers[GPIO_PORT_E][GPIO_PIN_1] != NULL)
		{
			InterruptHandlers[GPIO_PORT_E][GPIO_PIN_1]();
		}
	}
	if (GPIO_GetInterruptStatus(GPIO_PORT_E, GPIO_PIN_2, 1) == GPIO_INTERRUPT_STATUS_OCCURRED)
	{
		GPIO_ClearInterrupt(GPIO_PORT_E, GPIO_PIN_2);
		if (InterruptHandlers[GPIO_PORT_E][GPIO_PIN_2] != NULL)
		{
			InterruptHandlers[GPIO_PORT_E][GPIO_PIN_2]();
		}
	}
	if (GPIO_GetInterruptStatus(GPIO_PORT_E, GPIO_PIN_3, 1) == GPIO_INTERRUPT_STATUS_OCCURRED)
	{
		GPIO_ClearInterrupt(GPIO_PORT_E, GPIO_PIN_3);
		if (InterruptHandlers[GPIO_PORT_E][GPIO_PIN_3] != NULL)
		{
			InterruptHandlers[GPIO_PORT_E][GPIO_PIN_3]();
		}
	}
	if (GPIO_GetInterruptStatus(GPIO_PORT_E, GPIO_PIN_4, 1) == GPIO_INTERRUPT_STATUS_OCCURRED)
	{
		GPIO_ClearInterrupt(GPIO_PORT_E, GPIO_PIN_4);
		if (InterruptHandlers[GPIO_PORT_E][GPIO_PIN_4] != NULL)
		{
			InterruptHandlers[GPIO_PORT_E][GPIO_PIN_4]();
		}
	}
	if (GPIO_GetInterruptStatus(GPIO_PORT_E, GPIO_PIN_5, 1) == GPIO_INTERRUPT_STATUS_OCCURRED)
	{
		GPIO_ClearInterrupt(GPIO_PORT_E, GPIO_PIN_5);
		if (InterruptHandlers[GPIO_PORT_E][GPIO_PIN_5] != NULL)
		{
			InterruptHandlers[GPIO_PORT_E][GPIO_PIN_5]();
		}
	}
	if (GPIO_GetInterruptStatus(GPIO_PORT_E, GPIO_PIN_6, 1) == GPIO_INTERRUPT_STATUS_OCCURRED)
	{
		GPIO_ClearInterrupt(GPIO_PORT_E, GPIO_PIN_6);
		if (InterruptHandlers[GPIO_PORT_E][GPIO_PIN_6] != NULL)
		{
			InterruptHandlers[GPIO_PORT_E][GPIO_PIN_6]();
		}
	}
	if (GPIO_GetInterruptStatus(GPIO_PORT_E, GPIO_PIN_7, 1) == GPIO_INTERRUPT_STATUS_OCCURRED)
	{
		GPIO_ClearInterrupt(GPIO_PORT_E, GPIO_PIN_7);
		if (InterruptHandlers[GPIO_PORT_E][GPIO_PIN_7] != NULL)
		{
			InterruptHandlers[GPIO_PORT_E][GPIO_PIN_7]();
		}
	}
}
void GPIOPortF_Handler(void)
{
	if (GPIO_GetInterruptStatus(GPIO_PORT_F, GPIO_PIN_0, 1) == GPIO_INTERRUPT_STATUS_OCCURRED)
	{
		GPIO_ClearInterrupt(GPIO_PORT_F, GPIO_PIN_0);
		if (InterruptHandlers[GPIO_PORT_F][GPIO_PIN_0] != NULL)
		{
			InterruptHandlers[GPIO_PORT_F][GPIO_PIN_0]();
		}
	}
	if (GPIO_GetInterruptStatus(GPIO_PORT_F, GPIO_PIN_1, 1) == GPIO_INTERRUPT_STATUS_OCCURRED)
	{
		GPIO_ClearInterrupt(GPIO_PORT_F, GPIO_PIN_1);
		if (InterruptHandlers[GPIO_PORT_F][GPIO_PIN_1] != NULL)
		{
			InterruptHandlers[GPIO_PORT_F][GPIO_PIN_1]();
		}
	}
	if (GPIO_GetInterruptStatus(GPIO_PORT_F, GPIO_PIN_2, 1) == GPIO_INTERRUPT_STATUS_OCCURRED)
	{
		GPIO_ClearInterrupt(GPIO_PORT_F, GPIO_PIN_2);
		if (InterruptHandlers[GPIO_PORT_F][GPIO_PIN_2] != NULL)
		{
			InterruptHandlers[GPIO_PORT_F][GPIO_PIN_2]();
		}
	}
	if (GPIO_GetInterruptStatus(GPIO_PORT_F, GPIO_PIN_3, 1) == GPIO_INTERRUPT_STATUS_OCCURRED)
	{
		GPIO_ClearInterrupt(GPIO_PORT_F, GPIO_PIN_3);
		if (InterruptHandlers[GPIO_PORT_F][GPIO_PIN_3] != NULL)
		{
			InterruptHandlers[GPIO_PORT_F][GPIO_PIN_3]();
		}
	}
	if (GPIO_GetInterruptStatus(GPIO_PORT_F, GPIO_PIN_4, 1) == GPIO_INTERRUPT_STATUS_OCCURRED)
	{
		GPIO_ClearInterrupt(GPIO_PORT_F, GPIO_PIN_4);
		if (InterruptHandlers[GPIO_PORT_F][GPIO_PIN_4] != NULL)
		{
			InterruptHandlers[GPIO_PORT_F][GPIO_PIN_4]();
		}
	}
	if (GPIO_GetInterruptStatus(GPIO_PORT_F, GPIO_PIN_5, 1) == GPIO_INTERRUPT_STATUS_OCCURRED)
	{
		GPIO_ClearInterrupt(GPIO_PORT_F, GPIO_PIN_5);
		if (InterruptHandlers[GPIO_PORT_F][GPIO_PIN_5] != NULL)
		{
			InterruptHandlers[GPIO_PORT_F][GPIO_PIN_5]();
		}
	}
	if (GPIO_GetInterruptStatus(GPIO_PORT_F, GPIO_PIN_6, 1) == GPIO_INTERRUPT_STATUS_OCCURRED)
	{
		GPIO_ClearInterrupt(GPIO_PORT_F, GPIO_PIN_6);
		if (InterruptHandlers[GPIO_PORT_F][GPIO_PIN_6] != NULL)
		{
			InterruptHandlers[GPIO_PORT_F][GPIO_PIN_6]();
		}
	}
	if (GPIO_GetInterruptStatus(GPIO_PORT_F, GPIO_PIN_7, 1) == GPIO_INTERRUPT_STATUS_OCCURRED)
	{
		GPIO_ClearInterrupt(GPIO_PORT_F, GPIO_PIN_7);
		if (InterruptHandlers[GPIO_PORT_F][GPIO_PIN_7] != NULL)
		{
			InterruptHandlers[GPIO_PORT_F][GPIO_PIN_7]();
		}
	}
}

GPIO_Ret_t GPIO_UnregisterInterruptHandler(GPIO_Port_t portNum, GPIO_Pin_t pinNum)
{
	if (GPIOCfgs->portsCfgs[portNum].portState == GPIO_PORT_DISABLE)
	{
		return GPIO_RET_ERROR;
	}
	if (GPIOCfgs->portsCfgs[portNum].pinsCfgs[pinNum].pinState == GPIO_PIN_DISABLE)
	{
		return GPIO_RET_ERROR;
	}
	// unregister the interrupt handler
	InterruptHandlers[portNum][pinNum] = NULL;
	return GPIO_RET_OK;
}

void GPIO_WritePin(GPIO_Port_t portNum, GPIO_Pin_t pinNum, GPIO_PinStatus_t status)
{
	if (GPIOCfgs->portsCfgs[portNum].portState == GPIO_PORT_DISABLE)
	{
		return;
	}
	if (GPIOCfgs->portsCfgs[portNum].pinsCfgs[pinNum].pinState == GPIO_PIN_DISABLE)
	{
		return;
	}
	if (status == GPIO_HIGH)
	{
		GPIO_PORTS[portNum]->DATA |= (1 << pinNum);
	}
	else if (status == GPIO_LOW)
	{
		GPIO_PORTS[portNum]->DATA &= ~(1 << pinNum);
	}
}

GPIO_PinStatus_t GPIO_ReadPin(GPIO_Port_t portNum, GPIO_Pin_t pinNum)
{
	if (GPIOCfgs->portsCfgs[portNum].portState == GPIO_PORT_DISABLE)
	{
		return 0;
	}
	if (GPIOCfgs->portsCfgs[portNum].pinsCfgs[pinNum].pinState == GPIO_PIN_DISABLE)
	{
		return 0;
	}
	if (GPIO_PORTS[portNum]->DATA & (1 << pinNum))
	{
		return GPIO_HIGH;
	}
	return GPIO_LOW;
}
