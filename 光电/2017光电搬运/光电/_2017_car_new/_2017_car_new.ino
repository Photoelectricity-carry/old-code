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
int step_flag = 0;
int step_car = 0;

#include <Servo.h>
Servo myservo_left_x;
Servo myservo_left_s;
Servo myservo_right_x;
Servo myservo_right_s;
Servo myservo_front;
int servo_touch=15;//控制舵机触控开关
//舵机引脚
int left_1 = 13;
int left_2 = 12;
int right_1 = 4;
int right_2 = 3;
int front_1 = 7 ;
int front_2 = 8;

//灰度传感器
int a_1,a_2,b_1,b_2,b_3,b_4,c_1,c_2;
//电机编码器
long count_left,count_right,count_front;
int left = 0,right = 5,front=4;
int claw_1 = 178, claw_2 = 130, claw_3 = 72;
int up_1 = 235 ,up_2 = 410;
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
  pinMode(servo_touch, INPUT);//触控开关为输入模式
  myservo_left_x.attach(6);
  myservo_left_s.attach(5);
  myservo_right_x.attach(11);
  myservo_right_s.attach(10);
  myservo_front.attach(9);

  pinMode(left_1, OUTPUT);
  pinMode(left_2, OUTPUT);
  pinMode(right_1, OUTPUT);
  pinMode(right_2, OUTPUT);
  pinMode(front_1, OUTPUT);
  pinMode(front_2, OUTPUT);

  attachInterrupt(left, Code_left, FALLING);//中断打开
  detachInterrupt(left);//中断关闭
  attachInterrupt(right, Code_right, FALLING);
  detachInterrupt(right);
  attachInterrupt(front, Code_front, FALLING);
  detachInterrupt(front);
    
  digitalWrite(left_1,LOW);//初始两个电机都处于停止状态
  digitalWrite(left_2,LOW);
  digitalWrite(right_1,LOW);
  digitalWrite(right_2,LOW);

  myservo_left_x.write(180);//大,外
  myservo_left_s.write(50);//大,上
  myservo_right_x.write(50);//大,中
  myservo_right_s.write(110);//大,下
  myservo_front.write(179);//大,大178,82,112
}

void loop()
{
Stop_car_start(2000);
//get_value();
//turn_right_45();
//drag_C_block();
first_mean();
//drag_B_block();
}

void turn_direction(int a)//转向
 { 
   if    (a>7) {a=a-8;}
   else if(a<0) {a=a+8;}
   if(a==0){Stop_car(500);}
   else if(a==1){Stop_car(50);turn_left_45();Stop_car(50);}
   else if(a==2){Stop_car(50);turn_left_90();Stop_car(50);}
   else if(a==3){Stop_car(50);turn_left_135();Stop_car(50);}
   else if(a==4){Stop_car(50);turn_left_180();Stop_car(50);}
   else if(a==5){Stop_car(50);turn_right_135();Stop_car(50);}
   else if(a==6){Stop_car(50);turn_right_90();Stop_car(50);}
   else if(a==7){Stop_car(50);turn_right_45();Stop_car(50);}
} 

//void turn_direction(int a)//转向
// { 
//   if    (a>7) {a=a-8;}
//   else if(a<0) {a=a+8;}
//   if(a==0){Stop_car(500);}
//   else if(a==1){Stop_car(500);turn_left(65,65);Stop_car(500);}
//   else if(a==2){Stop_car(500);turn_right(136,136);Stop_car(500);}
//   else if(a==3){Stop_car(500);turn_left_135();Stop_car(500);}
//   else if(a==4){Stop_car(500);turn_right(281,281);Stop_car(500);}
//   else if(a==5){Stop_car(500);turn_right(207,207);Stop_car(500);}
//   else if(a==6){Stop_car(500);turn_right(136,136);Stop_car(500);}
//   else if(a==7){Stop_car(500);turn_right(65,65);Stop_car(500);}
//} 

 void set_first_block()//取物块后放第一层
{ 
     step_car = 1;
while(step_car==1)
       { Stop_car(150);step_car = 2;}
while(step_car==2)
       { hunting_go(120,120);step_car = 4;}
while(step_car==4)
 {hunting();get_value();
   if(c_1==1&&c_2 == 1){ hunting_very_slow_go(50,50);Stop_car(150);step_car=6;}}            
while(step_car==6)
  {claw_up_down(up_1,-1);Stop_car(100);step_car = 10;}//夹子下降
 while(step_car==10)
       {claw_open_close(claw_3,claw_1,1);Stop_car(150);step_car =11;}//夹子完全张开
 while(step_car==11)
       { blind_back(120,120);Stop_car(50);step_car = 12;}    
 while(step_car==12)
       { turn_direction(4);Stop_car(50);step_car = 13;}
 while(step_car==13)
       {  hunting_go(50,50);step_car = 16;}
 while(step_car==16)
       {  hunting_very_slow();
          get_value();if(c_1==1&&c_2==1){hunting_very_slow_go(44,44);step_car = 17;}}
 while(step_car==17)
       {  Stop_car(150);step_car = 0;}     
}


