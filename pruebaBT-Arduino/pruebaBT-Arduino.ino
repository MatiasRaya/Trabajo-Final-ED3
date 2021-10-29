#include <SoftwareSerial.h>
SoftwareSerial miBT(10, 11);

void setup()
{
  Serial.begin(9600);
  Serial.println("Listo");
  miBT.begin(9600);
}

void loop()
{
  if (miBT.available())
  {
    Serial.write(miBT.read());
    Serial.write("   ");
  }
  if(Serial.available())
  {
    miBT.write(Serial.read());
  }
}
