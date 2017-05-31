#include <Servo.h>
#include <SPI.h>

const int SERVOS = 4;
int PIN[SERVOS], MIN[SERVOS], MAX[SERVOS], INITANGLE[SERVOS], ANA[SERVOS], DIG[3], ARM[3][2][2], WRIST[2], BASE[5], CLAW[2], baseIndex, clawIndex, onOff, offset[3];
Servo myservo[SERVOS];

/////////////////
/*
THIS VERSION DOES NOT INCLUDE WRIST DOWN
Well not as far, everything is very tall.
Only temporary for school pilot on 06/03/2016
*/
/////////////////

//CURRENT STATUS
//Arm is not going out far enough
//Arm does not have enough difference when going up and down

void setup()   {
  Serial.begin(9600);

  //Dallas is 0000
  
  offset[0] = 0;//0;
  offset[1] = 0;//10;
  offset[2] = 0;//-35;
  offset[3] = 0;//-10;
  

  baseIndex = 2;
  BASE[0] = 0;
  BASE[1] = 45;
  BASE[2] = 90;
  BASE[3] = 135;
  BASE[4] = 180;
  //Middle Servo
  PIN[0] = 10;

  //Original values for max and min, not actually used anywhere
  /*
  MIN[0] = BASE[0];
  MAX[0] = BASE[4];
  */
  INITANGLE[0] = BASE[baseIndex];

  /////////////Right Side
  PIN[1] = 8;

  //Original values for max and min, not actually used anywhere
  /*
  MIN[1] = 60; // This should bring the lever to just below 90deg to ground
  MAX[1] = 165; //supposed to be 160. That's whay jamie left it at.
  */

  //CHANGE THESE VALUES FOR RIGHT MOTOR POSITION
  ARM[1][0][0] = 80;
  ARM[1][0][1] = 80;
  ARM[1][1][0] = 120;
  ARM[1][1][1] = 100;
  INITANGLE[1] = ARM[1][0][0]; // This should bring the lever parallel with the ground
  ANA[0] = 0;

  
  ///////////////Left Side
  PIN[2] = 7;

  //Original values for max and min, not actually used anywhere
  /*
  MIN[2] = 40;
  MAX[2] = 180;
  */
  //CHANGE THESE VALUES FOR LEFT ARM POSITION
  //FIRST INDEX IS BACK/FORWARD
  //SECOND INDEX IS UP/DOWN
  ARM[2][0][0] = 145;
  ARM[2][0][1] = 180;
  ARM[2][1][0] = 145;
  ARM[2][1][1] = 180;
  INITANGLE[2] = ARM[2][0][0];
  ANA[1] = 2;
  DIG[0] = 4;
  //Claw Servo
  PIN[3] = 6;
  MIN[3] = 90;
  MAX[3] = 135;
  INITANGLE[3] = MAX[3]; //started as 100
  DIG[1] = 3;

  WRIST[0] = 0;
  WRIST[1] = 0;
  CLAW[0] = MIN[3];
  CLAW[1] = MAX[3];
  clawIndex = 1;

  DIG[2] = 2;

  onOff = 1;

  for (int i = 0; i < SERVOS; i++) {
    myservo[i].attach(PIN[i]);
    myservo[i].write(INITANGLE[i]);
    delay(500);
  }
}

void basePos()
{
  int value = analogRead(ANA[1]);
  //Serial.print("Base: ");
  //Serial.print(value);
  if (value < 412)
  {
    Serial.print(" Moving Base ");
    baseIndex++;
    if (baseIndex > 4)
      baseIndex = 4;
  }
  else if (value > 612)
  {
    Serial.print(" Moving Base ");
    baseIndex--;
    if (baseIndex < 0)
      baseIndex = 0;
  }
  while (analogRead(ANA[1]) > 612 || analogRead(ANA[1]) < 412);
}

void horzPos()
{
  int value = analogRead(ANA[0]);
  //Serial.print("Horz: ");
  //Serial.println(value);
  if( WRIST[1] == 1 )
  {
    if (value > 612)
    {
      Serial.print(" Moving Arm ");
      if (WRIST[0] == 0)
        WRIST[0] = 1;
    }
    else if (value < 412)
    {
      Serial.print(" Moving Arm ");
      if (WRIST[0] == 1)
        WRIST[0] = 0;
    }
  }
  while (analogRead(ANA[0]) > 612 || analogRead(ANA[0]) < 412);
}

void toggleWrist()
{
  Serial.print(" Toggling wrist ");
  if (WRIST[1] == 0)
    WRIST[1] = 1;
  else if (WRIST[1] == 1)
    WRIST[1] = 0;
}

void toggleClaw()

{
  Serial.print(" Toggling Claw ");
  if (clawIndex == 0)
    clawIndex = 1;
  else if (clawIndex == 1)
    clawIndex = 0;
}

void toggleOn()
{
  if(onOff == 1)
    stopMoving();
  else
    startMoving();
  
}

void startMoving()
{

  //Serial.print("Start All Movement ");
  //Serial.println();

  for (int i = 0; i < SERVOS; i++) {
    myservo[i].attach(PIN[i]);
    myservo[i].write(INITANGLE[i]);
    delay(500);
  }
  onOff = 1;
}

void stopMoving()
{
  //Serial.print("Stop All Movement ");
  //Serial.println();

  for (int i = 0; i < SERVOS; i++)
    myservo[i].detach();

  WRIST[0] = 0;
  WRIST[1] = 0;
  clawIndex = 1;
  baseIndex = 2;

  onOff = 0;
}

int debounce(int pin)
{
  int value = digitalRead(pin);
  if ( value == 1 )
  {
    delay(100);
    if (value == digitalRead(pin))
    {
      while (digitalRead(pin) == 1);
      return 1;
    }
  }
  return 0;
}

void writeServos()
{
  myservo[0].write(BASE[baseIndex]);
  delay(50);
  for (int i = 1; i < 3; i++)
  {
    myservo[i].write(ARM[i][WRIST[0]][WRIST[1]]);
    delay(50);
  }
  myservo[3].write(CLAW[clawIndex]);
}


void loop()
{
  delay(15); // Delay function to slow movement of arm down

  if (debounce(DIG[0]) == 1)
    toggleWrist();

  if (debounce(DIG[1]) == 1)
    toggleClaw();

  if (debounce(DIG[2]) == 1)
    toggleOn();
 //delay(300);

  basePos();
  horzPos();
  //if(onOff == 1)
  writeServos();
  //Serial.println();
}
