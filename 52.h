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

//DS1302
void DS1302_Init();
void DS1302_Write(unsigned char Byte,unsigned char Data);
unsigned char DS1302_Read(unsigned char Byte);


//串口通信
void Ser_Init();
void Ser_Sent(unsigned char Byte);

/*
void Ser_A() interrupt 4
{
	if(RI)
	{
		 =SBUF;

		RI=0;
	}
}
*/


//LED点阵屏
void LEDP(unsigned char Col,unsigned char Row);

//I2C总线
void I2C_Start();
void I2C_Stop();
void 	I2C_Send(unsigned char Data);
unsigned char I2C_Receive();
void I2C_Send_Ack(bit Flag);
bit I2C_Receive_Ack();

//AT24C02
void I2C_Write(unsigned char Addr,unsigned char Data);
unsigned char I2C_Read(unsigned char Addr);


#endif
