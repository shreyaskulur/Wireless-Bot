#include <SPI.h>  
#include "RF24.h"

RF24 myRadio (6, 7);
byte addresses[][6] = {"0"};

struct package
{
  int lx;
  int ly;
  int rx;
  int ry;
};


typedef struct package Package;
Package data;

int lx, ly, rx, ry;

void updateJoy()
{
  data.lx= analogRead(0);
  data.ly= analogRead(1);
  data.rx= analogRead(2);
  data.ry= analogRead(3);
  Serial.print("LX = ");
  Serial.print(data.lx);
  Serial.print("  LY = ");
  Serial.print(data.ly);
  Serial.print("  RX = ");
  Serial.print(data.rx);
  Serial.print("  RY = ");
  Serial.println(data.ry);
}

void setup()
{
  Serial.begin(115200);
  delay(1000);
  myRadio.begin();  
  myRadio.setChannel(115); 
  myRadio.setPALevel(RF24_PA_LOW);
  myRadio.setDataRate( RF24_250KBPS ) ; 
  myRadio.openWritingPipe( addresses[0]);
  delay(1000);
}

void loop()
{
  myRadio.write(&data, sizeof(data)); 
  updateJoy();
  
}
