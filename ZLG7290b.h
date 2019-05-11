/*
	ZLG7290.h
	�������ʾ����̹���оƬZLG7290�ı�׼80C51��������ͷ�ļ�
	Copyright (c) 2005��������������Ƭ����չ���޹�˾
	All rights reserved.
	���������ѧϰ�ο������ṩ�κοɿ��Է���ĵ���������������ҵĿ��
*/


#ifndef _ZLG7290_H_
#define _ZLG7290_H_

//#include <reg52.h>

//ZLG7290�ж������źŵ����Ŷ���
//sbit ZLG7290_pinINT = P3^3;

//����ZLG7290��I2C����Э���еĴӻ���ַ
//����7λ����ַ��������дλ
#define ZLG7290_I2C_ADDR	0x38

//����ZLG7290�ڲ��Ĵ�����ַ���ӵ�ַ��
#define ZLG7290_SystemReg		0x00		//ϵͳ�Ĵ���
#define ZLG7290_Key			0x01		//��ֵ�Ĵ���
#define ZLG7290_RepeatCnt		0x02		//���������Ĵ���
#define ZLG7290_FunctionKey		0x03		//���ܼ��Ĵ���
#define ZLG7290_CmdBuf			0x07		//���������ʼ��ַ
#define ZLG7290_CmdBuf0			0x07		//�������0
#define ZLG7290_CmdBuf1			0x08		//�������1
#define ZLG7290_FlashOnOff		0x0C		//��˸���ƼĴ���
#define ZLG7290_ScanNum			0x0D		//ɨ��λ���Ĵ���
#define ZLG7290_DpRam			0x10		//��ʾ������ʼ��ַ
#define ZLG7290_DpRam0			0x10		//��ʾ����0
#define ZLG7290_DpRam1			0x11		//��ʾ����1
#define ZLG7290_DpRam2			0x12		//��ʾ����2
#define ZLG7290_DpRam3			0x13		//��ʾ����3
#define ZLG7290_DpRam4			0x14		//��ʾ����4
#define ZLG7290_DpRam5			0x15		//��ʾ����5
#define ZLG7290_DpRam6			0x16		//��ʾ����6
#define ZLG7290_DpRam7			0x17		//��ʾ����7
extern TDATETIME myDateTime;
//��ZLG7290��ĳ���ڲ��Ĵ���д������
bit ZLG7290_WriteReg(unsigned char RegAddr, char dat,uchar ch);

//��ZLG7290��ĳ���ڲ��Ĵ�����������
bit ZLG7290_ReadReg(unsigned char RegAddr, char *dat,uchar ch);

//��ZLG7290���Ϳ�������
bit ZLG7290_cmd(char cmd0, char cmd1,uchar ch);

//��Ѱַ������������Ϩ������ܣ���LED���е�ĳһ��
bit ZLG7290_SegOnOff(char seg, bit b,uchar ch);

//�������ݲ�����
bit ZLG7290_Download(char addr, bit dp, bit flash, char dat,uchar ch);

//��˸����ָ�FnӦ�����ֽ��ͣ�
//Fn��8��λ�ֱ��������ܵ�8��λ�Ƿ���˸��0������˸��1����˸
#define ZLG7290_Flash(Fn,ch) 	ZLG7290_cmd(0x70,(Fn),ch)
extern bit bZlg7290Flag;
extern uchar uKeyValue;
extern void SetDataTime();
#endif  //_ZLG7290_H_
