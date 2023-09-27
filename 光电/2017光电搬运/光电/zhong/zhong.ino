int LIN1 = 12;
int LIN2 = 13;
int i = 5;          
long count_right;
void setup() 
{ Serial.begin(9600);
  pinMode(LIN1, OUTPUT);
  digitalWrite(LIN1,LOW);
  attachInterrupt(i, Code1, FALLING);
  detachInterrupt(i);
}

void loop() 
{ 
    fan();
  zheng(); 




}

void zheng()
{   
  count_right =0;
  attachInterrupt(i, Code1, FALLING);
  while(1)
  {  
    if(count_right < 5)
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

void fan()
{   
  count_right =0;
  attachInterrupt(i, Code1, FALLING);
  while(1)
  {  
    if(count_right < 5)
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
