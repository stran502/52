#include <REGX52.H>

/**
  * @brief  循环延时
  * @param  ms 循环延时多少毫秒
  * @retval 无
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
  * @brief  独立键盘扫描
  * @retval 返回键码
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
  * @brief  数码管显示
  * @param  Num 显示的数字		范围 0-9
  * @param  Local 显示的位置	范围 1-8
	* @param  Flag 显示小数点  	不显示:0  显示:1
  * @retval 无
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
  * @brief  矩阵键盘扫描
  * @param  无
  * @retval 返回键码
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


//引脚配置：
sbit LCD_RS=P2^6;
sbit LCD_RW=P2^5;
sbit LCD_EN=P2^7;
#define LCD_DataPort P0

//函数定义：
/**
  * @brief  LCD1602延时函数，12MHz调用可延时1ms
  * @param  无
  * @retval 无
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
  * @brief  LCD1602写命令
  * @param  Command 要写入的命令
  * @retval 无
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
  * @brief  LCD1602写数据
  * @param  Data 要写入的数据
  * @retval 无
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
  * @brief  LCD1602设置光标位置
  * @param  Line 行位置，范围：1~2
  * @param  Column 列位置，范围：1~16
  * @retval 无
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
  * @brief  LCD1602初始化函数
  * @param  无
  * @retval 无
  */
void LCD_Init()
{
	LCD_WriteCommand(0x38);//八位数据接口，两行显示，5*7点阵
	LCD_WriteCommand(0x0c);//显示开，光标关，闪烁关
	LCD_WriteCommand(0x06);//数据读写操作后，光标自动加一，画面不动
	LCD_WriteCommand(0x01);//光标复位，清屏
}

/**
  * @brief  在LCD1602指定位置上显示一个字符
  * @param  Line 行位置，范围：1~2
  * @param  Column 列位置，范围：1~16
  * @param  Char 要显示的字符
  * @retval 无
  */
void LCD_ShowChar(unsigned char Line,unsigned char Column,char Char)
{
	LCD_SetCursor(Line,Column);
	LCD_WriteData(Char);
}

/**
  * @brief  在LCD1602指定位置开始显示所给字符串
  * @param  Line 起始行位置，范围：1~2
  * @param  Column 起始列位置，范围：1~16
  * @param  String 要显示的字符串
  * @retval 无
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
  * @brief  返回值=X的Y次方
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
  * @brief  在LCD1602指定位置开始显示所给数字
  * @param  Line 起始行位置，范围：1~2
  * @param  Column 起始列位置，范围：1~16
  * @param  Number 要显示的数字，范围：0~65535
  * @param  Length 要显示数字的长度，范围：1~5
  * @retval 无
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
  * @brief  在LCD1602指定位置开始以有符号十进制显示所给数字
  * @param  Line 起始行位置，范围：1~2
  * @param  Column 起始列位置，范围：1~16
  * @param  Number 要显示的数字，范围：-32768~32767
  * @param  Length 要显示数字的长度，范围：1~5
  * @retval 无
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
  * @brief  在LCD1602指定位置开始以十六进制显示所给数字
  * @param  Line 起始行位置，范围：1~2
  * @param  Column 起始列位置，范围：1~16
  * @param  Number 要显示的数字，范围：0~0xFFFF
  * @param  Length 要显示数字的长度，范围：1~4
  * @retval 无
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
  * @brief  在LCD1602指定位置开始以二进制显示所给数字
  * @param  Line 起始行位置，范围：1~2
  * @param  Column 起始列位置，范围：1~16
  * @param  Number 要显示的数字，范围：0~1111 1111 1111 1111
  * @param  Length 要显示数字的长度，范围：1~16
  * @retval 无
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
  * @brief  计时器T0的初始化
  * @param  无
  * @retval 无
  */
void Time0_Init()
{
	TMOD&=0xF0;	//将TMOD 高位也就是T1计时器不初始化，低位置0
	TMOD|=0x01;	//将T0 计时器初始化为16位计时器
	TL0=0x66;		//TL0 和 TH0 控制计时
	TH0=0xFC;		//这里是 1ms 计时
	TF0=0;			//TF0 中断请求，1为请求中断执行，0不执行中断
	TR0=1;			//启动计时器
	ET0=1;			//ET0 和 EA 为中断执行路希("T0路线)
	EA=1;				//ET0 和 EA 为中断执行路线("T0"路线)
	PT0=1;			//PT0 为 "T0" 路线中的优先级
}

/**
  * @brief  计时器T1的初始化
  * @param  无
  * @retval 无
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