/*******************************************
* �ļ����� 
* ���ܣ� 
* ˵���� 
/********************************************/
#include <iom128v.h>
#include <macros.h>
#include "12864.h"

//��ɫʶ����ɫ���˲���ѡ�񣺺�ɫ(S2,S3=0,0)����ɫ(S2,S3=0,1)����ɫ(S2,S3=1,1)
#define S2 _PC7
#define S3 _PC6

//��������������
volatile uchar red=0,blue=0,green=0,flag=0,i=0,j=0,data[5]={0};
volatile uint counter=0;

//�ж϶���
#pragma interrupt_handler interrupt_int2:4 
#pragma interrupt_handler interrupt_timer1:15

/*******************************************
* ��������: int2_init()
* ��������: �ⲿ�ж�2��ʼ��
* ��ڲ���: ��
* ���ڲ���: ��
/********************************************/
void int2_init() 
{
   DDRD &= ~BIT(2);//�ж���������Ϊ����
   PORTD |= BIT(2); //�������������
   EICRA = 0X20; //�½��ش���
}

/*******************************************
* ��������: timer1_init()
* ��������: ��ʱ��1��ʼ��
* ��ڲ���: ��
* ���ڲ���: ��
/********************************************/
void timer1_init()
{
    TCCR1B = 0X02;// ���÷�Ƶ��Ϊ8
	TCNT1H = 0x63;// ���ü�����ֵ, ��ʱ20ms
    TCNT1L = 0xC0;
}
/*******************************************
* ��������: port_init()
* ��������: �˿ڳ�ʼ��
* ��ڲ���: ��
* ���ڲ���: ��
/********************************************/
void port_init()
{
   DDRA = 0XFF;//PORTA3~0ΪҺ��������
   DDRC = 0XFF;//����S2��S3  
}

/*******************************************
* ��������:  main()
/********************************************/
void main(void)
{   
   port_init();
   int2_init();
   timer1_init();
   Init_12864();  
   LcmClearTXT(); //�ı�����RAM����
   Display_x_y_data(0,0,"��ɫʶ��");
   Display_x_y_data(1,0,"��ɫ�ɷ֣�");
   Display_x_y_data(2,0,"��ɫ�ɷ֣�");
   Display_x_y_data(3,0,"��ɫ�ɷ֣�");
   S2=0;//�ȼ���ɫ(S2,S3=0,0)
   S3=0;
   SEI();
   EIMSK |= BIT(2); //���ⲿ�ж�
   TIMSK |=  BIT(2);//������ж�
   while(1);  
}

 /*******************************************
* ��������:  interrupt_int2()  
* ��������: 
* ��ڲ���: ��
* ���ڲ���: ��
/********************************************/
void interrupt_int2()  
{  
	counter++;
}

/*******************************************
* ��������: interrupt_timer1()
* ��������: 
* ��ڲ���: ��
* ���ڲ���: ��
/********************************************/
void interrupt_timer1()
{
    CLI();//�����ж�
    TCCR1B = 0X00;//��ʱ��ֹͣ����
	TIMSK &= ~ BIT(2);//�ر�����ж�
	EIMSK &= ~BIT(2); //�ر��ⲿ�ж�      	
	flag++;//ʵ���ȼ���ɫ,�ټ����ɫ,Ȼ������ɫ,ѭ�����
	if(flag==1)
	{   		 
		 red=counter;
		 data[0]=counter/100+0x30;		 
		 counter=counter%100;
		 data[1]=counter/10+0x30;
		 counter=counter%10;
		 data[2]=counter+0x30;		
   		 Locate_x_y(1,5);	
   		 for(i=0;i<3;i++)	    
	     		 Writedata(data[i]);    		
		S2=0;//�´μ����ɫ(S2,S3=0,1)
		S3=1;		
	}
	else if(flag==2)
	{
   		 blue=counter;
		 data[0]=counter/100+0x30;		 
		 counter=counter%100;
		 data[1]=counter/10+0x30;
		 counter=counter%10;
		 data[2]=counter+0x30;		
   		 Locate_x_y(2,5);	
   		 for(i=0;i<3;i++)	    
	     		 Writedata(data[i]);    			
		S2=1;//�´μ����ɫ(S2,S3=1,1)
		S3=1;
	}
    else if(flag==3)
	{
   		 green=counter;
		 data[0]=counter/100+0x30;		 
		 counter=counter%100;
		 data[1]=counter/10+0x30;
		 counter=counter%10;
		 data[2]=counter+0x30;	
   		 Locate_x_y(3,5);	
   		 for(i=0;i<3;i++)	    
	     		 Writedata(data[i]);   				 
		S2=0;//�´μ���ɫ(S2,S3=0,0)
		S3=0;
	}
	else if(flag==4) 
	{      
	     flag=0;		 
		 if((red+5)>(blue+green))		 
		     Display_x_y_data(0,5,"��ɫ");
		 else if((blue+8>red)&&(blue+2>green))
		     Display_x_y_data(0,5,"��ɫ");		
		 else if((green-3<red)&&(green-15>blue))
		     Display_x_y_data(0,5,"��ɫ");	  	
		 else if((green+5>red)&&(green>blue))
		     Display_x_y_data(0,5,"��ɫ");		   
		/*else if((blue>red)&&(green>blue))
		     Display_x_y_data(0,5,"��ɫ");*/
		 else
		     Display_x_y_data(0,5,"δ֪");		 
	}
	//delay_ms(200); 
	counter = 0;//�������жϼ�����־		
	TCCR1B = 0X02;// ���÷�Ƶ��Ϊ8
	TCNT1H = 0x63;//����װ���ֵ
    TCNT1L = 0xC0;
	TIMSK |=  BIT(2);//������ж�
	EIMSK |= BIT(2); //���ⲿ�ж�		
	SEI();//�����ж�
}