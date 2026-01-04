#ifndef __RTCDEFINES_H__
#define __RTCDEFINES_H__
#define _LPC2148_
#define FOSC 12000000
#define CCLK (FOSC*5)
#define PCLK (CCLK/4)
#define PREINT_VALUE ((int)((PCLK/32768)-1))
#define PREFRAC_VALUE (PCLK-((PREINT_VALUE+1)*32768))

#define RTC_RESET (1<<1)
#define RTC_ENABLE (1<<0)
#define RTC_EXTOSC (1<<4)
#endif