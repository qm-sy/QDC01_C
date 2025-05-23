/*
|P0^0|      |P1^0|      |P2^0|B0    |P3^0|RX1       |P4^0|        |P5^0|         
|P0^1|BL    |P1^1|      |P2^1|B1    |P3^1|TX1       |P4^1|        |P5^1|         
|P0^2|RX4   |P1^2|      |P2^2|B2    |P3^2|LED1      |P4^2|        |P5^2|             
|P0^3|TX4   |P1^3|      |P2^3|B3    |P3^3|LED2      |P4^3|        |P5^3|         
|P0^4|DR4   |P1^4|      |P2^4|      |P3^4|LED3      |P4^4|        |P5^4|    
|P0^5|WR    |P1^5|      |P2^5|      |P3^5|LED4      |P4^5|        |P5^5|             
|P0^6|CS    |P1^6|      |P2^6|      |P3^6|LED5      |P4^6|        |P5^6|     
|P0^7|DATA  |P1^7|      |P2^7|      |P3^7|LED6      |P4^7|        |P5^7|     
*/ 
#include "gpio.h"

/**
 * @brief	GPIO初始化
 *
 * @param   void
 *
 * @return  void
 */
void GPIO_Init( void )
{
    P0M0 = 0X1A;    P0M1 = 0X00;        // 00001010  
    P1M0 = 0x00;    P1M1 = 0X00;   
    P2M0 = 0X00;    P2M1 = 0x00;
    P3M0 = 0XFE;    P3M1 = 0X00; 
    P4M0 = 0x00;    P4M1 = 0X00; 
    P5M0 = 0x00;    P5M1 = 0x00; 
}