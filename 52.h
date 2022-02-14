#ifndef __52_H__
#define __52_H__

/*
计时器中断模板
void Time1() interrupt 1
{
	static unsigned int count=0;
	TL0=0x18;
	TH0=0xFC;
	count++;
	if(count>=1000)
	{
		
		
		count=0;
	}
		
}
*/


//52模块集合

//独立键盘模块
unsigned int Lkey();

//数码管显示
void NixLed(unsigned int Num,unsigned int Local,unsigned int Flag);

//矩阵键盘模块
unsigned int Matkey();

//LCD模块
void LCD_Init();
void LCD_ShowChar(unsigned char Line,unsigned char Column,char Char);
void LCD_ShowString(unsigned char Line,unsigned char Column,char *String);
void LCD_ShowNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length);
void LCD_ShowSignedNum(unsigned char Line,unsigned char Column,int Number,unsigned char Length);
void LCD_ShowHexNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length);
void LCD_ShowBinNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length);

//循环延时模块
void Delay(unsigned int ms);

//计时器初始化
void Time0_Init();
void Time1_Init();

#endif