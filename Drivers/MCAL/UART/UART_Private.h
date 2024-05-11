#ifndef _UART_PRIVATE_H_
#define _UART_PRIVATE_H_

#include <stdint.h>

#define SYSCTL_RCGCUART_R  (*((volatile unsigned long *)0x400FE618))

#pragma anon_unions

typedef struct
{
    uint32_t DR;
    union
    {
        uint32_t ECR_UART_ALT;
        uint32_t RSR;
    };
    uint32_t RESERVED0[4];
    uint32_t FR;
    uint32_t RESERVED1;
    uint32_t ILPR;
    uint32_t IBRD;
    uint32_t FBRD;
    uint32_t LCRH;
    uint32_t CTL;
    uint32_t IFLS;
    uint32_t IM;
    uint32_t RIS;
    uint32_t MIS;
    uint32_t ICR;
    uint32_t DMACTL;
    uint32_t RESERVED2[22];
    uint32_t _9BITADDR;
    uint32_t _9BITAMASK;
    uint32_t RESERVED3[965];
    uint32_t PP;
    uint32_t RESERVED4;
    uint32_t CC;
} UART_t;

#define UART0_BASE 0x4000C000UL
#define UART1_BASE 0x4000D000UL
#define UART2_BASE 0x4000E000UL
#define UART3_BASE 0x4000F000UL
#define UART4_BASE 0x40010000UL
#define UART5_BASE 0x40011000UL
#define UART6_BASE 0x40012000UL
#define UART7_BASE 0x40013000UL

#define UART0 ((UART_t *)UART0_BASE)
#define UART1 ((UART_t *)UART1_BASE)
#define UART2 ((UART_t *)UART2_BASE)
#define UART3 ((UART_t *)UART3_BASE)
#define UART4 ((UART_t *)UART4_BASE)
#define UART5 ((UART_t *)UART5_BASE)
#define UART6 ((UART_t *)UART6_BASE)
#define UART7 ((UART_t *)UART7_BASE)

UART_t *UARTS[UARTS_UNITS_COUNT] = {
    UART0,
    UART1,
    UART2,
    UART3,
    UART4,
    UART5,
    UART6,
    UART7,
};
#endif