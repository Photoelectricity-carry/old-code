int a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,z;//向下一个颜色目标区域转向的相对转角数
int A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U;//小车上次推物块到相应颜色目标区域的绝对转角数
int first_A = 0,first_B = 0,first_C = 0,first_D = 0,first_E = 0;
int chou_qian_1,chou_qian_2,chou_qian_3,chou_qian_4,chou_qian_5;
int F_h = 7;//G物料区
int F_g = 6;//出发区
int F_f = 5;//F物料区
int F_G = 4;//绿色
int F_W = 3;//白色
int F_R = 2;//红色
int F_B = 1;//黑色
int F_L = 0;//蓝色
char color_G=1, color_W=2, color_R=3,color_B=4, color_L=5;
int  F_f_4=6,F_h_10=7,F_e_16=8;
#include <Servo.h>
int step_flag = 0;
int step_car = 0;

Servo myservo_1;//夹子上手下降
Servo myservo_2;//夹子闭合
Servo myservo_3;//钩子水平轴
Servo myservo_4;//钩子垂直轴

int RIN1 = 10;
int RIN2 = 9;//电机的四个端口

int LIN1 = 5;
int LIN2 = 6;


int FRR,FRL,FLR,FLL,FR,FML,FMR;
long count_left,count_right;

//定义的四个舵机的角度参数
int UA = 15;//最下面
int UB = 50;//方物块时比第一次稍稍高一点
int UC = 80;//最上面

int DA = 34;//完全闭合
int DB = 70;//微微张开防止物块倒
int DC = 155;//完全张开

void setup()
{
  chou_qian_1 = color_L, chou_qian_2 = color_W ,chou_qian_3 = color_R , chou_qian_4 = color_B , chou_qian_5 = color_G;
  A = chou_qian_5 , B = chou_qian_3 , C= chou_qian_1 ;
  D = F_f_4;
  E = chou_qian_2 , F = chou_qian_1 ,G = chou_qian_3 , H = chou_qian_5 , I = chou_qian_4;//B A C E D
  J =F_h_10 ;
  K = chou_qian_1 ,  L = chou_qian_2 , M = chou_qian_5 , N = chou_qian_3 , O = chou_qian_4; // B A E C D
  R =F_e_16 ;//第三环节结束后，回到出发地转角
  Serial.begin(9600);
  myservo_1.attach(8);
  myservo_2.attach(4);
  myservo_3.attach(11);
  myservo_4.attach(12);
  myservo_1.write(UA);//90,130
  myservo_2.write(DC);//140,40
  myservo_3.write(70);
  myservo_4.write(95);
  pinMode(LIN1, OUTPUT);
  pinMode(LIN2, OUTPUT);
  pinMode(RIN1, OUTPUT);
  pinMode(RIN2, OUTPUT);


  
  attachInterrupt(1, Code1, FALLING);//中断打开
  detachInterrupt(1);//中断关闭
  
  attachInterrupt(0, Code2, FALLING);
  detachInterrupt(0);


  
  digitalWrite(LIN1,LOW);//初始两个电机都处于停止状态
  digitalWrite(LIN2,LOW);
  digitalWrite(RIN1,LOW);
  digitalWrite(RIN2,LOW);
}
void loop()
{
  //hunting();
 Stop_car(3000);//在车运行前有3s的停止防止电机乱动
 first_mean();
 //drag_E_block();
 //turn_direction(5);
 Stop_car(3000);
}

void star_car()//开始到达中心
{
  step_car=1;
  if(step_car==1)
  { hunting_go(350,350);step_car = 2;}
  while(step_car==2)
  {hunting();
   get_value();if(FMR == 1&&FML == 1) {step_car = 3;}}
  while( step_car==3)
  { hunting_very_slow_go(41,41);Stop_car(1000);step_car=0; }
}

