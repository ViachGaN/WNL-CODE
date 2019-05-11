#include "STC12C5620AD.H"
#define uchar unsigned char
#define uint unsigned int
typedef struct 
{
	int m_year;
	char m_month;
	char m_day;
	char m_hour;
	char m_minute;
	char m_second;
	char m_week;
	char m_lmonth;//ũ����
	char m_lday;//ũ����
} TDATETIME;
#define FOSC 11059200L
sbit ZHD_LED          = P1^4;//���㱨ʱָʾ�ƿ�������
sbit DN_LED           = P3^5;//����ָʾ�ƿ�������
sbit BEEP_PIN         = P1^1;
#include "INTRINS.H"
sbit Z72901_SCL_PIN        = P2^0;
sbit Z72901_SDA_PIN        = P1^7;

sbit Z72902_SCL_PIN        = P2^7;
sbit Z72902_SDA_PIN        = P3^7;

sbit ZSCL2_PIN        = P2^7;
sbit ZSDA2_PIN        = P3^7;

sbit PCF8563_SCL_PIN  = P0^0;
sbit PCF8563_SDA_PIN  = P0^1;
//ģ��I2C���ߵ����Ŷ���
//sbit I2C_SCL = P2^0;
//sbit I2C_SDA = P1^7;
sbit I2C_SCL = P2^7;
sbit I2C_SDA = P3^7;
//ZLG7290�ж������źŵ����Ŷ���
sbit ZLG7290_pinINT = P3^3;


