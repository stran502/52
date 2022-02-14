#ifndef __52_H__
#define __52_H__

/*
��ʱ���ж�ģ��
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


//52ģ�鼯��

//��������ģ��
unsigned int Lkey();

//�������ʾ
void NixLed(unsigned int Num,unsigned int Local,unsigned int Flag);

//�������ģ��
unsigned int Matkey();

//LCDģ��
void LCD_Init();
void LCD_ShowChar(unsigned char Line,unsigned char Column,char Char);
void LCD_ShowString(unsigned char Line,unsigned char Column,char *String);
void LCD_ShowNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length);
void LCD_ShowSignedNum(unsigned char Line,unsigned char Column,int Number,unsigned char Length);
void LCD_ShowHexNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length);
void LCD_ShowBinNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length);

//ѭ����ʱģ��
void Delay(unsigned int ms);

//��ʱ����ʼ��
void Time0_Init();
void Time1_Init();

#endif