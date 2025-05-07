#include "lcd.h"


u8	idata	LCD_buff[20];	//LCD显存

/****************** 对第1~5数字装载显示函数 ***************************/
u8 code t_display[]={						//标准字库
//	 0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F
	0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71,
//black	 -     H    J	 K	  L	   N	o   P	 U     t    G    Q    r   M    y
	0x00,0x40,0x76,0x1E,0x70,0x38,0x37,0x5C,0x73,0x3E,0x78,0x3d,0x67,0x50,0x37,0x6e};

u8 code seg_pos[]={0,2,5,0,2,4,4,2,0,6,4,2,0,6};



/********************** 将显示内容导入显存 *****************************/
void	LoadToLcd(void)
{
	C0SEGV0  = LCD_buff[0];     // C0SEG 7~0数据寄存器
	C0SEGV1  = LCD_buff[1];     // C0SEG 15~8数据寄存器
	C0SEGV2  = LCD_buff[2];     // C0SEG 23~16数据寄存器
	C0SEGV3	 = LCD_buff[3];     // C0SEG 31~24数据寄存器
	C0SEGV4	 = LCD_buff[4];     // C0SEG 39~32数据寄存器
	C1SEGV0	 = LCD_buff[5];     // C1SEG 7~0数据寄存器
	C1SEGV1	 = LCD_buff[6];     // C1SEG 15~8数据寄存器
	C1SEGV2	 = LCD_buff[7];     // C1SEG 23~16数据寄存器
	C1SEGV3	 = LCD_buff[8];     // C1SEG 31~24数据寄存器
	C1SEGV4	 = LCD_buff[9];     // C1SEG 39~32数据寄存器
	C2SEGV0	 = LCD_buff[10];    // C2SEG 7~0数据寄存器
	C2SEGV1	 = LCD_buff[11];    // C2SEG 15~8数据寄存器
	C2SEGV2	 = LCD_buff[12];    // C2SEG 23~16数据寄存器
	C2SEGV3	 = LCD_buff[13];    // C2SEG 31~24数据寄存器
	C2SEGV4	 = LCD_buff[14];    // C2SEG 39~32数据寄存器
	C3SEGV0	 = LCD_buff[15];    // C3SEG 7~0数据寄存器
	C3SEGV1	 = LCD_buff[16];    // C3SEG 15~8数据寄存器
	C3SEGV2	 = LCD_buff[17];    // C3SEG 23~16数据寄存器
	C3SEGV3	 = LCD_buff[18];    // C3SEG 31~24数据寄存器
	C3SEGV4	 = LCD_buff[19];    // C3SEG 39~32数据寄存器
}