void grab_ACE() //将ACE收集到一起
 {
  step_car=1;
  if( step_car==1)
 { hunting_go(120,120);step_car=2;}  
  while( step_car==2)
  { hunting_very_slow();
    get_value();if(FR == 1) { step_car=6;break;}}
if( step_car==6)
 {hunting_set_go(30,30);step_car=7;} 
 if( step_car==7)
{ Stop_car(150);claw_open_close(DC,DA,-2);Stop_car(150);step_car=8;}//夹起物块
 if( step_car==8)
 {claw_up_down(UA,UC,2);Stop_car(150);step_car=9;} //抬起夹子
 if( step_car==9)
{ turn_direction(4);Stop_car(150);step_car=10;}
while(step_car==10)
   { hunting();
     get_value();if(FMR==1&&FML==1) {step_car = 11;}}
while( step_car==11)
  { hunting_very_slow_go(41,41);Stop_car(150);step_car=12; }
if( step_car==12)//转到C方向
{ turn_direction(2);hunting_go(120,120);step_car=13;}
while( step_car==13)
  { hunting_very_slow();
     get_value();if(FR==1) { step_car=14;break;}}
if( step_car==14)
 { hunting_set_go(30,30);Stop_car(150);claw_up_down(UC,UB,-2);Stop_car(150);step_car=15;} //放下爪子
if( step_car==15)
 {claw_open_close(DA,DB,1);Stop_car(150);claw_up_down(UB,UA,-1);Stop_car(150);step_car=16;}//微微张开 然后放下
 if( step_car==16)
{ claw_open_close(DB,DA,-1);Stop_car(150);step_car=17;}//加紧爪子
 if( step_car==17)
 { claw_up_down(UA,UC,2);Stop_car(150);step_car=18;} //爪子上升
 if( step_car==18)
{ turn_direction(4);Stop_car(150);step_car=19;}
  while(step_car==19)
   { hunting();
     get_value();if(FMR==1&&FML==1) {step_car = 20;}}
  while( step_car==20)
  { hunting_very_slow_go(41,41);Stop_car(150);step_car=21; }
  if( step_car==21)
{ turn_direction(2);hunting_go(120,120);step_car=22;}//转到E方向
while( step_car==22)
  { hunting_very_slow();
     get_value();if(FR==1 ) { step_car=23;break;}}
if( step_car==23)
 { hunting_set_go(30,30);Stop_car(150);claw_up_down(UC,UB,-2);Stop_car(150);step_car=24;} //微微放下爪子
if( step_car==24)
 {claw_open_close(DA,DB,1);Stop_car(150);claw_up_down(UB,UA,-1);Stop_car(150);step_car=25;}   //微微张开 然后完全放下
 if( step_car==25)
{claw_open_close(DB,DA,-1);Stop_car(150);step_car=27;}//加紧爪子
 if( step_car==27)
{ turn_direction(4);Stop_car(150);step_car=28;}
  while(step_car==28)
   { hunting();
     get_value();if(FMR==1&&FML == 1) {step_car = 29;}}
  while( step_car==29)
  { hunting_very_slow_go(41,41);Stop_car(150);step_car=0;}///夹子处入45的高度
 }
  void go_back_set_one()//放置ACE中最底部物块E
{
     step_car = 1;
 while(step_car==1)
       { Stop_car(150);step_car = 2;}
 while(step_car==2)
       {hunting_go(120,120); step_car = 4;}
 while(step_car==4)
       { hunting();
         get_value();if( FMR== 1&&FML==1 ) { hunting_very_slow_go(50,50);Stop_car(150);step_car=5;}}//4.5
 while(step_car==5)
       {claw_open_close(DA,DB,1);Stop_car(150);step_car = 6;}//夹子下降 然后 微微张开           
 while(step_car==6)         
       {claw_up_down(UA,UB,1);Stop_car(150);claw_open_close(DB,DA,-1);Stop_car(150);step_car = 8;}
 while(step_car==8)
       {claw_up_down(UB,UC,1); Stop_car(150);blind_back(100,100);Stop_car(150);step_car = 9;}         
 while(step_car==9)
       {turn_direction(4);Stop_car(150);step_car = 10;}
 while(step_car==10)
       { hunting_go(50,50);step_car = 11;}
 while(step_car==11)
       { hunting();
         get_value();if( FMR == 1&&FML == 1) { hunting_very_slow_go(45,45);Stop_car(150);step_car = 0;}}/////夹子处入90的高度
}
 void go_back_set_two()//放置ACE中最中部物块C
{  
     step_car = 1;
 while(step_car==1)
       { Stop_car(150);step_car = 2;}
 while(step_car==2)
       { hunting_go(120,120);step_car = 4;}
 while(step_car==4)         
       { hunting();
         get_value();if( FMR== 1&&FML==1 ) { hunting_very_slow_go(50,50);Stop_car(150);step_car=5;}}//4.5
 while(step_car==5)
       {claw_up_down(UC,UA,-1);Stop_car(150);claw_open_close(DA,DB,1);;Stop_car(150);step_car = 6;}//夹子下降到嘴下面   然后 微微张开
 while(step_car==6)         
       {claw_up_down(UA,UB,2);Stop_car(150);claw_open_close(DB,DA,-1);Stop_car(150);step_car = 7;}//夹子上升   然后 加紧
 while(step_car==7)         
       {claw_up_down(UB,UC,1);Stop_car(150);blind_back(100,100);Stop_car(150);step_car = 8;}         
 while(step_car==8)
       { turn_direction(4);Stop_car(150);step_car = 9;}
 while(step_car==9)
       { hunting_go(50,50);step_car = 10;}     
 while(step_car==10)
       { hunting();
         get_value();if( FMR == 1&&FML==1) { hunting_very_slow_go(45,45);Stop_car(150);step_car = 0;}}//夹子处入90的高度
}
void set_first_special_block()//放置ACE中最上部物块A
{ 
     step_car = 1;
while(step_car==1)
       { Stop_car(150);step_car = 2;}
while(step_car==2)
       { hunting_go(120,120);step_car = 4;}
 while(step_car==4)         
       { hunting();
         get_value();if( FMR == 1&&FML==1 ) { hunting_very_slow_go(50,50);Stop_car(150);step_car=5;}}
 while(step_car==5)     
 {claw_up_down(UC,UA,-1);Stop_car(150);claw_open_close(DA,DC,6);Stop_car(150);step_car = 13;}//夹子降到最下面 然后完全张开
 while(step_car==13)
       {blind_back(100,100);Stop_car(150);step_car = 14;} 
 while(step_car==14)
       {  turn_direction(4);Stop_car(150);step_car = 15;}
 while(step_car==15)
       {  hunting_go(50,50);step_car = 16;}
 while(step_car==16)
       {  hunting();
          get_value();if(FMR==1&&FML==1){hunting_very_slow_go(45,45);Stop_car(150);step_car = 0;}}//夹子降到最下面
}
void claw_up_down(int s,int d,int Speed)
{
  int i;
  if(Speed > 0)//上升
  {
    for(i=s;i<=d;i+=Speed){
    myservo_1.write(i);
    delay(40);}
  }
  if(Speed < 0)//下降
  {
    for(i=s;i>=d;i+=Speed)
    {myservo_1.write(i);
    delay(40);}
  }
}
void claw_open_close(int s,int d,int Speed)
{
  int i;
  if(Speed > 0)
  {
    for(i=s;i<=d;i+=Speed)//夹子张开
    {myservo_2.write(i);
    delay(40);}
  }
  if(Speed < 0)
  {
    for(i=s;i>=d;i+=Speed)//夹子闭合
    {myservo_2.write(i);
    delay(40);}
  }
}
void get_value(){//读传感器值
  FRR=(analogRead(A4)>=650? 0:1);
  FRL=(analogRead(A3)>=650? 0:1);
  FLR=(analogRead(A2)>=500? 0:1);
  FLL=(analogRead(A1)>=500? 0:1);
  FR =(analogRead(A5)>=450? 0:1);
  FMR=(analogRead(A10)>=650? 0:1);
  FML=(analogRead(A11)>=500? 0:1);
}
void hunt(int val_left,int val_right)
{
  analogWrite(LIN1,val_left);
  digitalWrite(LIN2,LOW);
  analogWrite(RIN1,val_right);
  digitalWrite(RIN2,LOW);
}
void hunting()//普通巡线
{
 get_value();
 if(FLL==0 && FRR==1) hunt(100,56);
 else if(FLL==1 && FRR==0) hunt(60,97);
 else if( FRL==1 && FLR ==0 ) hunt(100,77);
 else if(FLR==1 && FRL ==0 ) hunt(80,97);
 else if((FLR==1 && FRL==1)||(FLR==0 && FRL==0)) hunt(100,97);
 else if((FLL==1 && FRR==1)||(FLL==0 && FRR==0)) hunt(100,97);
}
void hunting_set()//只用于牙将物块先前推时的巡线
{
 get_value();
 if(FLL==0 && FRR==1) hunt(50,18);
 else if(FLL==1 && FRR==0) hunt(20,48);
 else if( FRL==1 && FLR ==0 ) hunt(50,28);
 else if(FLR==1 && FRL ==0 ) hunt(30,48);
 else if((FLR==1 && FRL==1)||(FLR==0 && FRL==0)) hunt(50,48);
 else if((FLL==1 && FRR==1)||(FLL==0 && FRR==0)) hunt(50,48);
}
void hunting_very_slow()
{
  get_value();
  if(FLL==0 && FRR==1) hunt(70,35);
  else if(FLL==1 && FRR==0) hunt(35,67);
  else if( FRL==1 && FLR ==0 ) hunt(69,47);
  else if(FLR==1 && FRL ==0 ) hunt(50,67);
  else if((FLR==1 && FRL==1)||(FLR==0 && FRL==0)) hunt(70,67);
  else if((FLL==1 && FRR==1)||(FLL==0 && FRR==0)) hunt(70,67);
}
void hunting_go(float x,float y)//普通编码器巡线前进
{
  count_left =0;
  count_right =0;

  
  attachInterrupt(1, Code1, FALLING);
  attachInterrupt(0, Code2, FALLING);

  
    while(1)
  { 
     hunting();
    if(count_left/5 > x && count_right/5 > y)
    {
      break;
    }
  }

  
  detachInterrupt(3);
  detachInterrupt(2);
}

