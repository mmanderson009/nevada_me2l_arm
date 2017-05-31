/*
 * Name: arm_program
 * Author: Jamie Poston
 * This program is designed to be used with the Unplugged Robotics lesson taught by the University of Nevada, Reno's Mobile Engineering Education Lab(ME2L).
 * This program sets the initial position of all the motors on the arm to take when turned on.
 * This program features:
 *      -Toggle Function to lift and lower left motor (wrist)
 *      -Toggle Function to extend and retract right motor (arm)
 *      -Toggle Function to open and close claw
 *      -Toggle Function to turn robot on and off (also known as 'reset')
 *      -Function to let robot move right and left (base)
 * Please keep in mind that your robots may need different angles than the ones here, but these are close for most robot arms.
 * Things to note:
 *      -The arm should be able to retract after extending with little issue
 *      -The base should hit, 0, 45, 90, 135, 180 degrees or at least angles that are distinct enough to represent that.
 *      -The wrist should be able to raise the jaw up to be parallel with the ground, and lower it to pick up no more than five stacked blocks
 *      -The claw should open up just a bit wider than the block, and close just enough to hold it. If the claw it too tight around the block, some of the other motors may be unable to operate appropriately.
 * Troubleshooting:
 *      -Robot shaking when plugged in:
 *            -Try: Pushing down all wires to make sure they're plugged in all the way
 *            -Try: Making sure the joystick is in the correct holes
 *            -Try: Plugging the robot into the wall
 *            -Try: Making sure you don't have stripped motors. You will hear a loud whirling if this is the case.
 */
#include <Servo.h>
#include <SPI.h>

const int SERVOS = 4; //sets SERVOS as a constant variable to represent 4
int PIN[SERVOS], MIN[SERVOS], MAX[SERVOS], INITANGLE[SERVOS], ANA[SERVOS], DIG[3], ARM[3][2][2], WRIST[2], BASE[5], CLAW[2], baseIndex, clawIndex, onOff, offset[3];
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
  INITANGLE[0] = BASE[baseIndex];

  //Left Side
  PIN[1] = 8;
  MIN[1] = 60; // This should bring the lever to just below 90deg to ground
  MAX[1] = 165; 

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
  MIN[3] = 100;
  MAX[3] = 145;
  INITANGLE[3] = MAX[3]; 
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
  Serial.print("Base: ");
  Serial.print(value);
  if (value < 412)
  {
    baseIndex++;
    if (baseIndex > 4)
      baseIndex = 4;
  }
  else if (value > 612)
  {
    baseIndex--;
    if (baseIndex < 0)
      baseIndex = 0;
  }
  while (analogRead(ANA[1]) > 612 || analogRead(ANA[1]) < 412);
}

void horzPos()
{
  int value = analogRead(ANA[0]);
  Serial.print("Horz: ");
  Serial.println(value);
  if (value > 612)
  {
    if (WRIST[0] == 0)
      WRIST[0] = 1;
  }
  else if (value < 412)
  {
    if (WRIST[0] == 1)
      WRIST[0] = 0;
  }
}

void toggleWrist()
{
  if (WRIST[1] == 0)
    WRIST[1] = 1;
  else if (WRIST[1] == 1)
    WRIST[1] = 0;
}

void toggleClaw()

{
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

  Serial.print("Start All Movement ");
  Serial.println();

  for (int i = 0; i < SERVOS; i++) {
    myservo[i].attach(PIN[i]);
    myservo[i].write(INITANGLE[i]);
    delay(500);
  }
  onOff = 1;
}

void stopMoving()
{
  Serial.print("Stop All Movement ");
  Serial.println();

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
  for (int i = 1; i < 3; i++)
    myservo[i].write(ARM[i][WRIST[0]][WRIST[1]]);
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

  basePos();
  horzPos();
  writeServos();

}
