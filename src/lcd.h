#ifndef __LCD_H__
#define __LCD_H__
#include "types.h"
void WriteLCD(u8 byte);
void cmdLCD(u8 cmdbyte);
void Init_LCD(void);
void char_LCD(u8 ascii);
void str_LCD(u8*);
void u32_LCD(u32);
void s32_LCD(s32);
void f32_LCD(f32,u32);
void buildCGRAM(u8*,u8);
#endif