void hunting_set_go(float x,float y)//普通编码器巡线前进
{
  count_left =0;
  count_right =0;
  attachInterrupt(1, Code1, FALLING);
  attachInterrupt(0, Code2, FALLING);
    while(1)
  { 
     hunting_set();
    if(count_left/5 > x && count_right/5 > y)
    {
      break;
    }
  }
  detachInterrupt(3);
  detachInterrupt(2);
}

void hunting_very_slow_go(float x,float y)
{
  count_left =0;
  count_right =0;
  attachInterrupt(1, Code1, FALLING);
  attachInterrupt(0, Code2, FALLING);
    while(1)
  { 
     hunting_very_slow();
    if(count_left/5 > x && count_right/5 > y)
    {
      break;
    }
  }
  detachInterrupt(0);
  detachInterrupt(1);
}

void blind_back(float x ,float y)//编码器不巡线后退
{   count_left =0;
    count_right =0;
    attachInterrupt(1, Code1, FALLING);
    attachInterrupt(0, Code2, FALLING);
    while(1)
  { 
     if(count_left/5 < x)
    {
       digitalWrite(LIN1,LOW);
       analogWrite(LIN2,69);
    }
     if(count_right/5 < y)
    {
       digitalWrite(RIN1,LOW); 
       analogWrite(RIN2,70);
    }
    if(count_left/5 > x && count_right/5 > y)
    {
      Stop_car(20);
      break;
    }
  }
  detachInterrupt(0);
  detachInterrupt(1);
}
void Stop_car(int x)
{
  digitalWrite(LIN1,LOW);
  digitalWrite(LIN2,LOW);
  digitalWrite(RIN1,LOW);
  digitalWrite(RIN2,LOW);
  delay(x);
}

void turn_left(float x ,float y)//原地左转
{   count_left =0;
    count_right =0;
   attachInterrupt(1, Code1, FALLING);
   attachInterrupt(0, Code2, FALLING);
    while(1)
  { 
     if(count_left/5 < x)
    {
       analogWrite(LIN2,75);
       digitalWrite(LIN1,LOW);
    }
     if(count_right/5 < y)
    {
       analogWrite(RIN1,65);
       digitalWrite(RIN2,LOW);
    }
    if(count_left/5 >= x || count_right/5 >= y)
    {
      Stop_car(200);
      break;
    }
  }
  detachInterrupt(1);
  detachInterrupt(0);
}


