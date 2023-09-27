/*=============================================================================
* FileName:TSL230.c
* Resouce Descption:
* S0:pc0;
* S1:pc1;
* S2:pc2;
* S3:pc3;
* OE:Pc5,LOW->Enable,High->Disable;
* Out:PD5;T1 
* Time1:clk计数
* time2:1s计时       F=clk/1s
=============================================================================*/
#include "includes.h"

unsigned char FrequencyMode = F_100_100;//TCS频率输出模式
unsigned char PhotoDiodeMode = PH_CLEAR;//TCS虑光模式

unsigned char Time1sCount=0;            //计时1s所用Time Buf
unsigned int  TCSPlus_1s=0;             //TCS 1s输出的脉冲个数
unsigned char Time_1sFlag = 0;
/*=============================================
*  TSL230 inital 
* pc0-pc3:s0-s3(out)
* OE(PC5):out
* 
=============================================*/
void TCS230Inital(void)
{
//..Mode Set
    //PC0-PC3 OUT
	DDRC  = DDRC  | 0x0f;
	PORTC = PORTC | 0x0f;
	
	//PC5 out
	PORTC = PORTC | 0x20;//0010 0000
	DDRC  = DDRC  | 0x20;
	PORTC = PORTC & 0xdf;//1101 1111	
	TCS230Mode(FrequencyMode,PhotoDiodeMode);
}
/*=====================================================================
PB1:计数PB1 CLK
* Timer/Counter 1 initialization
* Clock source: T1 pin Falling Edge
* Mode: Normal top=FFFFh
* OC1A output: Discon.
* OC1B output: Discon.
* Noise Canceler: Off
* Input Capture on Falling Edge
* Timer 1 Overflow Interrupt: Off
* Input Capture Interrupt: Off
* Compare A Match Interrupt: Off
* Compare B Match Interrupt: Off

* Timer/Counter 2 initialization
* Clock source: System Clock
* Clock value: 3.600 kHz
* Mode: Normal top=FFh
* OC2 output: Disconnected
=====================================================================*/
void TimerInital(void)
{
//..PB1 计数PB1 CLK timer1
	TCCR1A=0x00;
	TCCR1B=0x06;
	
	TCNT1H=0x00;
	TCNT1L=0x00;
	
	ICR1H=0x00;
	ICR1L=0x00;
	
	OCR1AH=0x00;
	OCR1AL=0x00;
	
	OCR1BH=0x00;
	OCR1BL=0x00;
//time2 1s  3.6KHz  72/(3.6*1000)s=20ms 255-72=183(初值)=0xb7
	ASSR  = 0x00;
	TCCR2 = 0x07;
	TCNT2 = 0xb7;
	OCR2  = 0x00;
	
	// Timer(s)/Counter(s) Interrupt(s) initialization
	TIMSK=0x40;
}
/*=====================================================================
* S0:pc0;
* S1:pC1;
* S2:pC2;
* S3:pC3;
* S1S0:00(PowerDown) 01(%20) 10(%2) 11(%100)
* s3s2:00(Red) 01(clear) 10(blue) 11(green)
* return 0:ACK  1:FOutMode erro  2:PhotoType erro
=====================================================================*/
unsigned char TCS230Mode(unsigned char FOutMode,unsigned char PhotoType)
{
//frequency mode
	
	if( FOutMode == F_POWERDOWN)
	{//S1S0:00 pc1=pC0=0
		PORTC = PORTC & 0xfc;//1111 1100 
	}
	else if(FOutMode == F_100_2)
	{//S1S0:10 pc1=1,pc0=0
		PORTD = PORTD & 0xfe;// 1111 1110
		PORTD = PORTD | 0x02;// 0000 0010 
	}
	else if(FOutMode == F_100_20)
	{//S1S0:01 pc1=0 pc0=1
		PORTD = PORTD & 0xfd;//1111 1101
		PORTD = PORTD | 0x01;//0000 0001 
	}
	else if(FOutMode == F_100_100)
	{//S1S0:11 pc1=pc0=1 
		PORTD = PORTD | 0x03;//0000 0011
	}
	else 
	{  //参数错误
		return 1;
	}
	FrequencyMode = FOutMode;
	
//photoDIODE type
    
	if(PhotoType==PH_RED)
	{//s3s2:00 pc3=pc2=0
		PORTD = PORTD & 0xf3;//1111 0011
	}
	else if(PhotoType==PH_CLEAR)
	{//s3s2:01 pc3=0 pc2=1
		PORTC = PORTC & 0xf7;//1111 0111
		PORTC = PORTC | 0x04;//0000 0100
	}
	else if(PhotoType==PH_BLUE)
	{//s3s2:10 pc3=1 pc2=0 
		 
		PORTC = PORTC & 0xfb;//1111 1011
		PORTC = PORTC | 0x08;//0000 1000
	}	
	else if(PhotoType==PH_GREEN)
	{//s3s2:11 pc3=pc2=1
		PORTC = PORTC | 0x0c;//1100 0000 
		//
	}
	else 
	{//参数错误
		return 2;
	}
	PhotoDiodeMode=PhotoType;	
	return 0;	
}
/*=====================================================================
*  Timer 2 overflow interrupt service routine
*  定时器定时:20ms
=====================================================================*/
SIGNAL(SIG_OVERFLOW2)
{
	// Reinitialize Timer 2 value
	TCNT2=0xb7;
	// Place your code here
	Time1sCount++;
	if(Time1sCount>=5)
	{//20ms*50=1s
	//..更新频率值    
		TCSPlus_1s = TCNT1;
	//..重新计数
		TCNT1 = 0;
		Time1sCount = 0;		
		Time_1sFlag = 1;
	}
}
//$
