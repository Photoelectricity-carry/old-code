
#include<reg52.h>
#include<absacc.h>
#include<intrins.h>
 unsigned char power=0;
 unsigned int rgb[4];
 unsigned char zx,th0=0xf9;
 float rx=1,gx=1,bx=1;//����ϵ�� 
 unsigned int x,y,z; 
 sbit REST=P2^2;//���縴λ
 sbit POWR=P1^7;//����
 sbit POWL=P2^0;//����
 sbit TEST=P2^1;//��·��⣿
 sbit BPH =P3^2;//��ƽ��� LED�� 
 sbit BCS =P3^3;//�������� 
 sbit OE=P1^7;


 bit zhb1;
 bit zhb2;
///////////////////////////
delay()
{
unsigned long x;
 for(x=0;x<10000;x++)
   {}


}

//////////////////////// 
w_transform();

rest()
{power=0;
 
}



code void (code *dos[])()=
  {w_transform,rest          };


xdos()
  {(*dos[power])();}



zhkz()
{
if(TEST==0)//����ʹ��
  zhb1=1;


}
  
main()

{ static unsigned int del=30,delx;
   OE=0;//TCS230Ƭѡ��Ч        
   Time();//��ʱ������ 
    
 //  zhb2=1;
   delay(); 
   while(1)
        {
          
          if(delx==0)
            {        
              if(BPH==0)  
                 {zhb2=1;delx=5000;}   
              if(BCS==0)
                {zhb1=1;delx=5000;}
              if(zx==0)
                 {ysxf(); }  //�������� ת��������ʾ
            
             }
           else delx--;          

         if(zhb1==1)
            {OE=0;
        
                { xdos();del=0;}//����
                    
             if(zx==0)
                  {zhb1=0;OE=1; }  //�������� ת��������ʾ
            }


         
          if(zhb2==1)
            {
              OE=0;
                              

              xdos();//����
             if(zx==0)//��������
                  {zhb2=0; 
                   gx=rgb[1];//����ɫϵ��Ϊ1
                 if(rgb[0]!=0)
                   rx=gx/rgb[0];//��ɫƽ��ϵ��
                 else rx=1;
                 if(rgb[2]!=0)   
                   bx=gx/rgb[2];//��ɫƽ��ϵ��
                 else bx=1; 
                   zhb2=0;  // zhb1=1;
                  OE=1; 
                  }  //��ƽ����ƽ��ϵ��
            }
          
        
     //    zhkz();//��ֵ�жϲ�ѡ����ִ�еĳ���
                                         
        }

}


/*ƫ��ƫ����*/