void turn_right(float x ,float y)//原地右转
{   
    count_left =0;
    count_right =0;
    attachInterrupt(1, Code1, FALLING);
    attachInterrupt(0, Code2, FALLING);
    while(1)
  { 
     if(count_left/5 < x)
    {
       analogWrite(LIN1,80);
       digitalWrite(LIN2,LOW);
    }
     if(count_right/5 < y)
    {
       analogWrite(RIN2,72);
       digitalWrite(RIN1,LOW);
    }
    if(count_left/5 > x || count_right/5 > y)
    {
      Stop_car(200);
      break;
    }
  }
  detachInterrupt(0);
  detachInterrupt(1);
}
void turn_direction(int a)//转向
 { 
   if    (a>7) {a=a-8;}
   else if(a<0) {a=a+8;}
   if(a==0){Stop_car(500);}
   else if(a==1){Stop_car(500);turn_left(73,73);Stop_car(500);}
   else if(a==2){Stop_car(500);turn_left(132,132);Stop_car(500);}
   else if(a==3){Stop_car(500);turn_left(198,198);Stop_car(500);}
   else if(a==4){Stop_car(500);turn_right(248,248);Stop_car(500);}
   else if(a==5){Stop_car(500);turn_right(209,208);Stop_car(500);}
   else if(a==6){Stop_car(500);turn_right(139,139);Stop_car(500);}
   else if(a==7){Stop_car(500);turn_right(68,68);Stop_car(500);}
} 
void drag_A() 
{ 
  for( int pos = 70; pos >= 30; pos --)  
  {
    myservo_3.write(pos ); 
    delay(20);                       
  }
  for(int pos = 95;pos>= 80;pos--)
  {
    myservo_4.write(pos);
    delay(10);
  }
}
void drag_B() 
{ 
  for(int pos = 70;pos>= 55;pos--)
  {
    myservo_3.write(pos);
    delay(20);
  }
  for(int pos = 95;pos>= 80;pos--)
  {
    myservo_4.write(pos);
    delay(10);
  }
}
void drag_C() 
{
  for( int pos = 70; pos >= 60; pos --)  
  {                                  
    myservo_3.write(pos ); 
    delay(20);                       
  }
  for(int pos = 95;pos>= 80;pos--)
  {
    myservo_4.write(pos);
    delay(10);
  }
}
void drag_E() 
{
  for( int pos = 70; pos >= 20; pos --)  
  {                                  
    myservo_3.write(pos ); 
    delay(20);                       
  }
  for(int pos = 95;pos>= 80;pos--)
  {
    myservo_4.write(pos);
    delay(10);
  }
}
void set_block_middle_A() 
{ 
   for( int pos = 35; pos < 55; pos ++)  
  {                                  
    myservo_3.write(pos ); 
    delay(20);                       
  }                                                
}
void set_block_middle_B() 
{                                 
  for( int pos = 55; pos >= 40; pos --)  
  {                                  
    myservo_3.write(pos ); 
    delay(10);                       
  }                                                   
}
void set_block_middle_C() 
{                                 
  for( int pos = 60;pos >= 45; pos --)  
  {                                  
    myservo_3.write(pos ); 
    delay(10);                       
  }                                                   
}
void set_block_middle_E() 
{
  for( int pos = 30; pos <= 55; pos ++)  
  { 
    myservo_3.write(pos ); 
    delay(10);                       
  }      
}
void release_block() 
{ 
  
  for( int pos = 80; pos <= 95; pos ++)  
  {                                  
    myservo_4.write(pos ); 
    delay(50);                       
  }
  delay(500);
  myservo_3.write(70);
  delay(200);
}
void drag_A_block()//夹物块前夹子放到最低处并且完全张开
{
    step_car =1;
  while(step_car==1)
       {claw_up_down(UA,UC,4);Stop_car(150);step_car=2;}  
  while(step_car==2)
       { hunting_go(120,120);step_car=3;}
  while(step_car==3)
       { hunting();
         get_value();if(FR == 1 ){step_car = 4;}}//前到中线
  while(step_car==4)
       {hunting();
        get_value();if(FML==1&&FMR==1){step_car = 5;}}
  while(step_car==5)
        {hunting_very_slow();
        get_value();if(FR==1){step_car=6;}}
  while(step_car==6)  
       {hunting_set_go(83,83);Stop_car(150);step_car = 7;}
  while(step_car==7)
       { drag_A();Stop_car(100);step_car = 8;}
  while(step_car==8)
       { blind_back(100,100);Stop_car(150);step_car =9;}
  while(step_car==9)
       { set_block_middle_A();Stop_car(150);step_car =10;}    
  while(step_car==10)
       { release_block();Stop_car(150);step_car =11;}    
  while(step_car==11)
       { claw_up_down(UC,UA,-4);hunting_very_slow_go(50,50);Stop_car(150);step_car =12;}//夹子下降  
  while(step_car==12)
       {claw_open_close(DC,DA,-6);Stop_car(80);claw_up_down(UA,UC,1);Stop_car(80);step_car =13;}//夹子加紧 然后上升
  while(step_car==13)
       { turn_direction(4);Stop_car(150);step_car =14;}
  while(step_car==14)
       { hunting_go(200,200);step_car=15;}
  while(step_car==15)
       { hunting();
         get_value();if(FMR == 1&&FML==1) { hunting_very_slow_go(45,45);Stop_car(80);step_car = 0;}}//夹子处于90
}
void drag_B_block()//夹物块前夹子放到最低处并且完全张开
{
    step_car =1;
  while(step_car==1)
       {/*claw_up_down(UA,UC,4);*/Stop_car(150);step_car=2;}  
  while(step_car==2)
       { hunting_go(120,120);step_car=3;}
  while(step_car==3)
       { hunting();
         get_value();if(FR == 1 ){ step_car = 4;}}//前到中线
  while(step_car==4)
       {hunting();
        get_value();if(FML==1&&FMR==1){step_car = 5;}}//后到中心
  while(step_car==5)
       {hunting_very_slow();
       get_value();if(FR==1){step_car=6;}}
  while(step_car==6)  
       {hunting_set_go(62,62);Stop_car(150);step_car = 7;}
  while(step_car==7)         
       { drag_B();step_car = 8;}
  while(step_car==8)
       { blind_back(100,100);Stop_car(150);step_car =9;}
  while(step_car==9)
       { set_block_middle_B();Stop_car(150);step_car =10;}    
  while(step_car==10)
       { release_block();Stop_car(150);step_car =11;}    
  while(step_car==11)
       {/*claw_up_down(UC,UA,-1);*/hunting_very_slow_go(50,50);Stop_car(150);step_car =12;}//夹子下降
  while(step_car==12)
       {claw_open_close(DC,DA,-6);Stop_car(150);claw_up_down(UA,UC,1);Stop_car(150);step_car =13;}//夹子加紧 然后上升
  while(step_car==13)
       { turn_direction(4);Stop_car(150);step_car =14;}
  while(step_car==14)
       { hunting_go(180,180);step_car=15;}
  while(step_car==15)
       { hunting();
         get_value();if(FMR == 1&&FML==1) { hunting_very_slow_go(45,45);Stop_car(150);step_car = 0;}}//夹子处于90
}
void drag_C_block() //夹物块前夹子放到最低处并且完全张开
{
    step_car =1;
  while(step_car==1)
       {/*claw_up_down(UA,UC,4);*/Stop_car(150);step_car=2;}  
  while(step_car==2)
       { hunting_go(120,120);step_car=3;}
  while(step_car==3)
       { hunting();
         get_value();if(FR == 1 ){ step_car = 4;}}//前到中线
  while(step_car==4)
       {hunting();
        get_value();if(FML==1&&FMR==1){step_car = 5;}}//后到中心
  while(step_car==5)
       {hunting_very_slow();if(FR==1){step_car=6;}}
  while(step_car==6)
       {hunting_set_go(90,90);Stop_car(1500);step_car = 7;}
  while(step_car==7)
       { drag_C();step_car = 8;}
  while(step_car==8)
       { blind_back(100,100);Stop_car(150);step_car =9;}
  while(step_car==9)
       { set_block_middle_C();Stop_car(150);step_car =10;}    
  while(step_car==10)
       { release_block();Stop_car(150);step_car =11;}    
  while(step_car==11)
       { /*claw_up_down(UC,UA,-4);*/hunting_very_slow_go(50,50);Stop_car(150);step_car =12;}//夹子下降  
  while(step_car==12)
       {claw_open_close(DC,DA,-6);Stop_car(150);claw_up_down(UA,UC,1);Stop_car(150);step_car =13;}//夹子加紧 然后上升  
  while(step_car==13)
       { turn_direction(4);Stop_car(150);step_car =14;}          
  while(step_car==14)
       { hunting_go(200,200);step_car=15;}
  while(step_car==15)
       { hunting();
         get_value();if(FMR == 1&&FML==1) { hunting_very_slow_go(45,45);Stop_car(150);step_car = 0;}}  //夹子处于90
}
void drag_D_block() //夹物块前夹子放到最低处并且完全张开
{
    step_car =2; 
  while(step_car==2)
       { hunting_go(120,120);step_car=3;}
  while(step_car==3)
       { hunting();
         get_value();if(FR == 1 ){ step_car = 4;}}//前到中线
  while(step_car==4)
       {hunting();
        get_value();if(FML==1&&FMR==1){step_car = 5;}}//后到中心
  while(step_car==5)
       {hunting_very_slow();
        get_value();if(FR==1){step_car=6;}}
  while(step_car==6)
       {hunting_set_go(150,150);Stop_car(150);step_car = 8;}   
  while(step_car==8)
       {claw_open_close(DC,DA,-6);Stop_car(150);claw_up_down(UA,UC,1);Stop_car(150);step_car =9;} //夹子加紧 然后上升   
  while(step_car==9)
       { turn_direction(4);Stop_car(150);step_car =10;}
  while(step_car==10)
       { hunting_go(330,330);step_car=11;}
  while(step_car==11)
       { hunting();
         get_value();if(FMR == 1&&FML==1) { hunting_very_slow_go(45,45);Stop_car(150);step_car = 0;}}  //夹子处于90
}
void drag_E_block() //夹物块前夹子放到最低处并且完全张开
{
    step_car =1;
  while(step_car==1)
       {claw_up_down(UA,UC,4);Stop_car(150);step_car=2;}  
  while(step_car==2)
       { hunting_go(120,120);step_car=3;}
  while(step_car==3)
       { hunting();
         get_value();if(FR == 1 ){ step_car = 4;}}//前到中线
  while(step_car==4)
       {hunting();
        get_value();if(FML==1&&FMR==1){step_car = 5;}}//后到中心
  while(step_car==5)
        {hunting_very_slow();
        get_value();if(FR==1){step_car=6;}}
  while(step_car==6)
       {hunting_set_go(118,118);Stop_car(1500);step_car = 7;}
  while(step_car==7) 
       { drag_E();Stop_car(150);step_car = 8;}
  while(step_car==8)
       { blind_back(100,100);Stop_car(150);step_car =9;}
  while(step_car==9)
       { set_block_middle_E();Stop_car(150);step_car =10;}    
  while(step_car==10)
       { release_block();Stop_car(150);step_car =11;}    
  while(step_car==11)
       {claw_up_down(UC,UA,-1); hunting_very_slow_go(50,50);Stop_car(150);step_car =12;}//夹子下降
  while(step_car==12)
       { claw_open_close(DC,DA,-6);Stop_car(150);claw_up_down(UA,UC,1);Stop_car(150);step_car =13;} //夹子加紧 然后上升   
  while(step_car==13)
       { turn_direction(4);step_car =14;}
  while(step_car==14)
       { hunting_go(250,250);step_car=15;}
  while(step_car==15)
       { hunting();
         get_value();if(FMR == 1&&FML==1) { hunting_go(45,45);Stop_car(150);step_car = 0;}}//夹子处于90
}
 void set_first_block()//取物块后放第一层
{ 
     step_car = 1;
while(step_car==1)
       { Stop_car(150);step_car = 2;}
while(step_car==2)
       { hunting_go(120,120);step_car = 4;}
while(step_car==4)
 {hunting();get_value();
   if(FML == 1&&FMR == 1){ hunting_very_slow_go(50,50);Stop_car(150);step_car=6;}}            
while(step_car==6)
  {claw_up_down(UC,UA,-1);Stop_car(300);step_car = 10;}//夹子下降
 while(step_car==10)
       {claw_open_close(DA,DC,4);Stop_car(300);step_car =11;}//夹子完全张开
 while(step_car==11)
       { blind_back(100,100);Stop_car(150);step_car = 12;}    
 while(step_car==12)
       { turn_direction(4);Stop_car(150);step_car = 13;}
 while(step_car==13)
       {  hunting_go(50,50);step_car = 16;}
 while(step_car==16)
       {  hunting();
          get_value();if(FML==1&&FMR==1){hunting_very_slow_go(45,45);step_car = 17;}}
 while(step_car==17)
       {  Stop_car(150);step_car = 0;}     
}
void set_second_blockA()//取物块后放第二层 3cheng
{ 
     step_car = 1;
while(step_car==1)
       {Stop_car(150);step_car = 2;}
while(step_car==2)
       {hunting_go(120,120);step_car = 3;}
 while(step_car==3)
       { hunting();
         get_value();if(FR == 1 ){ step_car = 4;}}
 while(step_car==4)     
 { Stop_car(150);claw_up_down(UC,UA,-1);Stop_car(300);step_car = 6;} //夹子下降
 while(step_car==6)           
     {claw_open_close(DA,DC,4);Stop_car(300);step_car =11;}//夹子完全张开
 while(step_car==11)         
       { blind_back(55,55);Stop_car(150);step_car = 12;}    
 while(step_car==12)
       { turn_direction(4);step_car = 16;}
 while(step_car==16)
       {  hunting_very_slow();
          get_value();if(FMR==1&&FML==1){hunting_very_slow_go(45,45);Stop_car(150);step_car = 17;}}
 while(step_car==17)
       {  Stop_car(150);step_car = 0;}
}







