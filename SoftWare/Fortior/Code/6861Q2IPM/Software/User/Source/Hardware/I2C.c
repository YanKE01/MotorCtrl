/**************************** (C) COPYRIGHT 2015 Fortiortech shenzhen *****************************
* File Name          : ADCInit.c
* Author             : Fortiortech Application Dept
* Version            : V1.0
* Date               : 01/07/2015
* Description        : This file contains ADC function used for Motor Control.
***************************************************************************************************
* All Rights Reserved
**************************************************************************************************/ 

/* Includes -------------------------------------------------------------------------------------*/
#include <FU68xx_2.h>
#include <Myproject.h>

//uint8 xdata RXdata[2] = {0,0};
#define SET_SCL_OUT()    SetBit(P1_OE, P14, 1);							// P14/SCL output(0:input,1:output)
#define SET_SDA_OUT()    SetBit(P1_OE, P16, 1);							// P16/SDA output(0:input,1:output)
#define SET_SDA_IN()     SetBit(P1_OE, P16, 0);							// P16/SDA output(0:input,1:output)

uint8 SlaAck=0;

//普通IO口模拟I2C通讯

/*-------------------------------------------------------------------------------------------------
	Function Name :	Delay2us
	Description   :	24MHZ,延迟2us
	Input         :	输入说明（详细）
  Output				:	输出说明（详细）
-------------------------------------------------------------------------------------------------*/
void Delay2us(void)		//@20.000MHz
{
	unsigned char i;

	_nop_();
	_nop_();
	i = 6;
	while (--i);
}

/*-------------------------------------------------------------------------------------------------
	Function Name :	I2C_Start
	Description   :	I2C起始信号
	Input         :	
  Output				:	
-------------------------------------------------------------------------------------------------*/
bool I2C_Start(void)//起始信号，在时钟线为高电平时，数据线由高电平变低电平。
{
		// SDA 1->0 while SCL High
	  SCL = 0;                    //拉高时钟线
    Delay2us();                 //延时
    SDA = 1;                    //拉高数据线
	  Delay2us();                 //延时
    SCL = 1;                    //拉高时钟线
    Delay2us();                 //延时
	  if(!SDA)return false;
    SDA = 0;                    //产生下降沿
    Delay2us();                 //延时
	  if(SDA) return false;
    SCL = 0;                    //拉低时钟线
}

/*-------------------------------------------------------------------------------------------------
	Function Name :	I2C_Stop
	Description   :	I2C停止信号
	Input         :	
  Output				:	
-------------------------------------------------------------------------------------------------*/
void I2C_Stop(void)//停止信号，在时钟线为高电平时，数据线由低电平变高电平。
{
		// SDA 0->1 while SCL High
	  SCL = 0; 
    Delay2us();                 //延时
    SDA = 0;                    //拉低数据线
	  Delay2us();                 //延时
    SCL = 1;                    //产生上升沿
    Delay2us();                 //延时
	  SDA = 1;                    //拉低数据线
	  Delay2us();                 //延时
		SCL = 0; 
}

/*-------------------------------------------------------------------------------------------------
	Function Name :	void I2C_SendACK()
	Description   :	I2C发送应答信号
	Input         :	ack (0:ACK 1:NAK)
  Output				:	
-------------------------------------------------------------------------------------------------*/
void I2C_SendACK()
{
		SDA = 0;
    SCL = 0;                    //拉低时钟线
    Delay2us();                 //延时
	  SCL = 1;                    //拉高时钟线
    Delay2us();                 //延时	
    SCL = 0;                    //拉低时钟线
}
/*-------------------------------------------------------------------------------------------------
	Function Name :	void I2C_SendACK()
	Description   :	I2C发送应答信号
	Input         :	ack (0:ACK 1:NAK)
  Output				:	
-------------------------------------------------------------------------------------------------*/
void I2C_SendNoACK()
{
		SDA = 1;
    SCL = 0;                    //拉低时钟线
    Delay2us();                 //延时
	  SCL = 1;                    //拉高时钟线
    Delay2us();                 //延时	
    SCL = 0;                    //拉低时钟线
}
/*-------------------------------------------------------------------------------------------------
	Function Name :	bit I2C_RecvACK(void)
	Description   :	I2C接收应答信号
	Input         :	
  Output				:	
-------------------------------------------------------------------------------------------------*/
bool I2C_RecvACK(void)
{
		SCL	= 0;
		Delay2us();                 //延时
		SET_SDA_IN();
		Delay2us();                 //延时
    SCL = 1;                    //拉高时钟线
		Delay2us();                 //延时
	  SlaAck = SDA;               //读应答信号
		Delay2us();                 //延时
    SCL = 0;                    //拉低时钟线
		SET_SDA_OUT();
	  if(SlaAck)
		{
			return false;
		}else
		{
			return true;			
		}
}

/*-------------------------------------------------------------------------------------------------
	Function Name :	void I2C_SendByte(unsigned char dat)
	Description   :	向I2C总线发送一个字节数据
	Input         :	
  Output				:	
-------------------------------------------------------------------------------------------------*/
void I2C_SendByte(unsigned char dat)
{
    unsigned char i;
    for (i=0; i<8; i++)         //8位计数器
    {
				SCL  = 0;
				Delay2us();             //延时
				if(dat&0x80)
				{
					SDA = 1;
				}
				else
				{
					SDA = 0;
				}
				Delay2us();             //延时				
        dat <<= 1;              //移出数据的最高位
        SCL = 1;                //拉高时钟线
        Delay2us();             //延时
				Delay2us();             //延时
    }
		SCL = 0;                    //拉低时钟线 

}