void set_second_blockA()//取物块后放第二层 3层
{ 
     step_car = 1;
while(step_car==1)
       {step_car = 2;}
while(step_car==2)
       {hunting_go(120,120);step_car = 3; Stop_car(150);}
 while(step_car==3)
       { hunting();
         get_value();if(a_1==1&&a_2 == 1 ){ step_car = 4; Stop_car(150);}}
 while(step_car==4)     
 { Stop_car(150);claw_up_down(up_1,-1);Stop_car(150);step_car = 6;} //夹子下降
 while(step_car==6)           
     {claw_open_close(claw_3,claw_1,4);Stop_car(150);step_car =11;}//夹子完全张开
 while(step_car==11)         
       { blind_back(55,55);Stop_car(150);step_car = 12;}    
 while(step_car==12)
       { turn_direction(4);step_car = 16;}
 while(step_car==16)
       {  hunting_very_slow();
          get_value();if(c_1==1&&c_2 == 1){hunting_very_slow_go(44,44);Stop_car(150);step_car = 17;}}
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
        {hunting_set();get_value();if(a_1==1&&a_2 == 1 ){hunting_set_go(23,23);Stop_car(150);step_car = 4;}}
  while(step_car==4)
        {step_car=5;}
  while(step_car==5)
        {claw_open_close(claw_3,claw_2,1);Stop_car(150);claw_up_down(up_1+10,-1);Stop_car(150);step_car=6;}////1
  while(step_car==6)
        {claw_open_close(claw_2,claw_3,-1);Stop_car(150);claw_up_down(up_1+10,1);Stop_car(150);step_car=7;}
  while(step_car==7)
        {hunting_very_slow();get_value();
      if(c_1==1&&c_2 == 1){hunting_set_go(67,67);Stop_car(150);step_car=8;}}
  while(step_car==8)
        {claw_open_close(claw_3,claw_2,1);Stop_car(150);step_car=9;}
  while(step_car==9)
        {claw_up_down(up_1+10,-1);Stop_car(150);claw_up_down(10,1);Stop_car(150);step_car=10;}
  while(step_car==10)
        {hunting_set();get_value();
        if(a_1==1&&a_2 == 1 ){Stop_car(150);step_car=12;}}
   while(step_car==12)
        {claw_open_close(claw_2,85,-1);Stop_car(150);claw_open_close(85,claw_1,1);Stop_car(150);step_car=15;}
   while(step_car==15)
         {blind_back(80,80);step_car=16;}
   while(step_car==16)
         {turn_direction(4);step_car=17;}
   while(step_car==17)
         {hunting_go(240,240);step_car=18;}
   while(step_car==18)
         {hunting_very_slow();get_value();
         if(c_1==1&&c_2 == 1){hunting_very_slow_go(44,44);step_car=19;}}
   while(step_car==19)
         {Stop_car(150);step_car=0;}//夹子处于最低
}


//1打开 0关闭
// int up_1 = 220 ,up_2 = 400;
//int claw_1 = 178, claw_2 = 120, claw_3 = 80;



void set_second_blockB()//应该两层
{
     step_car = 1;
while(step_car==1)
       {Stop_car(150);step_car = 2;}
while(step_car==2)
       { hunting_go(120,120);step_car = 3;}
 while(step_car==3)
       { hunting();
         get_value();if(a_1==1&&a_2 ==1){ step_car = 4;}}//从过中线
 while(step_car==4)
 { hunting();get_value();
   if(c_1==1&&c_2 == 1 ){hunting_set_go(65,65);Stop_car(150);step_car =6;}} 
while(step_car==6)
   {Stop_car(150);step_car = 7;}
 while(step_car==7)
     {claw_open_close(claw_3,claw_2,1);Stop_car(150);claw_up_down(up_1,-1);Stop_car(150);claw_open_close(claw_2,86,-1);Stop_car(150);step_car =8;}
 while(step_car==8)
       { hunting_set();get_value();
     if(a_1==1&&a_2 == 1){Stop_car(150);step_car =13;}}
while(step_car==13)
       {claw_open_close(86,claw_1,1);Stop_car(200);blind_back(80,80);step_car=14;} 
 while(step_car==14)
       { turn_direction(4);step_car = 15;}
 while(step_car==15)
       {  hunting_go(240,240);step_car = 16;}
 while(step_car==16)
       {  hunting_very_slow();
          get_value();if(c_1==1&&c_2 == 1){hunting_very_slow_go(44,44);step_car = 17;}}
 while(step_car==17)
       {  Stop_car(150);step_car = 0;}
}


void come_back()
{
  step_car =1;
  while(step_car==1)
       { hunting_go(120,120);step_car=2;}
   while(step_car==2)
       {hunting();get_value();if(c_1==1&&c_2 == 1)
                              {hunting_go(50,50);step_car=3;}
     }
    while(step_car==3)
    {hunting();get_value();if(c_1==1&&c_2 == 1)
                             {hunting_go(60,60);step_car=4;}
    }
   while(step_car==4)
   {
     Stop_car(150);step_car=4;
   }
}


void drag_A_block()//夹物块前夹子放到最低处并且完全张开
{   start_high();
    step_car =1;
  while(step_car==1)
       {Stop_car(150);step_car=2;}  
  while(step_car==2)
       { hunting_go(120,120);step_car=3;}
  while(step_car==3)
       { hunting();
         get_value();if(a_1 == 1 || a_2 == 1){step_car = 4;}}//前到中线
  while(step_car==4)
       {hunting();
        get_value();if(c_1==1&&c_2==1){step_car = 5;}}
  while(step_car==5)
        {hunting_very_slow();
        get_value();if(a_1 == 1 || a_2 == 1){step_car=6;}}
  while(step_car==6)  
       {hunting_set_go(92,92);Stop_car(150);step_car = 7;}
  while(step_car==7)
       { drag_A();Stop_car(100);step_car = 8;}
  while(step_car==8)
       {blind_back(100,100);Stop_car(150);step_car =9;}
  while(step_car==9)
       { set_block_middle_A();Stop_car(150);step_car =10;}    
  while(step_car==10)
       {release_block_left() ;Stop_car(150);step_car =11;}    
  while(step_car==11)
       { claw_up_down(400,-1);hunting_very_slow_go(50,50);Stop_car(150);step_car =12;}//夹子下降  
  while(step_car==12)
       {claw_open_close(claw_1,claw_3,-1);Stop_car(80);claw_up_down(up_1,1);Stop_car(80);step_car =13;}//夹子加紧 然后上升
  while(step_car==13)
       { turn_direction(4);Stop_car(150);step_car =14;}
  while(step_car==14)
       { hunting_go(200,200);step_car=15;}
  while(step_car==15)
       { hunting();
         get_value();if(c_1==1&&c_2==1) { hunting_very_slow_go(45,45);Stop_car(80);step_car = 0;}}//夹子处于90
}


