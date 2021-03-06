/* 
 *  BASE FUNCTIONS CREATED BY: Alex's Mearm code Serial Control Code 04/04/2015 (c)
*/
#include <Servo.h>

int pin_x = 0;
int pin_y = 1;

Servo base, arm, wrist, gripper;

/*  SET TO PARTICULAR VALUES TO PREVENT MOVEMENT AT START */
int basePos = 90;
int armPos = 90; //RIGHT is arm
int wristPos = 150; //LEFT is wrist
int gripperPos = 180;
bool gripperState = false;
bool wristState = false;
bool powerState = true;

void setup()
{
  Serial.begin(9600);

  base.attach(9);
  base.write(basePos);

  arm.attach(8);
  arm.write(armPos); //RIGHT is arm

  wrist.attach(7);
  wrist.write(wristPos); //LEFT is wrist

  gripper.attach(6);
  gripper.write(gripperPos);

  pinMode(0, INPUT); //on/off button
  pinMode(2, INPUT); //wrist button
  pinMode(4, INPUT); //claw button

  Serial.print("Let's start!");
  Serial.println();
}

void loop()
{
   //Check joystick
   int x = analogRead(pin_x);   
   int y = analogRead(pin_y);

   //Check buttons
   int onOFF = digitalRead(0);
   int wristRead = digitalRead(2);
   int gripperRead = digitalRead(4);

   //Set initial values for direction
   int baseDir = 0;
   int armDir = 0;

   if( !onOFF )
   {
      if( powerState )
      {
         //stopMoving();
         powerState = false;
      }
      else
      {
         //startMoving();
         powerState = true;
      }
   }

   if( !wristRead )
   {
      if( wristState )
      {
         //moveWristUp();
         wristState = false;
      }
      else
      {
         //moveWristDown();
         wristState = true;
      }
   }
/*
   if( gripperRead )
   {
      Serial.print(gripperRead);
      if( gripperState )
      {
         openGripper();
         gripperState = false;
      }
      else
      {
         //closeGripper();
         //gripperState = true;
      }
   }
*/

    if(x > 520)
    {
      moveBase(-1);
    } else if(x < 480)
    {
      moveBase(1);
    }

    if( y > 520 )
    {
      moveArm(1);
    } else if( y < 480 )
    {
      moveArm(-1);
    }
}

void moveBase(int dir)
{
  basePos = basePos + dir;
  
  //Just in case it goes past 180
  if (basePos >= 180)
  {
    Serial.print("Reached too high on base, stopping");
    Serial.println();
    basePos = 180;
  }
  else if( basePos <= 0 )
  {
    Serial.print("Reached too low on base, stopping");
    Serial.println();
    basePos = 0;
  }

  base.write(basePos);
  delay(20);    
  Serial.flush();

}
  
void moveArm(int dir)
{
  //UPDATE ALL FUNCTIONS WITH THIS PLS
  armPos = arm.read();
  armPos = armPos + dir;

  if (armPos >= 180)
  {
    Serial.print("Reached too high on arm, stopping");
    Serial.println();
    armPos = 180;
  }
  else if( armPos <= 40 )
  {
    Serial.print("Reached too low on arm, stopping");
    Serial.println();
    armPos = 40;
  }

  arm.write(armPos);

  if( armPos > 145 )
  {
    wrist.write(150);
  }
  delay(20);
  Serial.flush();
  
}
 
void moveWristUp()
{

  Serial.print("Moving Wrist Up ");
  Serial.println();
  /*
  Serial.print("wristPos Value: ");
  Serial.print(wristPos);
  Serial.println();
    
  if (wristPos >= 70 && wristPos != 165)
  {
    wristPos = wristPos + 1;
    wrist.write(wristPos);
  }
  
  if (wristPos == 165)
  {
    Serial.print("Reached too high on wrist, stopping");
    Serial.println();
  }
  */
  wrist.write(165);
  Serial.flush();

}

void moveWristDown()
{

  Serial.print("Moving Wrist Down ");
  /*
  Serial.println();
  Serial.print("wristPos Value: ");
  Serial.print(wristPos);
  Serial.println();

  if( armPos == 70 )
  {
      //??? ask merc
  } 
  else if (wristPos <= 165 && wristPos != 70)
  {
    wristPos = wristPos - 1;
    wrist.write(wristPos);
  }
  
  if (wristPos == 70)
  {
    Serial.print("Reached too low on wrist, stopping");
    Serial.println();
  }
  */
  wrist.write(70);
  Serial.flush();
 
}

void closeGripper()
{
//The exported expects 60 - 180 as an angle. Not 0 to 40
  Serial.print("Closing Gripper Jaws ");
  /*Serial.println();  
  Serial.print("gripperPos Value: ");
  Serial.print(gripperPos);
  Serial.println();
    
  if (gripperPos >= 60 && gripperPos <= 180)
    {
      gripperPos++;
      gripper.write(gripperPos);
    }
  
  if (gripperPos == 180)
    {
      Serial.print("Reached too high on wrist, stopping");
      Serial.println();
    }
*/
  gripperPos = 180;
  gripper.write(gripperPos);
      
  Serial.flush();
 
}

void openGripper()
{
  Serial.print("Opening Gripper Jaws ");
  /*Serial.println(); 
  Serial.print("gripperPos Value: ");
  Serial.print(gripperPos);
  Serial.println();
  
  if (gripperPos <= 180 && gripperPos != 60)
  {
    gripperPos--;
    gripper.write(gripperPos);
  }
  
  
  if (gripperPos == 60)
  {
    Serial.print("Reached end of travel....stopping");
    Serial.println();
  }       
  */

  gripperPos = 60;
  gripper.write(gripperPos);
  Serial.flush();
  
}


void startMoving()
{
  
  Serial.print("Start All Movement ");
  Serial.println();
 
  base.attach(9);
  arm.attach(8);
  wrist.attach(7);
  gripper.attach(6);
 
  Serial.flush();
 
}


void stopMoving()
{
  Serial.print("Stop All Movement ");
  Serial.println();
    
  base.detach();
  arm.detach();
  wrist.detach();
  gripper.detach();
  
  Serial.flush();
 
}

void software_Reboot()
{
/*
  wdt_enable(WDTO_15MS);
  while(1)
  {
  }
*/

}

