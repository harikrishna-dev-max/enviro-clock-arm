#include "myheader.h"
#include <LPC21xx.h>
void Init_ADC(void)
{
	ADCR|=(1<<PDN_BIT)|(CLKDIV<<CLK_DIV_BITS);
}
void Read_ADC(u32 chNo,u32* adcDval,f32* eAR)
{
	float fn;
	ADCR&=0xFFFFFF00;
	ADCR|=(1<<chNo)|(1<<ADC_START_BIT);
	delayUS(3);
	while(((ADDR>>DONE_BIT)&1)==0);
	ADCR &=~(1<<ADC_START_BIT);
	*adcDval = (ADDR>>RESULT_BITS)&1023;
	fn = (*adcDval*(3.3/1023));
	*eAR = fn*100;
}
