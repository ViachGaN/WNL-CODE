

#ifndef _PCF8563_H_
#define _PCF8563_H_

//#include <reg52.h>

//ZLG7290中断请求信号的引脚定义
//sbit ZLG7290_pinINT = P3^2;

//定义ZLG7290在I2C总线协议中的从机地址
//这是7位纯地址，不含读写位
#define PCF8563_I2C_ADDR	0x51
//定义PCF8563内部寄存器地址（子地址）
#define PCF8563_CONTROL1		0x00		/*控制/状态寄存器1*/
#define PCF8563_CONTROL2		0x01		/*控制/状态寄存器2*/
#define PCF8563_SECOND		    0x02		/*秒寄存器*/
#define PCF8563_MINUTE		    0x03		/*分寄存器*/
#define PCF8563_HOUR		    0x04		/*时寄存器*/
#define PCF8563_DAY		        0x05		/*日寄存器*/
#define PCF8563_WEEK		    0x06		/*星期寄存器*/
#define PCF8563_MONTH		    0x07		/*月寄存器*/
#define PCF8563_YEAR		    0x08		/*年寄存器*/
#define PCF8563_ALARM_MINUTE    0x09		/*分钟报警寄存器*/
#define PCF8563_ALARM_HOUR      0x0A		/*小时报警寄存器*/
#define PCF8563_ALARM_DAY       0x0B		/*日报警寄存器*/
#define PCF8563_ALARM_WEEK	    0x0C		/*星期报警寄存器*/
#define PCF8563_CLKOUT          0x0D		/*时钟输出寄存器*/
#define PCF8563_TIMER_CONTROL   0x0E		/*定时器控制寄存器*/
#define PCF8563_TIMER_COUNTER   0x0F		/*定时器倒计数值寄存器*/
extern void PCF8563_Init();
extern void Read_PCF8563();
extern void WritePCF8563();
extern bit bPCF8563Flag;
extern bit bAlarmFlag;//是否设置了报警
extern uchar ucAlarmValue[2];
extern void Read_PCF8563_Alarm();
extern void Write_PCF8563_Alarm();
extern void Cancel_PCF8563_Alarm();
#endif  //_ZLG7290_H_

