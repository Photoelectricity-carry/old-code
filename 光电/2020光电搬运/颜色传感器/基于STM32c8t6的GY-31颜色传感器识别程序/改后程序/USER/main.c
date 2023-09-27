#include "stm32f10x.h" 
#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h" 
#include "key.h"
#include "exti.h"
#include "timer.h"
#include "lcd1602.h"	   
#include "tcs3200.h"
#include "stdio.h"
#include "stmflash.h"
#include "beep.h"

float R=0,G=0,B=0;
u16 Rgena,Ggena,Bgena;
u16 Ramount,Gamount,Bamount;
u16 amount;
u16 d[3];
u16 s;
u16 y;
u8 red_flag;
u8 white_flag=0;
//��ʾ����
void show()
{
			int r,g,b;
			r=R/1;
			LCD1602_Show_Str(3,0,"Color");	
            LCD1602_Show_Str(8,0,":");	    
			LCD1602_Show_Str(1,1,"R");
			LCD1602_Write_Dat(r/100%10+0x30);
			LCD1602_Write_Dat(r/10%10+0x30);
			LCD1602_Write_Dat(r%10+0x30);
			
      g=G/1;
			LCD1602_Show_Str(6,1,"G");
			LCD1602_Write_Dat(g/100%10+0x30);
			LCD1602_Write_Dat(g/10%10+0x30);
			LCD1602_Write_Dat(g%10+0x30);
			
			b=B/1;
			LCD1602_Show_Str(11,1,"B");
			LCD1602_Write_Dat(b/100%10+0x30);
			LCD1602_Write_Dat(b/10%10+0x30);
			LCD1602_Write_Dat(b%10+0x30);

}

//����ֵ
void dcz()
{
		STMFLASH_Read(0x08004000,(u16*)d,3);
		Rgena=d[0];
		Ggena=d[1];
		Bgena=d[2];
}

int main()
{		
		delay_init();	    	 //��ʱ������ʼ��	 
		SystemInit();
		EXTIX_Init();		 //�ⲿ�жϳ�ʼ��
		LCD1602_Init();			//1602��ʼ
		KEY_Init();
        BEEP_Init();
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
		uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
		//tcs3200_init(1,1);
		dcz();
		while(1)
		{	
			s=KEY0;
            
			if(s==0)
			{
				white_flag=1;		
                whitebalance();	//��ƽ�� 
			}
            if(KEY1==0)
            {
            red_flag=1;
            }
			delay_ms(50);
			R=tcs3200_RED();
			G=tcs3200_GREEN();
			B=tcs3200_BLUE();
			printf("r:%f g;%f b;%f \r\n",R,G,B);
			show();
            
           if(red_flag==1) 
           {   
                if((170<R&&R<200)&&(70<G&&G<95)&&(100<B&&B<130))
                {

                    BEEP=1;
          			LCD1602_Show_Str(10,0,"Red");	
                 
                 }else 
                {
                    BEEP=0;
                    LCD1602_Show_Str(10,0,"    ");	
                   
                }

            }
		}

}


