#include "Arduino.h"
#include "LiquidCrystal.h"

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //Create lcd object called lcd

int trigPin = 9; //Sensor trig pin connected to pin #9
int echoPin = 7; //Sensor echo pin connected to pin #7
int myCounter = 0; //Declare variable myCounter and set to 0
int servoControlPin = 6; //Servo control line is connected to pin #6
float pingTime; //Time for ping to travel from sensor to target and back
float targetDistance; //Distance to target in inches
float speedOfSound = 760.5; //Speed of sound in MPH at sea level around 59 degrees

void setup()
{
	Serial.begin(9600);
	pinMode(trigPin, OUTPUT);
	pinMode(echoPin, INPUT);
	lcd.begin(16, 2); //Tell Arduino to start your lcd 16X2
	lcd.setCursor(0, 0); //Set lcd cursor to upper left corner, column 0, row 0
	lcd.print("Distance:"); //Print Message on first row

}

// The loop function is called in an endless loop
void loop()
{
	digitalWrite(trigPin, LOW); //Set trig pin low
	delayMicroseconds(2000); //Let signal settle
	digitalWrite(trigPin, HIGH); //set trigPin high
	delayMicroseconds(15); //delay in high state
	digitalWrite(trigPin, LOW); //Ping has now been sent
	delayMicroseconds(10); //Delay in high state

	pingTime = pulseIn(echoPin, HIGH); //pingTime in microseconds
	pingTime = pingTime/1000000; //convert pingTmie to seconds by dividing by 1000000(microseconds in a second)
	pingTime = pingTime/3600; //convert pingTime to hours by dividing by 3600 (seconds in an hour)
	targetDistance = speedOfSound * pingTime; //This will be in miles
	targetDistance = targetDistance/2; //ping travels to target and back so you must divide by 2 for actual distance
	targetDistance = targetDistance*63360; //Convert miles to inches by multiplying by 63360

	lcd.setCursor(1, 1); //Set cursor to the first column of the second row
	lcd.print("                "); //Clear the row
	lcd.setCursor(0, 1); //Set cursor to first column of the second row again
	lcd.print(targetDistance); //Print measured distance
	lcd.print(" inches "); //Print units
	delay(250); //Pause to let things settle

}
