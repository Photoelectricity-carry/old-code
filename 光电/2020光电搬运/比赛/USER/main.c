#include "sys.h"
#include "usmart.h"
#include "port.h"
#include "usart.h"
#include "delay.h"
#include "TRACK.h"
#include "stm32f10x.h"
#include "TCS3200.h"
#include "direction.h"
#include "exit.h"
#include "speed.h"
#include "pwm.h"
#include "move.h"
#include "turn.h"
#include "gouzi.h"


int main ()			          //�����޸�
{
  u16 n=0,n1=0,n2=0,n3=0,left,right,a1,c1,e1;
	delay_init();
	EXTIX_Init();
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);	 			 //���ڳ�ʼ��Ϊ9600
	usmart_dev.init(72);	   //��ʼ��USMART                              *
	Port_Init();
	LED_Init();
	TCS3200_Init(1,1);
	TIM4_PWM_CH1_Init(7200,0);//72000000
	TIM4_PWM_CH3_Init(7200,0);
	TIM2_PWM_CH3_Init(1999,719);//72000000	
	TIM5_PWM_CH1_Init(1999,719);

	   

	
	    
			
			
			stop();
	    gouzi31(1400);
	    stop();
      gouzi21(150);//��
	    gouzi41(850);//��
		  stop();	
			
		


		Track_delay(300);//ǰ��ѭ��
		test_qian();
		Track_delay(40);
		test_qian();
		Track_delay(40);
		test_qian();


		Turn90(0,450);
		test_left();

		Track_delay(100);
		test_qian();
	 	weiqianjin_slow(500);
		
		stop();
    stop();
		n=clour_disguish();	//A
		a1=n;

		weihoutui_slow(200);  //A1���˸� 4.14��
		gouzi41(2500);//��
		stop();
		gouzi31(2500);//��
		stop();
		gouzi41(850);//��
		stop();
		
		A1_colour_go(n);
		
		
		stop();
		n=clour_disguish();	//C
		c1=n;	
		stop();
		
    weihoutui_slow(300);
		gouzi41(2500);
		stop();
		gouzi31(2500);
		stop();
		gouzi41(850);
		stop();

		C1_colour_go(n);
		c1=n;
		
    weiqianjin_slow(1000);
    stop();			
		n=clour_disguish();	//E
		stop();
		e1=n;	
    weihoutui_slow(300);
		gouzi41(2500);
		stop();
		gouzi31(2500);
		stop();
		gouzi41(850);
		stop();

		E1_colour_go(n);
		
		
		weihoutui_quick(600);
    gouzi21(150);//��

    gouzi1(121);//��
	
		gouzi21(60);//��
		stop();
		
		xunji(50);
		test_hou1();
		
		gouzi1(140);//��
		gouzi21(150);//��
		gouzi1(120);//��
		
		Track_delay(80);//ǰ��ѭ��
		weihoutui_slow(160);
			
	 gouzi41(2500);
	 stop();
	 gouzi31(2500);
	 stop();
	 gouzi41(850);
	 stop();
		
	xunji(50);
	test_hou();
	xunji(25);
	test_hou();	
	xunji(25);
	
	test_hou();
	Turn90(1,450);
	test_right();
	Track_delay(250);//ǰ��ѭ��
	test_qian();
		
		weihoutui_quick(500);
		Turn90(1,50);

		
     gouzi21(150);//��
     gouzi1(120);//��
		 gouzi21(60);//��
		 gouzi1(150);//��
		 stop();
		 weihoutui_slow(500);
 			
			Turn90(0,35);
			stop();
			
			xunji(60);
			test_hou1();
			gouzi1(140);//��
	   gouzi21(150);//��
		 Track_delay(80);//ǰ��ѭ��
		 stop();

		weihoutui_slow(160);
		gouzi31(2000);
		stop();
		gouzi41(2500);
		stop();
		gouzi31(2500);
		stop();
		gouzi41(850);//��
		stop();
	
		xunji(50);
		test_hou();
		xunji(25);
		test_hou();	
		xunji(25);
		test_hou();
		A2_colour_go(a1);                                 //A2
		stop();

    weihoutui_quick(500);
		Turn90(1,50);
		
    gouzi21(150);//��
    gouzi1(122);//��  4.16
   	gouzi21(60);//��
		gouzi1(150);//��
		stop();
		weihoutui_slow(500);
 			
		 Turn90(0,40);
		 stop();
		 xunji(50);
		 test_hou1();
		 gouzi1(130);//��
	   gouzi21(150);//��
		 Track_delay(80);//ǰ��ѭ��
	   weihoutui_slow(160);
		 stop();
		 weiqianjin_slow(250);
		 n=clour_disguish();
		 stop();
			
		weihoutui_slow(250);
		gouzi41(2500);
		stop();
		gouzi31(2500);
		stop();
		gouzi41(850);
		stop();
		xunji(55);
	  test_hou();
	  xunji(25);
	  test_hou();	
	  xunji(25);
	  test_hou();
	
	
	    Turn90(1,450);
	    test_right();
	    Track_delay(250);//ǰ��ѭ��
		  test_qian();	
      weihoutui_quick(600);
      gouzi21(150);//��
      gouzi1(120);//��
	
			gouzi21(60);//��
			stop();
 			xunji(50);
	    test_hou1();
			gouzi1(140);//��
	    gouzi21(150);//��
		  gouzi1(120);//��
		  Track_delay(80);//ǰ��ѭ��
		 
		weihoutui_slow(160);
		gouzi31(2000);
		stop();
		gouzi41(2500);
		stop();
		gouzi31(2500);
		stop();
		gouzi41(850);
		stop();
		xunji(50);
	  test_hou();
	  xunji(25);
	  test_hou();	
	  xunji(25);
	  test_hou();
	  B2_colour_go(n);                                       //B2




     stop();
     weiqianjin_slow(50);	
     gouzi21(150);//��
     gouzi1(110);//��
	   gouzi21(60);//��
		 stop();

 		 xunji(50);
	   test_hou1();
		 gouzi1(140);//��
	   gouzi21(150);//��
		 gouzi1(120);//��
		 Track_delay(80);//ǰ��ѭ��
		 weihoutui_slow(160);
		 gouzi41(2500);
		 stop();
		 gouzi31(2500);
		 stop();
		 gouzi41(850);
		 stop();
		 xunji(50);
		 
		 
		 
		test_hou();
		xunji(25);
		test_hou();	
		xunji(25);
		test_hou();
		Turn90(1,450);
		test_right();
		Track_delay(250);//ǰ��ѭ��
		test_qian();
		weiqianjin_slow(250);
		
		
		Turn90(1,50);
		weihoutui_slow(160);
		stop();
		
     gouzi21(150);//��
     gouzi1(125);//��
		 gouzi21(60);//��
		 stop();
		 weihoutui_slow(500);
 			
			Turn90(0,35);
			stop();
			xunji(100);
			test_hou1();
			gouzi1(140);//��
	    gouzi21(150);//��
      Track_delay(80);//ǰ��ѭ��
		  stop();
		 weihoutui_slow(160);
			
		gouzi31(2000);
		stop();
		gouzi41(2500);
		stop();
		gouzi31(2500);
		stop();
		gouzi41(850);
		stop();
		xunji(50);
	  test_hou();
	  xunji(25);
	  test_hou();	
	  xunji(25);
	  test_hou();
	
		E2_colour_go(e1);                                         //E2
	

    stop();	
    weiqianjin_slow(300);
		Turn90(1,50);
	
     gouzi21(150);//��
     gouzi1(125);//��
     gouzi21(60);//��
		 gouzi1(150);//��
		 stop();
		 weihoutui_slow(500);
 			
			Turn90(0,40);
			stop();
			xunji(50);
			test_hou1();
			gouzi1(130);//��
	    gouzi21(150);//��
		  Track_delay(80);//ǰ��ѭ��
	
		weihoutui_slow(250);
		gouzi41(2500);
		stop();
		gouzi31(2500);
		stop();
		gouzi41(850);
		stop();
		xunji(60);
		test_hou();
		xunji(25);
		test_hou();	
		xunji(25);
		test_hou();
	
	
	Turn90(1,450);
	test_right();
	Track_delay(250);//ǰ��ѭ��
	test_qian();
  weiqianjin_slow(50);	

      gouzi21(150);//��
      gouzi1(110);//��
			gouzi21(60);//��
			stop();
		
 			xunji(50);
	    test_hou1();
			gouzi1(140);//��
	    gouzi21(150);//��
		  gouzi1(120);//��
		  Track_delay(80);//ǰ��ѭ��

		weihoutui_slow(160);
		gouzi31(2000);
		stop();
		gouzi41(2500);
		stop();
		gouzi31(2500);
		stop();
	  gouzi41(850);
		stop();
	
	xunji(50);
	test_hou();
	xunji(25);
	test_hou();	
	xunji(25);
	test_hou();
	C2_colour_go(c1);                                                   //C2
																					
																					
   stop();
   Track_delay(40);//ǰ��ѭ��
	 test_qian ();
	 stop();
	 stop();
	 n=clour_disguish();
	 weihoutui_slow (400);
	 gouzi41(2500);
	 
	stop();
	gouzi31(2500);
	stop();
	gouzi41(850);
	stop();
	xunji(280);
	test_hou();
	xunji(25);
	test_hou();	
	xunji(25);
	test_hou();
	
	Turn90(1,450);
	test_right();
	Track_delay(250);//ǰ��ѭ��
	test_qian();
	Track_delay(40);//ǰ��ѭ��
	  
		test_qian ();
	  weihoutui_slow(160);
	  stop();
		gouzi31(2000);
		stop();
		gouzi41(2500);
		stop();
		gouzi31(2500);
		stop();
		gouzi41(850);
		stop();
		xunji(280);
	  test_hou(); 	
  	xunji(25);
	  test_hou();
	
		xunji(25);
		test_hou();
		D2_colour_go(n);                               //D2
		stop();
}