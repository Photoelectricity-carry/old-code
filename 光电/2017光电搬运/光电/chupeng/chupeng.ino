int servo_touch=16;//控制舵机触控开关
void setup() 
{
  pinMode(servo_touch, INPUT);//触控开关为输入模式
  Serial.begin(9600);
}

void loop() 
{
while(1)
{
    Serial.println(digitalRead(servo_touch));
    delay(100);
}
}
