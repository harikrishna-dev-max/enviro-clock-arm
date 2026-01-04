#include "myheader.h"
#include <LPC21xx.h>
u32 kpmLUT[4][4] = {{7,8,9,13},
										{4,5,6,10},
										{1,2,3,11},
										{12,0,14,15}};
void Init_KPM(void)
{
	WRITENIBBLE(IODIR1,ROWS,15);
}
u32 colScan(void)
{
	return ((READNIBBLE(IOPIN1,COLS)<15)?0:1);
}
u32 RowCheck(void)
{
	u32 r;
	for(r=0;r<=3;r++)
	{
		WRITENIBBLE(IOPIN1,ROWS,(~(1<<r)));
		if(colScan()==0)
			break;
	}
	WRITENIBBLE(IOPIN1,ROWS,0);
	return r;
}
u32 ColCheck(void)
{
	u32 c;
	for(c=0;c<=3;c++)
	{
		if(READBIT(IOPIN1,(COL0+c))==0)
		{
			break;
		}
	}
	return c;
}
u32 keyScan(void)
{
	u32 r,c,keyV;
	while(colScan());
	r = RowCheck();
	c = ColCheck();
	keyV = kpmLUT[r][c];
	return keyV;
}