void drag_B_block()//夹物块前夹子放到最低处并且完全张开
{
    start_high();
    step_car =1;
  while(step_car==1)
       {/*claw_up_down(UA,UC,4);*/Stop_car(150);step_car=2;}  
  while(step_car==2)
       { hunting_go(120,120);step_car=3;}
  while(step_car==3)
       { hunting();
         get_value();if(a_1 == 1 || a_2 == 1 ){ step_car = 4;}}//前到中线
  while(step_car==4)
       {hunting();
        get_value();if(c_1==1&&c_2==1){step_car = 5;}}//后到中心
  while(step_car==5)
       {hunting_very_slow();
       get_value();if(a_1 == 1 || a_2 == 1){step_car=6;}}
  while(step_car==6)  
       {hunting_set_go(91,91);Stop_car(150);step_car = 7;}
  while(step_car==7)         
       { drag_B();step_car = 8;}
  while(step_car==8)
       { blind_back(120,120);Stop_car(150);step_car =9;}
  while(step_car==9)
       { set_block_middle_B();Stop_car(150);step_car =10;}    
  while(step_car==10)
       { release_block_right() ;Stop_car(150);step_car =11;}    
  while(step_car==11)
       {claw_up_down(up_2,-1);/*hunting_very_slow_go(50,50);*/Stop_car(150);step_car =12;}//夹子下降
  while(step_car==12)
       {claw_open_close(claw_1,claw_3,-6);Stop_car(150);claw_up_down(up_1,1);Stop_car(150);step_car =13;}//夹子加紧 然后上升
  while(step_car==13)
       { turn_direction(4);Stop_car(150);step_car =14;}
  while(step_car==14)
       { hunting_go(180,180);step_car=15;}
  while(step_car==15)
       { hunting();
         get_value();if(c_1==1&&c_2==1) { hunting_very_slow_go(47,47);Stop_car(150);step_car = 0;}}//夹子处于90
}

// int up_1 = 220 ,up_2 = 400;
//int claw_1 = 178, claw_2 = 120, claw_3 = 80;

void drag_C_block() //夹物块前夹子放到最低处并且完全张开
{
    start_high();
    step_car =1;
  while(step_car==1)
       {/*claw_up_down(UA,UC,4);*/Stop_car(150);step_car=2;}  
  while(step_car==2)
       { hunting_go(120,120);step_car=3;}
  while(step_car==3)
       { hunting();
         get_value();if(a_1 == 1 || a_2 == 1 ){ step_car = 4;}}//前到中线
  while(step_car==4)
       {hunting();
        get_value();if(c_1==1&&c_2==1){step_car = 5;}}//后到中心
  while(step_car==5)
       {hunting_very_slow();if(a_1 == 1 || a_2 == 1 ){step_car=6;}}
  while(step_car==6)
       {hunting_set_go(122,122);Stop_car(150);step_car = 7;}
  while(step_car==7)
       { drag_C();step_car = 8;}
  while(step_car==8)
       { blind_back(130,130);Stop_car(150);step_car =9;}
  while(step_car==9)
       { set_block_middle_C();Stop_car(150);step_car =10;}    
  while(step_car==10)
       { release_block_right();Stop_car(150);step_car =11;}    
  while(step_car==11)
       { claw_up_down(up_2,-4);/*hunting_very_slow_go(50,50);*/Stop_car(150);step_car =12;}//夹子下降  
  while(step_car==12)
       {claw_open_close(claw_1,claw_3,-1);Stop_car(150);claw_up_down(up_1,1);Stop_car(150);step_car =13;}//夹子加紧 然后上升  
  while(step_car==13)
       { turn_direction(4);Stop_car(150);step_car =14;}          
  while(step_car==14)
       { hunting_go(200,200);step_car=15;}
  while(step_car==15)
       { hunting();
         get_value();if(c_1==1&&c_2==1) { hunting_very_slow_go(45,45);Stop_car(150);step_car = 0;}}  //夹子处于90
}


void drag_E_block() //夹物块前夹子放到最低处并且完全张开
{   start_high();
    step_car =1;
  while(step_car==1)
       {Stop_car(150);step_car=2;}  
  while(step_car==2)
       { hunting_go(120,120);step_car=3;}
  while(step_car==3)
       { hunting();
         get_value();if(a_1 == 1 || a_2 == 1  ){ step_car = 4;}}//前到中线
  while(step_car==4)
       {hunting();
        get_value();if(c_1==1||c_2==1){step_car = 5;}}//后到中心
  while(step_car==5)
        {hunting_very_slow();
        get_value();if(a_1 == 1 || a_2 == 1 ){step_car=6;}}
  while(step_car==6)
       {hunting_set_go(121,121);Stop_car(150);step_car = 7;}
  while(step_car==7) 
       { drag_E();Stop_car(150);step_car = 8;}
  while(step_car==8)
       { blind_back(100,100);Stop_car(150);step_car =9;}
  while(step_car==9)
       { set_block_middle_E();Stop_car(150);step_car =10;}    
  while(step_car==10)
       { release_block_left();Stop_car(150);step_car =11;}    
  while(step_car==11)
       {claw_up_down(up_2,-1); hunting_very_slow_go(50,50);Stop_car(150);step_car =12;}//夹子下降
  while(step_car==12)
       { claw_open_close(claw_1,claw_3,-1);Stop_car(150);claw_up_down(up_1,1);Stop_car(150);step_car =13;} //夹子加紧 然后上升   
  while(step_car==13)
       { turn_direction(4);step_car =14;}
  while(step_car==14)
       { hunting_go(250,250);step_car=15;}
  while(step_car==15)
       { hunting();
         get_value();if(c_1==1||c_2==1) { hunting_go(45,45);Stop_car(150);step_car = 0;}}//夹子处于90
}

