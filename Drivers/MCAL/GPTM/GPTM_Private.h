#ifndef _GPTM_PRIVATE_H_
#define _GPTM_PRIVATE_H_

#include <stdint.h>

#define SYSCTL_RCGCTIMER_R (*((volatile unsigned long *)0x400FE604))

typedef struct
{
    uint32_t CFG;
    uint32_t TAMR;
    uint32_t TBMR;
    uint32_t CTL;
    uint32_t SYNC;
    uint32_t RESERVED0;
    uint32_t IMR;
    uint32_t RIS;
    uint32_t MIS;
    uint32_t ICR;
    uint32_t TAILR;
    uint32_t TBILR;
    uint32_t TAMATCHR;
    uint32_t TBMATCHR;
    uint32_t TAPR;
    uint32_t TBPR;
    uint32_t TAPMR;
    uint32_t TBPMR;
    uint32_t TAR;
    uint32_t TBR;
    uint32_t TAV;
    uint32_t TBV;
    uint32_t RTCPD;
    uint32_t TAPS;
    uint32_t TBPS;
    uint32_t TAPV;
    uint32_t TBPV;
    uint32_t RESERVED1[981];
    uint32_t PP;
} GPTM_t;

#define GPTM0_BASE 0x40030000UL
#define GPTM1_BASE 0x40031000UL
#define GPTM2_BASE 0x40032000UL
#define GPTM3_BASE 0x40033000UL
#define GPTM4_BASE 0x40034000UL
#define GPTM5_BASE 0x40035000UL

#define GPTM0 ((GPTM_t *)GPTM0_BASE)
#define GPTM1 ((GPTM_t *)GPTM1_BASE)
#define GPTM2 ((GPTM_t *)GPTM2_BASE)
#define GPTM3 ((GPTM_t *)GPTM3_BASE)
#define GPTM4 ((GPTM_t *)GPTM4_BASE)
#define GPTM5 ((GPTM_t *)GPTM5_BASE)

GPTM_t *GPTMS[TIMERS_BLOCKS_COUNT] = {
    GPTM0,
    GPTM1,
    GPTM2,
    GPTM3,
    GPTM4,
    GPTM5};

#endif