#include <Servo.h>

Servo motor;  // create servo object to control a servo(motor)


void setup() {
  motor.attach(9);  // attaches the servo on pin 9 to the motor.

  /* CALIBRATING NOTES:
   * -Connect the ground from the brains board to the brown wire on motor 
   * -Connect the VCC from the brains board to the red wire on motor
   * -Connect pin 9 from the brains board to the yellow wire on motor
   * -Only uncomment one segment at a time for each motor
   * -Press the arrow above to upload the program to the brains board after chosing which motor you're calibrating
   */
  
  /* Uncomment the segment below for calibration of BASE Motor by erasing the '//' */ 
  // motor.write(90);
  
  /* Uncomment the segment below for calibration of RIGHT Motor by erasing the '//' */ 
   motor.write(90);
  
  /* Uncomment the segment below for calibration of LEFT Motor by erasing the '//' */ 
  
   //motor.write(152);
  
  /* Uncomment the segment below for calibration of CLAW Motor by erasing the '//' */ 
  // motor.write(60);

}

void loop() {
  // Nothing will be looped while calibrating the motors.
}

