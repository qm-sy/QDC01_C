#include "stc.h"   //包含此头文件后，不需要再包含"reg51.h"头文件
#include "lcd.h"
#include "touch.h"
#include "delay.h"
#include "tm1722.h"
#include "uart.h"
#include "communication.h"

u8	isr_index;

/******************** 主函数 **************************/
void main(void)
{
	u8 i=0;
	
    P_SW2 |= 0x80;     //扩展寄存器(XFR)访问使能
    LED_R = 0;LED_G = 0; LED_B =0; 
	P0M1 = 0x00;   P0M0 = 0x07;   //设置为准双向口
	P1M1 = 0x00;   P1M0 = 0x30;   //设置为准双向口
	P2M1 = 0x00;   P2M0 = 0x10;   //设置为准双向口
	P3M0 = 0X82;    P3M1 = 0X00; 
	P4M1 = 0x00;   P4M0 = 0x01;   //设置为准双向口
	P5M1 = 0x00;   P5M0 = 0x00;   //设置为准双向口
	P6M1 = 0x00;   P6M0 = 0x00;   //设置为准双向口
	P7M1 = 0x00;   P7M0 = 0x00;   //设置为准双向口

	/*  调试使用 printf  */
	Uart1_Init();

    EA = 1;     //打开总中断



	BL = 0;
	screen_init();
	screen_all_dis();
	KEY_T_Init(); 	
	//LoadToLcd();	
	
	printf("====== code start ====== \r\n");

    while(1)
    {
		KEY_Deal();	
//		
		if( KEY_ReadState(1)==KEY_PRESS )
		{
			P24 = 0;
			printf("111 \r\n");
		}		
			
		
		if( KEY_ReadState(2)==KEY_PRESS )		//模式设置按钮
		{
			P24 = 0;
			printf("222 \r\n");
		}		
			
		if( KEY_ReadState(3)==KEY_PRESS )		//模式设置按钮
		{
			P24 = 0;
			printf("333 \r\n");
		}		
			
        if( KEY_ReadState(4)==KEY_PRESS )		//模式设置按钮
		{
			P24 = 0;
			printf("444 \r\n");
		}		
			
		if( KEY_ReadState(5)==KEY_PRESS )		//模式设置按钮
		{
			P24 = 0;
			printf("555 \r\n");
		}		
			
		if( KEY_ReadState(6)==KEY_PRESS )		//模式设置按钮
		{
			P24 = 0;
			printf("666 \r\n");
		}		
			
		if( KEY_ReadState(7)==KEY_PRESS )		//模式设置按钮
		{
			P24 = 0;
			printf("777 \r\n");
		}		
					

		delay_ms(10);
	
	}


}


//========================================================================
// 函数: void TKSU_Interrupt(void)
// 描述: 触摸按键中断。
// 参数: none.
// 返回: none.
// 版本: VER1.0
// 日期: 2021-02-01
// 备注: 
//========================================================================
void TKSU_Interrupt(void) interrupt 13
{
	u8	j;
	j = TSSTA2;
	if(j & 0x40)	//数据溢出, 错误处理(略)
	{
		TSSTA2 |= 0x40;	//写1清零
	}
	if(j & 0x80)	//扫描完成
	{
		j &= 0x0f;
		TSSTA2 |= 0x80;	//写1清零
		TK_cnt[j] = TSDAT;	//保存某个通道的读数
		if( j==5 )
			B_ReadKeyOk=1;
	}
    
//    if( intf )
//    {
//        P0INTF=0;
//    }    
}
