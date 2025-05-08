#include "modbus_rtu.h"

MODBIS_INFO modbus;

/**
 * @brief	modbus_rtu  无奇偶校验
 *
 * @param   void
 *
 * @return  void 
**/
void Modbus_Event( void )
{
    uint16_t crc,rccrc;
    
    /*1.接收完毕                                           */
    if( rs485.RX4_rev_end_Flag == 1 )
    {
        /*2.清空接收完毕标志位                              */    
        rs485.RX4_rev_end_Flag = 0;

        /*3.CRC校验                                         */
        crc = MODBUS_CRC16(rs485.RX4_buf, rs485.RX4_rev_cnt-2);
        rccrc = (rs485.RX4_buf[rs485.RX4_rev_cnt-1]) | (rs485.RX4_buf[rs485.RX4_rev_cnt-2]<<8);

        /*4.清空接收计数                                    */
        rs485.RX4_rev_cnt = 0; 

        /*5.CRC校验通过，进行地址域校验                      */
        if( crc == rccrc )
        {
            /*6.地址域校验通过，进入相应功能函数进行处理      */
            if( rs485.RX4_buf[0] == MY_ADDR )
            {
                switch ( rs485.RX4_buf[1] )
                {
                    case 0x03:		Modbus_Fun3();		break;
                    case 0x04:		Modbus_Fun4();      break;    

                    case 0x10:      Modbus_Fun4();      break;  
                    default:                            break;
                }
            }
        }
    }
}

void Modbus_Fun3()
{
    uint8_t start_addr_03 = 3;              //Slave reply  DATA1_H address
    uint16_t i;
    for( i = 0; i < 6; i++)
    {
        switch (i)
        {
         case 0:
            lcd_info.channel_num = rs485.RX4_buf[start_addr_03 + 1];

             break;
 
         case 1:
            lcd_info.sync_flag = rs485.RX4_buf[start_addr_03 + 1];

             break;
 
         case 2:
            lcd_info.fan_level = rs485.RX4_buf[start_addr_03 + 1];

             break; 
 
         case 3:
            lcd_info.power_level = rs485.RX4_buf[start_addr_03 + 1];

             break;
 
         case 4:
            lcd_info.alarm_temp_val = rs485.RX4_buf[start_addr_03 + 1];

             break;   
 
         case 5:
            lcd_info.mode_num = rs485.RX4_buf[start_addr_03 + 1];
 
             break;   
 
         default:
             break;
        }
        start_addr_03 += 2;
    }
    lcd_info.lcd_connect_flag = 1;
    num_dis(lcd_info.power_level);
    wind_dis(lcd_info.fan_level);
    channel_dis(lcd_info.channel_num);
    sync_dis(lcd_info.sync_flag);
}

void Modbus_Fun4()
{

}


/**
 * @brief	从机回复主机
 *  
 * @param   code_num:功能码       
 * @param   length:数据长度        
 * 
  @return  crc16:crc校验的值 2byte
 */
void slave_to_master(uint8_t code_num,uint8_t length)
{
    uint16_t crc;

    switch (code_num)
    {
        case 0x03:
            crc = MODBUS_CRC16(rs485.TX4_buf,length);

            rs485.TX4_buf[length+1] = crc;                 //CRC H
            rs485.TX4_buf[length] = crc>>8;            //CRC L

            rs485.TX4_send_bytelength = length + 2;
            
            break;
        case 0x04:
            crc = MODBUS_CRC16(rs485.TX4_buf,length);

            rs485.TX4_buf[length+1] = crc;                 //CRC H
            rs485.TX4_buf[length] = crc>>8;            //CRC L

            rs485.TX4_send_bytelength = length + 2;
            
            break;    

        case 0x06:
            memcpy(rs485.TX4_buf,rs485.RX4_buf,8);

            rs485.TX4_send_bytelength = length;
            
            break;   

        case 0x10:
            memcpy(rs485.TX4_buf,rs485.RX4_buf,6);
        
            crc = MODBUS_CRC16(rs485.TX4_buf,6);

            rs485.TX4_buf[7] = crc;                 //CRC H
            rs485.TX4_buf[6] = crc>>8;              //CRC L
        
            rs485.TX4_send_bytelength = length;
            
            break;         

        default:
            break;
    }

    DR_485 = 1;                                 //485可以发送
    delay_ms(2);
    S4CON |= S4TI;                              //开始发送
    delay_ms(1);
}


/**
 * @brief	crc校验函数
 * 
 * @param   buf：  Address(1 byte) +Funtion(1 byte) ）+Data(n byte)   
 * @param   length:数据长度           
 * 
  @return  crc16:crc校验的值 2byte
 */
uint16_t MODBUS_CRC16(uint8_t *buf, uint8_t length)
{
	uint8_t	i;
	uint16_t	crc16;

    /* 1, 预置16位CRC寄存器为0xffff（即全为1）                          */
	crc16 = 0xffff;	

	do
	{
        /* 2, 把8位数据与16位CRC寄存器的低位相异或，把结果放于CRC寄存器     */        
		crc16 ^= (uint16_t)*buf;		//
		for(i=0; i<8; i++)		
		{
            /* 3, 如果最低位为1，把CRC寄存器的内容右移一位(朝低位)，用0填补最高位 再异或0xA001    */
			if(crc16 & 1)
            {
                crc16 = (crc16 >> 1) ^ 0xA001;
            }
            /* 4, 如果最低位为0，把CRC寄存器的内容右移一位(朝低位)，用0填补最高位                */
            else
            {
                crc16 >>= 1;
            }		
		}
		buf++;
	}while(--length != 0);

	return	(crc16);
}

void get_slave_statu_03( void )
{
    uint8_t send_buf[8] = {0xDC,0x03,0x00,0x00,0x00,0x06,0x45,0xD7};

    memcpy(rs485.TX4_buf,send_buf,8);
    rs485.TX4_send_bytelength = 8;

    DR_485 = 1;                                 //485可以发送
    delay_ms(2);
    S4CON |= S4TI;                              //开始发送
    delay_ms(1);
}

void send_to_slave( void )
{
   uint8_t send_buf[21];
   uint16_t crc;

   send_buf[0] = 0xDC;
   send_buf[1] = 0x10;
   send_buf[2] = 0x00;
   send_buf[3] = 0x00;
   send_buf[4] = 0x00;
   send_buf[5] = 0x06;
   send_buf[6] = 0x0C;

   send_buf[7] = 0x00;
   send_buf[8] = lcd_info.channel_num;

   send_buf[9] = 0x00;
   send_buf[10] = lcd_info.sync_flag;

   send_buf[11] = 0x00;
   send_buf[12] = lcd_info.fan_level;

   send_buf[13] = 0x00;
   send_buf[14] = lcd_info.power_level;

   send_buf[15] = 0x00;
   send_buf[16] = lcd_info.alarm_temp_val;

   send_buf[17] = 0x00;
   send_buf[18] = lcd_info.mode_num;

   crc = MODBUS_CRC16(send_buf,19);

   send_buf[19] = crc>>8;
   send_buf[20] = crc;

   memcpy(rs485.TX4_buf,send_buf,21);
   
   rs485.TX4_send_bytelength = 21;
   DR_485 = 1;                                 //485可以发送
   delay_ms(2);
   S4CON |= S4TI;                              //开始发送
   delay_ms(1);
}