void drag_D_block() //夹物块前夹子放到最低处并且完全张开
{  
    step_car =2; 
  while(step_car==2)
       { hunting_go(120,120);step_car=3;}
  while(step_car==3)
       { hunting();
         get_value();if(a_1 == 1 || a_2 == 1 ){ step_car = 4;}}//前到中线
  while(step_car==4)
       {hunting();
        get_value();if(c_1==1||c_2==1){step_car = 5;}}//后到中心
  while(step_car==5)
       {hunting_very_slow();
        get_value();if(a_1 == 1 || a_2 == 1){step_car=6;}}
  while(step_car==6)
       {hunting_set_go(150,150);Stop_car(150);step_car = 8;}   
  while(step_car==8)
       {claw_open_close(claw_1,claw_3,-6);Stop_car(150);claw_up_down(up_1,1);Stop_car(150);step_car =9;} //夹子加紧 然后上升   
  while(step_car==9)
       { turn_direction(4);Stop_car(150);step_car =10;}
  while(step_car==10)
       { hunting_go(330,330);step_car=11;}
  while(step_car==11)
       { hunting();
         get_value();if(c_1==1||c_2==1) { hunting_very_slow_go(47,47);Stop_car(150);step_car = 0;}}  //夹子处于90
}

void drag_A() 
{ 
int i = 1;
while(i==1)
{
   for( int pos = 180; pos > 165; pos -= 3)  
  {                                  
    myservo_left_x.write(pos);
    delay(20);
  } 
  i=2; 
}
while(i==2)
{
   for( int pos = 50; pos >25; pos -= 3)  
  {                                  
    myservo_left_s.write(pos);
    delay(20);
  } 
  i=3; 
}
}

void drag_B() 
{ 
int i = 1;
while(i==1)
{
   for( int pos = 50; pos < 90; pos += 3)  
  {                                  
      myservo_right_x.write(pos);
    delay(20);
  } 
  i=2; 
}

while(i==2)
{
   for( int pos = 110; pos < 140; pos += 3)  
  {                                  
    myservo_right_s.write(pos);
    delay(20);
  } 
  i=3; 
}
}

void drag_C() 
{
int i = 1;
while(i==1)
{
   for( int pos = 50; pos < 82; pos += 2)  
  {                                  
      myservo_right_x.write(pos);
    delay(20);
  } 
  i=2; 
}
while(i==2)
{
   for( int pos = 110; pos < 136; pos += 2)  
  {                                  
    myservo_right_s.write(pos);
    delay(20);
  } 
  i=3; 
}
}

void drag_E() 
{
int i = 1;
while(i==1)
{
   for( int pos = 50; pos > 20; pos-= 3)  
  {                                  
    myservo_left_s.write(pos);
    delay(20);
  } 
  i=2; 
}
}

void set_block_middle_A() 
{ 
int i = 1;
while(i==1)
{
   for( int pos = 165; pos > 132; pos -=1)  
  {                                  
    myservo_left_x.write(pos);
    delay(20);
  } 
  i=2; 
}                                            
}
void set_block_middle_B() 
{                                 
int i = 1;
while(i==1)
{
   for( int pos = 82; pos < 113; pos +=1)  
  {                                  
    myservo_right_x.write(pos);
    delay(20);
  } 
  i=2; 
}                                                
}
void set_block_middle_C() 
{                                 
int i = 1;
while(i==1)
{
   for( int pos = 82; pos <123; pos +=1)  
  {                                  
      myservo_right_x.write(pos);
    delay(20);
  } 
  i=2; 
}                                      
}
void set_block_middle_E() 
{
int i = 1;
while(i==1)
{
   for( int pos = 180; pos > 130; pos -=1 ) 
  {                                  
    myservo_left_x.write(pos);
    delay(20);
  } 
  i=2; 
}
 
}
void release_block_left() 
{ 
  myservo_left_s.write(50);//大,上
    delay(200);
  myservo_left_x.write(180);//大,外
    delay(200);

}
void release_block_right() 
{ 
  myservo_right_s.write(110);//大,下
      delay(200);
  myservo_right_x.write(50);//大,中
      delay(200);
}

void star_car()//开始到达中心
{
  step_car=1;
  if(step_car==1)
  { hunting_go(350,350);step_car = 2;}
  while(step_car==2)
  {hunting();
   get_value();if(a_1 == 1&&a_2 == 1) {step_car = 3;}}
  while( step_car==3)
  { hunting_very_slow_go(160,160);Stop_car(150);step_car=0; }
}

void start_high()
{
  while(1)
  {
  Serial.println(digitalRead(servo_touch));
  if(digitalRead(servo_touch)==1)
  {
  analogWrite(front_2,254);
  digitalWrite(front_1,LOW);
  }
  else if(digitalRead(servo_touch)==0)
  {
  Stop_car_start(150);
  break;
  }
  }
}

