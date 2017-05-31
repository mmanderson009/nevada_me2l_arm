#include <Servo.h> 

const int SERVOS = 4;
const int ACC = 10; // the accurancy of the potentiometer value before idle starts counting
int PIN[SERVOS], MIN[SERVOS], MAX[SERVOS], INITANGLE[SERVOS], ANA[SERVOS], DIG[3], ARM[3][2][2], WRIST[2], BASE[5], CLAW[2], baseIndex, clawIndex, onOff, offset[3];
Servo myservo[SERVOS];
  

void setup() {
  //Middle Servo
  BASE[0] = 0;
  BASE[1] = 45;
  BASE[2] = 90;
  BASE[3] = 135;
  BASE[4] = 180;
  //Middle Servo
  PIN[0] = 10;
  MIN[0] = BASE[0];
  MAX[0] = BASE[4];
  INITANGLE[0] = BASE[baseIndex];

  //Left Side
  PIN[1] = 8;
  MIN[1] = 60; // This should bring the lever to just below 90deg to ground
  MAX[1] = 165; //supposed to be 160. That's whay jamie left it at.

  //CHANGE THESE VALUES FOR RIGHT MOTOR POSITION
  ARM[1][0][0] = 80;
  ARM[1][0][1] = 80;
  ARM[1][1][0] = 120;
  ARM[1][1][1] = 120;
  INITANGLE[1] = ARM[1][0][0]; // This should bring the lever parallel with the ground
  ANA[0] = 0;
  //Right Side
  PIN[2] = 7;
  MIN[2] = 40;
  MAX[2] = 180;

  //CHANGE THESE VALUES FOR LEFT ARM POSITION
  //FIRST INDEX IS BACK/FORWARD
  //SECOND INDEX IS UP/DOWN
  ARM[2][0][0] = 160;
  ARM[2][0][1] = 120;
  ARM[2][1][0] = 160;
  ARM[2][1][1] = 120;
  INITANGLE[2] = ARM[2][0][0];
  ANA[1] = 2;
  DIG[0] = 4;
  //Claw Servo
  PIN[3] = 6;
  MIN[3] = 100  + offset[3];
  MAX[3] = 145 + offset[3];
  INITANGLE[3] = MAX[3]; //started as 100
  DIG[1] = 3;

  WRIST[0] = 0;
  WRIST[1] = 0;
  CLAW[0] = MIN[3];
  CLAW[1] = MAX[3];
  clawIndex = 1;

  DIG[2] = 2;
  
  for (int i = 0; i < SERVOS; i++)
  {
    myservo[i].attach(PIN[i]);
    myservo[i].write(INITANGLE[i]);

  }
  Serial.begin(9600);

}

void loop() {

  while( myservo[3].read() != MIN[3] )
  {
     myservo[3].write(MIN[3]);
     delay(100); 
  }
  delay(3000);
  
  while( myservo[3].read() != MAX[3] )
  {
     myservo[3].write(MAX[3]);
     delay(100); 
  }
  delay(3000);

  /*
  for( int j = MIN[3]; j < MAX[3]; j = j + 10 )
  {
    myservo[3].write(j);
    Serial.println(j);
    delay(1000);
  }
  */

}
