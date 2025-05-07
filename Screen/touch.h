#ifndef __TOUCH_H
#define __TOUCH_H

#include "stc.h"   //包含此头文件后，不需要再包含"reg51.h"头文件
#include "delay.h"

#define	KEY_NOPRESS		0		//按键未按下
#define	KEY_FILCKER		1		//消抖
#define	KEY_PRESS		2		//单击
#define	KEY_PRESSOVER	3		//单击结束
#define	KEY_LONGPRESS	4		//长按3秒
#define	KEY_LONGOVER	5		//长按结束
#define	KEY_RELAX		6		//按键松开


extern u16	xdata TK_cnt[16];	// 键计数值
extern u32	xdata TK_zero[16];	// 0点读数 
extern u16 T_KeyCmp[16] ;
extern bit	B_ReadKeyOk;	//标志已转换完成16个键
extern u16 Count[16] ;
extern u16 LastState ;						//8位变量 	b0=1，代表k0上一次按下过 


void KEY_T_Init(void);
void KEY_Deal(void)	;		//检查所有的按键状态 10ms执行一次
u8 KEY_ReadState(u8 keynum);	//读取指定的按键的状态 10ms执行一次


#endif

