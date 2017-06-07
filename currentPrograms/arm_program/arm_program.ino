/*
 * Name: arm_program
 * Author: Jamie Poston and Mercedes Anderson
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

//**********INCLUDED LIBRARIES**********//
#include <Servo.h>
#include <SPI.h>
//////////////////////////////////////////

//****GLOBAL VARIABLE INITIALIZATION****//
const int NUM_SERVOS = 4;                       //Number of servos on the actual robot.
const int SERVO_PINS[NUM_SERVOS] = {10, 8, 7, 6};

Servo myservo[NUM_SERVOS]; //Create the servo objects for all servos

const int NUM_BASE_POSITIONS = 5;               //Number of pre-set base positions
const int BASE[NUM_BASE_POSITIONS] = {0, 45, 90, 135, 180}; //Pre-set positions for the base

const int NUM_ARM_POSITIONS = 2;                //Number of positions for one joint.
const int NUM_ARM_JOINTS = 3;                   //One more than the amount of joints so that the loops work properly.
//Pre-set positions for the arm joints. First index is back/forward. Second index is up/down.
const int ARM[NUM_ARM_JOINTS][NUM_ARM_POSITIONS][NUM_ARM_POSITIONS] = { { {0, 0} , {0, 0} }, { {80, 80}, {120, 120} }, { {160, 120}, {160, 120} } };

//Sets constant values for the joystick
//To determine where the joystick is being moved.
const int LOW_JOYSTICK_VALUE = 412;
const int HIGH_JOYSTICK_VALUE = 612;

const int TOGGLE_SIZE = 2;                      //Sets the size of the toggleable arrays
const int CLAW[TOGGLE_SIZE] = {100, 145};       //Pre-set positions for the claw

const int NUM_DIGITAL_BUTTONS = 3;              //Number of digital buttons for the robot
const int DIG[NUM_DIGITAL_BUTTONS] = {4, 3, 2}; //Pins for the digital buttons

const int NUM_ANALOG = 2;                       //Number of analog joysticks pins for the robot (One each for the x and y axises)
const int ANA[NUM_ANALOG] = {0, 2};             //Pins for the analog joystick

const int BASE_START_POS = 2;
const int CLAW_START_POS = 1;
const int WRIST_START_POS[TOGGLE_SIZE] = {0,0};

int baseIndex = BASE_START_POS;                 //Initial position for base
int clawIndex = CLAW_START_POS;                 //Initial position for claw
int onOff = 1;                                  //Initial setting for board being on initially
int WRIST[TOGGLE_SIZE];

//Initial angles for all the servos. Arm should be parallel with the ground.
const int INITANGLE[NUM_SERVOS] = {BASE[baseIndex], ARM[1][0][0], ARM[2][0][0], CLAW[clawIndex]};

bool update = false;                            //global variable for updating servo positions

//////////////////////////////////////////

//FUNCTION:   setup
//DEFINITION: Setup runs once at the begining of the program to initialize the program
//DETAILS:    This function initializes all the servos to the correct arduino pins
//            as well as writing the initial angle to the servos.
//            Also begins Serial for debugging.
//PARAMETERS: None.
//RETURNS:    None.
void setup()   {
	Serial.begin(9600); //Begins the Serial for debugging. Viewable through Arduino IDE


 memcpy(WRIST, WRIST_START_POS, sizeof(WRIST)); //Initialize array for WRIST
 
	//Attach all the servo objects to the correct pins
  //To be able to grab the right information for the servos
	for (int i = 0; i < NUM_SERVOS; i++) {
		myservo[i].attach(SERVO_PINS[i]); //Attaches servo to pin
		myservo[i].write(INITANGLE[i]);   //Writes initial angle to servo
		delay(500);                       //Time delay for safety
	}
}

//FUNCTION:   basePos
//DEFINITION: Updates position of base.
//DETAILS:    Based on analog value, increments or decrements baseIndex.
//            Waits until joystick returns to center.
//PARAMETERS: value from the analog joystick
//RETURNS:    None.
void basePos(int analogValue)
{
	Serial.print("Base: ");
	Serial.print(analogValue);
	if (analogValue < LOW_JOYSTICK_VALUE)
	{
		baseIndex++;
		if (baseIndex > 4)
			baseIndex = 4;
    update = true;
	}
	else if (analogValue > HIGH_JOYSTICK_VALUE)
	{
		baseIndex--;
		if (baseIndex < 0)
			baseIndex = 0;
    update = true;
	}
	while (analogRead(ANA[1]) > HIGH_JOYSTICK_VALUE || analogRead(ANA[1]) < LOW_JOYSTICK_VALUE);
}

