//teensy 3.2 Can test sanity check
//transciever TX connects to pin #3 (tx)
//transciever RX connects to pin #4(RX)
//this is not like serial which is weird.
#include <FlexCAN.h>
#include <Adafruit_NeoPixel.h>

void setup(void)
{
  Serial.begin(9600);
  Serial.println("online");

  Can0.begin(250000); //PE3 ECU SPEED

  //Allow Extended CAN id's through
  CAN_filter_t allPassFilter;
  allPassFilter.ext = 1;
  for (uint8_t filterNum = 1; filterNum < 16; filterNum++)
  {
    Can0.setFilter(allPassFilter, filterNum);
  }

  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
}

// -------------------------------------------------------------
void loop(void)
{
  CAN_message_t inMsg;
  inMsg.ext = true;
  while (Can0.available())
  {
    Can0.read(inMsg);

    Serial.print(inMsg.id);
    Serial.print(" ");

    for (int i = 0; i < inMsg.len; i++)
    {
      Serial.print(inMsg.buf[i]);
      Serial.print(" ");
    }

    Serial.println();

    digitalWrite(13, !digitalRead(13)); //flash the LED as messages come in
  }
}