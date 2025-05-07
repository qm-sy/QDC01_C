/*
|P0^0|          |P1^0|TK1       |P2^0|LED5      |P3^0|RX1       |P4^0|        |P5^0|         
|P0^1|DATA      |P1^1|TK2       |P2^1|LED4      |P3^1|TX1       |P4^1|        |P5^1|         
|P0^2|CS        |P1^2|          |P2^2|LED3      |P3^2|          |P4^2|        |P5^2|RX4         
|P0^3|WR        |P1^3|TK4       |P2^3|LED2      |P3^3|          |P4^3|        |P5^3|TX4     
|P0^4|DR4       |P1^4|TK5       |P2^4|LED1      |P3^4|          |P4^4|BL      |P5^4|TK3
|P0^5|          |P1^5|TK6       |P2^5|          |P3^5|          |P4^5|        |P5^5|             
|P0^6|          |P1^6|          |P2^6|          |P3^6|          |P4^6|        |P5^6|     
|P0^7|          |P1^7|          |P2^7|          |P3^7|LED6      |P4^7|        |P5^7|     
*/ 
#ifndef _GPIO_H_
#define _GPIO_H_

#include "stc.h" 

sbit DATA   = P0^1;
sbit CS     = P0^2;
sbit WR     = P0^3;
sbit DR_485 = P0^4;

sbit TK1    = P1^0;
sbit TK2    = P1^1;
sbit TK4    = P1^3;
sbit TK5    = P1^4;
sbit TK6    = P1^5;

sbit LED5   = P2^0;
sbit LED4   = P2^1;
sbit LED3   = P2^2;
sbit LED2   = P2^3;
sbit LED1   = P2^4;

sbit RX1    = P3^0;
sbit TX1    = P3^1;
sbit LED6   = P3^7;

sbit BL     = P4^4;

sbit COM1   = P5^0;

sbit RX4    = P5^2;
sbit TX4    = P5^3;
sbit TK3    = P5^4;

void GPIO_Init( void );

#endif