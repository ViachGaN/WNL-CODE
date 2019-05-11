#include "Board.h"
#include "PCF8563.H"
#include "I2C.H"
#include "ZLG7290b.h"
#include "convert.h"
bit bPCF8563Flag = 0;
bit bAlarmFlag;//是否设置了报警
uchar ucAlarmValue[2];

void PCF8563_Init()
{
    char buff[] = 
    	{
    	    0x00,//控制状态寄存器1
    	    0x03,//控制状态寄存器2     0000 0111 
    	         //控制状态寄存器2 & 1111 1011
    	         //控制状态寄存器2   0000 0011 
    	    0x00,//秒:00
    	    0x30,
    	    0x08,
    	    0x25,
    	    0x01,
    	    0x05,//月
    	    0x18,//年
    	    0x00,//分报警:30  
    	    0x00,//时报警:6
    	    0x00,//日报警无效
    	    0x00,//星期报警无效
    	    0x83,//CLOCKOUT输出1Hz方波
    	    0x82,//定时器控制寄存器,设置时钟频率为1Hz 1000 0010
    	    1	    
    	};
//	I2C_Puts(PCF8563_I2C_ADDR, PCF8563_CONTROL1, 1, buff, 16, 2);
	I2C_Puts(PCF8563_I2C_ADDR, PCF8563_CONTROL1, 1, buff, 2, 2);
	I2C_Puts(PCF8563_I2C_ADDR, PCF8563_ALARM_MINUTE, 1, &buff[9], 7, 2);

	
}

void Read_PCF8563()
{
    char buff[7];
	
    I2C_Gets(PCF8563_I2C_ADDR, PCF8563_SECOND, 1, buff, 7, 2);
    myDateTime.m_second = ((buff[0] & 0x7F) / 16) * 10 + ((buff[0] & 0x7F) % 16);
	
    myDateTime.m_minute = ((buff[1] & 0x7F) / 16) * 10 + ((buff[1] & 0x7F) % 16);
    myDateTime.m_hour = ((buff[2] & 0x3F) / 16) * 10 + ((buff[2] & 0x3F) % 16);
    myDateTime.m_day = ((buff[3] & 0x3F) / 16) * 10 + ((buff[3] & 0x3F) % 16);
    myDateTime.m_week = buff[4] & 0x07;//0-6
    
/*    if(myDateTime.m_week == 0)
	{
	    myDateTime.m_week = 8;
	}*/
	
    myDateTime.m_month = ((buff[5] & 0x1F) / 16) * 10 + ((buff[5] & 0x1F) % 16);

	myDateTime.m_year = ((uchar)buff[6] / 16) * 10 + ((uchar)buff[6] % 16);

	if(buff[5] & 0x80)
	{
	   myDateTime.m_year += 1900;// 0
	}
	else
	{
	   myDateTime.m_year += 2000;
	}

	Conversion(0, buff[6], buff[5] & 0x1F, buff[3] & 0x3F);
    myDateTime.m_lmonth = (month_moon / 16) * 10 +  (month_moon % 16);
	myDateTime.m_lday = (day_moon / 16) * 10  + (day_moon % 16);
}

void WritePCF8563()
{
    uchar buff[7];

	buff[0] = (myDateTime.m_second/ 10) * 16 + (myDateTime.m_second% 10);
	buff[0] &= 0x7F;
	
	buff[1] = (myDateTime.m_minute / 10) * 16 + (myDateTime.m_minute % 10);
	buff[1] &= 0x7F;
	
	buff[2] = (myDateTime.m_hour / 10) * 16 + (myDateTime.m_hour % 10);
	buff[2] &= 0x3F;	
	
	buff[3] = (myDateTime.m_day / 10) * 16 + (myDateTime.m_day % 10);
	buff[3] &= 0x3F;	
	
	buff[4] = myDateTime.m_week;	
	buff[5] = (myDateTime.m_month / 10) * 16 + (myDateTime.m_month % 10);
	if((myDateTime.m_year / 100) == 19)
	{
	    buff[5] |= 0x80;
	}
	else
	{
	    buff[5] &= 0x7F;	
	}
	
	buff[6] = ((myDateTime.m_year % 100) / 10) * 16 + ((myDateTime.m_year % 100) % 10);

	I2C_Puts(PCF8563_I2C_ADDR, PCF8563_SECOND, 1, buff, 7, 2);
	Conversion((bit)(buff[5] & 0x80), buff[6], buff[5] & 0x1F, buff[3] & 0x3F);
    myDateTime.m_lmonth = (month_moon / 16) * 10 +  (month_moon % 16);
	myDateTime.m_lday = (day_moon / 16) * 10  + (day_moon % 16);
	
}

void Read_PCF8563_Alarm()
{
    char buff[2];
	
    I2C_Gets(PCF8563_I2C_ADDR, PCF8563_ALARM_MINUTE, 1, buff, 2, 2);

	if(((buff[0] & 0x80) == 0) && ((buff[1] & 0x80) == 0))//设置了报警
	{
	    bAlarmFlag = 1;
	}
	else//没有设置报警
	{
	    bAlarmFlag = 0;	
	}

	ucAlarmValue[0] = ((buff[0] & 0x7F) / 16) * 10 + ((buff[0] & 0x7F) % 16);
    ucAlarmValue[1]= ((buff[1] & 0x3F) / 16) * 10 + ((buff[1] & 0x3F) % 16);
}
void Write_PCF8563_Alarm()
{
    uchar buff[2];

	buff[0] = (ucAlarmValue[0] / 10) * 16 + (ucAlarmValue[0] % 10);
	buff[0] &= 0x7F;
	buff[1] = (ucAlarmValue[1] / 10) * 16 + (ucAlarmValue[1] % 10);
	buff[1] &= 0x3F;	
	I2C_Puts(PCF8563_I2C_ADDR, PCF8563_ALARM_MINUTE, 1, buff, 2, 2);
}

void Cancel_PCF8563_Alarm()
{
    uchar buff[2];

	buff[0] = (ucAlarmValue[0] / 10) * 16 + (ucAlarmValue[0] % 10);
	buff[0] |= 0x80;
	buff[1] = (ucAlarmValue[1] / 10) * 16 + (ucAlarmValue[1] % 10);
	buff[1] &= 0x3F;
	buff[1] |= 0x80;	
	I2C_Puts(PCF8563_I2C_ADDR, PCF8563_ALARM_MINUTE, 1, buff, 2, 2);
}

