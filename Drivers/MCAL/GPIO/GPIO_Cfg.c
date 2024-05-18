#include "GPIO.h"

GPIO_Configurations_t configs = {
    .portsCfgs[GPIO_PORT_F] = {
        .portState = GPIO_PORT_ENABLE,
        .pinsCfgs[GPIO_PIN_0] = {
            .pinState = GPIO_PIN_ENABLE,
            .pinDirection = GPIO_DIR_INPUT,
            .pinFunction = GPIO_FUNCTION_GPIO,
            .pinStrength = GPIO_STRENGTH_2MA,
            .padConfig = GPIO_PAD_CONFIG_WEAK_PULL_UP,
            .digitalAnalogSelect = GPIO_MODE_DIGITAL,
            .interruptEvent =  GPIO_INTERRUPT_EVENT_NONE
        },
        .pinsCfgs[GPIO_PIN_1] = {
            .pinState = GPIO_PIN_ENABLE,
            .pinDirection = GPIO_DIR_OUTPUT,
            .pinFunction = GPIO_FUNCTION_GPIO,
            .pinStrength = GPIO_STRENGTH_2MA,
            .padConfig = GPIO_PAD_CONFIG_STANDARD,
            .digitalAnalogSelect = GPIO_MODE_DIGITAL,
            .interruptEvent =  GPIO_INTERRUPT_EVENT_NONE
        },
        .pinsCfgs[GPIO_PIN_2] = {
            .pinState = GPIO_PIN_ENABLE,
            .pinDirection = GPIO_DIR_OUTPUT,
            .pinFunction = GPIO_FUNCTION_GPIO,
            .pinStrength = GPIO_STRENGTH_2MA,
            .padConfig = GPIO_PAD_CONFIG_STANDARD,
            .digitalAnalogSelect = GPIO_MODE_DIGITAL,
            .interruptEvent =  GPIO_INTERRUPT_EVENT_NONE
        },
        .pinsCfgs[GPIO_PIN_3] = {
            .pinState = GPIO_PIN_ENABLE,
            .pinDirection = GPIO_DIR_OUTPUT,
            .pinFunction = GPIO_FUNCTION_GPIO,
            .pinStrength = GPIO_STRENGTH_2MA,
            .padConfig = GPIO_PAD_CONFIG_STANDARD,
            .digitalAnalogSelect = GPIO_MODE_DIGITAL,
            .interruptEvent =  GPIO_INTERRUPT_EVENT_NONE
        },
        .pinsCfgs[GPIO_PIN_4] = {
            .pinState = GPIO_PIN_ENABLE,
            .pinDirection = GPIO_DIR_INPUT,
            .pinFunction = GPIO_FUNCTION_GPIO,
            .pinStrength = GPIO_STRENGTH_2MA,
            .padConfig = GPIO_PAD_CONFIG_WEAK_PULL_UP,
            .digitalAnalogSelect = GPIO_MODE_DIGITAL,
            .interruptEvent =  GPIO_INTERRUPT_EVENT_NONE
        }
    },
    .portsCfgs[GPIO_PORT_A] = {
        .portState = GPIO_PORT_ENABLE,
        .pinsCfgs[GPIO_PIN_2] = {
            .pinState = GPIO_PIN_ENABLE,
            .pinDirection = GPIO_DIR_INPUT,
            .pinFunction = GPIO_FUNCTION_SSI,
            .pinStrength = GPIO_STRENGTH_2MA,
            .padConfig = GPIO_PAD_CONFIG_STANDARD,
            .digitalAnalogSelect = GPIO_MODE_DIGITAL,
            .interruptEvent =  GPIO_INTERRUPT_EVENT_NONE
        },
        .pinsCfgs[GPIO_PIN_3] = {
            .pinState = GPIO_PIN_ENABLE,
            .pinDirection = GPIO_DIR_INPUT,
            .pinFunction = GPIO_FUNCTION_SSI,
            .pinStrength = GPIO_STRENGTH_2MA,
            .padConfig = GPIO_PAD_CONFIG_STANDARD,
            .digitalAnalogSelect = GPIO_MODE_DIGITAL,
            .interruptEvent =  GPIO_INTERRUPT_EVENT_NONE
        },
        .pinsCfgs[GPIO_PIN_5] = {
            .pinState = GPIO_PIN_ENABLE,
            .pinDirection = GPIO_DIR_INPUT,
            .pinFunction = GPIO_FUNCTION_SSI,
            .pinStrength = GPIO_STRENGTH_2MA,
            .padConfig = GPIO_PAD_CONFIG_STANDARD,
            .digitalAnalogSelect = GPIO_MODE_DIGITAL,
            .interruptEvent =  GPIO_INTERRUPT_EVENT_NONE
        },
        .pinsCfgs[GPIO_PIN_6] = {
            .pinState = GPIO_PIN_ENABLE,
            .pinDirection = GPIO_DIR_OUTPUT,
            .pinFunction = GPIO_FUNCTION_GPIO,
            .pinStrength = GPIO_STRENGTH_2MA,
            .padConfig = GPIO_PAD_CONFIG_STANDARD,
            .digitalAnalogSelect = GPIO_MODE_DIGITAL,
            .interruptEvent =  GPIO_INTERRUPT_EVENT_NONE
        },
        .pinsCfgs[GPIO_PIN_7] = {
            .pinState = GPIO_PIN_ENABLE,
            .pinDirection = GPIO_DIR_OUTPUT,
            .pinFunction = GPIO_FUNCTION_GPIO,
            .pinStrength = GPIO_STRENGTH_2MA,
            .padConfig = GPIO_PAD_CONFIG_STANDARD,
            .digitalAnalogSelect = GPIO_MODE_DIGITAL,
            .interruptEvent =  GPIO_INTERRUPT_EVENT_NONE
        },
    },
    .portsCfgs[GPIO_PORT_D] = {
        .portState = GPIO_PORT_ENABLE,
        .pinsCfgs[GPIO_PIN_0] = {
            .pinState = GPIO_PIN_ENABLE,
            .pinDirection = GPIO_DIR_OUTPUT,
            .pinFunction = GPIO_FUNCTION_GPIO,
            .pinStrength = GPIO_STRENGTH_2MA,
            .padConfig = GPIO_PAD_CONFIG_STANDARD,
            .digitalAnalogSelect = GPIO_MODE_DIGITAL,
            .interruptEvent =  GPIO_INTERRUPT_EVENT_NONE
        },
        .pinsCfgs[GPIO_PIN_1] = {
            .pinState = GPIO_PIN_ENABLE,
            .pinDirection = GPIO_DIR_INPUT,
            .pinFunction = GPIO_FUNCTION_GPIO,
            .pinStrength = GPIO_STRENGTH_2MA,
            .padConfig = GPIO_PAD_CONFIG_WEAK_PULL_UP,
            .digitalAnalogSelect = GPIO_MODE_DIGITAL,
            .interruptEvent =  GPIO_INTERRUPT_EVENT_NONE
        },
        .pinsCfgs[GPIO_PIN_2] = {
            .pinState = GPIO_PIN_ENABLE,
            .pinDirection = GPIO_DIR_INPUT,
            .pinFunction = GPIO_FUNCTION_GPIO,
            .pinStrength = GPIO_STRENGTH_2MA,
            .padConfig = GPIO_PAD_CONFIG_WEAK_PULL_UP,
            .digitalAnalogSelect = GPIO_MODE_DIGITAL,
            .interruptEvent =  GPIO_INTERRUPT_EVENT_NONE
        },
        .pinsCfgs[GPIO_PIN_3] = {
            .pinState = GPIO_PIN_ENABLE,
            .pinDirection = GPIO_DIR_INPUT,
            .pinFunction = GPIO_FUNCTION_GPIO,
            .pinStrength = GPIO_STRENGTH_2MA,
            .padConfig = GPIO_PAD_CONFIG_WEAK_PULL_UP,
            .digitalAnalogSelect = GPIO_MODE_DIGITAL,
            .interruptEvent =  GPIO_INTERRUPT_EVENT_NONE
        },
        .pinsCfgs[GPIO_PIN_4] = {
            .pinState = GPIO_PIN_ENABLE,
            .pinDirection = GPIO_DIR_OUTPUT,
            .pinFunction = GPIO_FUNCTION_GPIO,
            .pinStrength = GPIO_STRENGTH_2MA,
            .padConfig = GPIO_PAD_CONFIG_STANDARD,
            .digitalAnalogSelect = GPIO_MODE_DIGITAL,
            .interruptEvent =  GPIO_INTERRUPT_EVENT_NONE
        },
        .pinsCfgs[GPIO_PIN_5] = {
            .pinState = GPIO_PIN_ENABLE,
            .pinDirection = GPIO_DIR_OUTPUT,
            .pinFunction = GPIO_FUNCTION_GPIO,
            .pinStrength = GPIO_STRENGTH_2MA,
            .padConfig = GPIO_PAD_CONFIG_STANDARD,
            .digitalAnalogSelect = GPIO_MODE_DIGITAL,
            .interruptEvent =  GPIO_INTERRUPT_EVENT_NONE
        },
        .pinsCfgs[GPIO_PIN_6] = {
            .pinState = GPIO_PIN_ENABLE,
            .pinDirection = GPIO_DIR_INPUT,
            .pinFunction = GPIO_FUNCTION_UART,
            .pinStrength = GPIO_STRENGTH_2MA,
            .padConfig = GPIO_PAD_CONFIG_STANDARD,
            .digitalAnalogSelect = GPIO_MODE_DIGITAL,
					//.interruptEvent =  GPIO_INTERRUPT_EVENT_NONE
        },
				.pinsCfgs[GPIO_PIN_7] = {
            .pinState = GPIO_PIN_ENABLE,
            .pinDirection = GPIO_DIR_OUTPUT,
            .pinFunction = GPIO_FUNCTION_UART,
            .pinStrength = GPIO_STRENGTH_2MA,
            .padConfig = GPIO_PAD_CONFIG_STANDARD,
            .digitalAnalogSelect = GPIO_MODE_DIGITAL,
					//.interruptEvent =  GPIO_INTERRUPT_EVENT_NONE
        },
    },
    .portsCfgs[GPIO_PORT_B] = {
        .portState = GPIO_PORT_ENABLE,
        .pinsCfgs[GPIO_PIN_0] = {
            .pinState = GPIO_PIN_ENABLE,
            .pinDirection = GPIO_DIR_OUTPUT,
            .pinFunction = GPIO_FUNCTION_GPIO,
            .pinStrength = GPIO_STRENGTH_2MA,
            .padConfig = GPIO_PAD_CONFIG_STANDARD,
            .digitalAnalogSelect = GPIO_MODE_DIGITAL,
            .interruptEvent =  GPIO_INTERRUPT_EVENT_NONE
        },
        .pinsCfgs[GPIO_PIN_1] = {
            .pinState = GPIO_PIN_ENABLE,
            .pinDirection = GPIO_DIR_OUTPUT,
            .pinFunction = GPIO_FUNCTION_GPIO,
            .pinStrength = GPIO_STRENGTH_2MA,
            .padConfig = GPIO_PAD_CONFIG_STANDARD,
            .digitalAnalogSelect = GPIO_MODE_DIGITAL,
            .interruptEvent =  GPIO_INTERRUPT_EVENT_NONE
        },
    }


};

GPIO_Configurations_t *GPIOCfgs = &configs;