void set_second_blockB()//应该两层
{
     step_car = 1;
while(step_car==1)
       {Stop_car(150);step_car = 2;}
while(step_car==2)
       { hunting_go(120,120);step_car = 3;}
 while(step_car==3)
       { hunting();
         get_value();if(FR == 1 ){ step_car = 4;}}//从过中线
 while(step_car==4)
 { hunting();get_value();
   if(FML == 1&&FMR == 1 ){hunting_set_go(65,65);Stop_car(150);step_car =6;}} 
while(step_car==6)
   {claw_up_down(UC,UB,-1);Stop_car(150);step_car = 7;}
 while(step_car==7)
     {claw_open_close(DA,DB,1);Stop_car(150);claw_up_down(UB,UA,-1);Stop_car(150);claw_open_close(DB,DA,-1);Stop_car(150);step_car =8;}
 while(step_car==8)
       { hunting_set();get_value();
     if(FR==1){Stop_car(150);step_car =13;}}
while(step_car==13)
       {claw_open_close(DA,DC,2);Stop_car(500);blind_back(80,80);step_car=14;} 
 while(step_car==14)
       { turn_direction(4);step_car = 15;}
 while(step_car==15)
       {  hunting_go(240,240);step_car = 16;}
 while(step_car==16)
       {  hunting();
          get_value();if(FMR==1&&FML==1){hunting_very_slow_go(45,45);step_car = 17;}}
 while(step_car==17)
       {  Stop_car(150);step_car = 0;}
}
void set_third_block()
{
  step_car = 1;
  while(step_car==1)
        {Stop_car(150);step_car = 2;}
  while(step_car==2)
        {hunting_go(120,120);step_car = 3;}
  while(step_car==3)
        {hunting_set();get_value();if(FR == 1){hunting_set_go(20,20);Stop_car(300);step_car = 4;}}
  while(step_car==4)
        {claw_up_down(UC,UB,-2);Stop_car(150);step_car=5;}
  while(step_car==5)
        {claw_open_close(DA,DB,1);Stop_car(150);claw_up_down(UB,UA,-1);Stop_car(150);step_car=6;}////1
  while(step_car==6)
        {claw_open_close(DB,DA,-1);Stop_car(150);claw_up_down(UA,UC,2);Stop_car(150);step_car=7;}
  while(step_car==7)
        {hunting_very_slow();get_value();
      if(FML==1&&FMR==1){hunting_set_go(65,65);Stop_car(150);step_car=8;}}
  while(step_car==8)
        {claw_up_down(UC,UB,-1);Stop_car(150);claw_open_close(DA,DB,1);Stop_car(150);step_car=9;}
  while(step_car==9)
        {claw_up_down(UB,UA,-1);Stop_car(150);claw_open_close(DB,DA,-1);Stop_car(150);step_car=10;}
  while(step_car==10)
        {hunting_set();get_value();
        if(FR==1){Stop_car(150);step_car=12;}}
   while(step_car==12)
        {claw_open_close(DA,DC,6);Stop_car(150);step_car=15;}
   while(step_car==15)
         {blind_back(80,80);step_car=16;}
   while(step_car==16)
         {turn_direction(4);step_car=17;}
   while(step_car==17)
         {hunting_go(240,240);step_car=18;}
   while(step_car==18)
         {hunting();get_value();
         if(FMR==1&&FML==1){hunting_very_slow_go(45,45);step_car=19;}}
   while(step_car==19)
         {Stop_car(150);step_car=0;}//夹子处于最低
}











