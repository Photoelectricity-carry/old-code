#include<reg52.h>
extern  unsigned char power; 
extern  unsigned int rgb[4],rgba[3];
extern  unsigned char zx,th0;
unsigned char sxy;
unsigned int gggg;
sbit S0=P1^5; //��λ����
sbit S1=P1^6;
sbit S2=P3^4;
sbit S3=P3^0;
sbit OE=P1^7;
display(unsigned int x);/////////////////
time0() interrupt 1//�����ж�������߱Ƚϰ����������Ӧ�Ӵ�����
{     
     TR1=0;//ֹͣ������
     gggg=0x00;//�������󷵻�ֵ
     TR0=0;//ֹͣ��ʱ��
     ET0=0;//���ж� 
     ET1=0;//�ؼ�����       
}


time1() interrupt 3//��ɫ����ͣ��
{unsigned int yx;
 
  if(sxy=='o')
    {
    TH0=0;TL0=0; 
    TH1=0xf0;TL1=0xf0;//Ӧ����һ��ֵ
    TR1=1;TR0=1;ET0=1;ET1=1;
     sxy='s';   
    }
  else {ET0=0;ET1=0;TR0=0;TR1=0;gggg=TH0;gggg=((gggg<<8)|TL0);  }//�˴�Ӧ��TL���ڵ�λ
         //оƬ�ķֱ���10λ��12λӦȡֵ����ֵԽ��Խ������ֵԽСԽ��
}

close()//�رյ�Դ����
{S0=S1=0;}
open(unsigned char x)//ѡ����ɫ����
{     if(x=='r'){S2=0;S3=0;} 
 else if(x=='g'){S2=1;S3=1;} 
 else if(x=='b'){S2=0;S3=1;}
 else if(x=='w'){S2=1;S3=0;}  
}
precision(unsigned char x)//����ѡ����
{
 if(x=='l')//2%
  {S0=0;S1=1;} 
 else if(x=='o')//20%
  {S0=1;S1=0;}
 else if(x=='h')//100%
  {S0=S1=1;}
}

s_time0()
{sxy='o';//������������־
 TH0=0x00;TL0=0x00;
 TH1=0xfF;TL1=0xfF;//��������жϵ�һ��Ϊ����ʱ��
 TR1=1;//����������0
 TR0=1;//������ʱ��
 ET0=1;//��ʱ���ж�����
 ET1=1;//�������ж����� 
}
w_transform()
{
          if((TR1==0))//���ֹͣ������������²���
              { 
                if(zx==0)
                   { precision('h');
                     open('r');//ѡ���ת��
                     s_time0();//������ɫʶ��
                     zx++;//close(); 
                    } 
                else if(zx==1)
                    {rgb[0]=gggg; 
                     open('g');//ѡ���ת��
                     s_time0();//������ɫʶ��
                     zx++;//close(); 
                    }

                 else if(zx==2)
                    { rgb[1]=gggg; 
                      open('b');//ѡ���ת��
                      s_time0();//������ɫʶ��
                      zx++; 
                    }
           
                 else if(zx==3)//����ɫʶ��
                    {rgb[2]=gggg;
                     open('w'); 
                     s_time0();  
                     zx++;
                     }
                 else if(zx==4)
                    {
                     rgb[3]=gggg; 
                     zx=0;
                     close();                            
                    }
     }
 power++;
}
/*�˶γ���Ϊ�Լ��������ش�������������ʱ�� zZZ*/
