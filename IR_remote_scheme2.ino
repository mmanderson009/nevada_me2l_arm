#include <IRremote.h>
#include <IRremoteInt.h>
#include <Servo.h>

//Jamie was here

int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;


Servo base, arm, wrist, gripper;

/*  SET TO PARTICULAR VALUES TO PREVENT MOVEMENT AT START */
int basePos = 90;
int armPos = 90; //RIGHT is arm
int wristPos = 90; //LEFT is wrist
int gripperPos = 15;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver

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
  if (irrecv.decode(&results))
    {
     Serial.println(results.value, HEX);
     irrecv.resume(); // Receive the next value
    }

     switch(results.value)
     {
        case 0xFD10EF: //left arrow
              Serial.print("Left Pressed");
              Serial.println();
              moveBaseLeft();
              break;
        case 0xFD50AF: //right arrow
              Serial.print("Right Pressed");
              Serial.println();
              moveBaseRight();
              break;
        case 0xFDA05F: //up arrow
              Serial.print("Up Pressed");
              Serial.println();
              moveArmForwards();
              break;
        case 0xFDB04F: //down arrow
              Serial.print("Down Pressed");
              Serial.println();
              moveArmBackwards();
              break;
        case 0xFD08F7: //one
              Serial.print("1 Pressed");
              Serial.println();
              moveWristUp();
              break;
        case 0xFD8877: //two
              Serial.print("2 Pressed");
              Serial.println();
              moveWristDown();
              break;
        case 0xFD28D7: //four
              Serial.print("4 Pressed");
              Serial.println();
              closeGripper();
              break;
        case 0xFDA857: //five
              Serial.print("5 Pressed");
              Serial.println();
              openGripper();
              break;
        case 0xFD58A7: //nine
              Serial.print("9 Pressed");
              Serial.println();
              stopMoving();
              break;
        case 0xFD807F: //Play button
              Serial.print("Play was pressed.");
              Serial.println();
              startMoving();
              break;
     }
}

void moveBaseLeft()
{
  Serial.print("Moving base left ");
  Serial.println();
  Serial.print("BasePos Value: ");
  Serial.print(basePos);
  Serial.println();

  
  if (basePos >= 0 && basePos != 180)
    {
      basePos = basePos + 45;
      base.write(basePos);
      delay(15);
    }
  
  if (basePos == 180)
    {
      Serial.print("Reached end of travel....stopping");
      Serial.println();
      
    }
      
  Serial.flush();

}

void moveBaseRight()
{
  Serial.print("Moving base right ");
  Serial.println();
  Serial.print("BasePos Value: ");
  Serial.print(basePos);
  Serial.println();
  
  if (basePos <= 180 && basePos != 0)
    {
      basePos = basePos - 45;
      base.write(basePos);
      delay(15);
    }
  
  if (basePos == 0)
    {
      Serial.print("Reached end of travel....stopping");
      Serial.println();
    }
    
  Serial.flush();
 
}
  
void moveArmForwards()
{
  Serial.print("I'm in the function");
  Serial.println();
  Serial.print("Moving Arm Forwards ");
  Serial.println();
  
  Serial.print("armPos Value: ");
  Serial.print(armPos);
  Serial.println();
  
  if (armPos >=40 && armPos != 180)
    {
      armPos = armPos + 10;
      arm.write(armPos);
      delay(15);
    }

  if( armPos > 145 )
  {
    wrist.write(150);
  }

  if (armPos == 180)
    {
      Serial.print("Reached end of travel....stopping");
      Serial.println(); 
    }
    
  Serial.flush();
  
}

void moveArmBackwards()
{
  Serial.print("I'm in the function");
  Serial.println();
  Serial.print("Moving Arm backwards ");
  Serial.println();
  
  Serial.print("armPos Value: ");
  Serial.print(armPos);
  Serial.println();


  if( wristPos <= 90 )
  {
      arm.write(70);
    
  } else if (armPos <= 180 && armPos != 40)
    {
      armPos = armPos - 10;
      arm.write(armPos);
      delay(15);
    }


  
  if (armPos == 40)
    {
      Serial.print("Reached end of travel....stopping");
      Serial.println();
    }
     
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
      wristPos = wristPos + 5;
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
      
  } else if (wristPos <= 165 && wristPos != 70)
    {
      wristPos = wristPos - 5;
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
