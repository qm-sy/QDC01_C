#include "common.h"

/**
 * @brief	一些定时执行的事件   Timer3：10ms
 *
 * @param   
 *
 * @return  void
**/
void Tim3_ISR( void ) interrupt 19
{
    static uint16_t fan_rotate_cnt = 0;
    static uint16_t modbus_04scan_cnt = 0;
    static uint16_t alarm_temp_flick_cnt = 0;
    /* 1, 风扇旋转           */
    fan_rotate_cnt++;
    if(fan_rotate_cnt == 15)
    {
        lcd_info.fan_rotate_flag = 1 - lcd_info.fan_rotate_flag;
        fan_rotate_cnt = 0;
    }

    /* 2, 04查询           */
    modbus_04scan_cnt++;
    if( modbus_04scan_cnt == 100 )
    {
        modbus.scan_flag_04 = 1;
        modbus_04scan_cnt = 0;
    }

    /* 3, 报警温度闪烁           */
    alarm_temp_flick_cnt++;
    if( alarm_temp_flick_cnt == 50 )
    {
        lcd_info.alarm_temp_flick_flag = 1 - lcd_info.alarm_temp_flick_flag;
        alarm_temp_flick_cnt = 0;
    }
}
