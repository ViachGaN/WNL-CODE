/*
	ZLG7290.h
	数码管显示与键盘管理芯片ZLG7290的标准80C51驱动程序头文件
	Copyright (c) 2005，广州周立功单片机发展有限公司
	All rights reserved.
	本程序仅供学习参考，不提供任何可靠性方面的担保；请勿用于商业目的
*/


#ifndef _ZLG7290_H_
#define _ZLG7290_H_

//#include <reg52.h>

//ZLG7290中断请求信号的引脚定义
//sbit ZLG7290_pinINT = P3^3;

//定义ZLG7290在I2C总线协议中的从机地址
//这是7位纯地址，不含读写位
#define ZLG7290_I2C_ADDR	0x38

//定义ZLG7290内部寄存器地址（子地址）
#define ZLG7290_SystemReg		0x00		//系统寄存器
#define ZLG7290_Key			0x01		//键值寄存器
#define ZLG7290_RepeatCnt		0x02		//连击次数寄存器
#define ZLG7290_FunctionKey		0x03		//功能键寄存器
#define ZLG7290_CmdBuf			0x07		//命令缓冲区起始地址
#define ZLG7290_CmdBuf0			0x07		//命令缓冲区0
#define ZLG7290_CmdBuf1			0x08		//命令缓冲区1
#define ZLG7290_FlashOnOff		0x0C		//闪烁控制寄存器
#define ZLG7290_ScanNum			0x0D		//扫描位数寄存器
#define ZLG7290_DpRam			0x10		//显示缓存起始地址
#define ZLG7290_DpRam0			0x10		//显示缓存0
#define ZLG7290_DpRam1			0x11		//显示缓存1
#define ZLG7290_DpRam2			0x12		//显示缓存2
#define ZLG7290_DpRam3			0x13		//显示缓存3
#define ZLG7290_DpRam4			0x14		//显示缓存4
#define ZLG7290_DpRam5			0x15		//显示缓存5
#define ZLG7290_DpRam6			0x16		//显示缓存6
#define ZLG7290_DpRam7			0x17		//显示缓存7
extern TDATETIME myDateTime;
//向ZLG7290的某个内部寄存器写入数据
bit ZLG7290_WriteReg(unsigned char RegAddr, char dat,uchar ch);

//从ZLG7290的某个内部寄存器读出数据
bit ZLG7290_ReadReg(unsigned char RegAddr, char *dat,uchar ch);

//向ZLG7290发送控制命令
bit ZLG7290_cmd(char cmd0, char cmd1,uchar ch);

//段寻址，单独点亮或熄灭数码管（或LED）中的某一段
bit ZLG7290_SegOnOff(char seg, bit b,uchar ch);

//下载数据并译码
bit ZLG7290_Download(char addr, bit dp, bit flash, char dat,uchar ch);

//闪烁控制指令（Fn应当是字节型）
//Fn的8个位分别控制数码管的8个位是否闪烁，0－不闪烁，1－闪烁
#define ZLG7290_Flash(Fn,ch) 	ZLG7290_cmd(0x70,(Fn),ch)
extern bit bZlg7290Flag;
extern uchar uKeyValue;
extern void SetDataTime();
#endif  //_ZLG7290_H_