//FUNCTION:   horzPos
//DEFINITION: Updates forward/backward position of arm
//DETAILS:    Based on analog values, toggle WRIST[0]
//PARAMETERS: value from the analog joystick
//RETURNS:    None.
void horzPos(int analogValue)
{
	Serial.print("Horz: ");
	Serial.println(analogValue);
	if (analogValue > HIGH_JOYSTICK_VALUE)
	{
		if (WRIST[0] == 0)
			toggleWrist(0);
	}
	else if (analogValue < LOW_JOYSTICK_VALUE)
	{
		if (WRIST[0] == 1)
			toggleWrist(0);
	}
}

//FUNCTION:   toggleWrist
//DEFINITION: toggles a WRIST value
//DETAILS:    None.
//PARAMETERS: index for which WRIST value needs to be toggled
//RETURNS:    None.
void toggleWrist(int wristIndex)
{
	if (WRIST[wristIndex] == 0)
		WRIST[wristIndex] = 1;
	else if (WRIST[wristIndex] == 1)
		WRIST[wristIndex] = 0;
  update = true;
}

//FUNCTION:   toggleClaw
//DEFINITION: toggles the clawIndex
//DETAILS:    None.
//PARAMETERS: None.
//RETURNS:    None.
void toggleClaw()

{
	if (clawIndex == 0)
		clawIndex = 1;
	else if (clawIndex == 1)
		clawIndex = 0;
  update = true;
}

//FUNCTION:   toggleOn
//DEFINITION: toggles on/Off
//DETAILS:    Checks onOff value
//            Calls appropriate start/stop moving function
//PARAMETERS: None.
//RETURNS:    None.
void toggleOn()
{
	if(onOff == 1)
  {
		stopMoving();
    onOff = 0;
  }
	else
  {
   memcpy(WRIST, WRIST_START_POS, sizeof(WRIST));
    baseIndex = BASE_START_POS;
    clawIndex = CLAW_START_POS;
    
		startMoving();
    onOff = 1;
  }
  update = true;
}

//FUNCTION:   startMoving
//DEFINITION: Initializes servos
//DETAILS:    Attaches all servos and writes initial angle
//PARAMETERS: None.
//RETURNS:    None.
void startMoving()
{

	Serial.print("Start All Movement ");
	Serial.println();

	for (int i = 0; i < NUM_SERVOS; i++) {
		myservo[i].attach(SERVO_PINS[i]);
		myservo[i].write(INITANGLE[i]);
		delay(500);
	}
}

//FUNCTION:   stopMoving
//DEFINITION: Stops all servos
//DETAILS:    Detaches all servos from pins
//            Doesn't actually turn the board off.
//            Resets values to inital values
//PARAMETERS: None.
//RETURNS:    None.
void stopMoving()
{
	Serial.print("Stop All Movement ");
	Serial.println();

	for (int i = 0; i < NUM_SERVOS; i++)
		myservo[i].detach();
}

//FUNCTION:   debounce
//DEFINITION: debounces data on digital pin
//DETAILS:    The data on an individual pin sometimes vacillates before settling.
//            This function 'debounces' the pin by checking the pin after .1 seconds
//            After the delay, if the new data off the pin is the same as the old data, then it must be true.
//            This is only really checking for a value of 1, or the button being pressed.
//PARAMETERS: The pin number that is being debounced.
//RETURNS:    The debounced value.
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

//FUNCTION:   writeServos  
//DEFINITION: Updates servo positions
//DETAILS:    Takes all the current positions and writes them to the servos
//PARAMETERS: None.
//RETURNS:    None.
void writeServos()
{
	myservo[0].write(BASE[baseIndex]);
	for (int i = 1; i < 3; i++)
		myservo[i].write(ARM[i][WRIST[0]][WRIST[1]]);
	myservo[3].write(CLAW[clawIndex]);
  update = false;
}

//FUNCTION:   loop
//DEFINITION: Constantly runs during the program
//DETAILS:    Every 0.15 seconds, this checks to see if a user has interacted with the buttons or joystick
//            If they have, then update the appropriate servo
//PARAMETERS: None.
//RETURNS:    None.
void loop()
{
	delay(15); // Delay function to slow movement of arm down

	if (debounce(DIG[0]) == 1)
		toggleWrist(1);

	if (debounce(DIG[1]) == 1)
		toggleClaw();

	if (debounce(DIG[2]) == 1)
		toggleOn();

	basePos(analogRead(ANA[1]));
	horzPos(analogRead(ANA[0]));

  if (update)
	  writeServos();

}
