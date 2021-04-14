float arr[10];
void setup()
{
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  digitalWrite(13, 0);
  arr[0] = 0.01;
  for (int i = 1; i < 10; i++)
  {
    arr[i] = arr[i - 1] + 0.01;
  }


}
int b = 0;
int state = 0;
void loop()
{
  if (Serial.available())
  {
    b = Serial.parseInt();
  }

  //Serial.print(b);
  switch (state)
  {
    case 0:
      {
        if (b != 40)
        {
          Serial.print(1);
        }
        else if (b == 40)
        {
          b = 0;
          state = 1;
        }
        break;
      }
    case 1:
      {
        //Serial.print(b);
        if (b == 43)
        {
          b = 0;
          state = 2;
        }
        else if (b == 45)
        {
          b = 0;
          state = 3;
        }
        break;
      }
    case 2:
      {
        digitalWrite(13, 1);

        for (int i = 0; i < 10; i++)
        {
          Serial.print(arr[i]);
          Serial.print(" ");
        }
        Serial.print('\n');
        state = 1;
        break;
      }
    case 3:
      {
        digitalWrite(13, 0);
        state = 1;
        break;
      }
  }

  /*
    if(b == 43)
    {
    digitalWrite(13, 1);
    }
    else if (b == 50)
    {
    digitalWrite(13, 0);
    }

    if (b == 43)
    {
    digitalWrite(13, 1);

    for (int i = 0; i < 10; i++)
    {
      Serial.print(arr[i]);
      Serial.print(" ");
    }
    Serial.print('\n');


    }
    else if (b == 50)
    {
    digitalWrite(13, 0);
    }
  */
}