void come_back()
{
  step_car =1;
  while(step_car==1)
       { hunting_go(120,120);step_car=2;}
   while(step_car==2)
       {hunting();get_value();if(FMR==1&&FML==1)
                              {hunting_go(50,50);step_car=3;}
     }
    while(step_car==3)
    {hunting();get_value();if(FMR==1&&FML==1)
                             {hunting_go(60,60);step_car=4;}
    }
   while(step_car==4)
   {
     Stop_car(1000);step_car=4;
   }
}
void first_mean()
{
  if     (A==1){a=0;A=F_G;first_A=1;}
  else if(A==2){a=7;A=F_W;first_B=1;}
  else if(A==3){a=6;A=F_R;first_C=1;}
  else if(A==4){a=5;A=F_B;first_D=1;}
  else if(A==5){a=4;A=F_L;first_E=1;}
  
  if     (B==1){b=F_G-A+4;B=F_G;first_A=1;}
  else if(B==2){b=F_W-A+4;B=F_W;first_B=1;}
  else if(B==3){b=F_R-A+4;B=F_R;first_C=1;}
  else if(B==4){b=F_B-A+4;B=F_B;first_D=1;}
  else if(B==5){b=F_L-A+4;B=F_L;first_E=1;}
  
  if     (C==1){c=F_G-B+4;C=F_G;first_A=1;}
  else if(C==2){c=F_W-B+4;C=F_W;first_B=1;}
  else if(C==3){c=F_R-B+4;C=F_R;first_C=1;}
  else if(C==4){c=F_B-B+4;C=F_B;first_D=1;}
  else if(C==5){c=F_L-B+4;C=F_L;first_E=1;}
  
  if(D==6){d=F_f-C+4;D=F_f;}
  
  if     (E==1){e=F_G-F_f+4;E=F_G;}
  else if(E==2){e=F_W-F_f+4;E=F_W;}
  else if(E==3){e=F_R-F_f+4;E=F_R;}
  else if(E==4){e=F_B-F_f+4;E=F_B;}
  else if(E==5){e=F_L-F_f+4;E=F_L;}
  
  if     (F==1){f=F_G-F_f+4;F=F_G;}
  else if(F==2){f=F_W-F_f+4;F=F_W;}
  else if(F==3){f=F_R-F_f+4;F=F_R;}
  else if(F==4){f=F_B-F_f+4;F=F_B;}
  else if(F==5){f=F_L-F_f+4;F=F_L;}
  
  if     (G==1){g=F_G-F_f+4;G=F_G;}
  else if(G==2){g=F_W-F_f+4;G=F_W;}
  else if(G==3){g=F_R-F_f+4;G=F_R;}
  else if(G==4){g=F_B-F_f+4;G=F_B;}
  else if(G==5){g=F_L-F_f+4;G=F_L;}
  
  if      (H==1){h=F_G-F_f+4;H=F_G;}
  else if(H==2){h=F_W-F_f+4;H=F_W;}
  else if(H==3){h=F_R-F_f+4;H=F_R;}
  else if(H==4){h=F_B-F_f+4;H=F_B;}
  else if(H==5){h=F_L-F_f+4;H=F_L;}
  
  if     (I==1){i=F_G-F_f+4;I=F_G;}
  else if(I==2){i=F_W-F_f+4;I=F_W;}
  else if(I==3){i=F_R-F_f+4;I=F_R;}
  else if(I==4){i=F_B-F_f+4;I=F_B;}
  else if(I==5){i=F_L-F_f+4;I=F_L;}
  
  if(J == 7) {j=F_h-I+4;J=F_h;}
  
  if      (K == 1) {k=F_G - F_h + 4;K=F_G;}
  else if (K == 2) {k=F_W - F_h + 4;K=F_W;}
  else if (K == 3) {k=F_R - F_h + 4;K=F_R;}
  else if (K == 4) {k=F_B - F_h + 4;K=F_B;}
  else if (K == 5) {k=F_L - F_h + 4;K=F_L;}
  
  if      (L == 1) {l=F_G - F_h + 4;L=F_G;}
  else if (L == 2) {l=F_W - F_h + 4;L=F_W;}
  else if (L == 3) {l=F_R - F_h + 4;L=F_R;}
  else if (L == 4) {l=F_B - F_h + 4;L=F_B;}
  else if (L == 5) {l=F_L - F_h + 4;L=F_L;}
  
  if      (M == 1) {m=F_G - F_h +4;M=F_G;}
  else if (M == 2) {m=F_W - F_h +4;M=F_W;}
  else if (M == 3) {m=F_R - F_h +4;M=F_R;}
  else if (M == 4) {m=F_B - F_h +4;M=F_B;}
  else if (M == 5) {m=F_L - F_h +4;M=F_L;}
  
  if      (N == 1) {n=F_G - F_h +4;N=F_G;}
  else if (N == 2) {n=F_W - F_h +4;N=F_W;}
  else if (N == 3) {n=F_R - F_h +4;N=F_R;}
  else if (N == 4) {n=F_B - F_h +4;N=F_B;}
  else if (N == 5) {n=F_L - F_h +4;N=F_L;}
  
  if      (O == 1) {o=F_G - F_h +4;O=F_G;}
  else if (O == 2) {o=F_W - F_h +4;O=F_W;}
  else if (O == 3) {o=F_R - F_h +4;O=F_R;}
  else if (O == 4) {o=F_B - F_h +4;O=F_B;}
  else if (O == 5) {o=F_L - F_h +4;O=F_L;}
  
  if (a>7) a=a-8;
  else if (a<0) a=a+8;
  
    if (b>7) b=b-8;
  else if (b<0) b=b+8;
  
    if (c>7) c=c-8;
  else if (c<0) c=c+8;
  
    if (d>7) d=d-8;
  else if (d<0) d=d+8;
  
    if (e>7) e=e-8;
  else if (e<0) e=e+8;
  
    if (f>7) f=f-8;
  else if (f<0) f=f+8;
  
    if (g>7) g=g-8;
  else if (g<0) g=g+8;
  
    if (h>7) h=h-8;
  else if (h<0) h=h+8;
  
    if (i>7) i=i-8;
  else if (i<0) i=i+8;
  
    if (j>7) j=j-8;
  else if (j<0) j=j+8;
  
    if (k>7) k=k-8;
  else if (k<0) k=k+8;
  
    if (l>7) l=l-8;
  else if (l<0) l=l+8;
  
    if (m>7) m=m-8;
  else if (m<0) m=m+8;
  
      if (n>7) n=n-8;
  else if (n<0) n=n+8;
  
      if (o>7) o=o-8;
  else if (o<0) o=o+8;
  
  if(step_flag==0)
  {step_flag=1;}
  if(step_flag==1)
  {star_car();step_flag=2;}
  if(step_flag==2)
  {turn_direction(2);step_flag=3;}
  if(step_flag==3)
  {grab_ACE();step_flag=4;}
  if(step_flag==4)
  {turn_direction(a);step_flag=5;}//放置E块
  if(step_flag==5)
  {go_back_set_one();step_flag=6;}
  
  
  if(step_flag==6)
  {turn_direction(b);step_flag=7;}//放置C块
  if(step_flag==7)
  {go_back_set_two();step_flag=8;}
  
  
  if(step_flag==8)
  {turn_direction(c);step_flag=9;}//放置A块
  if(step_flag==9)
  {set_first_special_block();step_flag=10;}
  
  if(step_flag==10)
  {turn_direction(d);step_flag=11;}//放置B块
  if(step_flag==11)
  {drag_B_block();step_flag=12;}
  if(step_flag==12)
  {turn_direction(e);step_flag=13;}
  if(step_flag==13)
  {set_first_block();step_flag=14;}
  
  
  if(step_flag=14)
  {turn_direction(F_f-E+4);step_flag=15;}//放置A块
  if(step_flag==15)
  {drag_A_block();step_flag=16;}
  if(step_flag==16)
  {turn_direction(f);step_flag=17;}
  if(step_flag==17)
  {set_second_blockA();step_flag=18;}
  
  
  if(step_flag==18)
  {turn_direction(F_f-F+4);step_flag=19;}//放置C块
  if(step_flag==19)
  {drag_C_block();step_flag=20;}
  if(step_flag==20)
  {turn_direction(g);step_flag=21;}
  if(step_flag==21)
  {set_second_blockA();step_flag=22;}
  
  
  if(step_flag==22)
  {turn_direction(F_f-G+4);step_flag=23;}//放置E块
  if(step_flag==23)
  {drag_E_block();step_flag=24;}
  if(step_flag==24)
  {turn_direction(h);step_flag=25;}
  if(step_flag==25)
  {set_second_blockA();step_flag=26;}
  
  
  if(step_flag==26)
  {turn_direction(F_f - H + 4);step_flag=27;}//放置D块
  if(step_flag==27)
  {drag_D_block();step_flag=28;}
  if(step_flag==28)
  {turn_direction(i);step_flag=29;}
  if(step_flag==29)
  {set_first_block();step_flag=30;}
  
  /////////////////////////////////////////////////////////////////////
  if(step_flag==30)
  {turn_direction(j);step_flag=31;}//放置A块
  if(step_flag==31)
  {drag_B_block();step_flag=32;}
  if(step_flag==32)
  {turn_direction(k);step_flag=33;}
  if(step_flag==33)
  {set_third_block();step_flag=34;}
  
  
  if(step_flag==34)
  {turn_direction(F_h-K+4);step_flag=35;}//放置B块
  if(step_flag==35)
  {drag_A_block();step_flag=36;}
  if(step_flag==36)
  {turn_direction(l);step_flag=37;}
  if(step_flag==37)
  {set_second_blockB();step_flag=38;}
  
  if(step_flag=38)
  {turn_direction(F_h-L+4);step_flag=39;}//放置E块
  if(step_flag=39)
  {drag_C_block();step_flag=40;}
  if(step_flag=40)
  {turn_direction(m);step_flag=41;}
  if(step_flag=41)
  {set_third_block();step_flag=42;}
  
  
  if(step_flag=42)
  {turn_direction(F_h-M+4);step_flag=43;}//放置C块
  if(step_flag=43)
  {drag_E_block();step_flag=44;}
  if(step_flag=44)
  {turn_direction(n);step_flag=45;}
  if(step_flag=45)
  {set_third_block();step_flag=46;}
  
  
  if(step_flag=46)
  {turn_direction(F_h-N+4);step_flag=47;}//放置D块
  if(step_flag=47)
  {drag_D_block();step_flag=48;}
  if(step_flag=48)
  {turn_direction(o);step_flag=49;}
  if(step_flag=49)
  {set_second_blockB();step_flag=50;}
  
  
  if(step_flag==50)
   { turn_direction(F_g-O+4);step_flag = 51;}  
   if(step_flag==51)
   { come_back();step_flag = 52;}
   while(step_flag==52)
   {Stop_car(100);step_flag = 53;}
  
}
 void Code1()
{
  count_right += 1; // 编码器码盘计数加一  
}
void Code2()
{
  count_left += 1;  
}
