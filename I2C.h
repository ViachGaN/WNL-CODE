/*
	I2C.h
	��׼80C51��Ƭ��ģ��I2C���ߵ���������ͷ�ļ�
	Copyright (c) 2005��������������Ƭ����չ���޹�˾
	All rights reserved.
	���������ѧϰ�ο������ṩ�κοɿ��Է���ĵ���������������ҵĿ��
*/

#ifndef _I2C_H_
#define _I2C_H_

//#include <reg52.h>

//ģ��I2C���ߵ����Ŷ���
//sbit I2C_SCL = P2^0;
//sbit I2C_SDA = P1^7;

//����I2C����ʱ�ӵ���ʱֵ��Ҫ����ʵ������޸ģ�ȡֵ1��255
//SCL�ź�����ԼΪ(I2C_DELAY_VALUE*4+15)����������
#define I2C_DELAY_VALUE		60

//����I2C����ֹͣ������һ�ο�ʼ֮ǰ�ĵȴ�ʱ�䣬ȡֵ1��65535
//�ȴ�ʱ��ԼΪ(I2C_STOP_WAIT_VALUE*8)����������
//���ڶ�������ȡֵΪ1���ɣ�������ĳЩ������˵���ϳ�����ʱ�Ǳ����
#define I2C_STOP_WAIT_VALUE	600

//I2C���߳�ʼ����ʹ���ߴ��ڿ���״̬
void I2C_Init(uchar a);

//I2C�����ۺϷ��ͺ�������ӻ����Ͷ���ֽڵ�����
bit I2C_Puts
(
	unsigned char SlaveAddr,
	unsigned int SubAddr,
	unsigned char SubMod,
	char *dat,
	unsigned int Size,
	uchar
);

//I2C�����ۺϽ��պ������Ӵӻ����ն���ֽڵ�����
bit I2C_Gets
(
	unsigned char SlaveAddr,
	unsigned int SubAddr,
	unsigned char SubMod,
	char *dat,
	unsigned int Size,
	uchar
);

#endif	//_I2C_H_
