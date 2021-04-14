#include <Wire.h>
#include <VL53L0X.h>
#include <Stepper.h>

Stepper stepper1(200, 3,  4,  5,  6);
Stepper stepper2(200, 9, 10, 11, 12);
VL53L0X sensor;

float S_mm, A_mm = 0;
int An = 10;

float get_mm()
{
  long mm = 0;
  for (int i = 0; i < 10; i++)
  {
    mm += sensor.readRangeContinuousMillimeters();
  }
  //S_mm = S_mm + mm - A_mm;
  //A_mm = S_mm / An;
  return mm / 10.0;
}


void setup()
{
  Serial.begin(9600);

  Wire.begin();
  sensor.setTimeout(500);
  //Serial.println("9600");
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    delay(1000);
    //while (1) {}
  }
  //Serial.println("9601");
  sensor.startContinuous();
  pinMode(47, 1);
  pinMode(43, 1);
  digitalWrite(47, 0);
  digitalWrite(43, 1);
  /*
    for(int i = 0; i < 150; i++)
    {
    Serial.println(get_mm());
    /get_mm();
    delay(1);
    }
    Serial.println("init done");
  */
  stepper1.setSpeed(200);
  pinMode( 2, 1);
  pinMode( 7, 1);
  digitalWrite( 2, 1);
  digitalWrite( 7, 1);

  stepper2.setSpeed(200);
  pinMode( 8, 1);
  pinMode(13, 1);
  digitalWrite( 8, 1);
  digitalWrite(13, 1);
}

void loop()
{
  Serial.print("go");
  for (int i = 0; i < 24; i++)
  {
    for (int j = 0; j < 20; j++)
    {
      if (i % 2 == 0)
      {
        stepper1.step( 120);     delay(1000);
      }
      else
      {
        stepper1.step(-120);    delay(1000);
      }
    }
    stepper2.step( 120);
    delay(1000);
  }
  stepper2.step(-120*24);
  while (1);
}
//Serial.print(get_mm());
//Serial.print(get_mm());
//        Serial.print(" ");
//        Serial.print(j);
//        Serial.print(" ");
//        Serial.print(i);
//        Serial.print('\n')
//
//        Serial.print(" ");
//        Serial.print(j);
//        Serial.print(" ");
//        Serial.print(i);
//        Serial.print('\n');