void start()
{
 while(1)
  {
  Serial.println(digitalRead(servo_touch));
  if(digitalRead(servo_touch)==1)
  {
  analogWrite(front_2,254);
  digitalWrite(front_1,LOW);
  }
  else if(digitalRead(servo_touch)==0)
  {
  claw_up_down(400,-1);
  Stop_car(150);
  break;
  }
  }
}

void claw_open_close(int s,int d,int Speed) //大,大180,80,110
{
  int i;
  if(Speed > 0)
  {
    for(i=s;i<=d;i+=1)//夹子张开
    {myservo_front.write(i);
    delay(40);}
  }
  if(Speed < 0)
  {
    for(i=s;i>=d;i-=3)//夹子闭合
    {myservo_front.write(i);
    delay(40);}
  }
}


void claw_up_down(int s, int Speed)
{
  if(Speed > 0)//上升
  {
  count_front=0;
  attachInterrupt(front, Code_front, FALLING);
    while(1)
  { 
    Serial.println(count_front);
    analogWrite(front_2,240);
    digitalWrite(front_1,LOW);
    analogWrite(right_1,LOW);
    digitalWrite(right_2,LOW);
    analogWrite(left_2,LOW);
    digitalWrite(left_1,LOW);
    Serial.println(count_front);
    if(count_front/5 > s)
    {
      digitalWrite(front_1,LOW);
      digitalWrite(front_2,LOW);
      break;
    }
  }  
  detachInterrupt(front);
  }
  
  if(Speed < 0)//下降
  {
     count_front=0;
     attachInterrupt(front, Code_front, FALLING);
    while(1)
  { 
    Serial.println(count_front);
    analogWrite(front_1,240);
    digitalWrite(front_2,LOW);
    analogWrite(right_1,LOW);
    digitalWrite(right_2,LOW);
    analogWrite(left_2,LOW);
    digitalWrite(left_1,LOW);
    Serial.println(count_front);
    if(count_front/5 > s)
    {  
    digitalWrite(front_1,LOW);
    digitalWrite(front_2,LOW);
    break;
    }
  }  
  detachInterrupt(front);
  }  
}

void grab_ACE() //将ACE收集到一起
 {
  step_car=1;
  if( step_car==1)
 { hunting_go(120,120);step_car=2;}  
  while( step_car==2)
  { hunting_very_slow();
    get_value();if(a_1 == 1&&a_2 == 1) { step_car=6;break;}}
if( step_car==6)
 {hunting_set_go(30,30);step_car=7;} 
 if( step_car==7)

{ Stop_car(150);claw_open_close(claw_1,claw_3,-2);Stop_car(150);step_car=8;}//夹起物块
 if( step_car==8)
 {claw_up_down(up_1,2);Stop_car(150);step_car=9;} //抬起夹子
 
 if( step_car==9)
{ turn_direction(4);Stop_car(150);step_car=10;}
while(step_car==10)
   { hunting();
     get_value();if(a_1==1&&a_2==1) {step_car = 11;}}
while( step_car==11)
  { hunting_very_slow_go(160,160);Stop_car(150);step_car=12; }
if( step_car==12)//转到C方向
{ turn_direction(2);hunting_go(120,120);step_car=13;}
while( step_car==13)
  { hunting_very_slow();
     get_value();if(a_1==1||a_2==2) { step_car=14;break;}}
if( step_car==14)
 { hunting_set_go(30,30);Stop_car(150);step_car=15;} //放下爪子
if( step_car==15)
 {claw_open_close(claw_3,claw_2,1);Stop_car(150);claw_up_down(up_1,-1);Stop_car(150);step_car=16;}//微微张开 然后放下
 if( step_car==16)
{ claw_open_close(claw_2,claw_3,-1);Stop_car(150);step_car=17;}//加紧爪子
 if( step_car==17)
 { claw_up_down(up_1,2);Stop_car(150);step_car=18;} //爪子上升
 if( step_car==18)
{ turn_direction(4);Stop_car(150);step_car=19;}
  while(step_car==19)
   { hunting();
     get_value();if(a_1==1&&a_2==1) {step_car = 20;}}
  while( step_car==20)
  { hunting_very_slow_go(160,160);Stop_car(150);step_car=21; }
  if( step_car==21)
{ turn_direction(2);Stop_car(150);hunting_go(120,120);step_car=22;}//转到E方向
while( step_car==22)
  { hunting_very_slow();
     get_value();if(a_1==1 || a_2==1) { step_car=23;Stop_car_start(150);break;}}
if( step_car==23)
 { hunting_very_slow_go(40,40);Stop_car(150);step_car=24;} //微微放下爪子
if( step_car==24)
 {claw_open_close(claw_3,claw_2,1);Stop_car(150);claw_up_down(up_1,-1);Stop_car(150);step_car=25;}   //微微张开 然后完全放下
 if( step_car==25)
{claw_open_close(claw_2,claw_3,-1);Stop_car(150);claw_up_down(20,1);step_car=27;}//加紧爪子
 if( step_car==27)
{ turn_direction(4);Stop_car(150);step_car=28;}
  while(step_car==28)
   { hunting();
     get_value();if(a_1==1&&a_2 == 1) {step_car = 29;}}
  while( step_car==29)
  { hunting_very_slow_go(160,160);Stop_car(150);step_car=0;}///夹子处入45的高度
 }


