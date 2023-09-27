//ISD51仿真软件的使用源程序

//例程见下：
#include <reg51.h>

//#define uchar unsigned char




//串口初始化程序
void InitUart(char bps){
SCON  = 0x50; /* SCON: mode 1, 8-bit UART, enable rcvr      */
    	TMOD |= 0x20; /* TMOD: timer 1, mode 2, 8-bit reload        */
	if (bps==1) TH1=0xE8;  //BPS=1200
		if (bps==2) TH1=0xF4 ;//BPS=2400
			if (bps==3)  TH1=0xFA;//BPS=4800
				if (bps==4)  TH1 =0xFD;//BPS=9600
					if (bps==5) {
PCON |=0x80;//BPS=19。2K
TH1 =0xFd;
}
    	TL1=TH1;
TR1   = 1;    /* TR1:  timer 1 run                          */
    	TI    = 1;    /* TI:   set TI to send first char of UART    */
}

