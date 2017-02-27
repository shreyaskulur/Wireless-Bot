#include <SPI.h>  
#include "RF24.h" 

#define lf_speed 5   //left front chip enable pin                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
#define rf_speed 10  //right front chip enable pin
#define lb_speed 6   //left back chip enable pin
#define rb_speed 11  //right back chip enable pin
#define lmf 5   //left motor forward
#define lmb 6   //left motor back
#define rmf 9   //right motor forward
#define rmb 10   //left motor back

int l_speed=255; // set left drive speed in the range 0 to 255
int r_speed=255; // set right drive speed in the range 0 to 255

//turn left
void left ()
{
  digitalWrite(lmf, LOW);
  digitalWrite(lmb, HIGH);
  digitalWrite(rmf, HIGH);
  digitalWrite(rmb, LOW);
}

//turn right
void right ()
{
  digitalWrite(lmf, HIGH);
  digitalWrite(lmb, LOW);
  digitalWrite(rmf, LOW);
  digitalWrite(rmb, HIGH);
}

//move forward
void fwd ()
{
  digitalWrite(lmf, HIGH);
  digitalWrite(lmb, LOW);
  digitalWrite(rmf, HIGH);
  digitalWrite(rmb, LOW);
}

//move backwards
void rev ()
{
  digitalWrite(lmf, LOW);
  digitalWrite(lmb, HIGH);
  digitalWrite(rmf, LOW);
  digitalWrite(rmb, HIGH);
}

//stop motion
void stp ()
{
  digitalWrite(lmf, LOW);
  digitalWrite(lmb, LOW);
  digitalWrite(rmf, LOW);
  digitalWrite(rmb, LOW);
}

void motor_init()
{
  pinMode(lmf , OUTPUT);
  pinMode(lmb , OUTPUT);
  pinMode(rmf , OUTPUT);
  pinMode(rmb , OUTPUT);
  analogWrite( lmf, 0);
  analogWrite( rmf, 0);
  analogWrite( lmb, 0);
  analogWrite( rmb, 0);
}

RF24 myRadio (7, 8); 
struct package
{
  int lx;
  int ly;
  int rx;
  int ry;
};


byte addresses[][6] = {"0"}; 



typedef struct package Package;
Package data;

void setup() 
{
  Serial.begin(115200);
  delay(1000);
  motor_init();
  myRadio.begin(); 
  myRadio.setChannel(115); 
  myRadio.setPALevel(RF24_PA_LOW);
  myRadio.setDataRate( RF24_250KBPS ) ; 
  myRadio.openReadingPipe(1, addresses[0]);
  myRadio.startListening();
}


void loop()  
{

  if ( myRadio.available()) 
  {
    while (myRadio.available())
    {
      myRadio.read( &data, sizeof(data) );
    }
    Serial.print("\nReceived Package:");
    Serial.print(data.lx);
    Serial.print("  ");
    Serial.print(data.ly);
    Serial.print("  ");
    Serial.print(data.rx);
    Serial.print("  ");
    Serial.print(data.ry);
    Serial.println("  ");
    
  }
  //Serial.print("* ");

}