/***************************************/
  void go_back_set_one()//放置ACE中最底部物块E
{
     step_car = 1;
 while(step_car==1)
       { Stop_car(150);step_car = 2;}
 while(step_car==2)
       {hunting_go(120,120); step_car = 4;}
 while(step_car==4)
       { hunting();
         get_value();if( c_1== 1||c_2==1 ) { hunting_very_slow_go(48,48);Stop_car(150);step_car=5;}}//4.5
 while(step_car==5)
       {claw_open_close(claw_3,claw_2,1);Stop_car(150);step_car = 6;}//夹子下降 然后 微微张开           
 while(step_car==6)         
       {claw_up_down(200,1);Stop_car(150);claw_open_close(claw_2,claw_3,-1);Stop_car(150);step_car = 8;}
 while(step_car==8)
       {claw_up_down(20 ,1); Stop_car(150);blind_back(100,100);Stop_car(150);step_car = 9;}         
 while(step_car==9)
       {turn_direction(4);Stop_car(150);step_car = 10;}
 while(step_car==10)
       { hunting_go(50,50);step_car = 11;}
 while(step_car==11)
       { hunting();
         get_value();if( c_1== 1||c_2==1) { hunting_very_slow_go(45,45);Stop_car(150);step_car = 0;}}/////夹子处入90的高度
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
         get_value();if(  c_1== 1||c_2==1 ) { hunting_very_slow_go(48,48);Stop_car(150);step_car=5;}}//4.5
 while(step_car==5)
       {claw_up_down(up_1,-1);Stop_car(150);claw_open_close( claw_3, claw_2,1);;Stop_car(150);step_car = 6;}//夹子下降到嘴下面   然后 微微张开_
 while(step_car==6)         
       {claw_up_down(up_1,1);Stop_car(150);claw_open_close(claw_2, claw_3,-1);Stop_car(150);step_car = 7;}//夹子上升   然后 加紧
 while(step_car==7)         
       {claw_up_down(20,1);Stop_car(150);blind_back(100,100);Stop_car(150);step_car = 8;}         
 while(step_car==8)
       { turn_direction(4);Stop_car(150);step_car = 9;}
 while(step_car==9)
       { hunting_go(50,50);step_car = 10;}     
 while(step_car==10)
       { hunting();
         get_value();if(  c_1== 1||c_2==1) { hunting_very_slow_go(45,45);Stop_car(150);step_car = 0;}}//夹子处入90的高度
}

// int up_1 = 220 ,up_2 = 390;
//int claw_1 = 178, claw_2 = 120, claw_3 = 80;

void set_first_special_block()//放置ACE中最上部物块A
{ 
     step_car = 1;
while(step_car==1)
       { Stop_car(150);step_car = 2;}
while(step_car==2)
       { hunting_go(120,120);step_car = 4;}
 while(step_car==4)         
       { hunting();
         get_value();if(  c_1== 1||c_2==1 ) { hunting_very_slow_go(48,48);Stop_car(150);step_car=5;}}
 while(step_car==5)     
 {claw_up_down(240,-1);Stop_car(150);claw_open_close(claw_3,claw_1,6);Stop_car(150);step_car = 13;}//夹子降到最下面 然后完全张开
 while(step_car==13)
       {blind_back(100,100);Stop_car(150);step_car = 14;} 
 while(step_car==14)
       {  turn_direction(4);Stop_car(150);step_car = 15;}
 while(step_car==15)
       {  hunting_go(50,50);step_car = 16;}
 while(step_car==16)
       {  hunting();
          get_value();if( c_1== 1||c_2==1){hunting_very_slow_go(45,45);Stop_car(150);step_car = 0;}}//夹子降到最下面
}


void get_value()
{//读传感器值
a_1=(analogRead(A0)>=400? 0:1);
a_2=(analogRead(A5)>=250? 0:1);
b_1=(analogRead(A1)>=700? 0:1);
b_2=(analogRead(A2)>=400? 0:1);
b_3=(analogRead(A3)>=600? 0:1);
b_4=(analogRead(A4)>=500? 0:1);
c_1=(analogRead(A10)>=600? 0:1);
c_2=(analogRead(A12)>=600? 0:1);
//Serial.print(a_1);
//Serial.print("\t");
//Serial.print(a_2);
//Serial.print("\t");
//Serial.print(b_1);
//Serial.print("\t");
//Serial.print(b_2);
//Serial.print("\t");
//Serial.print(b_3);
//Serial.print("\t");
//Serial.print(b_4);
//Serial.print("\t");
//Serial.print(c_1);
//Serial.print("\t");
//Serial.println(c_2);
//Serial.print("\t");


//
//Serial.print(analogRead(A0));
//Serial.print("\t");
//Serial.print(analogRead(A5));
//Serial.print("\t");
//Serial.print(analogRead(A1));
//Serial.print("\t");
//Serial.print(analogRead(A2));
//Serial.print("\t");
//Serial.print(analogRead(A3));
//Serial.print("\t");
//Serial.print(analogRead(A4));
//Serial.print("\t");
//Serial.print(analogRead(A10));
//Serial.print("\t");
//Serial.println(analogRead(A12));
//Serial.print("\t");


















}



void hunt(int val_left,int val_right)
{ analogWrite(front_1,LOW);
  digitalWrite(front_2,LOW);
  analogWrite(left_1,val_left);
  digitalWrite(left_2,LOW);
  analogWrite(right_1,val_right);
  digitalWrite(right_2,LOW);
}

//1是黑色,0是白色
void hunting()//普通巡线
{
 get_value();
 if(b_1==1 && b_2==0 && b_3==0 &&b_4 ==0) hunt(75,120);
 else if(b_1==1 && b_2==1 && b_3==0 && b_4==0) hunt(85,120);
 else if(b_1==0 && b_2==1 && b_3==0 && b_4==0) hunt(95,120);
 else if(b_1==0 && b_2==1 && b_3==1 && b_4==0) hunt(120,120);
 else if(b_1==0 && b_2==0 && b_3==0 && b_4==1) hunt(120,75);
 else if(b_1==0 && b_2==0 && b_3==1 && b_4==1) hunt(120,95);
 else if(b_1==0 && b_2==0 && b_3==1 && b_4==0) hunt(120,85);
 else if(b_1==0 && b_2==0 && b_3==0 && b_4==0) hunt(120,120);
 else hunt(120,120);
}
/* 0000,1000,1100,0100,0110,0001,0011,0010*/


