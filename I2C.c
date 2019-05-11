/*
	I2C.c
	��׼80C51��Ƭ��ģ��I2C���ߵ���������
	Copyright (c) 2005��������������Ƭ����չ���޹�˾
	All rights reserved.
	���������ѧϰ�ο������ṩ�κοɿ��Է���ĵ���������������ҵĿ��
*/
#include "Board.h"
#include "I2C.h"

//������ʱ���������ں�I2C_Delay()
unsigned char data I2C_Delay_t;

/*
�궨�壺I2C_Delay()
���ܣ���ʱ��ģ��I2C����ר��
*/
#define I2C_Delay()\
{\
	I2C_Delay_t = (I2C_DELAY_VALUE);\
	while ( --I2C_Delay_t != 0 );\
}

/*
������I2C_Init()
���ܣ�I2C���߳�ʼ����ʹ���ߴ��ڿ���״̬
˵������main()�����Ŀ�ʼ����ͨ��Ӧ��Ҫִ��һ�α�����
*/
void I2C_Init(uchar ch) //  0:zlg7290-1;
                          // 1:zlg7290-2;
                          // 2:PCF8563;
{
//	I2C_SCL = 1;
    switch(ch)
	{
		case 0:
			Z72901_SCL_PIN = 1;
			break;
		case 1:
			Z72902_SCL_PIN = 1;
			break;
		case 2:
			PCF8563_SCL_PIN = 1;
			break;
		default: break;
	}
	I2C_Delay();
//	I2C_SDA = 1;

    switch(ch)
	{
		case 0:
			Z72901_SDA_PIN = 1;
			break;
		case 1:
			Z72902_SDA_PIN = 1;
			break;
		case 2:
			PCF8563_SDA_PIN = 1;
			break;
		default: break;
	}
	I2C_Delay();
}

/*
������I2C_Start()
���ܣ�����I2C���ߵ���ʼ״̬
˵����
	SCL���ڸߵ�ƽ�ڼ䣬��SDA�����½���ʱ����I2C����
	����SDA��SCL����ʲô��ƽ״̬��������������ȷ������ʼ״̬
	������Ҳ�������������ظ���ʼ״̬
	������ִ�к�I2C���ߴ���æ״̬
*/
void I2C_Start(uchar ch)
{
//	I2C_SDA = 1;
    switch(ch)
	{
		case 0:
			Z72901_SDA_PIN = 1;
			break;
		case 1:
			Z72902_SDA_PIN = 1;
			break;
		case 2:
			PCF8563_SDA_PIN = 1;
			break;
		default: break;
	}

	I2C_Delay();
//	I2C_SCL = 1;
    switch(ch)
	{
		case 0:
			Z72901_SCL_PIN = 1;
			break;
		case 1:
			Z72902_SCL_PIN = 1;
			break;
		case 2:
			PCF8563_SCL_PIN = 1;
			break;
		default: break;
	}

	I2C_Delay();
//	I2C_SDA = 0;
    switch(ch)
	{
		case 0:
			Z72901_SDA_PIN = 0;
			break;
		case 1:
			Z72902_SDA_PIN = 0;
			break;
		case 2:
			PCF8563_SDA_PIN = 0;
			break;
		default: break;
	}
	
	I2C_Delay();
//	I2C_SCL = 0;
    switch(ch)
	{
		case 0:
			Z72901_SCL_PIN = 0;
			break;
		case 1:
			Z72902_SCL_PIN = 0;
			break;
		case 2:
			PCF8563_SCL_PIN = 0;
			break;
		default: break;
	}

	I2C_Delay();
}

