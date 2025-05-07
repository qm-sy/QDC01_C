#include "key.h"

//P54 P13 14 15 TK2 3 4 5
uint16_t	xdata TK_cnt[16];	// 键计数值
uint32_t	xdata TK_zero[16];	// 0点读数 
uint16_t T_KeyCmp[16] ;
bit	B_ReadKeyOk=1;	//标志已转换完成16个键
uint16_t Count[16] ;
uint16_t LastState ;						//8位变量 	b0=1，代表k0上一次按下过 

void KEY_T_Init(void)
{
    uint8_t i,j=0;

	TSRT = 0x00;		//没有LED分时扫描
	TSCHEN1 = 0x3f;	//TK00~TK07
	
	TSCFG1  = (7<<4) + 3;	//开关电容工作频率 = fosc/(2*(TSCFG1[6:4]+1)), 放电时间(系统时钟周期数) 0(125) 1(250) 2(500) 3(1000) 4(2000) 5(2500) 6(5000) 7(7500) 最小3
	TSCFG2  = 2;				//配置触摸按键控制器的内部参考电压(AVCC的分压比), 0(1/4)  1(1/2)  2(5/8)  3(3/4)
	TSCTRL = 0xA0;			//开始自动扫描, 无平均, B7: TSGO,  B6: SINGLE,  B5: TSWAIT, B4: TSWUCS, B3: TSDCEN, B2: TSWUEN, B1 B0: TSSAMP
	
//	TSCTRL = (1<<7) + (1<<6);	//开始单次扫描, 无平均
//	TSCTRL = (1<<7) + (1<<6)+3;	//开始单次扫描, 4次平均
//	TSCTRL = (1<<7) + (1<<6)+1;	//开始单次扫描, 2次平均
//	TSWUTC = 12;		//100ms唤醒一次
	IE2 |= 0x80;			//使能触摸中断 
 
	TSCTRL = 0xA0;
	
	delay_ms(100);
    for(i=0;i<16;i++)
        TK_zero[i]=0;	
    while(j<8)
    {
        if( B_ReadKeyOk )
        {
            for(i=0;i<16;i++)
                TK_zero[i] += TK_cnt[i];
            B_ReadKeyOk = 0;
            j++;
        }
        delay_ms(50);
    }
    for(i=0;i<16;i++)
    {
        TK_zero[i]=(TK_zero[i]>>3);
//        printf("%u\t",(uint16_t)TK_zero[i]);
        T_KeyCmp[i] = 1500;
    }    
    
}



//========================================================================
// 函数名称: KEY_Deal
// 函数功能: 按键状态读取
// 入口参数: 无
// 函数返回: 无
// 当前版本: VER1.0
// 修改日期: 2023 - 1-1
// 当前作者:
// 其他备注:循环读取八个端口的状态，并将按下的时间赋值给 Count 数组，按下的状态赋值给LastState
//========================================================================
void KEY_Deal(void)			//检查所有的按键状态 10ms执行一次
{
	uint8_t i = 0;
    
//    printf("(%u,%u,%u)\r\n",(uint16_t)TK_cnt[0],(uint16_t)TK_cnt[1],(uint16_t)TK_cnt[2]);
    
	for(i=0;i<16;i++)					//循环8次 i的取值范围是0-7  代表了P30-P37的状态查询
	{
		if( TK_cnt[i]< (TK_zero[i]-T_KeyCmp[i]))			//持续按下，变量+1  
//		if( TK_cnt[i]> (TK_zero[i]+T_KeyCmp[i]))			//持续按下，变量+1			
		{
			if( Count[i]<60000 )
				Count[i] ++;			//按键按下，这个计数变量+1
		}
		else							//按键松开了，变量清0
		{
			if( Count[i]>0 )			//如果这个变量是按下过的
			{
				LastState |= (1<<i);	//这个变量相应的标志位置位
			}
			else
			{
				LastState &= ~(1<<i);	//这个变量相应的标志位清0
			}
			Count[i] = 0;				//按键按下，这个计数变量清0
		}
	}
}

//========================================================================
// 函数名称: KEY_ReadState
// 函数功能: 读取指定的按钮的状态
// 入口参数: @keynum : 按钮的端口号 例如P32端口，端口号就是2
// 函数返回: 看其他备注
// 当前版本: VER1.0
// 修改日期: 2023 - 1- 1
// 当前作者:
// 其他备注: 函数返回值如下
//	#define	KEY_NOPRESS		0		//按键未按下
//	#define	KEY_FILCKER		1		//消抖
//	#define	KEY_PRESS		2		//单击
//	#define	KEY_PRESSOVER	3		//单击结束
//	#define	KEY_LONGPRESS	4		//长按3秒
//	#define	KEY_LONGOVER	5		//长按结束
//	#define	KEY_RELAX		6		//按键松开

//========================================================================

uint8_t KEY_ReadState(uint8_t keynum)	//读取指定的按键的状态 10ms执行一次
{
	if( Count[keynum]>0 )					//按键是按下的各种状态返回
	{
		if( Count[keynum]<3 )				//按下<30ms 返回消抖状态
		{
			return KEY_FILCKER;
		}
		else if( Count[keynum]==3 )			//按下正好30ms 返回单击
		{
			return KEY_PRESS;
		}
		else if( Count[keynum]<150 )		//按下不到3000ms 返回单击结束
		{
			return KEY_PRESSOVER;
		}		
		else if( Count[keynum]==150 )		//按下正好3000ms 返回长按状态
		{
			return KEY_LONGPRESS;
		}	
		else								//长按结束
		{
			return KEY_LONGOVER;
		}			
		
	}
	else									//按键已经松开了，返回各种状态
	{
		if( LastState &( 1<<keynum ) )		//按键之前按下过
		{
			return KEY_RELAX;		
		}
		else								//按键之前没有按下
		{
			return KEY_NOPRESS;
		}
	}
}

void TKSU_Interrupt(void) interrupt 13
{
	uint8_t	j;
//    u8 intf=P0INTF;
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
}