void hunting_set()//只用于将物块先前推时的巡线
{
      get_value();
      if(b_1==1 && b_2==0 && b_3==0 &&b_4 ==0) hunt(30,30);
 else if(b_1==1 && b_2==1 && b_3==0 && b_4==0) hunt(40,55);
 else if(b_1==0 && b_2==1 && b_3==0 && b_4==0) hunt(45,55);
 else if(b_1==0 && b_2==1 && b_3==1 && b_4==0) hunt(55,55);
 else if(b_1==0 && b_2==0 && b_3==0 && b_4==1) hunt(30,30);
 else if(b_1==0 && b_2==0 && b_3==1 && b_4==1) hunt(55,40);
 else if(b_1==0 && b_2==0 && b_3==1 && b_4==0) hunt(55,45);
 else if(b_1==0 && b_2==0 && b_3==0 && b_4==0) hunt(55,55);
 else hunt(55,55);
}

void hunting_very_slow()//只用于将物块先前推时的巡线
{
      get_value();
      if(b_1==1 && b_2==0 && b_3==0 &&b_4 ==0) hunt(45,45);
 else if(b_1==1 && b_2==1 && b_3==0 && b_4==0) hunt(55,70);
 else if(b_1==0 && b_2==1 && b_3==0 && b_4==0) hunt(60,70);
 else if(b_1==0 && b_2==1 && b_3==1 && b_4==0) hunt(70,70);
 else if(b_1==0 && b_2==0 && b_3==0 && b_4==1) hunt(45,45);
 else if(b_1==0 && b_2==0 && b_3==1 && b_4==1) hunt(70,55);
 else if(b_1==0 && b_2==0 && b_3==1 && b_4==0) hunt(70,60);
 else if(b_1==0 && b_2==0 && b_3==0 && b_4==0) hunt(70,70);
 else hunt(55,55);

}

void hunting_go(float x,float y)//普通编码器巡线前进
{
  count_left =0;
  count_right =0;
  attachInterrupt(left, Code_left, FALLING);
  attachInterrupt(right, Code_right, FALLING);
  attachInterrupt(front, Code_front, FALLING);

    while(1)
  { 
    hunting();
    if(count_left/5 > x && count_right/5 > y)
    {
      break;
    }
  }  
  detachInterrupt(left);
  detachInterrupt(right);
  detachInterrupt(front);
}

void hunting_set_go(float x,float y)//普通编码器巡线前进
{
  count_left =0;
  count_right =0;
  attachInterrupt(left, Code_left, FALLING);
  attachInterrupt(right, Code_right, FALLING);
  attachInterrupt(front, Code_front, FALLING);
    while(1)
  { 
    hunting_set();
    if(count_left/5 > x && count_right/5 > y)
    {
      break;
    }
  }  
  detachInterrupt(left);
  detachInterrupt(right);
  detachInterrupt(front);
}

void hunting_very_slow_go(float x,float y)
{
  count_left =0;
  count_right =0;
  attachInterrupt(front, Code_front, FALLING);
  attachInterrupt(left, Code_left, FALLING);
  attachInterrupt(right, Code_right, FALLING);
    while(1)
  { 
    hunting_very_slow();
// Serial.print(count_left);
// Serial.print("\t");
// Serial.println(count_right);
    if(count_left/5 > x && count_right/5 > y)
    {
      Stop_car(150);
      break;
    }
  }  
  detachInterrupt(left);
  detachInterrupt(right);
  detachInterrupt(front);
}

void blind_back(float x ,float y)//编码器不巡线后退
{   count_left =0;
    count_right =0;
  attachInterrupt(left, Code_left, FALLING);
  attachInterrupt(right, Code_right, FALLING);
  attachInterrupt(front, Code_front, FALLING);
    while(1)
  { 
     if(count_left/5 < x)
    {
       digitalWrite(left_1,LOW);
       analogWrite(left_2,65);
    }
     if(count_right/5 < y)
    {
       digitalWrite(right_1,LOW); 
       analogWrite(right_2,63);
    }
    if(count_left/5 > x && count_right/5 > y)
    {
      Stop_car(200);
      break;
    }
  }
  detachInterrupt(front);
  detachInterrupt(left);
  detachInterrupt(right);
}


void turn_right(float x ,float y)//原地左转
{   count_left =0;
    count_right =0;
    attachInterrupt(left, Code_left, FALLING);
    attachInterrupt(right, Code_right, FALLING);
    attachInterrupt(front, Code_front, FALLING);
    while(1)
  { 
    Serial.print(count_left);
    Serial.print("\t");
    Serial.println(count_right);
     if(count_left/5 < x)
    {
       digitalWrite(left_2,LOW);
       analogWrite(left_1,100);
    }
     if(count_right/5 < y)
    {
       digitalWrite(right_1,LOW); 
       analogWrite(right_2,100);
    }
    if(count_left/5 >= x || count_right/5 >= y)
    {
      Stop_car(200);
      break;
    }
  }
  detachInterrupt(left);
  detachInterrupt(right);
  detachInterrupt(front);
}



void turn_right_45()//原地左转
{ 
   turn_right(32,32);
   while(1)
  {
    get_value();
    digitalWrite(left_2,LOW);
    analogWrite(left_1,80);
    digitalWrite(right_1,LOW); 
    analogWrite(right_2,80);
  
    if((b_4==0&&b_3==1))
    {
      Stop_car(100);
      break;
    }
  }
}

