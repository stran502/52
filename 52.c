#include <REGX52.H>

/**
  * @brief  ѭ����ʱ
  * @param  ms ѭ����ʱ���ٺ���
  * @retval ��
  */
void Delay(unsigned int ms)
{
	unsigned char i, j;
	while(ms--)
	{
		i = 2;
		j = 199;
		do
		{
			while (--j);
		}while (--i);
	}
}
/**
  * @brief  ��������ɨ��
  * @retval ���ؼ���
  */
unsigned int Lkey()
{
	unsigned int KeyNum=0;
	if(P3_1==0){Delay(20);while(P3_1==0);Delay(20);KeyNum=1;}
	if(P3_0==0){Delay(20);while(P3_0==0);Delay(20);KeyNum=2;}
	if(P3_2==0){Delay(20);while(P3_2==0);Delay(20);KeyNum=3;}
	if(P3_3==0){Delay(20);while(P3_3==0);Delay(20);KeyNum=4;}
	return KeyNum;
}

/**
  * @brief  �������ʾ
  * @param  Num ��ʾ������		��Χ 0-9
  * @param  Local ��ʾ��λ��	��Χ 1-8
	* @param  Flag ��ʾС����  	����ʾ:0  ��ʾ:1
  * @retval ��
  */
void NixLed(unsigned int Num,unsigned int Local,unsigned int Flag)
{
	unsigned int Nixnum[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
	unsigned int temp=8-Local;
	P2_2=temp&0x01;
	P2_3=temp&0x02;
	P2_4=temp&0x04;
	P0=Nixnum[Num];
	if(Flag==1)
		P0|=0x80;
}

/**
  * @brief  �������ɨ��
  * @param  ��
  * @retval ���ؼ���
  */
unsigned int Matkey()
{
	unsigned int keynum=0;
	P1=0xFF;
	P1_3=0;
	if(P1_4==0){Delay(20);while(P1_4==0);Delay(20);keynum=13;}
	if(P1_5==0){Delay(20);while(P1_5==0);Delay(20);keynum=9;}
	if(P1_6==0){Delay(20);while(P1_6==0);Delay(20);keynum=5;}
	if(P1_7==0){Delay(20);while(P1_7==0);Delay(20);keynum=1;}
	
	P1=0xFF;
	P1_2=0;
	if(P1_4==0){Delay(20);while(P1_4==0);Delay(20);keynum=14;}
	if(P1_5==0){Delay(20);while(P1_5==0);Delay(20);keynum=10;}
	if(P1_6==0){Delay(20);while(P1_6==0);Delay(20);keynum=6;}
	if(P1_7==0){Delay(20);while(P1_7==0);Delay(20);keynum=2;}
	
	P1=0xFF;
	P1_1=0;
	if(P1_4==0){Delay(20);while(P1_4==0);Delay(20);keynum=15;}
	if(P1_5==0){Delay(20);while(P1_5==0);Delay(20);keynum=11;}
	if(P1_6==0){Delay(20);while(P1_6==0);Delay(20);keynum=7;}
	if(P1_7==0){Delay(20);while(P1_7==0);Delay(20);keynum=3;}
	
	P1=0xFF;
	P1_0=0;
	if(P1_4==0){Delay(20);while(P1_4==0);Delay(20);keynum=16;}
	if(P1_5==0){Delay(20);while(P1_5==0);Delay(20);keynum=12;}
	if(P1_6==0){Delay(20);while(P1_6==0);Delay(20);keynum=8;}
	if(P1_7==0){Delay(20);while(P1_7==0);Delay(20);keynum=4;}
	
	return keynum;
}


//�������ã�
sbit LCD_RS=P2^6;
sbit LCD_RW=P2^5;
sbit LCD_EN=P2^7;
#define LCD_DataPort P0

//�������壺
/**
  * @brief  LCD1602��ʱ������12MHz���ÿ���ʱ1ms
  * @param  ��
  * @retval ��
  */
void LCD_Delay()
{
	unsigned char i, j;

	i = 2;
	j = 239;
	do
	{
		while (--j);
	} while (--i);
}

/**
  * @brief  LCD1602д����
  * @param  Command Ҫд�������
  * @retval ��
  */
void LCD_WriteCommand(unsigned char Command)
{
	LCD_RS=0;
	LCD_RW=0;
	LCD_DataPort=Command;
	LCD_EN=1;
	LCD_Delay();
	LCD_EN=0;
	LCD_Delay();
}

/**
  * @brief  LCD1602д����
  * @param  Data Ҫд�������
  * @retval ��
  */
void LCD_WriteData(unsigned char Data)
{
	LCD_RS=1;
	LCD_RW=0;
	LCD_DataPort=Data;
	LCD_EN=1;
	LCD_Delay();
	LCD_EN=0;
	LCD_Delay();
}

/**
  * @brief  LCD1602���ù��λ��
  * @param  Line ��λ�ã���Χ��1~2
  * @param  Column ��λ�ã���Χ��1~16
  * @retval ��
  */
void LCD_SetCursor(unsigned char Line,unsigned char Column)
{
	if(Line==1)
	{
		LCD_WriteCommand(0x80|(Column-1));
	}
	else if(Line==2)
	{
		LCD_WriteCommand(0x80|(Column-1+0x40));
	}
}

/**
  * @brief  LCD1602��ʼ������
  * @param  ��
  * @retval ��
  */
void LCD_Init()
{
	LCD_WriteCommand(0x38);//��λ���ݽӿڣ�������ʾ��5*7����
	LCD_WriteCommand(0x0c);//��ʾ�������أ���˸��
	LCD_WriteCommand(0x06);//���ݶ�д�����󣬹���Զ���һ�����治��
	LCD_WriteCommand(0x01);//��긴λ������
}

/**
  * @brief  ��LCD1602ָ��λ������ʾһ���ַ�
  * @param  Line ��λ�ã���Χ��1~2
  * @param  Column ��λ�ã���Χ��1~16
  * @param  Char Ҫ��ʾ���ַ�
  * @retval ��
  */
void LCD_ShowChar(unsigned char Line,unsigned char Column,char Char)
{
	LCD_SetCursor(Line,Column);
	LCD_WriteData(Char);
}

/**
  * @brief  ��LCD1602ָ��λ�ÿ�ʼ��ʾ�����ַ���
  * @param  Line ��ʼ��λ�ã���Χ��1~2
  * @param  Column ��ʼ��λ�ã���Χ��1~16
  * @param  String Ҫ��ʾ���ַ���
  * @retval ��
  */
void LCD_ShowString(unsigned char Line,unsigned char Column,char *String)
{
	unsigned char i;
	LCD_SetCursor(Line,Column);
	for(i=0;String[i]!='\0';i++)
	{
		LCD_WriteData(String[i]);
	}
}

/**
  * @brief  ����ֵ=X��Y�η�
  */
int LCD_Pow(int X,int Y)
{
	unsigned char i;
	int Result=1;
	for(i=0;i<Y;i++)
	{
		Result*=X;
	}
	return Result;
}

/**
  * @brief  ��LCD1602ָ��λ�ÿ�ʼ��ʾ��������
  * @param  Line ��ʼ��λ�ã���Χ��1~2
  * @param  Column ��ʼ��λ�ã���Χ��1~16
  * @param  Number Ҫ��ʾ�����֣���Χ��0~65535
  * @param  Length Ҫ��ʾ���ֵĳ��ȣ���Χ��1~5
  * @retval ��
  */
void LCD_ShowNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length)
{
	unsigned char i;
	LCD_SetCursor(Line,Column);
	for(i=Length;i>0;i--)
	{
		LCD_WriteData(Number/LCD_Pow(10,i-1)%10+'0');
	}
}