/*
������I2C_Write()
���ܣ���I2C����д1���ֽڵ�����
������
	dat��Ҫд�������ϵ�����
*/
void I2C_Write(char dat, uchar ch)
{
	unsigned char t = 8;
	do
	{
//		I2C_SDA = (bit)(dat & 0x80);
	    switch(ch)
		{
			case 0:
				Z72901_SDA_PIN = (bit)(dat & 0x80);
				break;
			case 1:
				Z72902_SDA_PIN = (bit)(dat & 0x80);
				break;
			case 2:
				PCF8563_SDA_PIN = (bit)(dat & 0x80);
				break;
			default: break;
		}

		dat <<= 1;
//		I2C_SCL = 1;
	    switch(ch)
		{
			case 0:
				Z72901_SCL_PIN = 1;
				break;
			case 1:
				Z72902_SCL_PIN = 1;
				break;
			case 2:
				PCF8563_SCL_PIN = 1;
				break;
			default: break;
		}

		I2C_Delay();
//		I2C_SCL = 0;
	    switch(ch)
		{
			case 0:
				Z72901_SCL_PIN = 0;
				break;
			case 1:
				Z72902_SCL_PIN = 0;
				break;
			case 2:
				PCF8563_SCL_PIN = 0;
				break;
			default: break;
		}

		I2C_Delay();
	} while ( --t != 0 );
}

/*
������I2C_Read()
���ܣ��Ӵӻ���ȡ1���ֽڵ�����
���أ���ȡ��һ���ֽ�����
*/
char I2C_Read(uchar ch)
{
	char dat;
	unsigned char t = 8;
//	I2C_SDA = 1;	//�ڶ�ȡ����֮ǰ��Ҫ��SDA����
    switch(ch)
	{
		case 0:
			Z72901_SDA_PIN = 1;
			break;
		case 1:
			Z72902_SDA_PIN = 1;
			break;
		case 2:
			PCF8563_SDA_PIN = 1;
			break;
		default: break;
	}

	do
	{
//		I2C_SCL = 1;
	    switch(ch)
		{
			case 0:
				Z72901_SCL_PIN = 1;
				break;
			case 1:
				Z72902_SCL_PIN = 1;
				break;
			case 2:
				PCF8563_SCL_PIN = 1;
				break;
			default: break;
		}

		I2C_Delay();
		dat <<= 1;
//		if ( I2C_SDA ) dat |= 0x01;
	    switch(ch)
		{
			case 0:
				if ( Z72901_SDA_PIN ) dat |= 0x01;
				break;
			case 1:
				if ( Z72902_SDA_PIN ) dat |= 0x01;
				break;
			case 2:
				if ( PCF8563_SDA_PIN) dat |= 0x01;
				break;
			default: break;
		}

//		I2C_SCL = 0;
	    switch(ch)
		{
			case 0:
				Z72901_SCL_PIN = 0;
				break;
			case 1:
				Z72902_SCL_PIN = 0;
				break;
			case 2:
				PCF8563_SCL_PIN = 0;
				break;
			default: break;
		}

		I2C_Delay();
	} while ( --t != 0 );
	return dat;
}

/*
������I2C_GetAck()
���ܣ���ȡ�ӻ�Ӧ��λ
���أ�
	0���ӻ�Ӧ��
	1���ӻ���Ӧ��
˵����
	�ӻ����յ�ÿ���ֽڵ����ݺ�Ҫ����Ӧ��λ
	�ӻ����յ����1���ֽڵ����ݺ�һ��Ҫ������Ӧ��λ
*/
bit I2C_GetAck(uchar ch)
{
	bit ack;
//	I2C_SDA = 1;
    switch(ch)
	{
		case 0:
			Z72901_SDA_PIN = 1;
			break;
		case 1:
			Z72902_SDA_PIN = 1;
			break;
		case 2:
			PCF8563_SDA_PIN = 1;
			break;
		default: break;
	}

	I2C_Delay();
//	I2C_SCL = 1;
    switch(ch)
	{
		case 0:
			Z72901_SCL_PIN = 1;
			break;
		case 1:
			Z72902_SCL_PIN = 1;
			break;
		case 2:
			PCF8563_SCL_PIN = 1;
			break;
		default: break;
	}

	I2C_Delay();
//	ack = I2C_SDA;
    switch(ch)
	{
		case 0:
			ack = Z72901_SDA_PIN;
			break;
		case 1:
			ack = Z72902_SDA_PIN;
			break;
		case 2:
			ack = PCF8563_SDA_PIN;
			break;
		default: break;
	}

//	I2C_SCL = 0;
    switch(ch)
	{
		case 0:
			Z72901_SCL_PIN = 0;
			break;
		case 1:
			Z72902_SCL_PIN = 0;
			break;
		case 2:
			PCF8563_SCL_PIN = 0;
			break;
		default: break;
	}

	I2C_Delay();
	return ack;
}