void	LCD_load(u8 n, u8 dat)		//n为第几个数字，为1~5，dat为要显示的数字
{


	if((n == 0) || (n >= 15))	
		return;	//合法值 1~5

	dat =  t_display[dat];

	switch( n )
	{
		case 1:
		case 2:
		case 3:
			LCD_buff[0]  &= ~(1<<seg_pos[n-1]);
			LCD_buff[5]  &= ~(3<<seg_pos[n-1]);
			LCD_buff[10] &= ~(3<<seg_pos[n-1]);
			LCD_buff[15] &= ~(3<<seg_pos[n-1]);
		
			if(dat & 0x01)		LCD_buff[15] |= (1<<seg_pos[n-1]);	//T_SEG_ABC[n];		//A
			if(dat & 0x02)		LCD_buff[15] |= (2<<seg_pos[n-1]);	//T_SEG_ABC[n];		//B
			if(dat & 0x04)		LCD_buff[5]  |= (2<<seg_pos[n-1]);	//T_SEG_ABC[n];		//C
			if(dat & 0x08)		LCD_buff[0]  |= (1<<seg_pos[n-1]);	//T_SEG_DEFG[n];	//D
			if(dat & 0x10)		LCD_buff[5]  |= (1<<seg_pos[n-1]);	//T_SEG_DEFG[n];	//E
			if(dat & 0x20)		LCD_buff[10] |= (1<<seg_pos[n-1]);	//T_SEG_DEFG[n];	//F
			if(dat & 0x40)		LCD_buff[10] |= (2<<seg_pos[n-1]);	//T_SEG_DEFG[n];	//G		
			break;
		
		case 4:
			LCD_buff[0]  &= ~(1<<7);
			LCD_buff[5]  &= ~(1<<7);
			LCD_buff[10] &= ~(1<<7);
			LCD_buff[15] &= ~(1<<7);
//			LCD_buff[1]  &= ~(1<<0);
			LCD_buff[6]  &= ~(1<<0);
			LCD_buff[11] &= ~(1<<0);
			LCD_buff[16] &= ~(1<<0);
		
			if(dat & 0x01)		LCD_buff[15] |= (1<<7);	//T_SEG_ABC[n];		//A
			if(dat & 0x02)		LCD_buff[16] |= (1<<0);	//T_SEG_ABC[n];		//B
			if(dat & 0x04)		LCD_buff[6]  |= (1<<0);	//T_SEG_ABC[n];		//C
			if(dat & 0x08)		LCD_buff[0]  |= (1<<7);	//T_SEG_DEFG[n];	//D
			if(dat & 0x10)		LCD_buff[5]  |= (1<<7);	//T_SEG_DEFG[n];	//E
			if(dat & 0x20)		LCD_buff[10] |= (1<<7);	//T_SEG_DEFG[n];	//F
			if(dat & 0x40)		LCD_buff[11] |= (1<<0);	//T_SEG_DEFG[n];	//G				
			break;
		
		case 5:
		case 6:			
			LCD_buff[1]  &= ~(1<<seg_pos[n-1]);
			LCD_buff[6]  &= ~(3<<seg_pos[n-1]);
			LCD_buff[11] &= ~(3<<seg_pos[n-1]);
			LCD_buff[16] &= ~(3<<seg_pos[n-1]);
		
			if(dat & 0x01)		LCD_buff[16] |= (1<<seg_pos[n-1]);	//T_SEG_ABC[n];		//A
			if(dat & 0x02)		LCD_buff[16] |= (2<<seg_pos[n-1]);	//T_SEG_ABC[n];		//B
			if(dat & 0x04)		LCD_buff[6]  |= (2<<seg_pos[n-1]);	//T_SEG_ABC[n];		//C
			if(dat & 0x08)		LCD_buff[1]  |= (1<<seg_pos[n-1]);	//T_SEG_DEFG[n];	//D
			if(dat & 0x10)		LCD_buff[6]  |= (1<<seg_pos[n-1]);	//T_SEG_DEFG[n];	//E
			if(dat & 0x20)		LCD_buff[11] |= (1<<seg_pos[n-1]);	//T_SEG_DEFG[n];	//F
			if(dat & 0x40)		LCD_buff[11] |= (2<<seg_pos[n-1]);	//T_SEG_DEFG[n];	//G		
			break;
		
		case 14:			
			LCD_buff[1]  &= ~(3<<seg_pos[n-1]);
			LCD_buff[6]  &= ~(3<<seg_pos[n-1]);
			LCD_buff[11] &= ~(3<<seg_pos[n-1]);
			LCD_buff[16] &= ~(2<<seg_pos[n-1]);
		
			if(dat & 0x01)		LCD_buff[1]   |= (2<<seg_pos[n-1]);	//T_SEG_ABC[n];		//A
			if(dat & 0x02)		LCD_buff[1]   |= (1<<seg_pos[n-1]);	//T_SEG_ABC[n];		//B
			if(dat & 0x04)		LCD_buff[11]  |= (1<<seg_pos[n-1]);	//T_SEG_ABC[n];		//C
			if(dat & 0x08)		LCD_buff[16]  |= (2<<seg_pos[n-1]);	//T_SEG_DEFG[n];	//D
			if(dat & 0x10)		LCD_buff[11]  |= (2<<seg_pos[n-1]);	//T_SEG_DEFG[n];	//E
			if(dat & 0x20)		LCD_buff[6]   |= (2<<seg_pos[n-1]);	//T_SEG_DEFG[n];	//F
			if(dat & 0x40)		LCD_buff[6]   |= (1<<seg_pos[n-1]);	//T_SEG_DEFG[n];	//G		
			break;		
		
		case 13:	
		case 12:
		case 11:
		case 10:			
			LCD_buff[2]  &= ~(3<<seg_pos[n-1]);
			LCD_buff[7]  &= ~(3<<seg_pos[n-1]);
			LCD_buff[12] &= ~(3<<seg_pos[n-1]);
			LCD_buff[17] &= ~(2<<seg_pos[n-1]);
		
			if(dat & 0x01)		LCD_buff[2]   |= (2<<seg_pos[n-1]);	//T_SEG_ABC[n];		//A
			if(dat & 0x02)		LCD_buff[2]   |= (1<<seg_pos[n-1]);	//T_SEG_ABC[n];		//B
			if(dat & 0x04)		LCD_buff[12]  |= (1<<seg_pos[n-1]);	//T_SEG_ABC[n];		//C
			if(dat & 0x08)		LCD_buff[17]  |= (2<<seg_pos[n-1]);	//T_SEG_DEFG[n];	//D
			if(dat & 0x10)		LCD_buff[12]  |= (2<<seg_pos[n-1]);	//T_SEG_DEFG[n];	//E
			if(dat & 0x20)		LCD_buff[7]   |= (2<<seg_pos[n-1]);	//T_SEG_DEFG[n];	//F
			if(dat & 0x40)		LCD_buff[7]   |= (1<<seg_pos[n-1]);	//T_SEG_DEFG[n];	//G		
			break;	
		
		case 9:	
		case 8:
		case 7:	
			LCD_buff[3]  &= ~(3<<seg_pos[n-1]);
			LCD_buff[8]  &= ~(3<<seg_pos[n-1]);
			LCD_buff[13] &= ~(3<<seg_pos[n-1]);
			LCD_buff[14] &= ~(2<<seg_pos[n-1]);
		
			if(dat & 0x01)		LCD_buff[3]   |= (2<<seg_pos[n-1]);	//T_SEG_ABC[n];		//A
			if(dat & 0x02)		LCD_buff[3]   |= (1<<seg_pos[n-1]);	//T_SEG_ABC[n];		//B
			if(dat & 0x04)		LCD_buff[13]  |= (1<<seg_pos[n-1]);	//T_SEG_ABC[n];		//C
			if(dat & 0x08)		LCD_buff[18]  |= (2<<seg_pos[n-1]);	//T_SEG_DEFG[n];	//D
			if(dat & 0x10)		LCD_buff[13]  |= (2<<seg_pos[n-1]);	//T_SEG_DEFG[n];	//E
			if(dat & 0x20)		LCD_buff[8]   |= (2<<seg_pos[n-1]);	//T_SEG_DEFG[n];	//F
			if(dat & 0x40)		LCD_buff[8]   |= (1<<seg_pos[n-1]);	//T_SEG_DEFG[n];	//G		
			break;	
		
		default:
			break;
		
	}
}

