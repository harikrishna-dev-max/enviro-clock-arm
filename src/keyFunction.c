#include "myheader.h"
#include <LPC21xx.h>
u8 *enter[5] = {"Set Hour(0-23)","Set Minute(0-59)","Set Second(0-59)","Set Date","Set Month(1-12)"};
u8 *failure[5] = {"Invalid Hour","Invalid Minute","Invalid Second","Invalid Date","Invalid Month"};
u8*dup[5] = {"HH","MM","SS","DD","MM"};
u8 info[5] = {'H','M','S','D','M'};
u8 Day[][4] = {"SUN","MON","TUE","WED","THU","FRI","SAT"};
#define BACKSPACE 11
#define ENTER 14
#define UP_ARROW 12
#define DOWN_ARROW 15
void failureCase(int);
void validateKey(int ind,int* flag)
{
	s32 var,key,i=0;
	if(ind==5 || ind== 6)
	{
		ind = ind-2;
	}
	else
			ind = ind-1;
				var =0;
				while(colScan()==0);
				cmdLCD(CLR_LCD);
				cmdLCD(GOTO_LINE1_POS0);
				str_LCD(enter[ind]);
				cmdLCD(GOTO_LINE2_POS0);
				str_LCD(dup[ind]);
				cmdLCD(0x0e);
				cmdLCD(GOTO_LINE2_POS0);
				while(i<3)
				{
					key = keyScan();
					while(colScan()==0);
					if(i==0)
					{
							while(key==BACKSPACE)
							{
								key = keyScan();
								while(colScan()==0);
							}
					}
					if(i==2)
					{
						if(key==BACKSPACE)
						{
							goto label0;
						}
						if(key!=ENTER)
						{
							cmdLCD(CLR_LCD);
							str_LCD("Invalid Key");
							delayMS(200);
							break;
						}
					}
					label0:if(key==BACKSPACE)
					{
						if(i==1)
						{ 
							var=var/10;
							cmdLCD(GOTO_LINE2_POS0);
							char_LCD(info[ind]);
							cmdLCD(GOTO_LINE2_POS0);
						}
						else if(i==2)
						{
							var = var/10;
							cmdLCD(GOTO_LINE2_POS0+1);
							char_LCD(info[ind]);
							cmdLCD(GOTO_LINE2_POS0+1);
						}
						i--;
					}
					else if(key==ENTER)
					{
						i++;
						switch(ind)
						{
							case 0: if(var>=0 && var<=23)
											{
												HOUR = var;
												cmdLCD(CLR_LCD);
												str_LCD("SUCCESS");
												delayMS(200);
											}
											else
												failureCase(ind);
											break;
							case 1: if(var>=0 && var<=59)
											{
												MIN = var;
												cmdLCD(CLR_LCD);
												str_LCD("SUCCESS");
												delayMS(200);
											}
											else
												failureCase(ind);
											break;
							case 2: if(var>=0 && var<=59)
											{
												SEC = var;
												cmdLCD(CLR_LCD);
												str_LCD("SUCCESS");
												delayMS(200);
											}
											else
												failureCase(ind);
											break;
							
							case 3: 
											if(*flag==0)
											{
												cmdLCD(CLR_LCD);
												str_LCD("Set Month First");
												delayMS(200);
												return;
											}
											if(MONTH==1 || MONTH==3 || MONTH ==5 || MONTH ==7 ||MONTH ==8 || MONTH==10 || MONTH==12)
											{
													if(var>=1 && var<=31)
																{
																	DOM = var;
																	cmdLCD(CLR_LCD);
																	str_LCD("SUCCESS");
																	delayMS(200);
																}
																else
																	failureCase(ind);
																break;
												}
											else if(MONTH==4 || MONTH==6 || MONTH==9 || MONTH==11)
											{
												if(var>=1 && var<=30)
																{
																	DOM = var;
																	cmdLCD(CLR_LCD);
																	str_LCD("SUCCESS");
																	delayMS(200);
																}
																else
																	failureCase(ind);
																break;
											}
											else
											{
												if(var>=1 && var<=28)
																{
																	DOM = var;
																	cmdLCD(CLR_LCD);
																	str_LCD("SUCCESS");
																	delayMS(200);
																}
																else
																	failureCase(ind);
																break;
											}
												
							case 4: if(var>=1 && var<=12)
											{
												MONTH = var;
												*flag = 1;
												cmdLCD(CLR_LCD);
												str_LCD("SUCCESS");
												delayMS(200);
											}
											else
												failureCase(ind);
											break;
							case 5: if(var>=0000 && var<=3000)
											{
												YEAR = var;
												cmdLCD(CLR_LCD);
												str_LCD("SUCCESS");
												delayMS(200);
											}
											else
												failureCase(ind);
											break;
										}
								break;
						}
					else if(key>=0 && key<=9)
					{
							char_LCD(key+48);
							delayMS(200);
							var = var*10+key;
							i++;
					}
					else
					{
						cmdLCD(CLR_LCD);
						str_LCD("Invalid digit");
						delayMS(200);
						break;
					}
				}
			
}
			
