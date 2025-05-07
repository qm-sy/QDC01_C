#include "main.h"

void main( void )
{
    P_SW2 |= 0x80;
    
    GPIO_Init();
    
    /*  调试使用 printf  */
    Uart1_Init();
    /*  485控制  */
    Uart4_Init();               //串口4用作485
    Uart4_Send_Statu_Init();    //接收发送初始化
    Timer0_Init();              //不定长数据接收

    /*  定时事件  */
    Timer3_Init();
    led_status(LED_OPEN);

    screen_init();
    KEY_T_Init();//触摸功能初始化
    EA = 1;

    led_status(LED_OPEN);

    screen_init();

    num_dis(100);
    wind_dis(5);
    channel_dis(3);
    sun_dis(DIS_ON);
    sync_dis(DIS_ON);
    alarm_dis(DIS_ON);
    Celsius_dis(DIS_ON);
    mode_dis(DIS_ON);
    percentage_dis(DIS_ON);
    fan_center_dis(DIS_ON);
    fan_leaf1_dis(DIS_ON);
    fan_leaf2_dis(DIS_ON);

    printf("====== code start ====== \r\n");
    while (1)
    {
        Modbus_Event();
        KEY_Deal();
        if( KEY_ReadState(2)==KEY_PRESS )
        {
            printf("111");
        }
        if( KEY_ReadState(2)==KEY_PRESS )
        {
            printf("222");
        }
        if( KEY_ReadState(2)==KEY_PRESS )
        {
            printf("333");
        }
        if( KEY_ReadState(2)==KEY_PRESS )
        {
            printf("444");
        }
        if( KEY_ReadState(2)==KEY_PRESS )
        {
            printf("555");
        }
        if( KEY_ReadState(2)==KEY_PRESS )
        {
            printf("666");
        }
    }  
}