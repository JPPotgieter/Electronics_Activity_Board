//WS2182B LED Setup

#include <FastLED.h>
#define LED_PIN 14
#define NUM_LEDS 53
#define BRIGHTNESS 10
#define LED_TYPE WS2811
#define COLOR_ORDER GRB

// This tells the program how many LED's are on top, right, bottom and left, this allows us to be able to controll the size of the sqaure of LEDs we have
#define LED_TOP 11
#define LED_RIGHT 15
#define LED_BOT 12
#define LED_LEFT 15

int LED_POS = 0;
CRGB leds[NUM_LEDS];

///////////////////////

//JoyStick

#define RIGHT_JOY 22
#define DWN_JOY   23
#define UP_JOY    21
#define LEFT_JOY  19

int Right_Joy_Pressed = 0;
int Dwn_Joy_Pressed = 0;
int Up_Joy_Pressed = 0;
int Left_Joy_Pressed = 0;
int in;

//////////////////////

// Ulta Sonic Distance measurement
//////////////////////////////////////////////////////////////////
//This is the pins you connect your Ultra Sonic sensor 
#define echoPin 8 //echo pin
#define trigPin 9 //Trigger pin

float time;  // Time is used to measure the distace, we send a signal then measure the time when that signal comes back
float distance_cm; // We create a float to store the distance in a variable

////////////////////////////////////////////////////////////////////



void setup() {
 

Serial.begin(9600);

//Joystick

pinMode(RIGHT_JOY,INPUT);
pinMode(DWN_JOY,INPUT);
pinMode(UP_JOY,INPUT);
pinMode(LEFT_JOY,INPUT);


//LED Code

delay(3000); // we do this to first let the Arduino start up itself then we turn on the LED 3 seconds later.
FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
FastLED.setBrightness( BRIGHTNESS );

//Ultrasoic//
pinMode(trigPin, OUTPUT); // The trig pin sends a pulse, therefore its an output
pinMode(echoPin, INPUT); // The echo pin receives a pulse therefore we make it an input.


//////////////////////////////////


}

void loop() {

//Ultrasonic

digitalWrite(trigPin, LOW); //PULSE ___|---|___
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);

time = pulseIn(echoPin, HIGH);

distance_cm = (time/2) / 29.1; // distance for centimeter

//

//JoyStick

Right_Joy_Pressed = digitalRead(RIGHT_JOY);
Dwn_Joy_Pressed = digitalRead(DWN_JOY);
Up_Joy_Pressed = digitalRead(UP_JOY);
Left_Joy_Pressed = digitalRead(LEFT_JOY); 

// JoyStick with LED//

if (LED_POS < LED_TOP)
{
  if (Right_Joy_Pressed)
  {
    LED_POS ++;
  }

if (Left_Joy_Pressed)
{
  LED_POS --;
  in = 0;
  }
}

if ((LED_POS >= LED_TOP) & (LED_POS < (LED_TOP + LED_RIGHT)))
{
  if (Dwn_Joy_Pressed)
  {
    LED_POS ++;
  }
}


if ((LED_POS >= (LED_TOP + LED_RIGHT)) & (LED_POS < (LED_TOP + LED_RIGHT + LED_BOT)))
{
  if(Right_Joy_Pressed)
  {
    LED_POS--;
    in = 0;
  }
}

}
