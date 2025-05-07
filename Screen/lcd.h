#ifndef __LCD_H
#define __LCD_H

#include "stc.h"   //������ͷ�ļ��󣬲���Ҫ�ٰ���"reg51.h"ͷ�ļ�
#include "delay.h"

extern u8	idata	LCD_buff[20];	//LCD�Դ�

#define LCD_SET_P1		LCD_buff[0]	 |=  0x02
#define LCD_CLR_P1		LCD_buff[0]	 &= ~0x02
#define LCD_SET_P2		LCD_buff[0]	 |=  0x08
#define LCD_CLR_P2		LCD_buff[0]	 &= ~0x08
#define LCD_SET_Hyphen1	LCD_buff[0]	 |=  0x10
#define LCD_CLR_Hyphen1	LCD_buff[0]	 &= ~0x10
#define LCD_SET_Hyphen2	LCD_buff[10] |=  0x10
#define LCD_CLR_Hyphen2	LCD_buff[10] &= ~0x10
#define LCD_SET_colon1	LCD_buff[5]	 |=  0x10
#define LCD_CLR_colon1	LCD_buff[5]	 &= ~0x10

#define LCD_SET_P3		LCD_buff[0]	 |=  0x40
#define LCD_CLR_P3		LCD_buff[0]	 &= ~0x40
#define LCD_SET_P4		LCD_buff[1]	 |=  0x01
#define LCD_CLR_P4		LCD_buff[1]	 &= ~0x01
#define LCD_SET_Hyphen3	LCD_buff[1]	 |=  0x02
#define LCD_CLR_Hyphen3	LCD_buff[1]	 &= ~0x02
#define LCD_SET_Hyphen4	LCD_buff[11] |=  0x02
#define LCD_CLR_Hyphen4	LCD_buff[11] &= ~0x02
#define LCD_SET_colon2	LCD_buff[6]	 |=  0x02
#define LCD_CLR_colon2	LCD_buff[6]	 &= ~0x02
#define LCD_SET_STC		LCD_buff[16] |=  0x02
#define LCD_CLR_STC		LCD_buff[16] &= ~0x02

#define LCD_SET_P5		LCD_buff[1]	 |=  0x08
#define LCD_CLR_P5		LCD_buff[1]	 &= ~0x08
#define LCD_SET_P11		LCD_buff[17] |=  0x01
#define LCD_CLR_P11		LCD_buff[17] &= ~0x01
#define LCD_SET_P10		LCD_buff[17] |=  0x04
#define LCD_CLR_P10		LCD_buff[17] &= ~0x04
#define LCD_SET_P9		LCD_buff[17] |=  0x10
#define LCD_CLR_P9		LCD_buff[17] &= ~0x10

#define LCD_SET_P8		LCD_buff[18] |=  0x01
#define LCD_CLR_P8		LCD_buff[18] &= ~0x01
#define LCD_SET_P7		LCD_buff[18] |=  0x04
#define LCD_CLR_P7		LCD_buff[18] &= ~0x04
#define LCD_SET_P6		LCD_buff[18] |=  0x10
#define LCD_CLR_P6		LCD_buff[18] &= ~0x10

#define LCD_SET_LUX		LCD_buff[3]	 |=  0x40
#define LCD_CLR_LUX		LCD_buff[3]	 &= ~0x40
#define LCD_SET_PM25	LCD_buff[8]	 |=  0x40
#define LCD_CLR_PM25	LCD_buff[8]	 &= ~0x40
#define LCD_SET_CO2		LCD_buff[13] |=  0x40
#define LCD_CLR_CO2 	LCD_buff[13] &= ~0x40
#define LCD_SET_CO		LCD_buff[18] |=  0x40
#define LCD_CLR_CO	 	LCD_buff[18] &= ~0x40

#define LCD_SET_THU		LCD_buff[3]  |=  0x80
#define LCD_CLR_THU	 	LCD_buff[3]  &= ~0x80
#define LCD_SET_WED		LCD_buff[8]	 |=  0x80
#define LCD_CLR_WED		LCD_buff[8]	 &= ~0x80
#define LCD_SET_TUE		LCD_buff[13] |=  0x80
#define LCD_CLR_TUE 	LCD_buff[13] &= ~0x80
#define LCD_SET_MON		LCD_buff[18] |=  0x80
#define LCD_CLR_MON	 	LCD_buff[18] &= ~0x80

