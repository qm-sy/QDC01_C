#include "stc.h"   //包含此头文件后，不需要再包含"reg51.h"头文件
#include "lcd.h"
#include "touch.h"
#include "delay.h"
#include "tm1722.h"
#include "uart.h"
#include "communication.h"
#include "tim.h"

u8	isr_index;

/******************** 主函数 **************************/
void main(void)
{
	u8 i=0;
	//uint16_t cnt = 0;
    P_SW2 |= 0x80;     //扩展寄存器(XFR)访问使能
    GPIO_Init();

	/*  调试使用 printf  */
	Uart1_Init();

	Timer3_Init();

	Uart4_Init();
	Uart4_Send_Statu_Init();    //接收发送初始化
    Timer0_Init();              //不定长数据接收

    EA = 1;     //打开总中断
	BL = 0;
	lcd_info_init();
	screen_init();
	while ( lcd_info.lcd_connect_flag == 0 )
	{
		get_slave_params_03();
		Modbus_Event();
		delay_ms(50);
	}

	screen_clear();
	screen_all_dis();

	KEY_T_Init(); 	
	key_val_init();
	printf("====== code start ====== \r\n");

    while(1)
    {
		Modbus_Event();
		key_scan();
		fan_rotate();
		get_slave_status();
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