/*
������I2C_PutAck()
���ܣ���������Ӧ��λ���Ӧ��λ
������
	ack=0����������Ӧ��λ
	ack=1������������Ӧ��λ
˵����
	�����ڽ�����ÿһ���ֽڵ����ݺ󣬶�Ӧ������Ӧ��λ
	�����ڽ��������һ���ֽڵ����ݺ�Ӧ��������Ӧ��λ
*/
void I2C_PutAck(bit ack, uchar ch)
{
//	I2C_SDA = ack;
    switch(ch)
	{
		case 0:
			Z72901_SDA_PIN = ack;
			break;
		case 1:
			Z72902_SDA_PIN = ack;
			break;
		case 2:
			PCF8563_SDA_PIN= ack;
			break;
		default: break;
	}
	I2C_Delay();
//	I2C_SCL = 1;
    switch(ch)
	{
		case 0:
			Z72901_SCL_PIN = 1;
			break;
		case 1:
			Z72902_SCL_PIN = 1;
			break;
		case 2:
			PCF8563_SCL_PIN = 1;
			break;
		default: break;
	}

	I2C_Delay();
//	I2C_SCL = 0;
    switch(ch)
	{
		case 0:
			Z72901_SCL_PIN = 0;
			break;
		case 1:
			Z72902_SCL_PIN = 0;
			break;
		case 2:
			PCF8563_SCL_PIN = 0;
			break;
		default: break;
	}

	I2C_Delay();
}

/*
������I2C_Stop()
���ܣ�����I2C���ߵ�ֹͣ״̬
˵����
	SCL���ڸߵ�ƽ�ڼ䣬��SDA����������ʱֹͣI2C����
	����SDA��SCL����ʲô��ƽ״̬��������������ȷ����ֹͣ״̬
	������ִ�к�I2C���ߴ��ڿ���״̬
*/
void I2C_Stop(uchar ch)
{
	unsigned int t = I2C_STOP_WAIT_VALUE;
//	I2C_SDA = 0;
    switch(ch)
	{
		case 0:
			Z72901_SDA_PIN = 0;
			break;
		case 1:
			Z72902_SDA_PIN = 0;
			break;
		case 2:
			PCF8563_SDA_PIN = 0;
			break;
		default: break;
	}

	I2C_Delay();
//	I2C_SCL = 1;
    switch(ch)
	{
		case 0:
			Z72901_SCL_PIN = 1;
			break;
		case 1:
			Z72902_SCL_PIN = 1;
			break;
		case 2:
			PCF8563_SCL_PIN = 1;
			break;
		default: break;
	}

	I2C_Delay();
//	I2C_SDA = 1;
    switch(ch)
	{
		case 0:
			Z72901_SDA_PIN = 1;
			break;
		case 1:
			Z72902_SDA_PIN = 1;
			break;
		case 2:
			PCF8563_SDA_PIN = 1;
			break;
		default: break;
	}

	I2C_Delay();
	while ( --t != 0 );		//����һ�β���Start֮ǰ��Ҫ��һ������ʱ
}

