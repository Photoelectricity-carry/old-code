#include<reg52.h>
extern  unsigned char power; 
extern  unsigned int rgb[4],rgba[3];
extern  unsigned char zx,th0;
unsigned char sxy;
unsigned int gggg;
sbit S0=P1^5; //移位脉冲
sbit S1=P1^6;
sbit S2=P3^4;
sbit S3=P3^0;
sbit OE=P1^7;
display(unsigned int x);/////////////////
time0() interrupt 1//计数中断如果光线比较暗则容易溢出应加处理方法
{     
     TR1=0;//停止计数器
     gggg=0x00;//计数错误返回值
     TR0=0;//停止定时器
     ET0=0;//关中断 
     ET1=0;//关计数器       
}


time1() interrupt 3//颜色计数停用
{unsigned int yx;
 
  if(sxy=='o')
    {
    TH0=0;TL0=0; 
    TH1=0xf0;TL1=0xf0;//应该赙一个值
    TR1=1;TR0=1;ET0=1;ET1=1;
     sxy='s';   
    }
  else {ET0=0;ET1=0;TR0=0;TR1=0;gggg=TH0;gggg=((gggg<<8)|TL0);  }//此处应加TL放在底位
         //芯片的分辨率10位到12位应取值，，值越大越暗，，值越小越亮
}

close()//关闭电源函数
{S0=S1=0;}
open(unsigned char x)//选择颜色函数
{     if(x=='r'){S2=0;S3=0;} 
 else if(x=='g'){S2=1;S3=1;} 
 else if(x=='b'){S2=0;S3=1;}
 else if(x=='w'){S2=1;S3=0;}  
}
precision(unsigned char x)//精度选择函数
{
 if(x=='l')//2%
  {S0=0;S1=1;} 
 else if(x=='o')//20%
  {S0=1;S1=0;}
 else if(x=='h')//100%
  {S0=S1=1;}
}

s_time0()
{sxy='o';//启动计数器标志
 TH0=0x00;TL0=0x00;
 TH1=0xfF;TL1=0xfF;//进入计数中断第一次为卡定时间
 TR1=1;//启动计数器0
 TR0=1;//启动定时器
 ET0=1;//定时器中断允许
 ET1=1;//计数器中断允许 
}
w_transform()
{
          if((TR1==0))//如果停止计数则进行以下操作
              { 
                if(zx==0)
                   { precision('h');
                     open('r');//选择红转换
                     s_time0();//启动颜色识别
                     zx++;//close(); 
                    } 
                else if(zx==1)
                    {rgb[0]=gggg; 
                     open('g');//选择红转换
                     s_time0();//启动颜色识别
                     zx++;//close(); 
                    }

                 else if(zx==2)
                    { rgb[1]=gggg; 
                      open('b');//选择红转换
                      s_time0();//启动颜色识别
                      zx++; 
                    }
           
                 else if(zx==3)//白颜色识别
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
/*此段程序为以计数器边沿触发启动启动定时器 zZZ*/
