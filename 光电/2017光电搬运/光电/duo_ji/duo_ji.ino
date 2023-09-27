#include <Servo.h>
Servo myservo_1;

void setup() 
{
Serial.begin(9600);  
myservo_1.attach(9);
}

void loop() 
{                 
 myservo_1.write(50);                                            
}

