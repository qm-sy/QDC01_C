#ifndef __TOUCH_H
#define __TOUCH_H

#include "stc.h"   
#include "delay.h"
#include "tm1722.h"

#define	KEY_NOPRESS		0		
#define	KEY_FILCKER		1		//����
#define	KEY_PRESS		2		//����
#define	KEY_PRESSOVER	3		//��������
#define	KEY_LONGPRESS	4		//����3��
#define	KEY_LONGOVER	5		//��������
#define	KEY_RELAX		6		//�����ɿ�

#define KEY1            2
#define KEY2            1
#define KEY3            0
#define KEY4            3
#define KEY5            4
#define KEY6            5

extern u16	xdata TK_cnt[6];	// ������ֵ
extern u32	xdata TK_zero[6];	// 0�����? 
extern u16 T_KeyCmp[6] ;
extern bit	B_ReadKeyOk;	//��־��ת�����?16����
extern u16 Count[6] ;
extern u16 LastState ;						//8λ���� 	b0=1������k0��һ�ΰ��¹� 

typedef struct 
{
    uint8_t  key1_scan_allow;       
    uint8_t  key2_scan_allow;  
    uint8_t  key3_scan_allow;   
    uint8_t  key4_scan_allow;   
    uint8_t  key5_scan_allow;   
    uint8_t  key6_scan_allow;   
}KEY_VAL;

extern KEY_VAL key_val;

void KEY_T_Init(void);
void KEY_Deal(void)	;		//������еİ���״�? 10msִ��һ��
u8 KEY_ReadState(u8 keynum);	//��ȡָ���İ�����״̬ 10msִ��һ��

void key_scan( void );
void channel_choose( void );
void up_key( void );
void down_key( void );
void fan_up( void );
void fan_down( void );
void mode_choose( void );
void key_val_init( void );

#endif

