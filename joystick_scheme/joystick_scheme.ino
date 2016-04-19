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
int wristPos = 90; //LEFT is wrist
int gripperPos = 15;

void setup()
{
  Serial.begin(9600);

  base.attach(9);
  base.write(90);

  arm.attach(8);
  arm.write(90);

  wrist.attach(7);
  wrist.write(150);

  gripper.attach(6);
  gripper.write(60);

  Serial.print("Let's start!");
  Serial.println();
}

void loop()
{
   int x = analogRead(pin_x);   
   int y = analogRead(pin_y);
   int baseDir = 0;
   int armDir = 0;

   if(x > 520)
    {
      baseDir = -1;
    } else if(x < 480)
    {
      baseDir = 1;
    }
    if( y > 520 )
    {
      armDir = 1;
    } else if( y < 480 )
    {
      armDir = -1;
    }
    moveBase(baseDir); 
    moveArm(armDir);
}

void moveBase(int dir)
{
  Serial.print("Moving base left ");
  Serial.println();
  Serial.print("BasePos Value: ");
  Serial.print(basePos);
  Serial.println();
  basePos = basePos + dir;
  //Just in case it goes past 180
  if (basePos >= 180)
  {
    Serial.print("Reached end of travel....stopping");
    Serial.println();
    basePos = 180;
  }
  else if( basePos <= 0 )
  {
    Serial.print("Reached end of travel....stopping");
    Serial.println();
    basePos = 0;
  }

  base.write(basePos);
  delay(15);    
  Serial.flush();

}
  
void moveArm(int dir)
{
  Serial.print("Moving Arm Forwards ");
  Serial.println();
  
  Serial.print("armPos Value: ");
  Serial.print(armPos);
  Serial.println();
  armPos = armPos + dir;

  if (armPos >= 180)
  {
    Serial.print("Reached end of travel....stopping");
    Serial.println();
    armPos = 180;
  }
  else if( basePos <= 40 )
  {
    Serial.print("Reached end of travel....stopping");
    Serial.println();
    armPos = 40;
  }

  arm.write(armPos);

  if( armPos > 145 )
  {
    wrist.write(150);
  }

  delay(15);
  
  Serial.flush();
  
}
 
void moveWristUp()
{

  Serial.print("Moving Wrist Up ");
  Serial.println();
  
  Serial.print("wristPos Value: ");
  Serial.print(wristPos);
  Serial.println();
    
  if (wristPos >= 70 && wristPos != 165)
  {
    wristPos = wristPos + 1;
    wrist.write(wristPos);
    delay(15);
  }
  
  if (wristPos == 165)
  {
    Serial.print("Reached end of travel....stopping");
    Serial.println();
  }
      
  Serial.flush();

}

void moveWristDown()
{

  Serial.print("Moving Wrist Down ");
  Serial.println();
  Serial.print("wristPos Value: ");
  Serial.print(wristPos);
  Serial.println();

  if( armPos == 70 )
  {
      
  } 
  else if (wristPos <= 165 && wristPos != 70)
  {
    wristPos = wristPos - 1;
    wrist.write(wristPos);
    delay(15);
  }
  
  if (wristPos == 70)
  {
    Serial.print("Reached end of travel....stopping");
    Serial.println();
  }    
  Serial.flush();
 
}

void closeGripper()
{
//The exported expects 60 - 180 as an angle. Not 0 to 40
  Serial.print("Closing Gripper Jaws ");
  Serial.println();  
  Serial.print("gripperPos Value: ");
  Serial.print(gripperPos);
  Serial.println();
    
  if (gripperPos >= 0 && gripperPos != 40)
    {
      gripperPos++;
      gripper.write(gripperPos);
      delay(15);
    }
  
  if (gripperPos == 40)
    {
      Serial.print("Reached end of travel....stopping");
      Serial.println();
    }
      
  Serial.flush();
 
}

void openGripper()
{
  Serial.print("Opening Gripper Jaws ");
  Serial.println(); 
  Serial.print("gripperPos Value: ");
  Serial.print(gripperPos);
  Serial.println();
    
  if (gripperPos <= 40 && gripperPos != 0)
    {
      gripperPos--;
      gripper.write(gripperPos);
      delay(15);
    }
  
  if (gripperPos == 0)
    {
      Serial.print("Reached end of travel....stopping");
      Serial.println();
    }       
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
 
  delay(15);
 
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
 
  delay(15);
 
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
