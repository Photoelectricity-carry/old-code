#include <reg51.h>
extern unsigned  char rgb[];
extern float rx,gx,bx; 
//定时器初始化程序
void time()
{
  EA=1;//允许中断
  //ET0=1;//计数中断允许
  TMOD=0X61;//定时器0工作一16位方式定时器1工作方式二计数器
 
 
}

//白平衡
regph()
{
  





}