void turn_right_90()//原地左转
{ 
   turn_right(110,110);
   while(1)
  {
    get_value();
    digitalWrite(left_2,LOW);
    analogWrite(left_1,80);
    digitalWrite(right_1,LOW); 
    analogWrite(right_2,80);
  
    if((b_4==0&&b_3==1))
    {
      Stop_car(100);
      break;
    }
  }
}


void turn_right_135()//原地左转
{ 
   turn_right(175,175);
   while(1)
  {
    get_value();
    digitalWrite(left_2,LOW);
    analogWrite(left_1,80);
    digitalWrite(right_1,LOW); 
    analogWrite(right_2,80);
  
    if((b_4==0&&b_3==1))
    {
      Stop_car(100);
      break;
    }
  }
}



void turn_right_180()//原地左转
{ 
   turn_right(240,240);
   while(1)
  {
    get_value();
    digitalWrite(left_2,LOW);
    analogWrite(left_1,80);
    digitalWrite(right_1,LOW); 
    analogWrite(right_2,80);
  
    if((b_4==0&&b_3==1))
    {
      Stop_car(100);
      break;
    }
  }
}
void turn_left_180()//原地左转
{ 
   turn_left(240,240);
   while(1)
  {
    get_value();
    digitalWrite(left_1,LOW);
    analogWrite(left_2,80);
    digitalWrite(right_2,LOW); 
    analogWrite(right_1,80);
  
    if((b_1==0&&b_2==1))
    {
      Stop_car(100);
      break;
    }
  }
}

void turn_left_135()//原地左转
{ 
   turn_left(180,180);
   while(1)
  {
    get_value();
    digitalWrite(left_1,LOW);
    analogWrite(left_2,80);
    digitalWrite(right_2,LOW); 
    analogWrite(right_1,80);
  
    if((b_1==0&&b_2==1))
    {
      Stop_car(100);
      break;
    }
  }
}

void turn_left_90()//原地左转
{ 
   turn_left(110,110);
   while(1)
  {
    get_value();
    digitalWrite(left_1,LOW);
    analogWrite(left_2,80);
    digitalWrite(right_2,LOW); 
    analogWrite(right_1,80);
  
    if((b_1==0&&b_2==1))
    {
      Stop_car(100);
      break;
    }
  }
}
void turn_left_45()//原地左转
{ 
   turn_left(32,32);
   while(1)
  {
    get_value();
    digitalWrite(left_1,LOW);
    analogWrite(left_2,80);
    digitalWrite(right_2,LOW); 
    analogWrite(right_1,80);
  
    if((b_1==0&&b_2==1))
    {
      Stop_car(100);
      break;
    }
  }
}
void turn_left(float x ,float y)//原地左转
{   count_left =0;
    count_right =0;
    attachInterrupt(front, Code_front, FALLING);
    attachInterrupt(left, Code_left, FALLING);
    attachInterrupt(right, Code_right, FALLING);
    while(1)
  { 
     if(count_left/5 < x)
    {
       digitalWrite(left_1,LOW);
       analogWrite(left_2,130);
    }
     if(count_right/5 < y)
    {
       digitalWrite(right_2,LOW); 
       analogWrite(right_1,130);
    }
    if(count_left/5 >= x || count_right/5 >= y)
    {
      Stop_car(100);
      break;
    }
  }
  detachInterrupt(left);
  detachInterrupt(right);
  detachInterrupt(front);
}



void elevator_up(int x)
{

  count_left =0;
  count_right=0;
  count_front=0;
  attachInterrupt(front, Code_front, FALLING);
  attachInterrupt(left, Code_left, FALLING);
  attachInterrupt(right, Code_right, FALLING);
    while(1)
  { 
    Serial.println(count_front);
    analogWrite(front_2,240);
    digitalWrite(front_1,LOW);
    analogWrite(right_1,LOW);
    digitalWrite(right_2,LOW);
    analogWrite(left_2,LOW);
    digitalWrite(left_1,LOW);
    Serial.println(count_front);
    if(count_front/5 > x)
    {
      break;
    }
  }  
  detachInterrupt(left);
  detachInterrupt(right);
  detachInterrupt(front);
}

  
void elevator_down(int x)
{

  count_left =0;
  count_right=0;
  count_front=0;
   attachInterrupt(front, Code_front, FALLING);
   attachInterrupt(left, Code_left, FALLING);
   attachInterrupt(right, Code_right, FALLING);
    while(1)
  { 

    Serial.println(count_front);
    analogWrite(front_1,240);
    digitalWrite(front_2,LOW);
    analogWrite(right_1,LOW);
    digitalWrite(right_2,LOW);
    analogWrite(left_2,LOW);
    digitalWrite(left_1,LOW);
    Serial.println(count_front);
    if(count_front/5 > x)
    {
      break;
    }
  }  
  detachInterrupt(left);
  detachInterrupt(right);
  detachInterrupt(front);
  }

void Stop_car_start(int x)
{
  digitalWrite(left_1,LOW);
  digitalWrite(left_2,LOW);
  digitalWrite(right_1,LOW);
  digitalWrite(right_2,LOW);
  digitalWrite(front_1,LOW);
  digitalWrite(front_2,LOW);
  delay(x);
}

void Stop_car(int x)
{
  digitalWrite(left_1,LOW);
  digitalWrite(left_2,LOW);
  digitalWrite(right_1,LOW);
  digitalWrite(right_2,LOW);
  delay(x);
}

 void Code_right()
{
  count_right += 1; // 编码器码盘计数加一  
}
void Code_left()
{
  count_left += 1;  
}
void Code_front()
{
  count_front += 1;  
}



void first_mean()
{
  start();
  
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