/**
  * @brief  ��LCD1602ָ��λ�ÿ�ʼ���з���ʮ������ʾ��������
  * @param  Line ��ʼ��λ�ã���Χ��1~2
  * @param  Column ��ʼ��λ�ã���Χ��1~16
  * @param  Number Ҫ��ʾ�����֣���Χ��-32768~32767
  * @param  Length Ҫ��ʾ���ֵĳ��ȣ���Χ��1~5
  * @retval ��
  */
void LCD_ShowSignedNum(unsigned char Line,unsigned char Column,int Number,unsigned char Length)
{
	unsigned char i;
	unsigned int Number1;
	LCD_SetCursor(Line,Column);
	if(Number>=0)
	{
		LCD_WriteData('+');
		Number1=Number;
	}
	else
	{
		LCD_WriteData('-');
		Number1=-Number;
	}
	for(i=Length;i>0;i--)
	{
		LCD_WriteData(Number1/LCD_Pow(10,i-1)%10+'0');
	}
}

/**
  * @brief  ��LCD1602ָ��λ�ÿ�ʼ��ʮ��������ʾ��������
  * @param  Line ��ʼ��λ�ã���Χ��1~2
  * @param  Column ��ʼ��λ�ã���Χ��1~16
  * @param  Number Ҫ��ʾ�����֣���Χ��0~0xFFFF
  * @param  Length Ҫ��ʾ���ֵĳ��ȣ���Χ��1~4
  * @retval ��
  */