/*-------------------------------------------------------------------------------------------------
	Function Name :	unsigned char I2C_RecvByte(void)
	Description   :	从I2C总线接收一个字节数据
	Input         :	
  Output				:	
-------------------------------------------------------------------------------------------------*/
unsigned char I2C_RecvByte(void)
{
    unsigned char i;
    unsigned char dat = 0;
    SDA = 1;                    //使能内部上拉,准备读取数据,
		SET_SDA_IN();
    for (i=0; i<8; i++)         //8位计数器
    {
			  SCL = 0;                //拉低时钟线
        Delay2us();             //延时
        dat <<= 1;
        SCL = 1;                //拉高时钟线
				_nop_();
				_nop_();
				_nop_();
				if(SDA)
				{
					dat |= 0x01;
				}
				else
				{
					dat &= 0xfe;
				}
				Delay2us();             //延时
    }
	  SCL = 0;                //拉低时钟线
		SET_SDA_OUT();
    return dat;
}

/*-------------------------------------------------------------------------------------------------
	Function Name :	void Single_WriteI2C(unsigned char REG_Address,unsigned char REG_data)
	Description   :	向I2C设备写入一个字节数据
	Input         :	
  Output				:	
-------------------------------------------------------------------------------------------------*/
bool Single_WriteI2C(unsigned char REG_Address,unsigned char REG_data)
{
    I2C_Start();                  //起始信号
	
    I2C_SendByte(WC24C02);   //发送设备地址+写信号
	  if(I2C_RecvACK() == 0)
		{
			return false;
		}
		
    I2C_SendByte(REG_Address);    //内部寄存器地址
		if(I2C_RecvACK() == 0)
		{
			return false;
		}
		
    I2C_SendByte(REG_data);       //内部寄存器数据
		if(I2C_RecvACK() == 0)
		{
			return false;
		}
		
    I2C_Stop();                   //发送停止信号
		return true;
}
bool Page_WriteI2C(unsigned char Wrire_Address,unsigned char *Write_data,unsigned char n)
{
	unsigned char i;
	
	if((n > WC24C02_PAGESIZE) || (!n))
		return false;
	
	I2C_Start();                  //起始信号
	
  I2C_SendByte(WC24C02);   //发送设备地址+写信号
	if(I2C_RecvACK() == 0)
	{
		return false;
	}
	
	I2C_SendByte(Wrire_Address);   //发送设备地址+写信号
	if(I2C_RecvACK() == 0)
	{
		return false;
	}
	
	for(i = 0;i < n;i++)
	{
		I2C_SendByte(Write_data[i]);   //发送数据
		if(I2C_RecvACK() == 0)
		{
			return false;
		}
	}
	
	I2C_Stop();                   //发送停止信号
	return true;
}

/*-------------------------------------------------------------------------------------------------
	Function Name :	unsigned char Single_ReadI2C(unsigned char REG_Address)
	Description   :	从I2C设备读取一个字节数据
	Input         :	
  Output				:	
-------------------------------------------------------------------------------------------------*/
unsigned char Single_ReadI2C(unsigned char REG_Address)
{
	unsigned char REG_data;
	I2C_Start();                   //起始信号
	
	I2C_SendByte(WC24C02);    //发送设备地址+写信号
	if(I2C_RecvACK() == 0)
	{
		return false;
	}
	
	I2C_SendByte(REG_Address);     //发送存储单元地址，从0开始	
	if(I2C_RecvACK() == 0)
	{
		return false;
	}
	
	I2C_Start();                   //起始信号
	
	I2C_SendByte(RC24C02);  //发送设备地址+读信号
	if(I2C_RecvACK() == 0)
	{
		return false;
	}
	
	REG_data=I2C_RecvByte();       //读出寄存器数据
	I2C_SendACK();                //发送应答信号
	
	I2C_Stop();                    //停止信号
	return REG_data;
}
bool I2C_BufferRead(unsigned char Read_Address,unsigned char *Read_data,unsigned char n) 
{
	unsigned char i;
	if(n > WC24C02_MAXSIZE)
		return 0;
	
	I2C_Start();                   //起始信号

	I2C_SendByte(WC24C02);   //发送设备地址+写信号
	if(I2C_RecvACK() == 0)
	{
		return false;
	}
	
	I2C_SendByte(Read_Address);   //发送寄存器地址
	if(I2C_RecvACK() == 0)
	{
		return false;
	}

	I2C_Start();                   //起始信号
	
	I2C_SendByte(RC24C02);   //发送设备地址+写信号
	if(I2C_RecvACK() == 0)
	{
		return false;
	}
	
	for(i = 0;i < (n - 1);i++)
	{
	  Read_data[i] = I2C_RecvByte(); //读出寄存器数据
	  I2C_SendACK();                //发送应答信号
	}
	Read_data[n - 1] = I2C_RecvByte();
	I2C_SendNoACK();
	
	I2C_Stop();                    //停止信号
  return true;
}

