#include <Wire.h>
#include <VL53L0X.h>
VL53L0X sensor;

#define xEN 38
#define xDR A1
#define xST A0

#define yEN A2
#define yDR A7
#define yST A6

#define zEN A8
#define zDR 48
#define zST 46

#define FRW  1
#define BCK -1

#define X_STEPS_MM 200.0
#define Y_STEPS_MM 200.0

#define INIT        0
#define CONNECT     1
#define GET_COOR    2
#define RUN         3
#define OUTPUT_DATA 4

#define pm pinMode
#define dr digitalRead
#define dw digitalWrite
#define ar analogRead
#define aw analogWrite

const float x_dis = 0.1;
const float y_dis = 0.1;
int state, b, bx, by = 0;
float x, y;

void setup_x()
{
  pm(xEN, 1); dw(xEN, 1);
  pm(xDR, 1); dw(xDR, 0);
  pm(xST, 1); dw(xST, 0);
}

void setup_y()
{
  pm(yEN, 1); dw(xEN, 1);
  pm(yDR, 1); dw(xDR, 0);
  pm(yST, 1); dw(xST, 0);
}

void setup_z()
{

}

void setup_steppers()
{
  setup_x();
  setup_y();
  setup_z();
}

void sprint(int x, int y, float h)
{
  Serial.print(x);
  Serial.print('\t');
  Serial.print(y);
  Serial.print('\t');
  Serial.print(h);
  Serial.print('\n');
}

void x_enable(int a)
{
  dw(xEN, !a);
}

void y_enable(int a)
{
  dw(yEN, !a);
}

void z_enable(int a)
{
  dw(zEN, !a);
}

void x_step(int dir)
{
  bool d = dir == FRW ? 1 : 0;
  dw(xST, 0); dw(xDR, d);
  delayMicroseconds(600);
  dw(xST, 1); dw(xDR, !d);
  delayMicroseconds(600);
  x += dir * (1 / X_STEPS_MM);
}

void y_step(int dir)
{
  bool d = dir == FRW ? 1 : 0;
  dw(yST, 0); dw(yDR, d);
  delayMicroseconds(600);
  dw(yST, 1); dw(yDR, !d);
  delayMicroseconds(600);
  y += dir * (1 / Y_STEPS_MM);
}

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

void x_go(float mm)
{
  float steps = mm * X_STEPS_MM;
  x_enable(1);
  int d = steps > 0 ? FRW : BCK;
  for (long i = 0; i < abs(steps); i++)
  {
    x_step(d);
  }
  x_enable(0);
}

void y_go(float mm)
{
  float steps = mm * Y_STEPS_MM;
  y_enable(1);
  int d = steps > 0 ? FRW : BCK;
  for (long i = 0; i < abs(steps); i++)
  {
    y_step(d);
  }
  y_enable(0);
}

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    delay(1000);
    while (1) {}
  }
  sensor.startContinuous();
  setup_steppers(); x = 0; y = 0;

}

void loop()
{
  y_go(10);
//  delay(1000);
//  y_go(0.1);
//
//  while(1);
  //y_go(-10);
  //x_go(-10);
  /*
  if (Serial.available())
  {
    b = Serial.parseInt();
  }
  switch (state)
  {
    case INIT:
      {
        if (b != 40)
        {
          Serial.print(1);
        }
        else if (b == 40)
        {
          b = 0;
          state = CONNECT;
        }
        break;
      }
    case CONNECT:
      {
        if (b == 43)
        {
          b = 0;
          Serial.println();
          state = GET_COOR;
        }
        break;
      }
    case GET_COOR:
      {
        if (b == 50)
        {
          b = 0;
          state = RUN;
        }
        else if (b == 55)
        {
          b = 0;
          state = OUTPUT_DATA;
        }
        break;
      }
    case RUN:
      {
        if (b != 0)
        {
          //          1 = "-"
          //          2 = "+"
          //          3 = "0"
          bx = b / 10;
          by = b % 10;
          bx == 3 ? bx = 0 : bx = bx;
          by == 3 ? by = 0 : by = by;
          bx == 2 ? bx = 1 : bx = -1;
          by == 2 ? by = 1 : by = -1;
          x_go(bx * x_dis);
          y_go(10 * by * y_dis);
          b = 0;
          bx = 0;
          by = 0;
          state = RUN;
        }
        else if(b == 60)
        {
          b = 0;
          state = GET_COOR;
        }

        break;
      }
    case OUTPUT_DATA:
      {
        Serial.println(get_mm());
        state = GET_COOR;
        break;
      }
  }
  */
}
