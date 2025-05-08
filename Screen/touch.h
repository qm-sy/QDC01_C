#ifndef __TOUCH_H
#define __TOUCH_H

#include "stc.h"   //包含此头文件后，不需要再包含"reg51.h"头文件
#include "delay.h"
#include "tm1722.h"

#define	KEY_NOPRESS		0		//按键未按下
#define	KEY_FILCKER		1		//消抖
#define	KEY_PRESS		2		//单击
#define	KEY_PRESSOVER	3		//单击结束
#define	KEY_LONGPRESS	4		//长按3秒
#define	KEY_LONGOVER	5		//长按结束
#define	KEY_RELAX		6		//按键松开

#define KEY1            2
#define KEY2            1
#define KEY3            0
#define KEY4            3
#define KEY5            4
#define KEY6            5

extern u16	xdata TK_cnt[6];	// 键计数值
extern u32	xdata TK_zero[6];	// 0点读数 
extern u16 T_KeyCmp[6] ;
extern bit	B_ReadKeyOk;	//标志已转换完成16个键
extern u16 Count[6] ;
extern u16 LastState ;						//8位变量 	b0=1，代表k0上一次按下过 

typedef struct 
{
    uint8_t  key1_scan_allow;       
    uint8_t  key2_scan_allow;  
    uint8_t  key3_scan_allow;   
    uint8_t  key4_scan_allow;   
    uint8_t  key5_scan_allow;   
    uint8_t  key6_scan_allow;   
    uint8_t  key_sacn_flag;
}KEY_VAL;

extern KEY_VAL key_val;

void KEY_T_Init(void);
void KEY_Deal(void)	;		//检查所有的按键状态 10ms执行一次
u8 KEY_ReadState(u8 keynum);	//读取指定的按键的状态 10ms执行一次

void key_scan( void );
void channel_choose( void );
void up_key( void );
void down_key( void );
void fan_up( void );
void fan_down( void );

#endif

