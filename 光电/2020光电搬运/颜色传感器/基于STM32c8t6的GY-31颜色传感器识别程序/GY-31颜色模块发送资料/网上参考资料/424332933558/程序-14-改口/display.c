#include<reg52.h>
#include <string.h>
#include<intrins.h>
/*新板*/
sbit SCK=P3^7; //移位脉冲
sbit RCK=P2^0;
sbit SER=P1^0;//DA
 
/*以下为数码管显示*/

zell()
{
 SER=0;
 SCK=1;
 _nop_();
 _nop_();
 _nop_();
 _nop_(); 
 _nop_();
 _nop_();
 _nop_();
 _nop_(); 
 SCK=0;


}
flas()
{ SER=1;
  SCK=1;
 _nop_();
 _nop_();
 _nop_();
 _nop_(); 
 _nop_();
 _nop_();
 _nop_();
 _nop_(); 
  SCK=0;
}

void byte(unsigned char r) 
{ 
unsigned char i,r1;
for(i=0;i<8;i++)
   {
    r1=r&0x80;
    if(r1==0)
       zell();  
    else flas(); 

    r=r<<1;
   } 
}
display(unsigned int x)
{
 unsigned char year,i;          
 code  unsigned char list[16]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};
                            //   0    1    2    3    4    5    6    7    8    9    a     b   c    d   e   f

         i=x;                  
         year=i&0x0f; 
         byte(list[year]);
         year=(i>>4)&0x0f;//秒
         byte(list[year]);//
        
         i=(x>>8);                     
         year=i&0x0f; 
         byte(list[year]);//
         year=(i>>4)&0x0f;//秒
         byte(list[year]);   
         RCK=1;                    
         RCK=0;

}


/*数码管显示结束*/