/*
������I2C_Puts()
���ܣ�I2C�����ۺϷ��ͺ�������ӻ����Ͷ���ֽڵ�����
������
	SlaveAddr���ӻ���ַ��7λ����ַ��������дλ��
	SubAddr���ӻ����ӵ�ַ
	SubMod���ӵ�ַģʽ��0�����ӵ�ַ��1�����ֽ��ӵ�ַ��2��˫�ֽ��ӵ�ַ
	*dat��Ҫ���͵�����
	Size�����ݵ��ֽ���
���أ�
	0�����ͳɹ�
	1���ڷ��͹����г����쳣
˵����
	�������ܹ��ܺõ���Ӧ���г�����I2C�������������Ƿ����ӵ�ַ
	���ӻ�û���ӵ�ַʱ������SubAddr���⣬��SubModӦ��Ϊ0
*/
bit I2C_Puts
(
	unsigned char SlaveAddr,
	unsigned int SubAddr,
	unsigned char SubMod,
	char *dat,
	unsigned int Size,
	uchar ch
)
{
//������ʱ����
	unsigned char i;
	char a[3];
//��鳤��
	if ( Size == 0 ) return 0;
//׼���ӻ���ַ
	a[0] = (SlaveAddr << 1);
//����ӵ�ַģʽ
	if ( SubMod > 2 ) SubMod = 2;
//ȷ���ӵ�ַ
	switch ( SubMod )
	{
	case 0:
		break;
	case 1:
		a[1] = (char)(SubAddr);
		break;
	case 2:
		a[1] = (char)(SubAddr >> 8);
		a[2] = (char)(SubAddr);
		break;
	default:
		break;
	}
//���ʹӻ���ַ�����ŷ����ӵ�ַ��������ӵ�ַ�Ļ���
	SubMod++;
	I2C_Start(ch);
	for ( i=0; i<SubMod; i++ )
	{
		I2C_Write(a[i],ch);
		if ( I2C_GetAck(ch) )
		{
			I2C_Stop(ch);
			return 1;
		}
	}
//��������
	do
	{
		I2C_Write(*dat++,ch);
		if ( I2C_GetAck(ch) ) break;
	} while ( --Size != 0 );
//������ϣ�ֹͣI2C���ߣ������ؽ��
	I2C_Stop(ch);
	if ( Size == 0 )
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

/*
������I2C_Gets()
���ܣ�I2C�����ۺϽ��պ������Ӵӻ����ն���ֽڵ�����
������
	SlaveAddr���ӻ���ַ��7λ����ַ��������дλ��
	SubAddr���ӻ����ӵ�ַ
	SubMod���ӵ�ַģʽ��0�����ӵ�ַ��1�����ֽ��ӵ�ַ��2��˫�ֽ��ӵ�ַ
	*dat��������յ�������
	Size�����ݵ��ֽ���
���أ�
	0�����ճɹ�
	1���ڽ��չ����г����쳣
˵����
	�������ܹ��ܺõ���Ӧ���г�����I2C�������������Ƿ����ӵ�ַ
	���ӻ�û���ӵ�ַʱ������SubAddr���⣬��SubModӦ��Ϊ0
*/
bit I2C_Gets
(
	unsigned char SlaveAddr,
	unsigned int SubAddr,
	unsigned char SubMod,
	char *dat,
	unsigned int Size,
	uchar ch

)
{
//������ʱ����
	unsigned char i;
	char a[3];
//��鳤��
	if ( Size == 0 ) return 0;
//׼���ӻ���ַ
	a[0] = (SlaveAddr << 1);
//����ӵ�ַģʽ
	if ( SubMod > 2 ) SubMod = 2;
//��������ӵ�ַ�Ĵӻ�����Ҫ�ȷ��ʹӻ���ַ���ӵ�ַ
	if ( SubMod != 0 )
	{
	//ȷ���ӵ�ַ
		if ( SubMod == 1 )
		{
			a[1] = (char)(SubAddr);
		}
		else
		{
			a[1] = (char)(SubAddr >> 8);
			a[2] = (char)(SubAddr);
		}
	//���ʹӻ���ַ�����ŷ����ӵ�ַ
		SubMod++;
		I2C_Start(ch);
		for ( i=0; i<SubMod; i++ )
		{
			I2C_Write(a[i],ch);
			if ( I2C_GetAck(ch) )
			{
				I2C_Stop(ch);
				return 1;
			}
		}
	}
//�����I2C_Start()�������ӵ�ַ�Ĵӻ����ظ���ʼ״̬
//�������ӵ�ַ�Ĵӻ�������������ʼ״̬
	I2C_Start(ch);
//���ʹӻ���ַ
	I2C_Write(a[0]+1,ch);
	if ( I2C_GetAck(ch) )
	{
		I2C_Stop(ch);
		return 1;
	}
//��������
	for (;;)
	{
		*dat++ = I2C_Read(ch);
		if ( --Size == 0 )
		{
			I2C_PutAck(1,ch);
			break;
		}
		I2C_PutAck(0,ch);
	}
//������ϣ�ֹͣI2C���ߣ������ؽ��
	I2C_Stop(ch);
	return 0;
}