/********************** LCD配置函数 *****************************/
void	LCD_config(void)
{
	u8	i;

//	LCDCFG  = 0x80 + 0;	// 0x00:选择CPU时钟为LCD时钟, 0x80: 选择外部32K晶振做时钟. VLCD电压选择0~7对应0.65+VLCD*0.05.
//	DBLEN   = 2;		// 设置LCD显示时的死区时间长度, 取值0~7.
//	COMLENH	= 0;		// COM时间长度设置 高字节COMLEN[19:16],  一共20bit.
//	COMLENM	= 0;		// COM时间长度设置 中字节COMLEN[15:8]	LCD刷新率 = LCD时钟频率 / ((DBLEN[2:0]+COMLEN[19:0]+1) *2 * COM数)
//	COMLENL	= 65;		// COM时间长度设置 低字节COMLEN[7:0]	LCD刷新率 = 32768/((2+65+1)*2*4) = 60Hz
//	BLINKRATE = 60;		// 闪烁率配置寄存器, LCD闪烁率 = LCD刷新率 / BLINKRATE[7:0] Hz
	
	LCDCFG  = 0x00 + 0;	// 0x00:选择CPU时钟为LCD时钟, 0x80: 选择外部32K晶振做时钟. VLCD电压选择0~7对应0.65+VLCD*0.05.
	DBLNTH   = 2;		// 设置LCD显示时的死区时间长度, 取值0~7.
	COMLNTHH	= 0x01;		// COM时间长度设置 高字节COMLEN[19:16],  一共20bit.
	COMLNTHM	= 0x86;		// COM时间长度设置 中字节COMLEN[15:8]	LCD刷新率 = LCD时钟频率 / ((DBLEN[2:0]+COMLEN[19:0]+1) *2 * COM数)
	COMLNTHL	= 0x9d;		// COM时间长度设置 低字节COMLEN[7:0]	LCD刷新率 = 32768/((2+65+1)*2*4) = 60Hz
	BLINKFRPS = 60;		// 闪烁率配置寄存器, LCD闪烁率 = LCD刷新率 / BLINKRATE[7:0] Hz
	
	COM_ON_A  = 0x0f;		// COM使能寄存器
	SEG_ON_A = 0xff;		// SEG线使能寄存器1, SEG7~SEG0
	SEG_ON_B = 0xff;		// SEG线使能寄存器2, SEG15~SEG8
	SEG_ON_C = 0xff;		// SEG线使能寄存器3, SEG23~SEG16
	SEG_ON_D = 0xff;		// SEG线使能寄存器4, SEG31~SEG24
	SEG_ON_E = 0xff;		// SEG线使能寄存器5, SEG39~SEG32
	
	P5n_pure_input(0x03);	//P5.0 P5.1 设置为高阻输入	COM0 COM1
	P3n_pure_input(0x60);	//P3.5 P3.6 设置为高阻输入	COM2 COM3

	LCDCFG2 = 0x0f;			// SEG0~3切换到P7.7~7.4
	P7n_pure_input(0xf0);	//P7.7~P7.4 设置为高阻输入	SEG0~SEG3 (对应P7.7~7.4)
	P4n_pure_input(0x80);	//P4.7      设置为高阻输入	SEG4
	P1n_pure_input(0x03);	//P1.1~P1.0 设置为高阻输入	SEG5 SEG6       (对应P1.1 P1.0)
	P0n_pure_input(0xe0);	//P0.7~P0.5 设置为高阻输入	SEG7 SEG8 SEG9  (对应P0.7 P0.6 P0.5)
	P5n_pure_input(0x0C);	//P5.3 P5.2 设置为高阻输入	SEG10 SEG11     (对应P5.3 P5.2)
	P0n_pure_input(0x1f);	//P0.4~P0.0 设置为高阻输入	SEG12~SEG16  (对应P0.4 ~ 0.0)
	P4n_pure_input(0x60);	//P4.6 P4.5 设置为高阻输入	SEG17 SEG18
	//P2n_pure_input(0xff);	//P2.7~P2.0 设置为高阻输入	SEG19~SEG26  (对应P2.7~2.0)
	P4n_pure_input(0x1e);	//P4.4~P4.1 设置为高阻输入	SEG27~SEG30  (对应P4.4~4.1)
	P3n_pure_input(0x80);	//P3.7      设置为高阻输入	SEG31
	P7n_pure_input(0x0f);	//P7.3~P7.0 设置为高阻输入	SEG32~SEG35  (对应P7.3~7.0)
	P6n_pure_input(0x0f);	//P6.0~P6.3 设置为高阻输入	SEG36~SEG39  (对应P6.3~6.0)

	for(i=0; i<20; i++)	
		LCD_buff[i] = 0xff;	//清除显示内容
		
//	LCD_buff[15]=0x05;
	
	LoadToLcd();	//将显示内容导入显存

	LCDCR = (0<<1) + 1;	// LCD控制寄存器, 0:普通模式, 1:长暗模式, 2:长亮模式, 3:闪烁模式.  +0:禁止LCD模块,  +1:允许LCD模块.
}

