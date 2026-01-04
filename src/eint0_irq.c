#include "myheader.h"
#include <LPC21xx.h>
#define EINT0_VIC_CHNO 14
void eint0_isr(void) __irq;
u32 gcount;
void Init_Eint0(void)
{
	//cfg VIC Peripheral
	cfgPortPinFunc(0,1,EINT0_0_1);
	//VICIntSelect = 0;
	VICIntEnable = 1<<EINT0_VIC_CHNO;
	VICVectCntl0 = (1<<5)|(EINT0_VIC_CHNO);
	VICVectAddr0 = (u32) eint0_isr;
	//cfg External Interrupt Peripheral
	//EXTINT = 0;
	EXTMODE =1<<0;
	//EXTPOLAR = 0;
}
void eint0_isr(void) __irq
{
	//u32 eint0_flag=1;
	show_Menu();
	EXTINT = 1<<0;
	VICVectAddr = 0;
}
