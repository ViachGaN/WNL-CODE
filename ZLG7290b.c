/*
	ZLG7290.c
	数码管显示与键盘管理芯片ZLG7290的标准80C51驱动程序C文件
	Copyright (c) 2005，广州周立功单片机发展有限公司
	All rights reserved.
	本程序仅供学习参考，不提供任何可靠性方面的担保；请勿用于商业目的
*/
#include "Board.h"

#include "I2C.h"
#include "ZLG7290b.h"
TDATETIME myDateTime={2018,6,25,8,27,40,1,5,12};
bit bZlg7290Flag = 0;
uchar uKeyValue = 0;
/*
函数：ZLG7290_WriteReg()
功能：向ZLG7290的某个内部寄存器写入数据
参数：
	RegAddr：ZLG7290的内部寄存器地址
	dat：要写入的数据
返回：
	0：正常
	1：访问ZLG7290时出现异常
*/
bit ZLG7290_WriteReg(unsigned char RegAddr, char dat,uchar ch)
{
	bit b;
	b = I2C_Puts(ZLG7290_I2C_ADDR,RegAddr,1,&dat,1,ch);
	return b;
}

/*
函数：ZLG7290_ReadReg()
功能：从ZLG7290的某个内部寄存器读出数据
参数：
	RegAddr：ZLG7290的内部寄存器地址
	*dat：保存读出的数据
返回：
	0：正常
	1：访问ZLG7290时出现异常
*/
bit ZLG7290_ReadReg(unsigned char RegAddr, char *dat,uchar ch)
{
	bit b;
	b = I2C_Gets(ZLG7290_I2C_ADDR,RegAddr,1,dat,1,ch);
	return b;
}

/*
函数：ZLG7290_cmd()
功能：向ZLG7290发送控制命令
参数：
	cmd0：写入CmdBuf0寄存器的命令字（第1字节）
	cmd1：写入CmdBuf1寄存器的命令字（第2字节）
返回：
	0：正常
	1：访问ZLG7290时出现异常
*/
bit ZLG7290_cmd(char cmd0, char cmd1,uchar ch)
{
	bit b;
	char buf[2];
	buf[0] = cmd0;
	buf[1] = cmd1;
	b = I2C_Puts(ZLG7290_I2C_ADDR,ZLG7290_CmdBuf,1,buf,2,ch);
	return b;
}

/*
函数：ZLG7290_SegOnOff()
功能：段寻址，单独点亮或熄灭数码管（或LED）中的某一段
参数：
	seg：取值0～63，表示数码管（或LED）的段号
	b：0表示熄灭，1表示点亮
返回：
	0：正常
	1：访问ZLG7290时出现异常
说明：
	在每一位数码管中，段号顺序按照“a,b,c,d,e,f,g,dp”进行
*/
bit ZLG7290_SegOnOff(char seg, bit b,uchar ch)
{
	char cmd;
	cmd = seg & 0x3F;
	if ( b ) cmd |= 0x80;
	return ZLG7290_cmd(0x01,cmd,ch);
}

/*
函数：ZLG7290_Download()
功能：下载数据并译码
参数：
	addr：取值0～7，显示缓存DpRam0～DpRam7的编号
	dp：是否点亮该位的小数点，0－熄灭，1－点亮
	flash：控制该位是否闪烁，0－不闪烁，1－闪烁
	dat：取值0～31，表示要显示的数据
返回：
	0：正常
	1：访问ZLG7290时出现异常
说明：
	显示数据具体的译码方式请参见ZLG7290的数据手册
*/
bit ZLG7290_Download(char addr, bit dp, bit flash, char dat,uchar ch)
{
	char cmd0;
	char cmd1;
	cmd0 = addr & 0x0F;
	cmd0 |= 0x60;
	cmd1 = dat & 0x1F;
	if ( dp ) cmd1 |= 0x80;
	ZLG7290_Flash(0x18,0);//0001 1000 //年闪烁
	if ( flash ) cmd1 |= 0x40;
	return ZLG7290_cmd(cmd0,cmd1,ch);
}
void SetFlashItem(uchar item)
{
	switch(item)
	{
		case 0://year flash
			ZLG7290_Flash(0x00,1);//0000 0100 //闪烁
			ZLG7290_Flash(0x18,0);//0001 1000 //年闪烁
			break;
		case 1://day flash
			ZLG7290_Flash(0x24,0);//0000 0011 //闪烁
			break;
		case 2://month flash
			ZLG7290_Flash(0x03,0);//0010 0100 //闪烁
			break;
		case 3://hour flash
			ZLG7290_Flash(0xc0,0);//0000 0000 //闪烁
			break;
		case 4://minute flash
			ZLG7290_Flash(0x00,0);//0000 0000 //闪烁
			ZLG7290_Flash(0x03,1);//0000 0011 //闪烁
			break;
		case 5://week flash
			ZLG7290_Flash(0x18,1);//0001 1000 //闪烁
			break;
		case 6://week flash
			ZLG7290_Flash(0x04,1);//0000 0100 //闪烁
			break;
		default: break;
	}
}

