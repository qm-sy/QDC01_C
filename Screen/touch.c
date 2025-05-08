#include "touch.h"

//P54 P13 14 15 TK2 3 4 5
u16	xdata TK_cnt[6];	// 键计数值
u32	xdata TK_zero[6];	// 0点读数 
u16 T_KeyCmp[6] ;
bit	B_ReadKeyOk=1;	//标志已转换完成16个键
u16 Count[6] ;
u16 LastState ;						//8位变量 	b0=1，代表k0上一次按下过 
KEY_VAL key_val;
	
void KEY_T_Init(void)
{
    u8 i,j=0;

	TSRT = 0x00;		//没有LED分时扫描
	TSCHEN1 = 0x3f;	//TK00~TK07
	TSCHEN2 = 0x00;	//TK08~TK15
	
	TSCFG1  = (7<<4) + 3;	//开关电容工作频率 = fosc/(2*(TSCFG1[6:4]+1)), 放电时间(系统时钟周期数) 0(125) 1(250) 2(500) 3(1000) 4(2000) 5(2500) 6(5000) 7(7500) 最小3
	TSCFG2  = 2;				//配置触摸按键控制器的内部参考电压(AVCC的分压比), 0(1/4)  1(1/2)  2(5/8)  3(3/4)
	TSCTRL = 0xA0;			//开始自动扫描, 无平均, B7: TSGO,  B6: SINGLE,  B5: TSWAIT, B4: TSWUCS, B3: TSDCEN, B2: TSWUEN, B1 B0: TSSAMP
	
//	TSCTRL = (1<<7) + (1<<6);	//开始单次扫描, 无平均
//	TSCTRL = (1<<7) + (1<<6)+3;	//开始单次扫描, 4次平均
//	TSCTRL = (1<<7) + (1<<6)+1;	//开始单次扫描, 2次平均
//	TSWUTC = 12;		//100ms唤醒一次
	IE2 |= 0x80;			//使能触摸中断 
    EA = 1;
    
	TSCTRL = 0xA0;
	
	delay_ms(100);
    for(i=0;i<6;i++)
	{
		TK_zero[i]=0;
	}
        	
    while(j<6)
    {
        if( B_ReadKeyOk )
        {
            for(i=0;i<6;i++)
                TK_zero[i] += TK_cnt[i];
            B_ReadKeyOk = 0;
            j++;
        }
        delay_ms(50);
    }
    for(i=0;i<6;i++)
    {
        TK_zero[i]=(TK_zero[i]>>3);
//        printf("%u\t",(u16)TK_zero[i]);
        T_KeyCmp[i] = 1500;
		//T_KeyCmp[i] = TK_zero[i] * 0.3;
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
	u8 i = 0;
    
//    printf("(%u,%u,%u)\r\n",(u16)TK_cnt[0],(u16)TK_cnt[1],(u16)TK_cnt[2]);
    
	for(i=0;i<6;i++)					//循环8次 i的取值范围是0-7  代表了P30-P37的状态查询
	{
		if( i < 3 )
		{
			if( TK_cnt[i]< (TK_zero[i]-T_KeyCmp[i]))			//持续按下，变量+1 
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
		}else
		{
			if( TK_cnt[i]> (TK_zero[i]+T_KeyCmp[i]))			//持续按下，变量+1			
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

u8 KEY_ReadState(u8 keynum)	//读取指定的按键的状态 10ms执行一次
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

void key_val_init( void )
{
	key_val.key1_scan_allow = 1;       
    key_val.key2_scan_allow = 1;  
    key_val.key3_scan_allow = 1;   
    key_val.key4_scan_allow = 1;   
    key_val.key5_scan_allow = 1;   
    key_val.key6_scan_allow = 1; 
	key_val.key_sacn_flag   = 1;
}
void key_scan( void )
{
	if( key_val.key_sacn_flag == 1 )
	{
		KEY_Deal();	
		if( KEY_ReadState(KEY4) == KEY_PRESS )											//调节通道
		{
			channel_choose();
			send_to_slave();
		}
		if(( KEY_ReadState(KEY2) == KEY_PRESS ) && ( key_val.key2_scan_allow == 1 ))	//调节功率↑
		{
			up_key();
			send_to_slave();
		}
		if(( KEY_ReadState(KEY3) == KEY_PRESS ) && ( key_val.key3_scan_allow == 1 ))	//调节功率↓
		{
			down_key();
			send_to_slave();
		}
		if(( KEY_ReadState(KEY5) == KEY_PRESS ) && ( key_val.key5_scan_allow == 1 ))
		{
			mode_choose();
			get_slave_statu_03();
		}

		if( KEY_ReadState(KEY6) == KEY_LONGOVER )										//调节风力
		{
			key_val.key2_scan_allow = 0;
			key_val.key3_scan_allow = 0;
			key_val.key5_scan_allow = 0;

			if( KEY_ReadState(KEY2) == KEY_PRESS )
			{
				fan_up();
				send_to_slave();
			}
			if( KEY_ReadState(KEY3) == KEY_PRESS )
			{
				fan_down();
				send_to_slave();
			}
			if( KEY_ReadState(KEY5) == KEY_PRESS )
			{
				lcd_info.sync_flag = 1 - lcd_info.sync_flag;
				sync_dis(lcd_info.sync_flag);
				send_to_slave();
			}
		}
		if( KEY_ReadState(KEY6) == KEY_NOPRESS )//释放按键2、3
		{
			key_val.key2_scan_allow = 1;
			key_val.key3_scan_allow = 1;
			key_val.key5_scan_allow = 1;
		}
		//key_val.key_sacn_flag = 0;
	}	
}


void channel_choose( void )
{
    if(lcd_info.channel_num == 7)
    {
        lcd_info.channel_num = 1;
    }
    else
    {
        lcd_info.channel_num += 1;
    }
    channel_dis(lcd_info.channel_num);
}

void up_key( void )
{
    if( lcd_info.power_level < 100 )
    {
        lcd_info.power_level += 5;
    }

    num_dis(lcd_info.power_level);
}

void down_key( void )
{

    if( lcd_info.power_level > 0)
    {
        lcd_info.power_level -= 5;
    }

    num_dis(lcd_info.power_level);
}

void fan_up( void )
{
    if( lcd_info.fan_level < 6 )
    {
        lcd_info.fan_level++;
    }

    wind_dis(lcd_info.fan_level);
}

void fan_down( void )
{
    if( lcd_info.fan_level > 0 )
    {
        lcd_info.fan_level--;
    }

    wind_dis(lcd_info.fan_level);
}


void mode_choose( void )
{

    if(lcd_info.mode_num < 6)
    {
        lcd_info.mode_num++;
		if( lcd_info.mode_num == 6 )
		{
			lcd_info.mode_num = 1;
		}
    }
    
    screen_clear();                //一次清屏

    mode_dis(DIS_ON);       
    num_dis(lcd_info.mode_num);           //显示模式序号和标志
         
    delay_ms(500);
    
    screen_clear();                 //二次清屏
    
    mode_dis(DIS_OFF);

    sync_dis(lcd_info.sync_flag);
    num_dis(lcd_info.power_level);
    channel_dis(3);
    percentage_dis(DIS_ON);
    wind_dis(lcd_info.fan_level);         
}
