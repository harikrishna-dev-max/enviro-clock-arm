#ifndef _LPC2148_
#include <LPC21xx.h>
#else
#include <LPC214x.h>
#endif
#include "myheader.h"
s32 hour,min,sec,date,month,year,day;
u32 dVal;
f32 temp;
int main()
{
	Init_LCD();
	Init_KPM();
	Init_Eint0();
	Init_RTC();
	Init_ADC();
	SetRTCTimeInfo(07,24,10);
	SetRTCDateInfo(23,10,2025);
	SetRTCDay(4);
	while(1)
	{
		Read_ADC(0,&dVal,&temp);
		GetRTCTimeInfo(&hour,&min,&sec);
		DisplayRTCTime(hour,min,sec);
		GetRTCDateInfo(&date,&month,&year);
		DisplayRTCDate(date,month,year);
		GetRTCDay(&day);
		DisplayRTCDay(day);
		DisplayTemp(temp);
		
		if(checkAlarm())
		{
			DisplayAlarm();
		}
		else if(Alarmset())
		{
			DisplayBell();
		}
	}		
}