uchar GetMonthDays(uint year, uchar month)
{
	switch(month)
	{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			return 31;
		case 4:
		case 6:
		case 9:
		case 11:
			return 30;
		case 2:
			if(
					(((year % 4) == 0) && ((year % 100) != 0))
					|| ((year % 400) == 0)
			   )
			   return 29;
		   else
			   return 28;
			
	}
}
void EditDateTime(item)
{
    uchar yearHigh = myDateTime.m_year / 100;
    uchar yearLow = myDateTime.m_year % 100;
	uchar days = GetMonthDays(myDateTime.m_year, myDateTime.m_month);
	
	switch(item)
	{
		case 0://year flash
		    yearLow++;
			if(yearLow > 99) yearLow = 0;
			myDateTime.m_year = yearHigh * 100 + yearLow;
			break;
		case 1://day flash
			myDateTime.m_day++;
			if(myDateTime.m_day > days)
				myDateTime.m_day = 1;
			break;
		case 2://month flash
			myDateTime.m_month++;
			if(myDateTime.m_month > 12) myDateTime.m_month = 1;
			break;
		case 3://hour flash
			myDateTime.m_hour++;
			if(myDateTime.m_hour > 23) myDateTime.m_hour= 0;
			break;
		case 4://minute flash
			myDateTime.m_minute++;
			if(myDateTime.m_minute> 59) myDateTime.m_minute= 0;
			break;
			
case 5:
			myDateTime.m_second++;
			if(myDateTime.m_second>59)myDateTime.m_second=0;
			break;	
		case 6://week flash
			myDateTime.m_week++;
			if(myDateTime.m_week > 7) myDateTime.m_week = 1;
			break;
		default: break;
	}
}
void cutDateTime(item)
{
    uchar yearHigh = myDateTime.m_year / 100;
    uchar yearLow = myDateTime.m_year % 100;
	uchar days = GetMonthDays(myDateTime.m_year, myDateTime.m_month);
	
	switch(item)
	{
		case 0://year flash
		    yearLow--;
			if(yearLow <0) yearLow = 99;
			myDateTime.m_year = yearHigh * 100 + yearLow;
			break;
		case 1://day flash
			myDateTime.m_day--;
			if(myDateTime.m_day < 1)
				myDateTime.m_day = days;
			break;
		case 2://month flash
			myDateTime.m_month--;
			if(myDateTime.m_month < 1) myDateTime.m_month = 12;
			break;
		case 3://hour flash
			myDateTime.m_hour--;
			if(myDateTime.m_hour < 0) myDateTime.m_hour= 23;
			break;
		case 4://minute flash
			myDateTime.m_minute--;
			if(myDateTime.m_minute< 0) myDateTime.m_minute= 59;
			break;
			
		case 5:
			myDateTime.m_second--;
			if(myDateTime.m_second<0)myDateTime.m_second=59;
			break;	
		case 6://week flash
			myDateTime.m_week--;
			if(myDateTime.m_week < 1) myDateTime.m_week = 7;
			break;	
			


		default: break;
	}
}
void Zlg7290_Test()
{
//    Read_PCF8563();
	ZLG7290_Download(3, 0, 0, (myDateTime.m_year % 100) / 10 , 0);//year
	ZLG7290_Download(4, 0, 0, (myDateTime.m_year % 100) % 10 , 0);
	
	ZLG7290_Download(2, 0, 0,  myDateTime.m_day / 10, 0);//day
	ZLG7290_Download(5, 0, 0, myDateTime.m_day % 10, 0);
	
	ZLG7290_Download(1, 0, 0,  myDateTime.m_month / 10 , 0);//month
	ZLG7290_Download(0, 0, 0, myDateTime.m_month % 10, 0);



	ZLG7290_Download(6, 0, 0, myDateTime.m_hour / 10, 0);//hour 
	ZLG7290_Download(7, 0, 0, myDateTime.m_hour % 10, 0);

	
	ZLG7290_Download(0, 0, 0, myDateTime.m_minute / 10, 1);//minute
	ZLG7290_Download(1, 0, 0, myDateTime.m_minute % 10, 1);

	ZLG7290_Download(3, 0, 0, myDateTime.m_second/ 10, 1);// 11
	ZLG7290_Download(4, 0, 0, myDateTime.m_second% 10, 1);

	ZLG7290_Download(5, 0, 0, myDateTime.m_lday / 10, 1);
	ZLG7290_Download(6, 0, 0, myDateTime.m_lday % 10, 1);

	ZLG7290_Download(2, 0, 0, myDateTime.m_week, 1);
//	ZLG7290_Download(7, 0, 0, 9, 1);
}

void SetDataTime()
{
    uchar item = 0;
	ZLG7290_Flash(0x18,0);//0001 1000 //年闪烁
	while(1)
	{
		if(1 == bZlg7290Flag)//有按键被按下
		{
		    bZlg7290Flag = 0;
			I2C_Gets(ZLG7290_I2C_ADDR, ZLG7290_Key, 1, &uKeyValue, 1, 0);
			switch(uKeyValue)
			{
				case 4://按下"设置"键
					uKeyValue = 0;
				       item++;
					if(item > 6) item = 0;					
	                             SetFlashItem(item);	
					break;
				case 3://按下"修改"键
					uKeyValue = 0;
				       EditDateTime(item);
					Zlg7290_Test();
  	                            SetFlashItem(item);	
  					break;
				case 2://按下"定闹"键
					uKeyValue=0;
					cutDateTime(item);
					Zlg7290_Test();
					SetFlashItem(item);
					break;
				case 1://按下"退出"键
					ZLG7290_Flash(0x00,0);//0001 1000 //取消闪烁
					ZLG7290_Flash(0x00,1);//0001 1000 //取消闪烁

				        return;
				 default: break;
			}
		}
	}
}
