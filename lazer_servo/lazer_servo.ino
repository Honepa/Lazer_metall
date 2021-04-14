#include <Servo.h>

Servo servo_lazer;

void setup() 
{
  servo_lazer.attach(3);
  pinMode(13, 1);
  digitalWrite(13, 1);

}

void loop() 
{
  
  for(int i = 0; i < 180; i++)
  {
    servo_lazer.write(i);
    delay(10);
  }
  delay(1000);
  for(int i = 180; i > 0; i--)
  {
    servo_lazer.write(i);
    delay(10);
  }
  
  //servo_lazer.write(0);
}
