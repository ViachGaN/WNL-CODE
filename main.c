//#include "STC12C5620AD.H"
#include "Board.H"
#include "ZLG7290b.H"
#include "I2c.H"
#include "pcf8563.H"

void IO_Init();
void T0_Init();//函数声明
void Zlg7290_Test();
void System_Init();

void main()
{
    char value;
    IO_Init();
	System_Init();
//	T0_Init();
	I2C_Init(0);
	I2C_Init(1);
	I2C_Init(2);
	PCF8563_Init();
	Zlg7290_Test();
	ZLG7290_Flash(0x00,0);//0001 1000 //取消闪烁
	ZLG7290_Flash(0x00,1);//0001 1000 //取消闪烁
	

	while(1)
	{
		if(1 == bPCF8563Flag)// 1 minute 
		{
			Read_PCF8563();
			Zlg7290_Test();
			I2C_Gets(PCF8563_I2C_ADDR, PCF8563_CONTROL2, 1, &value, 1, 2);
			value &= 0xFB;
			I2C_Puts(PCF8563_I2C_ADDR, PCF8563_CONTROL2, 1, &value, 1, 2);
			bPCF8563Flag = 0;
		}

		if(1 == bZlg7290Flag)//有按键被按下
		{   
		    bZlg7290Flag = 0;
			I2C_Gets(ZLG7290_I2C_ADDR, ZLG7290_Key, 1, &uKeyValue, 1, 0);
			switch(uKeyValue)
			{
				case 4://按下"设置"键
				    uKeyValue = 0;
                    SetDataTime();				
					break;
				case 3://按下"修改"键
					break;
				case 2://按下"定闹"键
					break;
				case 1://按下"退出"键
					break;
				default: break;
			}
			
		}
	}
}

void IO_Init()
{

	P0M0 = 0x03;//0000 0011
	P0M1 = 0x03;//0000 0011

	P1M0 = 0x80;//1000 0000
	P1M1 = 0x82;//1000 0010
	
	P2M0 = 0x81;//1000 0001
	P2M1 = 0x81;//1000 0001

	P3M0 = 0x80;//1000 0000
	P3M1 = 0x80;//1000 0000
}

void System_Init()
{
	IT0 = 1;
	EX0 = 1;
	IT1 = 1;
	EX1 = 1;
	EA = 1;
}

void T0_Init()
{
    TMOD |= 0x01;
	TH0 = (int)(65536 - 0.05 * FOSC / 12) / 256;//设置50ms
	TL0 = (int)(65536 - 0.05 * FOSC / 12) % 256;
	ET0 = 1;
//	EA = 1;
}


void T0_ISR() interrupt 1
{
    static uint count = 0;
	
	TH0 = (int)(65536 - 0.05 * FOSC / 12) / 256;//设置50ms
	TL0 = (int)(65536 - 0.05 * FOSC / 12) % 256;
    count++;
	if(count >= 10)
	{
	    ZHD_LED = ~ZHD_LED;
		count = 0;
	}
}

void INT0_ISR(void) interrupt 0
{
	bPCF8563Flag = 1;
}

void INT1_ISR(void) interrupt 2
{
	bZlg7290Flag = 1;
}

