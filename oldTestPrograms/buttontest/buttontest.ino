//This code has the mode select commented out as well as the slider code
//The result is a faster joysticks code. There's a delay function that we use to
// slow the movemement of the arm down.
// Idle is also set at 100 which probably needs adjusting to stop the servos timing out so quickly.

#include <Servo.h> 
#include <SPI.h>
//#include <Adafruit_GFX.h>
//#include <Adafruit_PCD8544.h>

// Hardware SPI (faster, but must use certain hardware pins):
// SCK is LCD serial clock (SCLK) - this is pin 13 on Arduino Uno
// MOSI is LCD DIN - this is pin 11 on an Arduino Uno
// pin 4 - Data/Command select (D/C)
// pin 8 - LCD chip select (CS)
// pin 7 - LCD reset (RST)
//Adafruit_PCD8544 display = Adafruit_PCD8544(4, 8, 7);//updated MeArm Pins
// Note with hardware SPI MISO and SS pins aren't used but will still be read
// and written to during SPI transfer.  Be careful sharing these pins!

#define XPOS 0
#define YPOS 1

const int SERVOS = 4;
const int ACC = 10; // the accurancy of the potentiometer value before idle starts counting
int PIN[SERVOS], idle[SERVOS], currentAngle[SERVOS], MIN[SERVOS], MAX[SERVOS], INITANGLE[SERVOS], previousAngle[SERVOS], ANA[SERVOS], DIG[2], ARM[3][2][2], pos[2];
Servo myservo[SERVOS];
//int modePin = 3;
//int mode = LOW; // mode stores button push to change between Joysticks and Sliders

#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16

/*static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };
*/

void setup()   {
  Serial.begin(9600);
//  int mode = LOW; 
//  pinMode(modePin, INPUT); // Enables button for Mode Change on Startup

/*
  display.begin();
  // init done
  // you can change the contrast around to adapt the display
  // for the best viewing!
  display.setContrast(60);
  display.display(); // show splashscreen
  display.clearDisplay(); 
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0,0);
//  display.println("To Use Sliders");
//  display.println("Hold Right Button");
//  display.println("Else");
  display.println("Hello!");
  display.println(" ");
  display.println(" ");
  display.println(" ");
  display.println(" ");
  display.println("from MeArm.com");
  display.display(); // show splashscreen
  delay(5000);
  display.clearDisplay();   // clears the screen and buffer
  */
  
//  mode=digitalRead(modePin);
  
/*  if (mode == HIGH){
    display.clearDisplay();   // clears the screen and buffer
    display.println("Sliders");
    display.println("Enabled");
    display.display(); // push display to screen
    delay(2000);
  } else {
    display.clearDisplay();   // clears the screen and buffer
    display.println("Joysticks");
    display.println("Enabled");
    display.display(); // push display to screen
    delay(2000);
  }
 */
  //Middle Servo
  PIN[0] = 10;
  MIN[0] = 0;
  MAX[0] = 180;
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
  INITANGLE[2] = 140;
  ANA[1] = 2;
  DIG[0] = 4;
  //Claw Servo
  PIN[3] = 6;
  MIN[3] = 100;
  MAX[3] = 180;
  INITANGLE[3] = 100;
  DIG[1] = 2;

  pos[0] = 0;
  pos[1] = 0;

  DIG[2] = 0;
   
  for (int i = 0; i < SERVOS; i++){
    myservo[i].attach(PIN[i]);
    myservo[i].write(INITANGLE[i]);
    idle[i] = 0;
    previousAngle[i]=INITANGLE[i];
  }
}

void toggleWrist()
{
    if (pos[1] == 0)
        pos[1] = 1;
    else if(pos[1] == 1)
        pos[1] = 0;
}

void loop() 
{
  delay(15); // Delay function to slow movement of arm down

  for(int i = 1; i < 3; i++)
    myservo[i].write(ARM[i][pos[0]][pos[1]]);
  myservo[0].write(currentAngle[0]);  
}



/*********************************************************************
This is an example sketch for our Monochrome Nokia 5110 LCD Displays

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/338

These displays use SPI to communicate, 4 or 5 pins are required to
interface

Adafruit invests time and resources providing this open source code,
please support Adafruit and open-source hardware by purchasing
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/
