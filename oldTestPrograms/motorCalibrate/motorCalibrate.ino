#include <Servo.h>
#include <SPI.h>

const int SERVOS = 4;
int PIN[SERVOS], currentAngle[SERVOS], MIN[SERVOS], MAX[SERVOS], INITANGLE[SERVOS], ANA[SERVOS], DIG[3], ARM[3][2][2], WRIST[2], BASE[5], CLAW[2], baseIndex, clawIndex, onOff;
Servo myservo[SERVOS];

void setup()   {
  Serial.begin(9600);

  baseIndex = 2;
  BASE[0] = 0;
  BASE[1] = 45;
  BASE[2] = 90;
  BASE[3] = 135;
  BASE[4] = 180;
  //Middle Servo
  PIN[0] = 10;
  MIN[0] = BASE[0];
  MAX[0] = BASE[4];
  INITANGLE[0] = 90;

  //Left Side
  PIN[1] = 8;
  MIN[1] = 60; // This should bring the lever to just below 90deg to ground
  MAX[1] = 165;
  ARM[1][0][0] = 67;
  ARM[1][0][1] = 150;
  ARM[1][1][0] = 122;
  ARM[1][1][1] = 152;
  INITANGLE[1] = 152; // This should bring the lever parallel with the ground
  ANA[0] = 0;
  //Right Side
  PIN[2] = 7;
  MIN[2] = 40;
  MAX[2] = 180;
  ARM[2][0][0] = 180;
  ARM[2][0][1] = 65;
  ARM[2][1][0] = 180;
  ARM[2][1][1] = 140;
  INITANGLE[2] = 90;
  ANA[1] = 2;
  DIG[0] = 4;
  //Claw Servo
  PIN[3] = 6;
  MIN[3] = 90;
  MAX[3] = 160;
  INITANGLE[3] = 60;
  DIG[1] = 3;

  WRIST[0] = 0;
  WRIST[1] = 0;
  CLAW[0] = MIN[3];
  CLAW[1] = MAX[3];
  clawIndex = 0;

  DIG[2] = 2;

  onOff = 1;

  for (int i = 0; i < SERVOS; i++) {
    myservo[i].attach(PIN[i]);
    myservo[i].write(INITANGLE[i]);
    delay(500);
  }
}

void loop()
{
  
}