void LCD_ShowHexNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length)
{
	unsigned char i,SingleNumber;
	LCD_SetCursor(Line,Column);
	for(i=Length;i>0;i--)
	{
		SingleNumber=Number/LCD_Pow(16,i-1)%16;
		if(SingleNumber<10)
		{
			LCD_WriteData(SingleNumber+'0');
		}
		else
		{
			LCD_WriteData(SingleNumber-10+'A');
		}
	}
}

/**
  * @brief  ��LCD1602ָ��λ�ÿ�ʼ�Զ�������ʾ��������
  * @param  Line ��ʼ��λ�ã���Χ��1~2
  * @param  Column ��ʼ��λ�ã���Χ��1~16
  * @param  Number Ҫ��ʾ�����֣���Χ��0~1111 1111 1111 1111
  * @param  Length Ҫ��ʾ���ֵĳ��ȣ���Χ��1~16
  * @retval ��
  */
void LCD_ShowBinNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length)
{
	unsigned char i;
	LCD_SetCursor(Line,Column);
	for(i=Length;i>0;i--)
	{
		LCD_WriteData(Number/LCD_Pow(2,i-1)%2+'0');
	}
}

/**
  * @brief  ��ʱ��T0�ĳ�ʼ��
  * @param  ��
  * @retval ��
  */
void Time0_Init()
{
	TMOD&=0xF0;	//��TMOD ��λҲ����T1��ʱ������ʼ������λ��0
	TMOD|=0x01;	//��T0 ��ʱ����ʼ��Ϊ16λ��ʱ��
	TL0=0x66;		//TL0 �� TH0 ���Ƽ�ʱ
	TH0=0xFC;		//������ 1ms ��ʱ
	TF0=0;			//TF0 �ж�����1Ϊ�����ж�ִ�У�0��ִ���ж�
	TR0=1;			//������ʱ��
	ET0=1;			//ET0 �� EA Ϊ�ж�ִ��·ϣ("T0·��)
	EA=1;				//ET0 �� EA Ϊ�ж�ִ��·��("T0"·��)
	PT0=1;			//PT0 Ϊ "T0" ·���е����ȼ�
}

/**
  * @brief  ��ʱ��T1�ĳ�ʼ��
  * @param  ��
  * @retval ��
  */
void Time1_Init()
{
	TMOD&=0x0F;
	TMOD|=0x10;
	TL1=0x66;
	TH1=0xFC;
	TF1=0;
	TR1=1;
	ET1=1;
	EA=1;
	PT1=0;
}