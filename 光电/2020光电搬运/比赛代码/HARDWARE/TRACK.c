#include "TRACK.h"
#include "speed.h"
#include "delay.h"
#include "direction.h"
#include "turn.h"
#include "sys.h"

void track()//前进循迹
{
u16 left,right;
left=4900;
right=5100;	

if( A3==1 && A2==0 && A1==0&& A0==1 )

		{Direction (0,1);Speed (left,right);delay_ms(10,0);}
		
else if(  A3==1 && A2==0 && A1==1 && A0==1)
	//0100
		{Direction (0,1);Speed (left-600,right+820);delay_ms(10,0);}
		
else if(  A3==1 && A2==1 && A1==0 && A0==1)
	//0010 
		{Direction (0,1);Speed (left+800,right-600);delay_ms(10,0);}
		
else if(  A3==0 && A2==0 && A1==1 && A0==1)
	//1100
		{Direction (0,1);Speed (left-600,right+820);delay_ms(10,0);}
		
else if(  A3==1 && A2==1 && A1==0 && A0==0)
	//0011
		{Direction (0,1);Speed (left+800,right-600);delay_ms(10,0);}
		
else if(  A3==0 && A2==1 && A1==1 && A0==1)
	//1000
		{Direction (0,1);Speed (left-800,right+1020);delay_ms(10,0);}
		
else if(  A3==1 && A2==1 && A1==1 && A0==0)
	//0001
		{Direction (0,1);Speed (left+1000,right-800);delay_ms(10,0);}
		
//else if(  A3==0 && A2==0 && A1==0 && A0==1)
//	//1000
//		{Direction (1,0);Speed (left,right);delay_ms(10,0);}
//		
//else if(  A3==1 && A2==0 && A1==0 && A0==0)
//	//0001
//		{Direction (1,1);Speed (left,right);delay_ms(10,0);}
//		else if(  A3==0 && A2==0 && A1==0 && A0==0)
//	//0001
//		{Direction (1,0);Speed (left,right);delay_ms(10,0);}
else
		{Direction (0,1);Speed (left,right);delay_ms(10,0);}		
	}


void track_back()//后退循迹
{
u16 left,right;
left=4900;
right=4960;	

if( B3==1 && B2==0 && B1==0&& B0==1)
	//0110
		{Direction (1,0);Speed (left,right);delay_ms(10,0);}
		
else if(  B3==1 && B2==0 && B1==1&& B0==1)
	//0100
		{Direction (1,0);Speed (left-500,right+700);delay_ms(10,0);}
		
else if(  B3==1 && B2==1 && B1==0&& B0==1)
	//0010
		{Direction (1,0);Speed (left+700,right-500);delay_ms(10,0);}
		
else if(  B3==0 && B2==0 && B1==1&& B0==1)
	//1100
		{Direction (1,0);Speed (left-500,right+700);delay_ms(10,0);}
		
else if(  B3==1 && B2==1 && B1==0&& B0==0)
	//0011
		{Direction (1,0);Speed (left+700,right-500);delay_ms(10,0);}
		
else if(  B3==0 && B2==1 && B1==1&& B0==1)
	//1000
		{Direction (1,0);Speed (left-700,right+900);delay_ms(10,0);}
		
else if(  B3==1 && B2==1 && B1==1&& B0==0)
	//0001
		{Direction (1,0);Speed (left+900,right-700);delay_ms(10,0);}

else
		{Direction (1,0);Speed (left,right);delay_ms(10,0);}
		
	}






void Track_delay(u16 time)//前进循迹
{
	u16 i;
	for(i=0;i<time;i++)
		{
			track();
		}	
}



void xunji(u16 time)//后退循迹
{
	u16 i;
	for(i=0;i<time;i++)
		{
			track_back();
		}
	
}

void qian()
{
  Direction(0,1);
	Speed(3000,3000);
  delay_ms(400,0);
	stop();	
}


void test_hou1()
 {
			while(QL!=1)
		{
      track_back();
		}
		while(QL==1)
		{
			stop();
			break;
		}
	}

void test_qian()
 {
		while(QL!=1)
		{
     track();
		while(QL==1)
		{
			stop();
			break;
		}    
		}
}

void test_hou()
 {
			while(HOU!=1)
		{
      track_back();
		}
		while(HOU==0)
		{
			stop();
			break;
		}
		
 }
 
void test_right()
{
	while(QR==0)
		{
				Turn_weizhuan(0);
		}
		while(QR!=0)
		{
			stop();
			break;
		}
}


void test_left()
{
	while(QL!=1)
		{
				Turn_weizhuan(1);
		}
		while(QL==1)
		{
			stop();
			break;
		}
}

void turn180()
{
	stop();
	Turn90(0,970);  //90°
	stop();
	
	test_right(); //中点检测
	
	stop();
	Turn90(0,960);  //90°
	stop();
}




