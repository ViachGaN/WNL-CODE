

#ifndef _PCF8563_H_
#define _PCF8563_H_

//#include <reg52.h>

//ZLG7290�ж������źŵ����Ŷ���
//sbit ZLG7290_pinINT = P3^2;

//����ZLG7290��I2C����Э���еĴӻ���ַ
//����7λ����ַ��������дλ
#define PCF8563_I2C_ADDR	0x51
//����PCF8563�ڲ��Ĵ�����ַ���ӵ�ַ��
#define PCF8563_CONTROL1		0x00		/*����/״̬�Ĵ���1*/
#define PCF8563_CONTROL2		0x01		/*����/״̬�Ĵ���2*/
#define PCF8563_SECOND		    0x02		/*��Ĵ���*/
#define PCF8563_MINUTE		    0x03		/*�ּĴ���*/
#define PCF8563_HOUR		    0x04		/*ʱ�Ĵ���*/
#define PCF8563_DAY		        0x05		/*�ռĴ���*/
#define PCF8563_WEEK		    0x06		/*���ڼĴ���*/
#define PCF8563_MONTH		    0x07		/*�¼Ĵ���*/
#define PCF8563_YEAR		    0x08		/*��Ĵ���*/
#define PCF8563_ALARM_MINUTE    0x09		/*���ӱ����Ĵ���*/
#define PCF8563_ALARM_HOUR      0x0A		/*Сʱ�����Ĵ���*/
#define PCF8563_ALARM_DAY       0x0B		/*�ձ����Ĵ���*/
#define PCF8563_ALARM_WEEK	    0x0C		/*���ڱ����Ĵ���*/
#define PCF8563_CLKOUT          0x0D		/*ʱ������Ĵ���*/
#define PCF8563_TIMER_CONTROL   0x0E		/*��ʱ�����ƼĴ���*/
#define PCF8563_TIMER_COUNTER   0x0F		/*��ʱ��������ֵ�Ĵ���*/
extern void PCF8563_Init();
extern void Read_PCF8563();
extern void WritePCF8563();
extern bit bPCF8563Flag;
extern bit bAlarmFlag;//�Ƿ������˱���
extern uchar ucAlarmValue[2];
extern void Read_PCF8563_Alarm();
extern void Write_PCF8563_Alarm();
extern void Cancel_PCF8563_Alarm();
#endif  //_ZLG7290_H_

