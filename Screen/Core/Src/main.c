#include "main.h"

/******************** ������ **************************/
void main(void)
{
    P_SW2 |= 0x80;     //��չ�Ĵ���(XFR)����ʹ��
    GPIO_Init();

	/*  ����ʹ�� printf  */
	Uart1_Init();

	Timer3_Init();

	/*  485ͨѶ  */
	Uart4_Init();
	Uart4_Send_Statu_Init();    //���շ��ͳ�ʼ��
    Timer0_Init();              //���������ݽ���

    EA = 1;     //�����ж�
	key.key_read_allow = 1;
	modbus.modbus_04_rcv_over = 1;
	led_status(LED_SLEEP);
	lcd_info_init();

	delay_ms(200);

	while(lcd_info.power_on == 0)
	{
		key_scan();
		delay_ms(10);
	}
	screen_init();

	while ( lcd_info.lcd_connect_flag == 0 ) 
	{
		get_slave_params_03();
		Modbus_Event();
		delay_ms(50);
	}

	screen_clear();
	screen_all_dis();

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

