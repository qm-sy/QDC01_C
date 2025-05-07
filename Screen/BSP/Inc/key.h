#ifndef __KEY_H_
#define __KEY_H_

#include "sys.h"
#include "delay.h"
#include "stdio.h"

#define	KEY_NOPRESS		0		//按键未按下
#define	KEY_FILCKER		1		//消抖
#define	KEY_PRESS		2		//单击
#define	KEY_PRESSOVER	3		//单击结束
#define	KEY_LONGPRESS	4		//长按3秒
#define	KEY_LONGOVER	5		//长按结束
#define	KEY_RELAX		6		//按键松开

extern uint16_t	xdata TK_cnt[16];	// 键计数值
extern uint32_t	xdata TK_zero[16];	// 0点读数 
extern uint16_t T_KeyCmp[16] ;
extern bit	B_ReadKeyOk;	//标志已转换完成16个键
extern uint16_t Count[16] ;
extern uint16_t LastState ;						//8位变量 	b0=1，代表k0上一次按下过 

void KEY_T_Init(void);
void KEY_Deal(void)	;		//检查所有的按键状态 10ms执行一次
uint8_t KEY_ReadState(uint8_t keynum);	//读取指定的按键的状态 10ms执行一次

#endif