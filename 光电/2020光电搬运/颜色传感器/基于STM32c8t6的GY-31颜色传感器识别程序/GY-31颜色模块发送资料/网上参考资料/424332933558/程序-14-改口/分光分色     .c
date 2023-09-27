
#include<reg52.h>
#include<absacc.h>
#include<intrins.h>
 unsigned char power=0;
 unsigned int rgb[4];
 unsigned char zx,th0=0xf9;
 float rx=1,gx=1,bx=1;//红蓝系数 
 unsigned int x,y,z; 
 sbit REST=P2^2;//掉电复位
 sbit POWR=P1^7;//换向
 sbit POWL=P2^0;//换向
 sbit TEST=P2^1;//短路检测？
 sbit BPH =P3^2;//白平衡的 LED灯 
 sbit BCS =P3^3;//启动测试 
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
if(TEST==0)//测试使能
  zhb1=1;


}
  
main()

{ static unsigned int del=30,delx;
   OE=0;//TCS230片选有效        
   Time();//定时器配置 
    
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
                 {ysxf(); }  //结束采样 转换排序显示
            
             }
           else delx--;          

         if(zhb1==1)
            {OE=0;
        
                { xdos();del=0;}//采样
                    
             if(zx==0)
                  {zhb1=0;OE=1; }  //结束采样 转换排序显示
            }


         
          if(zhb2==1)
            {
              OE=0;
                              

              xdos();//采样
             if(zx==0)//采样结束
                  {zhb2=0; 
                   gx=rgb[1];//设绿色系数为1
                 if(rgb[0]!=0)
                   rx=gx/rgb[0];//红色平衡系数
                 else rx=1;
                 if(rgb[2]!=0)   
                   bx=gx/rgb[2];//兰色平衡系数
                 else bx=1; 
                   zhb2=0;  // zhb1=1;
                  OE=1; 
                  }  //白平衡算平衡系数
            }
          
        
     //    zhkz();//键值判断并选择所执行的程序
                                         
        }

}


/*偏红偏蓝蓝*/