#define LCD_SET_Hyphen5	LCD_buff[4]  |=  0x01
#define LCD_CLR_Hyphen5	LCD_buff[4]  &= ~0x01
#define LCD_SET_FRI		LCD_buff[9]	 |=  0x01
#define LCD_CLR_FRI		LCD_buff[9]	 &= ~0x01
#define LCD_SET_SAT		LCD_buff[14] |=  0x01
#define LCD_CLR_SAT 	LCD_buff[14] &= ~0x01
#define LCD_SET_SUM		LCD_buff[19] |=  0x01
#define LCD_CLR_SUM	 	LCD_buff[19] &= ~0x01

#define LCD_SET_m		LCD_buff[4]  |=  0x02
#define LCD_CLR_m		LCD_buff[4]  &= ~0x02
#define LCD_SET_k		LCD_buff[9]	 |=  0x02
#define LCD_CLR_k		LCD_buff[9]	 &= ~0x02
#define LCD_SET_g		LCD_buff[14] |=  0x02
#define LCD_CLR_g	 	LCD_buff[14] &= ~0x02
#define LCD_SET_m3		LCD_buff[19] |=  0x02
#define LCD_CLR_m3	 	LCD_buff[19] &= ~0x02

#define LCD_SET_2W		LCD_buff[4]  |=  0x04
#define LCD_CLR_2W		LCD_buff[4]  &= ~0x04
#define LCD_SET_2h		LCD_buff[9]	 |=  0x04
#define LCD_CLR_2h		LCD_buff[9]	 &= ~0x04
#define LCD_SET_om		LCD_buff[14] |=  0x04
#define LCD_CLR_om	 	LCD_buff[14] &= ~0x04
#define LCD_SET_hz		LCD_buff[19] |=  0x04
#define LCD_CLR_hz	 	LCD_buff[19] &= ~0x04

#define LCD_SET_2m		LCD_buff[4]  |=  0x08
#define LCD_CLR_2m		LCD_buff[4]  &= ~0x08
#define LCD_SET_2k		LCD_buff[9]	 |=  0x08
#define LCD_CLR_2k		LCD_buff[9]	 &= ~0x08
#define LCD_SET_2M		LCD_buff[14] |=  0x08
#define LCD_CLR_2M	 	LCD_buff[14] &= ~0x08
#define LCD_SET_Pa		LCD_buff[19] |=  0x08
#define LCD_CLR_Pa	 	LCD_buff[19] &= ~0x08

#define LCD_SET_uA		LCD_buff[9]	 |=  0x10
#define LCD_CLR_uA		LCD_buff[9]	 &= ~0x10
#define LCD_SET_mA		LCD_buff[14] |=  0x10
#define LCD_CLR_mA	 	LCD_buff[14] &= ~0x10
#define LCD_SET_A		LCD_buff[19] |=  0x10
#define LCD_CLR_A	 	LCD_buff[19] &= ~0x10

#define LCD_SET_C		LCD_buff[4]  |=  0x20
#define LCD_CLR_C		LCD_buff[4]  &= ~0x20
#define LCD_SET_F		LCD_buff[9]	 |=  0x20
#define LCD_CLR_F		LCD_buff[9]	 &= ~0x20
#define LCD_SET_percent	LCD_buff[19] |=  0x20
#define LCD_CLR_percent	LCD_buff[19] &= ~0x20
#define LCD_SET_RH		LCD_buff[14] |=  0x20
#define LCD_CLR_RH	 	LCD_buff[14] &= ~0x20

#define LCD_SET_kV		LCD_buff[4]  |=  0x40
#define LCD_CLR_kV		LCD_buff[4]  &= ~0x40
#define LCD_SET_V		LCD_buff[9]	 |=  0x40
#define LCD_CLR_V		LCD_buff[9]	 &= ~0x40
#define LCD_SET_mV		LCD_buff[14] |=  0x40
#define LCD_CLR_mV		LCD_buff[14] &= ~0x40
#define LCD_SET_uV		LCD_buff[19] |=  0x40
#define LCD_CLR_uV	 	LCD_buff[19] &= ~0x40

#define LCD_SET_Hyphen7	LCD_buff[4]  |=  0x80
#define LCD_CLR_Hyphen7	LCD_buff[4]  &= ~0x80
#define LCD_SET_DC		LCD_buff[9]	 |=  0x80
#define LCD_CLR_DC		LCD_buff[9]	 &= ~0x80
#define LCD_SET_AC		LCD_buff[14] |=  0x80
#define LCD_CLR_AC		LCD_buff[14] &= ~0x80
#define LCD_SET_Hyphen6	LCD_buff[19] |=  0x80
#define LCD_CLR_Hyphen6	LCD_buff[19] &= ~0x80


void	LCD_config(void);
void	LCD_load(u8 n, u8 dat);	
void	LoadToLcd(void);

#endif



