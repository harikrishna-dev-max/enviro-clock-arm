#include "myheader.h"
#include <LPC21xx.h>
#include <string.h>
s8 str[] = "Vector India";
int main()
{
	u8 t;
	s8* ptr = str;
	int len = strlen(ptr);
	int l = len;
	while(len)
	{
		t = ptr[0];
		memmove(ptr,ptr+1,l);
		ptr[l-1] = t;
		delayS(1);
		len--;
	}
	while(1);
}
