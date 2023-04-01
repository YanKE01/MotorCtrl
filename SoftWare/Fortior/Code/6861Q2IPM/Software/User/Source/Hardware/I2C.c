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

//��ͨIO��ģ��I2CͨѶ

/*-------------------------------------------------------------------------------------------------
	Function Name :	Delay2us
	Description   :	24MHZ,�ӳ�2us
	Input         :	����˵������ϸ��
  Output				:	���˵������ϸ��
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
	Description   :	I2C��ʼ�ź�
	Input         :	
  Output				:	
-------------------------------------------------------------------------------------------------*/
bool I2C_Start(void)//��ʼ�źţ���ʱ����Ϊ�ߵ�ƽʱ���������ɸߵ�ƽ��͵�ƽ��
{
		// SDA 1->0 while SCL High
	  SCL = 0;                    //����ʱ����
    Delay2us();                 //��ʱ
    SDA = 1;                    //����������
	  Delay2us();                 //��ʱ
    SCL = 1;                    //����ʱ����
    Delay2us();                 //��ʱ
	  if(!SDA)return false;
    SDA = 0;                    //�����½���
    Delay2us();                 //��ʱ
	  if(SDA) return false;
    SCL = 0;                    //����ʱ����
}

/*-------------------------------------------------------------------------------------------------
	Function Name :	I2C_Stop
	Description   :	I2Cֹͣ�ź�
	Input         :	
  Output				:	
-------------------------------------------------------------------------------------------------*/
void I2C_Stop(void)//ֹͣ�źţ���ʱ����Ϊ�ߵ�ƽʱ���������ɵ͵�ƽ��ߵ�ƽ��
{
		// SDA 0->1 while SCL High
	  SCL = 0; 
    Delay2us();                 //��ʱ
    SDA = 0;                    //����������
	  Delay2us();                 //��ʱ
    SCL = 1;                    //����������
    Delay2us();                 //��ʱ
	  SDA = 1;                    //����������
	  Delay2us();                 //��ʱ
		SCL = 0; 
}

