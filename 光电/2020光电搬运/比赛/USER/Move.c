	#include <Move.h>
	#include "speed.h"
	#include "direction.h"
	#include "TRACK.h"
	#include "turn.h"
	#include "gouzi.h"


	//   /******************************************************************************
	//* ��������:   void Turn_Left(uint16 n)
	//* ��;:       ���Ƴ�����ת�ĺ�����
	//* ע�⣺
	//******************************************************************************/

	//  /******************************************************************************
	//* ��������:   void Turn_right(uint16 n)
	//* ��;:       ���Ƴ��嵹�˵ĺ�����
	//* ע�⣺
	//******************************************************************************/
	 u8 x=0;
	void A1_colour_go(u16 n)
		{
			 if(n==0)		     		   //��ɫ	
		 {
		xunji(60);
		test_hou();
		xunji(25);
		test_hou();	
		xunji(25);
		test_hou();

		Turn90(1,200);
		test_right();

		
		Track_delay(300); 
		test_qian();

		xunji(30);
		
		gouzi41(2500);//��
		stop();		
		gouzi31(1400);//��
		stop();
		gouzi41(850);//��
		stop();
		
		xunji(250);
		test_hou();
		xunji(25);
		test_hou();
		xunji(25);
		test_hou();
		
		Turn90(1,220);
		test_right();
		Track_delay(150);
		test_qian();
		stop();	
	}
		 else if (n==1)		  		   //��ɫ
		 {
		xunji(60);
		test_hou();
		xunji(25);
		test_hou();
		xunji(25);
		test_hou();

		Turn90(1,750);
		test_right();
		
		Track_delay(300); 
		test_qian();
		xunji(30);
			 
		gouzi41(2500);
		stop();		
		gouzi31(1400);//��
		stop();
		gouzi41(850);//��
		stop();	 
			 
		xunji(250);
		test_hou();
		xunji(25);
		test_hou();
		xunji(25);
		test_hou();
		
		Turn90(0,220);
		test_left();
		
		Track_delay(150);
		test_qian();
		stop();
		 }	 
			else if (n==2)	 //��ɫ
		 {	
		xunji(60);
		test_hou();
		xunji(25);
		test_hou();
		xunji(25);
		test_hou();
		 
		Turn90(1,450);
		test_right();

		
		Track_delay(150);	 
		test_qian();
		weiqianjin_slow(1000);
			 
		weihoutui_slow(1500);
		gouzi1(130);
		gouzi21(60);//��
		gouzi1(80);
		
		Track_delay(100);	 
		test_qian();
		xunji(30);

		
		gouzi41(2400);
		stop();		
		gouzi31(1400);//��
		stop();
		gouzi41(850);//��
		stop();
		
		xunji(80);
		test_hou1();
		
		gouzi1(140);//��			
		gouzi21(150);//��
		gouzi1(80);//��
		
		weiqianjin_slow(1000);
		weiqianjin_slow(1000);
		
		stop();		
	}	 
		 else if (n==3)		//��ɫ	    
		 {
				
		Track_delay(150); 
		test_qian();
		xunji(25);
		
		gouzi41(2500);
		stop();		
		gouzi31(1400);//��
		stop();
		gouzi41(850);//��
		stop();
		
		xunji(250);
		test_hou();
		xunji(25);
		test_hou();
		xunji(25);
		test_hou();
			 
		Turn90(1,400);
		test_right();
		Track_delay(150);
		test_qian();
		stop();	
		 }
		 else if (n==4)		  //��ɫ
		 { 
		xunji(50);
		test_hou();
		xunji(25);
		test_hou();
		xunji(25);
		test_hou();
			 
		Turn90(1,1100);
		test_right();

		Track_delay(150);	 
		test_qian();
			 
		weiqianjin_slow(1000);
		weihoutui_slow(1500);
		gouzi1(130);
		stop();
		gouzi21(60);
		stop();
		gouzi1(80);
		stop();
		
		Track_delay(100);	 
		test_qian();
		xunji(30);

		
		gouzi41(2500);
		stop();		
		gouzi31(1400);//��
		stop();
		gouzi41(850);//��
		stop();
		
		xunji(80);
		test_hou1();
		weihoutui_slow(1400);
		
			gouzi1(140);//��			
			gouzi21(150);//��
			gouzi1(80);//��

		xunji(20);
		test_hou();
		xunji(25);
		test_hou();
		xunji(25);
		test_hou();
		Turn90(0,450);
		test_left();
		Track_delay(150);
		test_qian();
		stop();	
		 }
		}
	void C1_colour_go(u16 n)
		{
			 if	(n==0)		       //��ɫ	 
		 {
			xunji(60);
			test_hou();
			xunji(25);
			test_hou();	
			xunji(25);
			test_hou();

			Turn90(0,220);
			test_left();

			
			Track_delay(300); 
			test_qian();
			xunji(30);
			
			gouzi41(2500);//��
			stop();		
			gouzi31(1400);//��
		  stop();
			gouzi41(850);//��
			stop();
			
			xunji(250);
			test_hou();
			xunji(25);
			test_hou();
			xunji(25);
			test_hou();
			
			Turn90(1,750);
			test_right();
			
			Track_delay(150);
			test_qian();
			stop();
		 } 
		 else if (n==1)		   //��ɫ	 
		 {
		xunji(60);
		test_hou();
		xunji(25);
		test_hou();	
		xunji(25);
		test_hou();

		Turn90(1,220);
		test_right();

		
		Track_delay(300); 
		test_qian();

		xunji(30);
		
		gouzi41(2500);//��
		stop();		
		gouzi31(1400);//��
		stop();
		gouzi41(850);//��
		stop();
		
			xunji(250);
			test_hou();
			xunji(25);
			test_hou();
			xunji(25);
			test_hou();
		
		Turn90(1,220);
		test_right();
		
		Track_delay(150);
		test_qian();
		stop();
		 }	 
		 else if (n==2)	   //��ɫ	  
		 {	
		Track_delay(150); 
		test_qian();
		xunji(25);
		
		gouzi41(2500);
		stop();		
		gouzi31(1400);//��
		stop();
		gouzi41(850);//��
		stop();
		
			xunji(250);
			test_hou();
			xunji(25);
			test_hou();
			xunji(25);
			test_hou();
			 
		Turn90(1,400);
		test_right();
		Track_delay(150);
		test_qian();
		stop();	
		 }	 
		 else if (n==3)		   //��ɫ	  
		 {
		xunji(60);
		test_hou();
		xunji(25);
		test_hou();	
		xunji(25);
		test_hou();

		Turn90(0,450);
		test_left();

		
		Track_delay(300); 
		test_qian();

		xunji(30);
		
		gouzi41(2500);//��
		stop();		
		gouzi31(1400);//��
		stop();
		gouzi41(850);//��
		stop();	
		
			xunji(250);
			test_hou();
			xunji(25);
			test_hou();
			xunji(25);
			test_hou();
		
		Turn90(1,1100);
		test_right();
		Track_delay(150);
		test_qian();
		stop();
		 }
		 else if (n==4)		   //��ɫ	
		 {	 
		xunji(60);
		test_hou();
		xunji(25);
		test_hou();
		xunji(25);
		test_hou();
		 
		Turn90(1,450);
		test_right();

		
		Track_delay(150);	 
		test_qian();
			 
		weiqianjin_slow(1000);
		 
		weihoutui_slow(1500);
			 
		gouzi1(130);
		stop();
		gouzi21(60);
		stop();
		gouzi1(80);
		stop();
		
		Track_delay(100);	 
		test_qian();
		xunji(30);

		
		gouzi41(2400);
		stop();		
		gouzi31(1400);//��
		stop();
		gouzi41(850);//��
		stop();
		
		xunji(80);
		test_hou1();
		
		gouzi1(140);//��			
		gouzi21(150);//��
		gouzi1(80);//��
		
		weiqianjin_slow(1000);	
		stop();		
			}
		 }
		
	void E1_colour_go(u16 n)
		{
		 if	(n==0)		       //��ɫ   
		 {	  
			xunji(60);
			test_hou();
			xunji(25);
			test_hou();
			xunji(25);
			test_hou();
			 
			Turn90(0,750);
			test_left();

			Track_delay(300);
			test_qian();
			xunji(30);

			gouzi41(2500);
			stop();		
			gouzi31(1400);//��
			stop();
			gouzi41(850);
			stop();
			 
			xunji(250);
			test_hou();
			xunji(25);
			test_hou();
			xunji(25);
			test_hou();

			Turn90(1,1200);
			test_right();
			Track_delay(250);
			test_qian();
		 }
		 else if (n==1)		   //��ɫ	 
		 {
		xunji(60);
		test_hou();
		xunji(25);
		test_hou();
		xunji(25);
		test_hou();
			 
		Turn90(0,220);
		test_left();
		
		Track_delay(300); 
		test_qian();

		xunji(30);
		
		gouzi41(2500);
		stop();		
		gouzi31(1400);//��
		stop();
		gouzi41(850);
		stop();
			 
		xunji(250);
		test_hou();
		xunji(25);
		test_hou();
		xunji(25);
		test_hou();

		Turn90(1,500);
		test_right();
		
		Track_delay(250);
		test_qian();
		 }	 
			else if (n==2)	   //��ɫ	  
		 {	
		xunji(50);
		test_hou();
		xunji(25);
		test_hou();
		xunji(25);
		test_hou();

		Turn90(0,500);
		test_left();
		
		Track_delay(300);
		test_qian();
		xunji(30);
		
		gouzi41(2500);
		stop();		
		gouzi31(1400);//��
		stop();
		gouzi41(850);
		stop();
			 
		xunji(250);
		test_hou();
		xunji(25);
		test_hou();
		xunji(25);
		test_hou();

		Turn90(1,800);	
		test_right();
		
		Track_delay(250);
		test_qian();
		 }	 
		 else if (n==3)		   //��ɫ	 
		 {
		xunji(60);
		test_hou();
		xunji(25);
		test_hou();
		xunji(25);
		test_hou();
			 
		Turn90(0,1100);
		test_left();

		
		Track_delay(300);
		test_qian();
		xunji(30);
		
		gouzi41(2500);
		stop();		
		gouzi31(1400);//��
		stop();
		gouzi41(850);
		stop();
			 
		xunji(250);
		test_hou();
		xunji(25);
		test_hou();
		xunji(25);
		test_hou();

		Turn90(0,800);
		test_left();
		Track_delay(250);
		test_qian();		
		 }
		 else if (n==4)		   //��ɫ	 
		 {
		Track_delay(50); 
		test_qian();
		xunji(25);
		
		gouzi41(2500);
		stop();		
		gouzi31(1400);//��
		stop();
		gouzi41(850);
		stop();
		
		xunji(250);
		test_hou();
		xunji(25);
		test_hou();
		xunji(25);
		test_hou();

		Turn90(1,200);
		test_right();
		Track_delay(250);
		test_qian();
		 }
	}
		
	void A2_colour_go(u16 n)
		 {
		 if	(n==0)		       //��ɫ   
		 {
			Turn90(1,450);
			test_right();
			Track_delay(300); 
			test_qian();	 
			weihoutui_slow(160);
			gouzi31(2000);
			stop();
			gouzi41(2500);
			stop();
			gouzi31(2500);
			stop();
			xunji(25);
			stop();
			gouzi31(2200);
			stop();
			gouzi31(1400);//KAI
			stop();	
			xunji(250);
			test_hou();
			xunji(25);
			test_hou();
			xunji(25);
			test_hou();
			gouzi41(850);
			stop();
			Turn90(1,1100);
			test_right();
			Track_delay(250);
			test_qian();
		
		 }
		 else if (n==1)		   //��ɫ	 
		 {
		  Turn90(1,1100);
		  test_right();
			Track_delay(300); 
			test_qian();	 
			weihoutui_slow(160);
			gouzi31(2100);
			stop();
			gouzi41(2500);
			stop();
			gouzi31(2500);
			stop();
			xunji(25);
			stop();
			gouzi31(2100);
			stop();
			gouzi31(1400);//KAI	
			stop();
			xunji(250);
			test_hou();
			xunji(25);
			test_hou();
			xunji(25);
			test_hou();
			gouzi41(850);
			stop();
			Turn90(1,450);
			test_right();
			Track_delay(250);
			test_qian();
		 }	 
			else if (n==2)		   //��ɫ	 
		 {
			Turn90(1,750);
			test_right();
			Track_delay(300); 
			test_qian();	 
			weihoutui_slow(160);
			gouzi31(2000);
			stop();
			gouzi41(2500);
			stop();
			gouzi31(2500);
			stop();
			xunji(25);
			stop();
			gouzi31(2100);
			stop();
			gouzi31(1400);//KAI
			stop();	
			xunji(250);
			test_hou();
			xunji(25);
			test_hou();
			xunji(25);
			test_hou();
			gouzi41(850);
			stop();
			Turn90(1,750);
			test_right();
			Track_delay(250);
			test_qian();
		 }	
		 else if (n==3)		   //��ɫ	 
		 {				
			Turn90(1,220);
			test_right();
			Track_delay(300); 
			test_qian();	 
			weihoutui_slow(160);
			gouzi31(2000);
			stop();
			gouzi41(2500);
			stop();
			gouzi31(2500);
			stop();
			xunji(25);
			stop();
			gouzi31(2100);
			stop();
			gouzi31(1400);//KAI
			stop();	
			xunji(250);
			test_hou();
			xunji(25);
			test_hou();
			xunji(25);
			test_hou();
			gouzi41(850);
			stop();
			Turn90(0,750);
			test_left();
			Track_delay(250);
			test_qian();
			 }  
		 else if (n==4)		   //��ɫ	 
		 {
			Turn90(0,750);
			test_left();
			Track_delay(300); 
			test_qian();	 
			weihoutui_slow(160);
			gouzi31(2000);
			stop();
			gouzi41(2500);
			stop();
			gouzi31(2500);
			stop();
			xunji(25);
			stop();
			gouzi31(2100);
			stop();
			gouzi31(1400);//KAI
			stop();	
			xunji(250);
			test_hou();
			xunji(25);
			test_hou();
			xunji(25);
			test_hou();
			gouzi41(850);
			stop();
			Turn90(1,200);
			test_right();
			Track_delay(250);
			test_qian();
		 }	
		}
	void B2_colour_go(u16 n)
		 {
		 if	(n==0)		       //��ɫ   
		 {
			Turn90(1,450);
			test_right();			 
			Track_delay(300); 
			test_qian();	 
			xunji(25);
			stop();
			gouzi41(2500);
		  stop();	
	    gouzi31(2000);
			stop();		 
		  gouzi31(1400);//KAI
		  stop();
			xunji(250);
			test_hou();
			xunji(25);
			test_hou();
			xunji(25);
			test_hou();
			gouzi41(850);
			stop();
			
			Turn90(1,1100);
			test_right();
			Track_delay(250);
			test_qian();
		 }
		 else if (n==1)		   //��ɫ	 
		 {
			Turn90(1,1100);
		  test_right();
	    Track_delay(300); 
			test_qian();
			stop();
			 
			xunji(25);
			stop();
			gouzi41(2500);
		  stop();	
	    gouzi31(2100);
			stop();		 
		  gouzi31(1400);//KAI
		  stop();
			xunji(250);
			test_hou();
			xunji(25);
			test_hou();
			xunji(25);
			test_hou();
			gouzi41(850);
			stop();
			Turn90(1,450);
			test_right();
			Track_delay(250);
			test_qian();
		 }	 
		 else if (n==2)		   //��ɫ	 
		 {
			Turn90(1,750);
		  test_right();
	    Track_delay(300); 
			test_qian();
		
			xunji(25);
			stop();
			gouzi41(2500);
		  stop();	
	    gouzi31(2000);
			stop();		 
		  gouzi31(1400);//KAI
		  stop();
			xunji(250);
			test_hou();
			xunji(25);
			test_hou();
			xunji(25);
			test_hou();
			gouzi41(850);
			stop();
			Turn90(1,750);
			test_right();
			Track_delay(250);
			test_qian();
		 }  
			else if (n==3)
	{
			Turn90(1,220);
			test_right();
			Track_delay(300); 
			test_qian();
		
			xunji(25);
			stop();
			gouzi41(2500);
		  stop();	
	    gouzi31(2000);
			stop();		 
		  gouzi31(1400);//KAI
		  stop();
			xunji(250);
			test_hou();
			xunji(25);
			test_hou();
			xunji(25);
			test_hou();
			gouzi41(850);
			stop();
			Turn90(0,750);
			test_left();
			Track_delay(250);
			test_qian();
	}	
	else if (n==4)		   //��ɫ	 
		 {
		  Turn90(0,750);
		  test_left();
	    Track_delay(300); 
			test_qian();
		
			xunji(25);
			stop();
			gouzi41(2500);
		  stop();	
	    gouzi31(2000);
			stop();		 
		  gouzi31(1400);//KAI
		  stop();
			xunji(250);
			test_hou();
			xunji(25);
			test_hou();
			xunji(25);
			test_hou();
			gouzi41(850);
			stop();
			Turn90(1,200);
			test_right();
			Track_delay(250);
			test_qian();
		 }	
	}
		 void C2_colour_go(u16 n)
		 {
		 if	(n==0)		       //��ɫ   
		 {
		Turn90(1,450);
		test_right();
			 
		Track_delay(300); 
		test_qian();
		stop();
			 
		weihoutui_slow(160);
		gouzi31(2000);
		stop();
		gouzi41(2500);
		stop();
		gouzi31(2500);
		stop();
		xunji(25);
	  stop();
	  gouzi31(2100);
		stop();		 
		gouzi31(1400);//KAI
		stop();
		xunji(250);
		test_hou();
		xunji(25);
		test_hou();
		xunji(25);
		test_hou();
		gouzi41(850);
	  stop();
		Turn90(1,1500);
		test_right();
		Track_delay(250);
		test_qian();
		 }
		 else if (n==1)		   //��ɫ	 
		 {
	  Turn90(1,1100);
		test_right();
    Track_delay(300); 
		test_qian();
		stop();
			 
		weihoutui_slow(160);
		gouzi31(2000);
		stop();
		gouzi41(2500);
		stop();
		gouzi31(2500);
		stop();
		xunji(25);
		stop();	
	  gouzi31(2100);
		stop();		 
		gouzi31(1400);//KAI
		stop();
		xunji(250);
		test_hou();
		xunji(25);
		test_hou();
		xunji(25);
		test_hou();
		gouzi41(850);
	  stop();
		Turn90(1,450);
		test_right();
		Track_delay(250);
		test_qian();
		 }	 
		 else if (n==2)		   //��ɫ	 
		 {
		Turn90(1,750);
		test_right();
    Track_delay(300); 
		test_qian();
		stop();
			 
		weihoutui_slow(160);
		gouzi31(2000);
		stop();
		gouzi41(2500);
		stop();
		gouzi31(2500);
		stop();
		xunji(25);
		stop();
		gouzi41(2500);
		stop();	
	  gouzi31(2100);
		stop();		 
		gouzi31(1400);//KAI
		stop();
		xunji(250);
		test_hou();
		xunji(25);
		test_hou();
		xunji(25);
		test_hou();
		gouzi41(850);
	  stop();
		Turn90(1,750);
		test_right();
		Track_delay(250);
		test_qian();
		 }  
			else if (n==3)
	{
		Turn90(1,220);
		test_right();
	  Track_delay(300); 
		test_qian();
		stop();
			 
		weihoutui_slow(160);
		gouzi31(2000);
		stop();
		gouzi41(2500);
		stop();
		gouzi31(2500);
		stop();
		xunji(25);
		stop();
	  gouzi31(2100);
		stop();		 
		gouzi31(1400);//KAI
		stop();
		xunji(250);
		test_hou();
		xunji(25);
		test_hou();
		xunji(25);
		test_hou();
		gouzi41(850);
	  stop();
		Turn90(0,750);
		test_left();
		Track_delay(250);
		test_qian();
	}	
	else if (n==4)		   //��ɫ	 
		 {
		Turn90(0,750);
		test_left();
	  Track_delay(300); 
		test_qian();
		stop();
			 
		weihoutui_slow(160);
		gouzi31(2000);
		stop();
		gouzi41(2500);
		stop();
		gouzi31(2500);
		stop();
		xunji(25);
	  stop();
	  gouzi31(2100);
		stop();		 
		gouzi31(1400);//KAI
		stop();
		xunji(250);
		test_hou();
		xunji(25);
		test_hou();
		xunji(25);
		test_hou();
		gouzi41(850);
	  stop();
		Turn90(1,200);
		test_right();
		Track_delay(250);
		test_qian();
		 }	
	}
		 void E2_colour_go(u16 n)
		 {
		 if	(n==0)		       //��ɫ   
		 {
		Turn90(1,450);
		test_right();

		Track_delay(300); 
		test_qian();
		stop();
			 
		weihoutui_slow(150);
		gouzi31(2100);
		stop();
		gouzi41(2500);
		stop();
		gouzi31(2500);
		stop();
		xunji(25);
		stop();	
	  gouzi31(2100);
		stop();		 
		gouzi31(1400);//KAI
		stop();

		xunji(250);
		test_hou();
		xunji(25);
		test_hou();
		xunji(25);
		test_hou();
		gouzi41(850);
		stop();
		Turn90(1,1100);
		test_right();
		Track_delay(250);
		test_qian();
		 }
		 else if (n==1)		   //��ɫ	 
		 {
		Turn90(1,1100);
		test_right();

			 
		Track_delay(300); 
		test_qian();
		stop();
			 
		weihoutui_slow(150);
		gouzi31(2100);
		stop();
		gouzi41(2500);
		stop();
		gouzi31(2500);
		stop();
		xunji(25);
		stop();	
	  gouzi31(2100);
		stop();		 
		gouzi31(1400);//KAI
		stop();

		xunji(250);
		test_hou();
		xunji(25);
		test_hou();
		xunji(25);
		test_hou();
		gouzi41(850);
		stop();
		Turn90(1,450);
		test_right();
		Track_delay(250);
		test_qian();
		 }	 
		 else if (n==2)		   //��ɫ	 
		 {
		Turn90(1,750);
		test_right();
			 
		Track_delay(300); 
		test_qian();
		stop();
			 
		weihoutui_slow(150);
		gouzi31(2100);
		stop();
		gouzi41(2500);
		stop();
		gouzi31(2500);
		stop();
		xunji(25);
		
		gouzi41(2500);
		stop();	
	  gouzi31(2100);
		stop();		 
		gouzi31(1400);//KAI
		stop();
		xunji(250);
		test_hou();
		xunji(25);
		test_hou();
		xunji(25);
		test_hou();
		gouzi41(850);
		stop();
		Turn90(1,750);
		test_right();
		Track_delay(250);
		test_qian();
		 }  
			else if (n==3)
	{
		Turn90(1,220);
		test_right();
		 
		Track_delay(300); 
		test_qian();
		stop();
			 
		weihoutui_slow(150);
		gouzi31(2100);
		stop();
		gouzi41(2500);
		stop();
		gouzi31(2500);
		stop();
		xunji(25);
		
		gouzi41(2500);
		stop();	
	  gouzi31(2100);
		stop();		 
		gouzi31(1400);//KAI
		stop();
		xunji(255);
		test_hou();
		xunji(25);
		test_hou();
		xunji(25);
		test_hou();
		gouzi41(850);
		stop();
		Turn90(0,750);
		test_left();
		Track_delay(250);
		test_qian();
	}	
	else if (n==4)		   //��ɫ	 
		 {
		Turn90(0,750);
		test_left();

			 
		Track_delay(300); 
		test_qian();
		stop();
			 
		weihoutui_slow(150);
	  gouzi31(2100);
		stop();
		gouzi41(2500);
		stop();
		gouzi31(2500);
		stop();
		xunji(25);
		stop();	
	  gouzi31(2100);
		stop();		 
		gouzi31(1400);//KAI
		stop();
		xunji(250);
		test_hou();
		xunji(25);
		test_hou();
		xunji(25);
		test_hou();
		gouzi41(850);
		stop();
		Turn90(1,200);
		test_right();
		Track_delay(250);
		test_qian();
		 }	
	}
		 void D2_colour_go(u16 n)
		 {
		 if	(n==0)		       //��ɫ   
		 {
			Turn90(1,450);
		  test_right();		 
			Track_delay(300); 
			test_qian();
		
			xunji(25);
		
			gouzi41(2500);
			stop();		
			gouzi31(2100);
			stop();
			gouzi31(1400);//KAI
			stop();
		
			xunji(250);
			test_hou();
			xunji(25);
			test_hou();
			xunji(25);
		  test_hou();
		  stop();
			Turn90(0,750);
		  test_left();
			Track_delay(250);
		  test_qian();
		  Track_delay(30);
		  test_qian();
		 }
		 else if (n==1)		   //��ɫ	 
		 {
			Turn90(1,1100);
		  test_right();
	    Track_delay(300); 
			test_qian();
			
			xunji(25);
		
			gouzi41(2500);
			stop();		
			gouzi31(2100);
			stop();
			gouzi31(1400);//KAI
			stop();
			xunji(250);
			test_hou();
			xunji(25);
			test_hou();
			xunji(25);
			test_hou();
			gouzi41(850);
			stop();
			Turn90(1,750);
			test_right();
			Track_delay(250);
			test_qian();
			Track_delay(30);
			test_qian();
		 }	 
		 else if (n==2)		   
		 {
			 Turn90(1,750);
		   test_right();
	 
		  Track_delay(300); 
			test_qian();
			
			xunji(25);
		
			gouzi41(2500);
			stop();		
			gouzi31(2100);
			stop();
			gouzi31(1400);//KAI
			stop();
		
			xunji(500);
			test_hou();
			xunji(25);
			test_hou();
			xunji(25);
		  test_hou();
		  stop();
		 }  
			else if (n==3)
	{
		  Turn90(1,220);
		  test_right();
      Track_delay(300); 
			test_qian();
		
			xunji(25);
		
			gouzi41(2500);
			stop();		
			gouzi31(2100);
			stop();
			gouzi31(1400);//KAI
			stop();
		
			xunji(250);
			test_hou();
			xunji(25);
			test_hou();
			xunji(25);
		  test_hou();
		  stop();
			Turn90(0,450);
			test_left();
			Track_delay(250);
			test_qian();
			Track_delay(30);
			test_qian();
	}	
	else if (n==4)		   //��ɫ	 
		 {
		  Turn90(0,750);
		  test_left();
      Track_delay(300); 
			test_qian();
	
			xunji(25);
		
			gouzi41(2500);
			stop();		
			gouzi31(2100);
			stop();
			gouzi31(1400);//KAI
			stop();
		
			xunji(250);
			test_hou();
			xunji(25);
			test_hou();
			xunji(25);
		  test_hou();
		  stop();
			stop();
			Turn90(1,450);
			test_right();
			Track_delay(250);
			test_qian();
			Track_delay(30);
			test_qian();
		 }	
	}


