int LIN1 = 13;
int LIN2 = 12;
int i = 5;
          
//18,19,20   
// 5, 4, 3

long count_right;
void setup() 
{ Serial.begin(9600);
  pinMode(LIN1, OUTPUT);
  pinMode(LIN2, OUTPUT);
  digitalWrite(LIN1,LOW);//初始两个电机都处于停止状态
  digitalWrite(LIN2,LOW);
  attachInterrupt(i, Code1, FALLING);
  detachInterrupt(i);
}

void loop() 
{     up(); 
  down();



}

void down()
{   
  count_right =0;
  attachInterrupt(i, Code1, FALLING);
  while(1)
  {  
    if(count_right < 10)
   {    
    analogWrite(LIN2,25);
    digitalWrite(LIN1,LOW);
    Serial.print("down");
    Serial.println(count_right);
    }
    else
    {
    break;
    }
  }
   detachInterrupt(i);
}

void up()//原地右转
{   
  count_right =0;
  attachInterrupt(i, Code1, FALLING);
  while(1)
  {  
    if(count_right < 10)
   {
    analogWrite(LIN1,25);
    digitalWrite(LIN2,LOW);
    Serial.print("up");
    Serial.println(count_right);
    }
    else
    {
      break ;
    }
  }
   detachInterrupt(i);
}

void stop_1()
{
       digitalWrite(LIN1,LOW);
       analogWrite(LIN2,LOW);
}

void Code1()
{
  count_right += 1; // 编码器码盘计数加一
}