/*-------------------------------------------------------------------------------------------------
	Function Name :	void I2C_SendACK()
	Description   :	I2C����Ӧ���ź�
	Input         :	ack (0:ACK 1:NAK)
  Output				:	
-------------------------------------------------------------------------------------------------*/
void I2C_SendACK()
{
		SDA = 0;
    SCL = 0;                    //����ʱ����
    Delay2us();                 //��ʱ
	  SCL = 1;                    //����ʱ����
    Delay2us();                 //��ʱ	
    SCL = 0;                    //����ʱ����
}
/*-------------------------------------------------------------------------------------------------
	Function Name :	void I2C_SendACK()
	Description   :	I2C����Ӧ���ź�
	Input         :	ack (0:ACK 1:NAK)
  Output				:	
-------------------------------------------------------------------------------------------------*/
void I2C_SendNoACK()
{
		SDA = 1;
    SCL = 0;                    //����ʱ����
    Delay2us();                 //��ʱ
	  SCL = 1;                    //����ʱ����
    Delay2us();                 //��ʱ	
    SCL = 0;                    //����ʱ����
}
/*-------------------------------------------------------------------------------------------------
	Function Name :	bit I2C_RecvACK(void)
	Description   :	I2C����Ӧ���ź�
	Input         :	
  Output				:	
-------------------------------------------------------------------------------------------------*/
bool I2C_RecvACK(void)
{
		SCL	= 0;
		Delay2us();                 //��ʱ
		SET_SDA_IN();
		Delay2us();                 //��ʱ
    SCL = 1;                    //����ʱ����
		Delay2us();                 //��ʱ
	  SlaAck = SDA;               //��Ӧ���ź�
		Delay2us();                 //��ʱ
    SCL = 0;                    //����ʱ����
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
	Description   :	��I2C���߷���һ���ֽ�����
	Input         :	
  Output				:	
-------------------------------------------------------------------------------------------------*/
void I2C_SendByte(unsigned char dat)
{
    unsigned char i;
    for (i=0; i<8; i++)         //8λ������
    {
				SCL  = 0;
				Delay2us();             //��ʱ
				if(dat&0x80)
				{
					SDA = 1;
				}
				else
				{
					SDA = 0;
				}
				Delay2us();             //��ʱ				
        dat <<= 1;              //�Ƴ����ݵ����λ
        SCL = 1;                //����ʱ����
        Delay2us();             //��ʱ
				Delay2us();             //��ʱ
    }
		SCL = 0;                    //����ʱ���� 

}

/*-------------------------------------------------------------------------------------------------
	Function Name :	unsigned char I2C_RecvByte(void)
	Description   :	��I2C���߽���һ���ֽ�����
	Input         :	
  Output				:	
-------------------------------------------------------------------------------------------------*/
unsigned char I2C_RecvByte(void)
{
    unsigned char i;
    unsigned char dat = 0;
    SDA = 1;                    //ʹ���ڲ�����,׼����ȡ����,
		SET_SDA_IN();
    for (i=0; i<8; i++)         //8λ������
    {
			  SCL = 0;                //����ʱ����
        Delay2us();             //��ʱ
        dat <<= 1;
        SCL = 1;                //����ʱ����
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
				Delay2us();             //��ʱ
    }
	  SCL = 0;                //����ʱ����
		SET_SDA_OUT();
    return dat;
}

/*-------------------------------------------------------------------------------------------------
	Function Name :	void Single_WriteI2C(unsigned char REG_Address,unsigned char REG_data)
	Description   :	��I2C�豸д��һ���ֽ�����
	Input         :	
  Output				:	
-------------------------------------------------------------------------------------------------*/
bool Single_WriteI2C(unsigned char REG_Address,unsigned char REG_data)
{
    I2C_Start();                  //��ʼ�ź�
	
    I2C_SendByte(WC24C02);   //�����豸��ַ+д�ź�
	  if(I2C_RecvACK() == 0)
		{
			return false;
		}
		
    I2C_SendByte(REG_Address);    //�ڲ��Ĵ�����ַ
		if(I2C_RecvACK() == 0)
		{
			return false;
		}
		
    I2C_SendByte(REG_data);       //�ڲ��Ĵ�������
		if(I2C_RecvACK() == 0)
		{
			return false;
		}
		
    I2C_Stop();                   //����ֹͣ�ź�
		return true;
}
bool Page_WriteI2C(unsigned char Wrire_Address,unsigned char *Write_data,unsigned char n)
{
	unsigned char i;
	
	if((n > WC24C02_PAGESIZE) || (!n))
		return false;
	
	I2C_Start();                  //��ʼ�ź�
	
  I2C_SendByte(WC24C02);   //�����豸��ַ+д�ź�
	if(I2C_RecvACK() == 0)
	{
		return false;
	}
	
	I2C_SendByte(Wrire_Address);   //�����豸��ַ+д�ź�
	if(I2C_RecvACK() == 0)
	{
		return false;
	}
	
	for(i = 0;i < n;i++)
	{
		I2C_SendByte(Write_data[i]);   //��������
		if(I2C_RecvACK() == 0)
		{
			return false;
		}
	}
	
	I2C_Stop();                   //����ֹͣ�ź�
	return true;
}

/*-------------------------------------------------------------------------------------------------
	Function Name :	unsigned char Single_ReadI2C(unsigned char REG_Address)
	Description   :	��I2C�豸��ȡһ���ֽ�����
	Input         :	
  Output				:	
-------------------------------------------------------------------------------------------------*/
unsigned char Single_ReadI2C(unsigned char REG_Address)
{
	unsigned char REG_data;
	I2C_Start();                   //��ʼ�ź�
	
	I2C_SendByte(WC24C02);    //�����豸��ַ+д�ź�
	if(I2C_RecvACK() == 0)
	{
		return false;
	}
	
	I2C_SendByte(REG_Address);     //���ʹ洢��Ԫ��ַ����0��ʼ	
	if(I2C_RecvACK() == 0)
	{
		return false;
	}
	
	I2C_Start();                   //��ʼ�ź�
	
	I2C_SendByte(RC24C02);  //�����豸��ַ+���ź�
	if(I2C_RecvACK() == 0)
	{
		return false;
	}
	
	REG_data=I2C_RecvByte();       //�����Ĵ�������
	I2C_SendACK();                //����Ӧ���ź�
	
	I2C_Stop();                    //ֹͣ�ź�
	return REG_data;
}
bool I2C_BufferRead(unsigned char Read_Address,unsigned char *Read_data,unsigned char n) 
{
	unsigned char i;
	if(n > WC24C02_MAXSIZE)
		return 0;
	
	I2C_Start();                   //��ʼ�ź�

	I2C_SendByte(WC24C02);   //�����豸��ַ+д�ź�
	if(I2C_RecvACK() == 0)
	{
		return false;
	}
	
	I2C_SendByte(Read_Address);   //���ͼĴ�����ַ
	if(I2C_RecvACK() == 0)
	{
		return false;
	}

	I2C_Start();                   //��ʼ�ź�
	
	I2C_SendByte(RC24C02);   //�����豸��ַ+д�ź�
	if(I2C_RecvACK() == 0)
	{
		return false;
	}
	
	for(i = 0;i < (n - 1);i++)
	{
	  Read_data[i] = I2C_RecvByte(); //�����Ĵ�������
	  I2C_SendACK();                //����Ӧ���ź�
	}
	Read_data[n - 1] = I2C_RecvByte();
	I2C_SendNoACK();
	
	I2C_Stop();                    //ֹͣ�ź�
  return true;
}