void failureCase(int ind)
{
	cmdLCD(CLR_LCD);
	str_LCD(failure[ind]);
	delayMS(200);
}
void validateDayKey(void)
{
				s32 i=0,day = -1,key;
				while(colScan()==0);
				cmdLCD(CLR_LCD);
				cmdLCD(GOTO_LINE1_POS0);
				str_LCD("Set Day(0-6)");
				cmdLCD(GOTO_LINE2_POS0);
				char_LCD('D');
				cmdLCD(GOTO_LINE2_POS0);
				while(i<2)
				{
					key = keyScan();
					while(colScan()==0);
					if(i==1)
					{
						if(key==BACKSPACE)
						{
							goto label1;
						}
						if(key!=ENTER)
						{
							cmdLCD(CLR_LCD);
							str_LCD("Invalid Key");
							delayMS(200);
							return;
						}
					}
					label1: if(key==BACKSPACE)
					{
						if(i==1)
						{
							day = -1;
							cmdLCD(GOTO_LINE2_POS0);
							str_LCD("D  ");
							cmdLCD(GOTO_LINE2_POS0);
						}
						i--;
					}
					else if(key==ENTER)
					{
						goto label4;
					}
					else if(key>=0 && key<=6)
					{
						str_LCD(Day[key]);
						delayMS(200);
						day=key;
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
label4: if(day>=0 && day<=6)
				{
						cmdLCD(CLR_LCD);
						str_LCD("SUCCESS");
						delayMS(200);
						DOW = day;
				}
				else
				{
					cmdLCD(CLR_LCD);
					str_LCD("Invalid Day");
					delayMS(200);
				}
}
void validateYearKey(void)
{
				u32 i=0;
				s32 key,year=0;
				while(colScan()==0);
				cmdLCD(CLR_LCD);
				cmdLCD(GOTO_LINE1_POS0);
				str_LCD("Set Year(2025-3000)");
				cmdLCD(GOTO_LINE2_POS0);
				str_LCD("YYYY");
				cmdLCD(0x0e);
				cmdLCD(GOTO_LINE2_POS0);
				while(i<5)
				{
					key = keyScan();
					while(colScan()==0);
					if(i==4)
					{
						if(key==BACKSPACE)
						{
							goto label0;
						}
						if(key!=ENTER)
						{
							cmdLCD(CLR_LCD);
							str_LCD("Invalid key");
							delayMS(200);
							return;
						}
					}
					label0:	if(key==BACKSPACE)
					{
						if(i==1)
						{
							year=year/10;
							cmdLCD(GOTO_LINE2_POS0);
							char_LCD('Y');
							cmdLCD(GOTO_LINE2_POS0);
						}
						else if(i==2)
						{
							year = year/10;
							cmdLCD(GOTO_LINE2_POS0+1);
							char_LCD('Y');
							cmdLCD(GOTO_LINE2_POS0+1);
						}
						else if(i==3)
						{
							year = year/10;
							cmdLCD(GOTO_LINE2_POS0+2);
							char_LCD('Y');
							cmdLCD(GOTO_LINE2_POS0+2);
						}
						else if(i==4)
						{
							year = year/10;
							cmdLCD(GOTO_LINE2_POS0+3);
							char_LCD('Y');
							cmdLCD(GOTO_LINE2_POS0+3);
						}
						i--;
					}
					else if(key==ENTER)
					{
						goto label7;
					}
					else if(key>=0 && key<=9)
					{
							char_LCD(key+48);
							delayMS(200);
							year = year*10+key;
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
				label7:
				if(year>=2025 && year<=3000)
				{
					YEAR = year;
					cmdLCD(CLR_LCD);
					str_LCD("SUCCESS");
					delayMS(200);
				}
				else
				{
					cmdLCD(CLR_LCD);
					str_LCD("Invalid Year");
					delayMS(200);
				}
}
