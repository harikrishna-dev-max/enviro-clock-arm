#ifndef _LPC2148_
#include <LPC21xx.h>
#else
#include <LPC214x.h>
#endif
#include "myheader.h"
#define BUZZER_PIN 5
#define BUZZER_OFF_SWITCH 29
#define BACKSPACE 11
#define ENTER 14
#define UP_ARROW 12
#define DOWN_ARROW 15
u8 DAY[][4] = {"SUN","MON","TUE","WED","THU","FRI","SAT"};
u8 cgramLUT[48] = {0x02,0x04,0x0A,0x0C,0x0C,0x0A,0x04,0x02,
									0x04,0x0E,0x0E,0x0E,0x0E,0x1F,0x1F,0x04,
									0x08,0x04,0x0A,0x06,0x06,0x0A,0x04,0x08,
									0x04,0x0E,0x15,0x04,0x04,0x04,0x04,0x04,
									0x04,0x04,0x04,0x04,0x04,0x15,0x0E,0x04,
									0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02};
u32 flag=0;
s32 Ahh=0,Amm=0;
u32 flag1=0;
u8 inMenu=0;									
void Init_RTC(void)
{
	CCR = RTC_RESET;
	PREINT = PREINT_VALUE;
	PREFRAC = PREFRAC_VALUE;
	CCR = RTC_EXTOSC|RTC_ENABLE;
}
void SetRTCTimeInfo(u32 hour,u32 min,u32 sec)
{
	HOUR = hour;
	MIN = min;
	SEC = sec;
}
void SetRTCDateInfo(u32 date,u32 month,u32 year)
{
	DOM = date;
	MONTH = month;
	YEAR = year;
}
void SetRTCDay(u32 day)
{
	DOW = day;
}
void GetRTCTimeInfo(s32* hour,s32* min,s32* sec)
{
	*hour = HOUR;
	*min = MIN;
	*sec = SEC;
}
void GetRTCDateInfo(s32* date,s32* month,s32* year)
{
	*date = DOM;
	*month = MONTH;
	*year = YEAR;
}
void GetRTCDay(s32* day)
{
	*day = DOW;
}
void DisplayRTCTime(u32 hour,u32 min,u32 sec)
{
		cmdLCD(GOTO_LINE1_POS0);
		char_LCD(hour/10+48);
		char_LCD(hour%10+48);
		char_LCD(':');
		char_LCD(min/10+48);
		char_LCD(min%10+48);
		char_LCD(':');
		char_LCD(sec/10+48);
		char_LCD(sec%10+48);
}
void DisplayRTCDay(u32 day)
{
		cmdLCD(GOTO_LINE2_POS0+9);
		str_LCD(DAY[day]);
}
void DisplayRTCDate(u32 date,u32 month,u32 year)
{
		cmdLCD(GOTO_LINE2_POS0);
		char_LCD(date/10+48);
		char_LCD(date%10+48);
		char_LCD('/');
		char_LCD(month/10+48);
		char_LCD(month%10+48);
		char_LCD('/');
		u32_LCD(year%100);
}
void DisplayTemp(u32 val)
{
		cmdLCD(GOTO_LINE1_POS0+9);
		char_LCD('T');
		char_LCD(':');
		cmdLCD(GOTO_LINE1_POS0+11);
		u32_LCD(val);
		cmdLCD(GOTO_LINE1_POS0+13);
		char_LCD(DISP_DEGREE);
		char_LCD('C');
}
void show_Menu(void)
{
	
	u32 gcount=0,display=0;
	Init_KPM();
	cmdLCD(CLR_LCD);
		str_LCD("1.Edit RTC Info");
		cmdLCD(GOTO_LINE2_POS0);
		str_LCD("2.Set Alarm");
		buildCGRAM(cgramLUT,48);
		cmdLCD(GOTO_LINE2_POS0+14);
		char_LCD(4);
		cmdLCD(GOTO_LINE1_POS0+15);
		char_LCD(5);
	while(1)
	{
		while(colScan());
		gcount = keyScan();
		if(gcount==1 || gcount==2 || gcount==3 || gcount ==UP_ARROW || gcount == DOWN_ARROW)
		{
			switch(display)
			{
				case 0: if(gcount==UP_ARROW)
								{
									display = 1;
									cmdLCD(CLR_LCD);
									str_LCD("2.Set Alarm");
									cmdLCD(GOTO_LINE2_POS0);
									str_LCD("3.Exit");
									buildCGRAM(cgramLUT,48);
									cmdLCD(GOTO_LINE1_POS0+14);
									char_LCD(3);
									cmdLCD(GOTO_LINE2_POS0+15);
									char_LCD(5);
								}
								else if(gcount==1)
								{
									SetRTCTimeDateInfoByUsr();
									cmdLCD(CLR_LCD);
									str_LCD("1.Edit RTC Info");
									cmdLCD(GOTO_LINE2_POS0);
									str_LCD("2.Set Alarm");
									buildCGRAM(cgramLUT,48);
									cmdLCD(GOTO_LINE2_POS0+14);
									char_LCD(4);
									cmdLCD(GOTO_LINE1_POS0+15);
									char_LCD(5);
								}
								else if(gcount==2)
								{
									cmdLCD(CLR_LCD);
									setAlarm();
									cmdLCD(CLR_LCD);
									str_LCD("1.Edit RTC Info");
									cmdLCD(GOTO_LINE2_POS0);
									str_LCD("2.Set Alarm");
									buildCGRAM(cgramLUT,48);
									cmdLCD(GOTO_LINE2_POS0+14);
									char_LCD(4);
									cmdLCD(GOTO_LINE1_POS0+15);
									char_LCD(5);
								}
								break;
				case 1: if(gcount==DOWN_ARROW)
								{
									display = 0;
									cmdLCD(CLR_LCD);
									str_LCD("1.Edit RTC Info");
									cmdLCD(GOTO_LINE2_POS0);
									str_LCD("2.Set Alarm");
									buildCGRAM(cgramLUT,48);
									cmdLCD(GOTO_LINE2_POS0+14);
									char_LCD(4);
									cmdLCD(GOTO_LINE1_POS0+15);
									char_LCD(5);
								}
								else if(gcount==2)
								{
									cmdLCD(CLR_LCD);
									setAlarm();
									cmdLCD(CLR_LCD);
									str_LCD("2.Set Alarm");
									cmdLCD(GOTO_LINE2_POS0);
									str_LCD("3.Exit");
									buildCGRAM(cgramLUT,48);
									cmdLCD(GOTO_LINE1_POS0+14);
									char_LCD(3);
									cmdLCD(GOTO_LINE2_POS0+15);
									char_LCD(5);
								}
								else if(gcount==3)
								{
									cmdLCD(CLR_LCD);
									break;
								}
								break;
					}
					if(gcount==3 && display==1)
						{
								cmdLCD(CLR_LCD);
								break;
						}
				}
		else
			continue;
				
		}
}
void SetRTCTimeDateInfoByUsr(void)
{
    s32 key=0;
		u32 flag=0;
    //s32 hh = 0,mm=0, ss=0;
		//s32 day=0, date=0, month=0, year=0;
    Init_KPM();
	label:		cmdLCD(CLR_LCD);
		str_LCD("1.H 2.M 3.S 4.D");
			cmdLCD(GOTO_LINE2_POS0);
			str_LCD("5.D 6.M 7.Y 8.E");	
			
		while(1)
		{
			while((colScan()==0));
			key = keyScan();
			if(key==1 || key==2 || key==3 || key==5 || key==6)
			{
				validateKey(key,&flag);
				goto label;
			}
			else if(key==4)
			{
				validateDayKey();
				goto label;
			}
			else if(key==7)
			{
				validateYearKey();
				goto label;
			}
			else if(key==8)
			{
				while(colScan()==0);
				//delayMS(200);
				break;
			}
		}
}
void setAlarm()
{
	u32 display=0;
	s32 key=-1;
	cmdLCD(CLR_LCD);
	while(colScan()==0);
		//delayMS(200);
		str_LCD("1.Set Hour");
		cmdLCD(GOTO_LINE2_POS0);
		str_LCD("2.Set Minute");
	buildCGRAM(cgramLUT,48);
	cmdLCD(GOTO_LINE2_POS0+14);
	char_LCD(4);
	cmdLCD(GOTO_LINE1_POS0+15);
	char_LCD(5);
	while(1)
	{
		
		key = keyScan();
		while(colScan()==0);
		//delayMS(200);
		switch(display)
		{
			case 0: if(key==UP_ARROW)
							{
								display = 1;
								cmdLCD(CLR_LCD);
								str_LCD("2.Set Minute");
								cmdLCD(GOTO_LINE2_POS0);
								str_LCD("3.Exit");
								buildCGRAM(cgramLUT,48);
								cmdLCD(GOTO_LINE1_POS0+14);
								char_LCD(3);
								cmdLCD(GOTO_LINE2_POS0+15);
								char_LCD(5);
							}
							else if(key==1)
							{
								setAh(key);
								cmdLCD(CLR_LCD);
								str_LCD("1.Set Hour");
								cmdLCD(GOTO_LINE2_POS0);
								str_LCD("2.Set Minute");
								buildCGRAM(cgramLUT,48);
								cmdLCD(GOTO_LINE2_POS0+14);
								char_LCD(4);
								cmdLCD(GOTO_LINE1_POS0+15);
								char_LCD(5);
							}
							else if(key==2)
							{
								setAm(key);
								cmdLCD(CLR_LCD);
								str_LCD("1.Set Hour");
								cmdLCD(GOTO_LINE2_POS0);
								str_LCD("2.Set Minute");
								buildCGRAM(cgramLUT,48);
								cmdLCD(GOTO_LINE2_POS0+14);
								char_LCD(4);
								cmdLCD(GOTO_LINE1_POS0+15);
								char_LCD(5);
							}
							break;
			case 1: if(key==DOWN_ARROW)
							{
								display = 0;
								cmdLCD(CLR_LCD);
								str_LCD("1.Set Hour");
								cmdLCD(GOTO_LINE2_POS0);
								str_LCD("2.Set Minute");
								buildCGRAM(cgramLUT,48);
								cmdLCD(GOTO_LINE2_POS0+14);
								char_LCD(4);
								cmdLCD(GOTO_LINE1_POS0+15);
								char_LCD(5);
							}
							else if(key==2)
							{
								setAm(key);
								cmdLCD(CLR_LCD);
								str_LCD("2.Set Minute");
								cmdLCD(GOTO_LINE2_POS0);
								str_LCD("3.Exit");
								buildCGRAM(cgramLUT,48);
								cmdLCD(GOTO_LINE1_POS0+14);
								char_LCD(3);
								cmdLCD(GOTO_LINE2_POS0+15);
								char_LCD(5);
							}
							else if(key==3)
								break;
							break;
				}
			if(key==3 && display==1)
				break;
		}
}
void DisplayAlarm()
{
	if(!Alarmset())
		return;
	if(flag==1)
	{
		cmdLCD(GOTO_LINE2_POS0+13);
		str_LCD("   ");
		cmdLCD(GOTO_LINE2_POS0+13);
		return;
	}
	IODIR1 |= (1<<BUZZER_OFF_SWITCH);
	IODIR0 |= (1<<BUZZER_PIN);
	if(((IOPIN1>>BUZZER_OFF_SWITCH)&1)==1)
	{
		if(checkAlarm())
		{
				IOSET0 = 1<<BUZZER_PIN;
				buildCGRAM(cgramLUT,48);
				cmdLCD(GOTO_LINE2_POS0+13);
				char_LCD(0);
				char_LCD(1);
				char_LCD(2);
				delayMS(100);
				cmdLCD(GOTO_LINE2_POS0+13);
				char_LCD(' ');
				cmdLCD(GOTO_LINE2_POS0+15);
				char_LCD(' ');
				cmdLCD(GOTO_LINE2_POS0+13);
		}
	}
	else
	{
		flag = 1;
		IOCLR0 = 1<<BUZZER_PIN;
		cmdLCD(GOTO_LINE2_POS0+13);
		str_LCD("   ");
		cmdLCD(GOTO_LINE2_POS0+13);
		Ahh=0,Amm=0;
		return;
	}
}
u32 checkAlarm()
{
	if((HOUR==Ahh) && (MIN ==Amm))
	{
		return 1;
	}
	return 0;
}
u32 Alarmset()
{
	if(Ahh!=0 || Amm!=0)
	{
		return 1;
	}
	return 0;
}
void DisplayBell()
{
	buildCGRAM(cgramLUT,48);
	cmdLCD(GOTO_LINE2_POS0+13);
			char_LCD(0);
			char_LCD(1);
			char_LCD(2);
}
void setAh(s32 key)
{
	
				u32 i=0;
				Ahh =0;
				while(colScan()==0);
				cmdLCD(CLR_LCD);
				cmdLCD(GOTO_LINE1_POS0);
				str_LCD("EnterHour(0-23)");
				cmdLCD(GOTO_LINE2_POS0);
				str_LCD("HH");
				cmdLCD(0x0e);
				cmdLCD(GOTO_LINE2_POS0);
				while(i<3)
				{
					key = keyScan();
					while(colScan()==0);
					if(key==11)
					{
						if(i==1)
						{
							Ahh=Ahh/10;
							cmdLCD(GOTO_LINE2_POS0);
							char_LCD('H');
							cmdLCD(GOTO_LINE2_POS0);
						}
						else if(i==2)
						{
							Ahh = Ahh/10;
							cmdLCD(GOTO_LINE2_POS0+1);
							char_LCD('H');
							cmdLCD(GOTO_LINE2_POS0+1);
						}
						i--;
					}
					else if(key==ENTER)
					{
						goto label1;
					}
					else if(key>=0 && key<=9)
					{
							char_LCD(key+48);
							delayMS(200);
							Ahh = Ahh*10+key;
							i++;
					}
					else
					{
						cmdLCD(CLR_LCD);
						str_LCD("Invalid digit");
						delayMS(200);
						return;
					}
				}
				label1:
				if(Ahh>=0 && Ahh<=23)
				{
					cmdLCD(CLR_LCD);
					str_LCD("SUCCESS");
					delayMS(200);
					return;
				}
				else
				{
					cmdLCD(CLR_LCD);
					str_LCD("Invalid Hours");
					delayMS(200);
					return;
				}
}	
void setAm(s32 key)
{
	if(key==2)
			{
				u32 i=0;
				Amm = 0;
				while(colScan()==0);
				cmdLCD(CLR_LCD);
				cmdLCD(GOTO_LINE1_POS0);
				str_LCD("EnterMinutes(0-59)");
				cmdLCD(GOTO_LINE2_POS0);
				str_LCD("MM");
				cmdLCD(0x0e);
				cmdLCD(GOTO_LINE2_POS0);
				while(i<3)
				{
					key = keyScan();
					while(colScan()==0);
					if(key==11)
					{
						if(i==1)
						{
							Amm=Amm/10;
							cmdLCD(GOTO_LINE2_POS0);
							char_LCD('M');
							cmdLCD(GOTO_LINE2_POS0);
						}
						else if(i==2)
						{
							Amm = Amm/10;
							cmdLCD(GOTO_LINE2_POS0+1);
							char_LCD('M');
							cmdLCD(GOTO_LINE2_POS0+1);
						}
						i--;
					}
					else if(key==ENTER)
					{
						goto label2;
					}
					else if(key>=0 && key<=9)
					{
							char_LCD(key+48);
							delayMS(200);
							Amm = Amm*10+key;
							i++;
					}
					else
					{
						cmdLCD(CLR_LCD);
						str_LCD("Invalid digit");
						delayMS(200);
						return;
					}
				}
				label2:
				if(Amm>=0 && Amm<=59)
				{
					cmdLCD(CLR_LCD);
					str_LCD("SUCCESS");
					delayMS(200);
					return;
				}
				else
				{
					cmdLCD(CLR_LCD);
					str_LCD("Invalid Minutes");
					delayMS(200);
					return;
				}
			}
}

