
void setup()
{
  pinMode(19, INPUT);
  pinMode(15, INPUT);
  pinMode(2,  INPUT);
  Serial.begin(9600);
}

void loop()
{
  Serial.print(digitalRead(19)); //y
  Serial.print("  ");
  Serial.print(digitalRead(15)); //x
  Serial.print("  ");
  Serial.print(digitalRead(2)); //z
  Serial.println("");
  delay(1500);
}
