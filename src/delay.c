#include "myheader.h"
void delayUS(u32 dly)
{
	dly *=12;
	while(dly--);
}
void delayMS(u32 dly)
{
	dly *= 12000;
	while(dly--);
}
void delayS(u32 dly)
{
	dly *= 12000000;
	while(dly--);
}
