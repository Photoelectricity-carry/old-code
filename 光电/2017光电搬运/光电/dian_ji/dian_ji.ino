int LIN1 = 7;
int LIN2 = 8;


int LIN3 = 3;
int LIN4 = 4;


void setup() 
{
  pinMode(LIN1, OUTPUT);
  pinMode(LIN2, OUTPUT);
    pinMode(LIN3, OUTPUT);
  pinMode(LIN4, OUTPUT);
  digitalWrite(LIN1,LOW);//初始电机都处于停止状态
  digitalWrite(LIN2,LOW);
    digitalWrite(LIN3,LOW);//初始电机都处于停止状态
  digitalWrite(LIN4,LOW);
}

void loop() 
{
start_shun();
}

void start_shun()//编码器不巡线后退
{
       digitalWrite(LIN1,LOW);
       analogWrite(LIN2,120);

       
       digitalWrite(LIN3,LOW);
       analogWrite(LIN4,130);
       

}
void start_fan()//编码器不巡线后退
{
       digitalWrite(LIN2,LOW);
       analogWrite(LIN1,20);
       delay(3000);
}

void stop_1()
{
       digitalWrite(LIN1,LOW);
       analogWrite(LIN2,LOW);
       delay(2000);
  }
