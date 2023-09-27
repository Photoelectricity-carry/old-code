int left=0;

void setup() 
{
Serial.begin(9600);
pinMode(left,INPUT);
}

 
void loop() {
int a=analogRead(left);
Serial.print(a);
Serial.print("\t");
delay(300);
}
