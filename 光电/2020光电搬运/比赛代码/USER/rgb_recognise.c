#include <rgb_recognise.h>
#define BLACK 0
#define GREEN 1
#define BLUE 2
#define RED 3
#define WHITE 4	

u8 rgb_recognise(void)
{
   	 u8 temp;
	u16 R = 0x00,G = 0x00,B = 0x00;
	u16 r = 0x00,g = 0x00,b = 0x00;

	
	EXTIX_Init();
	
	WhiteBalance();
 	r=RGB.Rgena;
	g=RGB.Ggena;
	b=RGB.Bgena;
	R = tcs3200_RED(r);
	G = tcs3200_GREEN(g);
	B = tcs3200_BLUE(b);
		if(R > 245 && G > 245 && B > 245) 			//识别为白色
			{	
			    temp = WHITE;			
				led_w();
			}
		 if(R < 48 && G < 48 && B < 48)				//否则是黑色
	   		{
			     temp =  BLACK; 				
				led_black();
			}			
		if(R>G&&R>B) 			//识别为红色
			{			
			    temp = RED;	
				led_r();
			}
		 if(G>R&&G>B) 			//识别为绿色
			{	
			    temp = GREEN;			
				led_g();
			 }
		 if(B>R&&B>G) 			//识别为蓝色
			{			
			    temp = BLUE;
				led_b();
			}
	return temp;
	
}
