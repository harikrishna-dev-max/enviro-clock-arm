// clock defines
#ifndef __ADCDEFINES_H__
#define __ADCDEFINES_H__
#define FOSC 12000000
#define CCLK (FOSC*5)
#define ADCCLK 3000000
#define PCLK (CCLK/4)
#define CLKDIV ((PCLK/ADCCLK)-1)

// ADCR SFR defines

#define CLK_DIV_BITS 8
#define PDN_BIT 21
#define ADC_START_BIT 24

// ADDR SFR defines

#define RESULT_BITS 6
#define DONE_BIT 31
#endif
