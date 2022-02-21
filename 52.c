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
void Time1_Init()		//和上面Time0_Init()函数的一样
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

//DS1302 芯片
sbit DS1302_SCK=P3^6;
sbit DS1302_IO=P3^4;
sbit DS1302_CE=P3^5;
/**
  * @brief  DS1302初始化
  * @retval 无
  */
void DS1302_Init()
{
	DS1302_SCK=0;
	DS1302_CE=0;
}
/**
  * @brief  DS1302写入
  * @param  Byte 地址 值为“年月日时分秒的规定地址”
  * @param  Data	初始化Byte对应时间的值
	* @retval 无
  */
void DS1302_Write(unsigned char Byte,unsigned char Data)
{
	int i;
	DS1302_CE=1;
	for(i=0;i<8;i++)
	{
		DS1302_IO=Byte&(0x01<<i);
		DS1302_SCK=1;
		DS1302_SCK=0;
	}
		for(i=0;i<8;i++)
	{
		DS1302_IO=Data&(0x01<<i);
		DS1302_SCK=1;
		DS1302_SCK=0;
	}
	DS1302_CE=0;
}
/**
  * @brief  DS1302读出
  * @param 	Byte 地址 值为“年月日时分秒的规定地址” 
  * @retval Byte 地址中的值
  */
unsigned char DS1302_Read(unsigned char Byte)
{
	unsigned int i,temp=0;

	DS1302_CE=1;
	for(i=0;i<8;i++)
	{
		DS1302_IO=Byte&(0x01<<i);
		DS1302_SCK=0;
		DS1302_SCK=1;
	}
	for(i=0;i<8;i++)
	{
			DS1302_SCK=1;
			DS1302_SCK=0;
			if(DS1302_IO)
			temp|=0x01<<i;
	}
	DS1302_CE=0;
	DS1302_IO=0;
	return temp/16*10+temp%16;
}

//串口通信
/**
  * @brief  串口通信初始化
  * @retval 无
  */
void Ser_Init()
{
	SCON=0x50;
	PCON|=0x80;
	TMOD&=0x0F;
	TMOD|=0x20;
	TL1=0xF4;
	TH1=0xF4;
	TR1=1;
	ET1=0;
	ES=1;
	EA=1;
}
/**
  * @brief  串口发送
  * @param  Byte 从单片机发送数据
  * @retval 无
  */
void Ser_Sent(unsigned char Byte)
{
	SBUF=Byte;
	while(TI==0);
	TI=0;
}

//LED点阵屏
sbit RCK=P3^5;
sbit SCK=P3^6;
sbit SER=P3^4;
/**
  * @brief  LED点阵屏控制输出
  * @param  Col 哪几行亮 用数的二进制中的1对应哪几行亮 0x00-0xFF
  * @param  Row 哪一列亮	用十进制表示某一列亮 1-8
  * @retval 无
  */
void LEDP(unsigned char Col,unsigned char Row)
{
	int i=1;
	SCK=0;
	P0=~(0x80>>(Row-1));
	
	for(;i<=8;i++,Col<<=1)
	{
		SER=Col&0x80;
		SCK=1;
		SCK=0;
	}
	RCK=1;
	RCK=0;
	Delay(1);
	P0=0xFF;
}



//I2C 通信
#define SLAVE 0xA0		//AT24C02固定地址 0xA0为写  0xA1为读
sbit I2C_SDA=P2^0;
sbit I2C_SCL=P2^1;

/**
  * @brief  I2C帧开始 
  * @retval 无
  */
void I2C_Start()
{
	I2C_SDA=1;
	I2C_SCL=1;
	I2C_SDA=0;
	I2C_SCL=0;
	
}
/**
  * @brief  I2C帧结束  
  * @retval 无
  */
void I2C_Stop()
{
	I2C_SDA=0;
	I2C_SCL=1;
	I2C_SDA=1;
}

/**
  * @brief  I2C发送
  * @param   Data 要发送的数据
  * @retval 无
  */
void 	I2C_Send(unsigned char Data)
{
	unsigned char i;
	for(i=0;i<8;i++)
		{
			I2C_SDA=Data&0x80>>i;
			I2C_SCL=1;
			I2C_SCL=0;
		}
}
/**
  * @brief  I2C接收
  * @retval 无
  */
unsigned char I2C_Receive()
{
	unsigned char Data=0x00,i;
	I2C_SDA=1;
	for(i=0;i<8;i++)
		{
			I2C_SCL=1;
			if(I2C_SDA) Data|=0x80>>i;
			I2C_SCL=0;
		}
	return Data;
}
/**
  * @brief  发送ACK应答
  * @param  Flag ACK应答 0-1
  * @retval 无
  */
void I2C_Send_Ack(bit Flag)
{
	I2C_SDA=Flag;
	I2C_SCL=1;
	I2C_SCL=0;
}
/**
  * @brief   接收ACK应答	
  * @retval  从机ACK应答
  */
bit I2C_Receive_Ack()
{
	bit Flag;
	I2C_SDA=1;
	I2C_SCL=1;
	Flag=I2C_SDA;
	I2C_SCL=0;
	return Flag;
}

//AT24C02
/**
  * @brief  写入AT24C02 
  * @param  Addr AT24C02芯片中的某处地址 0-255
  * @param  Data 要写入AT24C02的数据
  * @retval 无
  */
void AT24C02_Write(unsigned char Addr,unsigned char Data)
{
	I2C_Start();
	I2C_Send(SLAVE);
	I2C_Receive_Ack();
	I2C_Send(Addr);
	I2C_Receive_Ack();
	I2C_Send(Data);
	I2C_Receive_Ack();
	I2C_Stop();
}
/**
  * @brief  AT24C02读出
  * @param  Addr 读出AT24C02的某处地址的值 0-255 
  * @retval AT24C02中Addr里的数据
  */
unsigned char AT24C02_Read(unsigned char Addr)
{
	unsigned char Data;
	I2C_Start();
	I2C_Send(SLAVE);
	I2C_Receive_Ack();
	I2C_Send(Addr);
	I2C_Receive_Ack();
	I2C_Start();
	I2C_Send(SLAVE+1);
	I2C_Receive_Ack();
	Data=I2C_Receive();
	I2C_Send_Ack(1);
	I2C_Stop();
	return Data;
}
