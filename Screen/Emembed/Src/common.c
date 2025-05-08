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

    static uint16_t key_scan_cnt = 0;

    /* 1, key查询           */
    if( key_val.key_sacn_flag == 0 )
    {
        key_scan_cnt++;
        if( key_scan_cnt == 2 )
        {
            key_val.key_sacn_flag = 1;
            key_scan_cnt = 0;
        }
    }

}
