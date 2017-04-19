

/*
Clock Alarm Timer 12h or 24h
Version : 2.0,  April 18, 2017
Author: GrisWold Diablo
Twitter: @GrisWoldDiablo

NOTES:
Feel free to use this code, no need to give me credit.

APPLICATION CONTROL INFORMATION

SCREEN:
Press LEFT and RIGHT to turn screen OFF, clock still run in the background.
Press UP and DOWN to turn screen ON.

12H or 24H:
Press LEFT and DOWN to set clock type to 12h AM/PM (Default)
Press RIGHT and UP to set clock type to 24h

ADJUST TIME:
Hours: hold A, press UP or DOWN
Minutes: hold B, press UP or DOWN
Seconds: hold A and B, press UP or DOWN

ALARM SETTING:
Hold DOWN from the main screen to enter Alarm setting window.
Hold LEFT to turn the Alarm ON
Tap LEFT or RIGHT to turn the Alarm music off while its playing.

TIMER SETTING:
Hold UP from the main screen to enter Timer setting window.
Hold RIGHT to turn the Timer ON
Tap LEFT or RIGHT to turn the Timer music off while its playing.

PAUSE CLOCK:
Pause clock hold A and B, Only works with screen ON


*/

#include <Arduboy2.h>
#include <ArduboyPlaytune.h>

Arduboy2 arduboy;
ArduboyPlaytune ardtune(arduboy.audio.enabled);

int frameRate = 15;	// Frame rate, default 15 to save battery
int sc = frameRate; // Frame counter used for Pause and AM/PM swap

long milSec = 1000;	// Secound counter, 1 second = 1000 milliseconds
long fullSec = 1000;// Incrematation of second counter

String clockText;	// Text variable for Clock
String clockS = ":";// Seperator between clock digit
int h = 12, m = 0, s = 0;	// h:Hours, m:Minutes, s:Seconds
String secD = "0";	// Make seconds diplay as 01 instead of 1
String minD = "0";	// Make minutes diplay as 01 instead of 1
String hourD = " ";	// Add space in front of hour to center display

bool clockType = true;	// 12 or 24 hour clock type, TRUE = 12h AM/PM, FALSE = 24h 
String clockTypeText; // Display 12h or 24h depending of clock type
bool ampm = true;	// Used if clock type set to 12h, TRUE = AM, FALSE = PM
String ampmText = " AM";	// Show AM or PM to clock display

bool diplayOnOff = true;	// Display On or Off, TRUE = ON, FALSE = OFF

int locX = 32, locY = 9;	// Clock location on display Default locX = 32, locY = 0

int sAv, mAv, hAv; // Variable used to adjust time. Seconds, Minutes, Hours.
int * arrD; // Display Array pointer Seconds[0], Minutes[1], Hours[2]

// Counter used for when a button is held down.
long heldTime = 1500;	// Default 1.5 seconds button held down, count milliseconds
long timeHeld = 0;	// Used for counting
bool startCounting = true;	// Start the counter to change window
bool buttonHeld = false; // Check if button has been held long enough, TRUE = Change, FALSE = Keep counting

// Alarm variables
int hA = 12, mA = 0, sA = 0; // Alarm variables, hA:Hours, mA:Minutes, sA:Seconds
String alarmText;	// Text variable for Alarm
bool alarmSetting = false; // Change to Alarm setting window, TRUE = Display Alarm
bool ampmA = true;	// Used if clock type set to 12h, TRUE = AM, FALSE = PM
bool alarmOnSetting = false; // Verify is alarm is On or OFF, TRUE = Alarm ON, FALSE - Alarm OFF

// Timer variables
int hT = 0, mT = 0, sT = 0;	// Timer variables, hT:Hours, mT:Minutes, sT:Seconds
String timerText;	// Text variable for Timer
bool timerSetting = false; // Change to Timer setting window, TRUE = Display Timer
bool timerOnSetting = false;	// Verify is timer is On or OFF, TRUE = Timer ON, FALSE - Timer OFF



const byte score[] PROGMEM = {
	2,154, 0x90,62, 0,166, 0x90,64, 0,166, 0x90,66, 0,166, 0x90,64, 0,166,
	0x90,67, 0,166, 0x90,66, 0,166, 0x90,64, 0,166, 0x90,62, 0,166, 0x90,69,
	0,166, 0x90,67, 0,166, 0x90,66, 0,166, 0x90,64, 0,166, 0x91,50, 0x90,66,
	0,166, 0x91,52, 0x90,62, 0,166, 0x91,54, 0x90,69, 0,166, 0x91,52, 0,166,
	0x90,71, 0x91,55, 0,166, 0x91,54, 0,166, 0x90,73, 0x91,52, 0,55, 0x90,71,
	0,55, 0x90,73, 0,55, 0x91,50, 0x90,74, 0,166, 0x91,57, 0x90,73, 0,83,
	0x90,74, 0,83, 0x91,55, 0x90,73, 0,166, 0x91,54, 0x90,71, 0,83, 0x90,69,
	0,83, 0x91,52, 0,125, 0x80, 0,41, 0x90,73, 0x91,54, 0,166, 0x90,74, 0x91,50,
	0,166, 0x90,76, 0x91,57, 0,166, 0x90,73, 0,166, 0x91,45, 0x90,78, 0,166,
	0x90,74, 0,166, 0x91,57, 0x90,73, 0,166, 0x90,71, 0,138, 0x81, 0,27, 0x91,57,
	0x90,76, 0,166, 0x90,73, 0,166, 0x91,45, 0x90,74, 0,166, 0x90,71, 0,166,
	0x91,57, 0x90,69, 0,166, 0x90,68, 0,138, 0x81, 0,27, 0x91,57, 0x90,76, 0,166,
	0x90,73, 0,166, 0x91,45, 0x90,78, 0,166, 0x90,74, 0,166, 0x91,57, 0x90,73,
	0,166, 0x90,71, 0,138, 0x81, 0,27, 0x91,57, 0x90,76, 0,166, 0x90,73, 0,166,
	0x91,45, 0x90,74, 0,166, 0x90,71, 0,166, 0x91,57, 0x90,69, 0,166, 0x90,68,
	0,138, 0x81, 0,27, 0x91,57, 0x90,73, 0,166, 0x90,71, 0,166, 0x91,59, 0x90,74,
	0,166, 0x90,73, 0,166, 0x91,61, 0x90,71, 0,166, 0x90,69, 0,166, 0x91,62,
	0x90,78, 0,166, 0x91,61, 0,166, 0x90,68, 0x91,64, 0,166, 0x91,62, 0,166,
	0x90,69, 0x91,61, 0,166, 0x91,59, 0,166, 0x91,61, 0,27, 0x80, 0,27, 0x90,71,
	0,55, 0x90,69, 0,55, 0x91,62, 0x90,68, 0,55, 0x90,69, 0,55, 0x90,71,
	0,27, 0x80, 0,27, 0x90,71, 0x91,64, 1,77, 0x91,52, 0,166, 0x90,69, 0,166,
	0x91,57, 0x90,69, 0,166, 0x91,52, 0,166, 0x91,54, 0,166, 0x91,56, 0,166,
	0x91,57, 0x80, 0,166, 0x91,59, 0,166, 0x91,61, 0,166, 0x91,59, 0,166, 0x90,76,
	0x91,62, 0,166, 0x91,61, 0,166, 0x90,81, 0x91,59, 0,166, 0x91,57, 0,166,
	0x91,64, 0,166, 0x90,71, 0,166, 0x91,52, 0x90,73, 0,166, 0x90,75, 0,166,
	0x90,76, 0x81, 0,166, 0x90,78, 0,166, 0x90,79, 0,166, 0x90,78, 0,166, 0x91,59,
	0x90,81, 0,166, 0x90,79, 0,166, 0x91,64, 0x90,78, 0,166, 0x90,76, 0,166,
	0x90,83, 0,166, 0x91,54, 0,166, 0x90,71, 0x91,56, 0,166, 0x91,58, 0,166,
	0x91,59, 0x80, 0,166, 0x91,61, 0,166, 0x91,62, 0,166, 0x91,61, 0,166, 0x90,66,
	0x91,64, 0,166, 0x91,62, 0,166, 0x90,71, 0x91,61, 0,166, 0x91,59, 0,166,
	0x91,66, 0,166, 0x90,70, 0,166, 0x91,54, 0x90,71, 0,166, 0x90,73, 0,166,
	0x91,64, 0x90,74, 0,166, 0x90,76, 0,166, 0x91,62, 0x90,78, 0,166, 0x90,76,
	0,166, 0x91,71, 0x90,79, 0,166, 0x91,70, 0x90,78, 0,166, 0x91,71, 0x90,76,
	0,166, 0x90,74, 0,166, 0x91,61, 0x90,76, 0,166, 0x90,74, 0,166, 0x91,70,
	0x90,78, 0,166, 0x91,68, 0x90,76, 0,166, 0x91,70, 0x90,74, 0,166, 0x90,73,
	0,166, 0x91,71, 0x90,74, 0,166, 0x91,69, 0x90,73, 0,166, 0x91,67, 0x90,76,
	0,166, 0x91,66, 0x90,74, 0,166, 0x91,64, 0x90,73, 0,166, 0x91,62, 0x90,71,
	0,166, 0x91,64, 0x90,73, 0,166, 0x91,62, 0,166, 0x90,70, 0x91,66, 0,83,
	0x90,68, 0,83, 0x91,64, 0x90,70, 0,166, 0x91,62, 0x90,71, 0,166, 0x91,61,
	0,166, 0x91,62, 0,166, 0x90,73, 0x91,64, 0,138, 0x80, 0,27, 0x90,73, 0x91,66,
	0,83, 0x90,74, 0,83, 0x90,73, 0,166, 0x91,54, 0,166, 0x90,71, 0,166,
	0x91,59, 0,166, 0x90,66, 0,166, 0x91,54, 0x90,68, 0,166, 0x90,70, 0,166,
	0x91,50, 0x90,71, 0,166, 0x90,73, 0,166, 0x91,47, 0x90,74, 0,166, 0x90,73,
	0,166, 0x90,76, 0,166, 0x90,74, 0,166, 0x90,73, 0x81, 0,166, 0x90,71, 0,166,
	0x90,79, 0,166, 0x91,47, 0,166, 0x91,49, 0,166, 0x91,51, 0,166, 0x91,52,
	0,166, 0x91,54, 0,166, 0x91,55, 0,166, 0x91,54, 0,166, 0x91,57, 0,166,
	0x91,55, 0,166, 0x91,54, 0,166, 0x91,52, 0,166, 0x91,57, 0,138, 0x80, 0,27,
	0x90,64, 0,166, 0x90,66, 0,166, 0x90,68, 0,166, 0x90,69, 0,166, 0x90,71,
	0,166, 0x90,73, 0,166, 0x90,71, 0,166, 0x90,74, 0,166, 0x90,73, 0,166,
	0x90,71, 0,166, 0x90,69, 0,166, 0x90,78, 0,138, 0x81, 0,27, 0x91,45, 0,166,
	0x91,47, 0,166, 0x91,49, 0,166, 0x91,50, 0,166, 0x91,52, 0,166, 0x91,54,
	0,166, 0x91,52, 0,166, 0x91,55, 0,166, 0x91,54, 0,166, 0x91,52, 0,166,
	0x91,50, 0,166, 0x91,56, 0,138, 0x80, 0,27, 0x90,71, 0,166, 0x90,76, 0,166,
	0x91,52, 0x90,74, 0,166, 0x91,54, 0x90,73, 0,166, 0x91,56, 0x90,71, 0,166,
	0x91,57, 0x90,73, 0,166, 0x91,56, 0x90,71, 0,166, 0x91,54, 0x90,74, 0,166,
	0x91,52, 0x90,73, 0,166, 0x91,50, 0x90,71, 0,166, 0x91,54, 0x90,69, 0,166,
	0x91,52, 0x90,68, 0,83, 0x90,69, 0,83, 0x91,50, 0x90,68, 0,166, 0x91,49,
	0x90,64, 0,166, 0x91,47, 0,166, 0x90,69, 0x91,49, 0,166, 0x90,71, 0x91,45,
	0,166, 0x90,73, 0x91,57, 0,166, 0x90,71, 0,166, 0x91,54, 0x90,74, 0,166,
	0x90,73, 0,166, 0x91,49, 0x90,71, 0,166, 0x90,69, 0,166, 0x91,50, 0x90,78,
	0,166, 0x91,49, 0,166, 0x91,52, 0,166, 0x90,68, 0x91,50, 0,166, 0x90,69,
	0x91,49, 0,166, 0x90,68, 0x91,47, 0,166, 0x90,69, 0x91,49, 0,166, 0x90,74,
	0x91,50, 0,166, 0x90,71, 0x91,52, 1,77, 0x91,40, 0,166, 0x90,69, 0,138,
	0x80, 0,27, 0x90,69, 0x91,45, 0,166, 0x91,49, 0,166, 0x91,50, 0,166, 0x90,73,
	0x91,52, 0,166, 0x90,74, 0x91,54, 0,166, 0x90,76, 0x91,55, 0,166, 0x90,66,
	0x91,57, 0,166, 0x91,55, 0,166, 0x90,67, 0x91,59, 0,166, 0x91,57, 0,166,
	0x90,71, 0x91,55, 0,83, 0x90,69, 0,83, 0x91,54, 0x90,67, 0,83, 0x90,69,
	0,83, 0x91,55, 0x90,71, 0,166, 0x91,54, 0,166, 0x90,74, 0x91,57, 0,83,
	0x90,73, 0,83, 0x91,55, 0x90,71, 0,83, 0x90,73, 0,83, 0x91,54, 0x90,74,
	0,166, 0x91,52, 0,166, 0x91,54, 0,166, 0x90,73, 0x91,52, 0,166, 0x90,76,
	0x91,55, 0,166, 0x90,74, 0x91,54, 0,166, 0x90,73, 0x91,52, 0,166, 0x90,74,
	0x91,50, 0,166, 0x90,76, 0x91,57, 0,166, 0x90,74, 0,166, 0x91,45, 0x90,73,
	0,166, 0x90,71, 0,166, 0x90,69, 0x81, 0,166, 0x90,67, 0,166, 0x90,66, 0,166,
	0x90,64, 0,166, 0x90,67, 0,166, 0x90,66, 0,166, 0x90,64, 0,166, 0x90,62,
	0,166, 0x90,69, 0,166, 0x90,67, 0,166, 0x90,66, 0,166, 0x90,64, 0,166,
	0x91,50, 0x90,66, 0,166, 0x91,52, 0x90,62, 0,166, 0x91,54, 0x90,69, 0,166,
	0x91,52, 0,166, 0x90,71, 0x91,55, 0,166, 0x91,54, 0,166, 0x90,73, 0x91,52,
	0,55, 0x90,71, 0,55, 0x90,73, 0,55, 0x91,50, 0x90,74, 0,166, 0x91,57,
	0x90,73, 0,83, 0x90,74, 0,83, 0x91,55, 0x90,73, 0,166, 0x91,54, 0x90,71,
	0,83, 0x90,69, 0,83, 0x91,52, 0,125, 0x80, 0,41, 0x90,74, 0x91,54, 0,166,
	0x91,50, 0,138, 0x80, 0,27, 0x90,74, 0x91,57, 0,166, 0x91,54, 0,166, 0x90,62,
	0x91,59, 0,166, 0x91,55, 0,166, 0x90,74, 0x91,54, 0,166, 0x91,52, 0,138,
	0x80, 0,27, 0x90,74, 0x91,57, 0,166, 0x91,54, 0,166, 0x90,62, 0x91,55, 0,166,
	0x91,52, 0,166, 0x90,74, 0x91,50, 0,166, 0x91,49, 0,138, 0x80, 0,27, 0x90,74,
	0x91,57, 0,166, 0x91,54, 0,166, 0x90,62, 0x91,59, 0,166, 0x91,55, 0,166,
	0x90,74, 0x91,54, 0,166, 0x91,52, 0,138, 0x80, 0,27, 0x90,74, 0x91,57, 0,166,
	0x91,54, 0,166, 0x90,62, 0x91,55, 0,166, 0x91,52, 0,166, 0x90,74, 0x91,50,
	0,166, 0x90,76, 0x91,49, 0,166, 0x90,78, 0x91,50, 0,166, 0x90,76, 0,166,
	0x91,52, 0x90,79, 0,166, 0x90,78, 0,166, 0x91,54, 0x90,76, 0,166, 0x90,74,
	0,166, 0x91,55, 0x90,83, 0,166, 0x91,54, 0,166, 0x90,73, 0x91,57, 0,166,
	0x91,55, 0,166, 0x90,74, 0x91,54, 0,166, 0x91,52, 0,166, 0x91,54, 0,27,
	0x80, 0,27, 0x90,76, 0,55, 0x90,74, 0,55, 0x91,55, 0x90,73, 0,55, 0x90,74,
	0,55, 0x90,76, 0,41, 0x80, 0,13, 0x90,76, 0x91,57, 1,77, 0x91,45, 0,166,
	0x90,74, 0,138, 0x80, 0,27, 0x90,74, 0x91,47, 0,166, 0x91,45, 0,166, 0x90,62,
	0x91,48, 0,166, 0x91,47, 0,166, 0x90,67, 0x91,45, 0,166, 0x91,43, 0,166,
	0x91,50, 0,166, 0x90,57, 0,166, 0x90,59, 0,166, 0x90,61, 0,166, 0x90,62,
	0,166, 0x90,64, 0,166, 0x90,66, 0,138, 0x81, 0,27, 0x91,49, 0x90,64, 0,166,
	0x91,47, 0x90,67, 0,166, 0x91,45, 0x90,66, 0,166, 0x91,43, 0x90,64, 0,166,
	0x91,42, 0x90,62, 0,166, 0x91,43, 0x90,71, 0,166, 0x91,42, 0,166, 0x91,45,
	0,166, 0x90,61, 0x91,43, 0,166, 0x90,62, 0x91,42, 0,166, 0x90,61, 0x91,40,
	0,166, 0x90,62, 0x91,42, 0,166, 0x90,67, 0x91,43, 0,166, 0x90,64, 0x91,45,
	1,244, 0x90,62, 0,138, 0x80, 0,27, 0x90,62, 0x91,38, 7,208, 0x80, 0x81,
	0xf0
};

void setup()
{
	ardtune.initChannel(PIN_SPEAKER_1);
	ardtune.initChannel(PIN_SPEAKER_2);
	arduboy.boot();
	arduboy.setFrameRate(frameRate);	// Time calculated based on set variable frames per second.
	arduboy.clear();
	arduboy.audio.on();
}

void loop()
{	
	arduboy.clear();

	// Second incrementation, every 1000 millisecond 1 second is added
	if (millis() >= milSec)
	{
		milSec += fullSec;

		// Verify if Timer should be ON
		if (timerOnSetting)
		{
			TimerCountDown();
		}
		// Pause clock hold A and B, Only works with screen ON
		if (arduboy.pressed(A_BUTTON) && arduboy.pressed(B_BUTTON) && diplayOnOff && !alarmSetting && !timerSetting)
		{
			sc = frameRate;
			return;
		}
		
		s++;

	}

	if (!arduboy.nextFrame())
	{
		return;
	}

	

	// Calculate time and store it.
	clock();

	// Verify if Alarm is on and start playing Music and turn lights on if it is.
	if (sA == s && mA == m && hA == h && ampmA == ampm && alarmOnSetting)
	{
		ardtune.playScore(score);
		alarmOnSetting = false;
	}
	
	
	
	// Exit loop function if screen should be OFF
	ShowDisplay();
	if (!diplayOnOff)
	{
		return;
	}
	
	HeldLeftButton();
	HeldRightButton();

	if (HeldDownButton() || alarmSetting)
	{
		arduboy.clear();
		DisplayAlarm();		
	}
	else if (HeldUpButton() || timerSetting)
	{
		arduboy.clear();
		DisplayTimer();
	}
	else
	{	
		DisplayClock();
	}

	
	arduboy.display();
}

// Calculate time and store it.
void clock()
{

	// Frame counter used for Pause and AM/PM swap
	if (sc == 0)
	{
		sc = frameRate;
	}
	else
	{
		sc--;
	}

	// Clock incrementation
	// Add 1 min every 60 seconds and reset second to 0
	if (s == 60)
	{
		s = 0;
		m++;
	}
	// Add 1 hour every 60 minutes and reset minute to 0
	if (m == 60 && s == 0)
	{
		m = 0;
		h++;
	}
	// Turn over clock 
	if (h == 24 && m == 0 && s == 0 && !clockType && sc == frameRate)
	{
		h = 0;
		ampm = true;
	}
	else if (h == 11 && m == 59 && s == 59 && clockType && ampm && sc == frameRate)
	{
		ampm = false;
	}
	else if (h == 11 && m == 59 && s == 59 && clockType && !ampm && sc == frameRate)
	{
		ampm = true;
	}
	if (h > 12 && m == 0 && s == 0 && clockType)
	{
		h = 1;
	}
	if (h >= 12 && !clockType)
	{
		ampm = false;
	}

}

// Display On or Off, TRUE = ON, FALSE = OFF
void ShowDisplay()
{
	// Press LEFT and RIGHT to turn screen OFF, clock still run in the background.
	if (arduboy.pressed(LEFT_BUTTON) && arduboy.pressed(RIGHT_BUTTON) && arduboy.notPressed(A_BUTTON) && arduboy.notPressed(B_BUTTON) && arduboy.notPressed(UP_BUTTON) && arduboy.notPressed(DOWN_BUTTON))
	{
		arduboy.clear();
		arduboy.display();
		arduboy.digitalWriteRGB(RGB_OFF, RGB_OFF, RGB_OFF);
		diplayOnOff = false;
		startCounting = true;
		alarmSetting = false;
		timerSetting = false;
		

	}
	// Press UP and DOWN to turn screen ON and display clock.
	else if (arduboy.pressed(UP_BUTTON) && arduboy.pressed(DOWN_BUTTON) && arduboy.notPressed(A_BUTTON) && arduboy.notPressed(B_BUTTON) && arduboy.notPressed(LEFT_BUTTON) && arduboy.notPressed(RIGHT_BUTTON))
	{
		arduboy.digitalWriteRGB(RGB_OFF, RGB_OFF, RGB_OFF);
		diplayOnOff = true;
	}
}

// Modify time sA=Seconds, mA=Minutes, hA=Hours, 'ClockOrAlarm' TRUE=Setting Clock, FALSE=Setting Alarm, 'SetTimer' TRUE=Setting Timer
int * AdjustTime(int sAA, int mAA, int hAA, bool ClockOrAlarm, bool SetTimer)
{
	sAv = sAA;
	mAv = mAA;
	hAv = hAA;
	static int adjT[3];
	
	// Disable changing clocktype if your are setting up Timer.
	if (!SetTimer)
	{
		// Press RIGHT and UP to set clock type to 24h
		if (arduboy.pressed(RIGHT_BUTTON) && arduboy.pressed(UP_BUTTON) && clockType&& arduboy.notPressed(A_BUTTON) && arduboy.notPressed(B_BUTTON) && arduboy.notPressed(LEFT_BUTTON) && arduboy.notPressed(DOWN_BUTTON))
		{
			clockType = false;
			// Set Hours according to AM PM
			if (hAv == 12)
			{
				if (ClockOrAlarm && ampm)
				{
					hAv = 0;
				}
				else if (h == 12 && ampm)
				{
					h = 0;
				}

				if (!ClockOrAlarm && ampmA)
				{
					hAv = 0;
				}
				else if (hA == 12 && ampmA)
				{
					hA = 0;
				}
			}
			else if (hAv != 12)
			{
				if (ClockOrAlarm && !ampm)
				{
					hAv += 12;
				}
				else if (h != 12 && !ampm)
				{
					h += 12;
				}

				if (!ClockOrAlarm && !ampmA)
				{
					hAv += 12;
				}
				else if(hA != 12 && !ampmA)
				{
					hA += 12;
				}
			}
		}
		// Press LEFT and DOWN to set clock type to 12h AM/PM
		if (arduboy.pressed(LEFT_BUTTON) && arduboy.pressed(DOWN_BUTTON) && !clockType&& arduboy.notPressed(A_BUTTON) && arduboy.notPressed(B_BUTTON) && arduboy.notPressed(RIGHT_BUTTON) && arduboy.notPressed(UP_BUTTON))
		{
			clockType = true;
			// Set AM PM according to current time
			if (hAv >= 12)
			{
				if (ClockOrAlarm)
				{
					hAv -= 12;
					ampm = false;
				}
				else if (h > 12)
				{
					h -= 12;
					ampm = false;
				}

				if (!ClockOrAlarm)
				{
					hAv -= 12;
					ampmA = false;
				}
				else if (hA > 12)
				{
					hA -= 12;
					ampmA = false;
				}

			}
			else
			{
				if (ClockOrAlarm)
				{
					ampm = true;
				}
				else if (hA < 12)
				{
					ampmA = true;
				}

				if (!ClockOrAlarm)
				{
					ampmA = true;
				}	
				else if (h < 12)
				{
					ampm = true;
				}
			}
			if (hAv == 0)
			{
				if (ClockOrAlarm)
				{
					hAv = 12;
				}
				else if (hA == 0)
				{
					hA = 12;
				}

				if (!ClockOrAlarm)
				{
					hAv = 12;
				}
				else if (h == 0)
				{
					h = 12;
				}
			}
		}
	}

	// Adjust Hours hold A, press UP or DOWN
	if (arduboy.pressed(A_BUTTON) && arduboy.pressed(UP_BUTTON) && arduboy.notPressed(B_BUTTON))
	{
		HourTurn(true, ClockOrAlarm, SetTimer);
	}
	else if (arduboy.pressed(A_BUTTON) && arduboy.pressed(DOWN_BUTTON) && arduboy.notPressed(B_BUTTON))
	{
		HourTurn(false, ClockOrAlarm, SetTimer);
	}
	// Adjust Minutes hold B, press UP or DOWN
	else if (arduboy.pressed(B_BUTTON) && arduboy.pressed(UP_BUTTON) && arduboy.notPressed(A_BUTTON))
	{
		MinuteTurn(true, ClockOrAlarm, SetTimer);
	}
	else if (arduboy.pressed(B_BUTTON) && arduboy.pressed(DOWN_BUTTON) && arduboy.notPressed(A_BUTTON))
	{
		MinuteTurn(false, ClockOrAlarm, SetTimer);
	}
	// Adjust Seconds hold A and B, press UP or DOWN
	else if (arduboy.pressed(A_BUTTON) && arduboy.pressed(B_BUTTON) && arduboy.pressed(UP_BUTTON))
	{
		SecondTurn(true, ClockOrAlarm, SetTimer);
	}
	else if (arduboy.pressed(A_BUTTON) && arduboy.pressed(B_BUTTON) && arduboy.pressed(DOWN_BUTTON))
	{
		SecondTurn(false, ClockOrAlarm, SetTimer);
	}

	adjT[0] = sAv;
	adjT[1] = mAv;
	adjT[2] = hAv;

	return adjT;
}

// Swap AM/PM depending of which time your are adjusting, 'ClockOrAlarm' TRUE=Clock, FALSE=Alarm
boolean AmPmSwap(bool ClockOrAlarm) 
{
	if (ClockOrAlarm)
	{
		if (ampm)
		{
			ampm = false;
		}
		else
		{
			ampm = true;
		}
	}
	else if (!ClockOrAlarm)
	{
		if (ampmA)
		{
			ampmA = false;
		}
		else
		{
			ampmA = true;
		}
	}
}

// 'changeH' Increment(TRUE) or Decrement(FALSE) hours, 'ClockOrAlarm' TRUE=Setting Clock, FALSE=Setting Alarm, 'setTimer' TRUE=Setting Timer
int HourTurn(bool changeH, bool ClockOrAlarm, bool setTimer)
{
	if (changeH)
	{
		hAv++;
		if (!setTimer)
		{
			if (clockType && hAv > 12)
			{
				hAv = 1;
			}
			else if (clockType && hAv == 12)
			{
				AmPmSwap(ClockOrAlarm);
			}
			else if (!clockType && hAv == 24)
			{
				hAv = 0;
			}
		}
	}
	else
	{
		hAv--;
		if (!setTimer)
		{
			if (clockType && hAv < 1)
			{
				hAv = 12;
			}
			else if (clockType && hAv == 11)
			{
				AmPmSwap(ClockOrAlarm);
			}
			else if (!clockType && hAv < 0)
			{
				hAv = 23;
			}
		}
		else
		{
			if (hAv < 0)
			{
				hAv = 0;
			}
		}
	}
}

// 'changeM' Increment(TRUE) or Decrement(FALSE) minutes, 'ClockOrAlarm' TRUE=Setting Clock, FALSE=Setting Alarm, 'setTimer' TRUE=Setting Timer
int MinuteTurn(bool changeM, bool ClockOrAlarm, bool setTimer)
{
	if (changeM)
	{
		mAv++;
		if (mAv > 59)
		{
			mAv = 0;
			HourTurn(true, ClockOrAlarm, setTimer);
		}
	}
	else
	{
		mAv--;
		if (mAv < 0)
		{
			if (!setTimer)
			{
				mAv = 59;
				HourTurn(false, ClockOrAlarm, setTimer);
			}
			else
			{
				mAv = 0;
			}
			
		}
	}
}

// 'changeS' Increment(TRUE) or Decrement(FALSE) seconds, 'ClockOrAlarm' TRUE=Setting Clock, FALSE=Setting Alarm, 'setTimer' TRUE=Setting Timer
int SecondTurn(bool changeS, bool ClockOrAlarm, bool setTimer)
{
	if (changeS)
	{
		sAv++;
		if (sAv > 59)
		{
			sAv = 0;
			MinuteTurn(true, ClockOrAlarm, setTimer);
		}
	}
	else
	{
		sAv--;
		if (sAv < 0)
		{
			if (!setTimer)
			{
				sAv = 59;
				MinuteTurn(false, ClockOrAlarm, setTimer);
			}
			else
			{
				sAv = 0;
			}
			
		}
	}
}


// Combine necessary strings to present the time, 'ClockOrAlarm' TRUE=Clock, FALSE=Alarm, 'Timer' TRUE=Timer Display
String CreateDisplayText(int sD, int mD, int hD, bool ClockOrAlarm, bool Timer)
{
	// Seconds diplay as 01 instead of 1
	if (sD >= 0 && sD <= 9)
	{
		secD = "0";
	}
	else
	{
		secD = "";
	}
	// Minutes diplay as 01 instead of 1
	if (mD >= 0 && mD <= 9)
	{
		minD = "0";
	}
	else
	{
		minD = "";
	}
	// Hour Space in front for time under 10
	if (hD < 10)
	{
		hourD = " ";
	}
	else
	{
		hourD = "";
	}
	// Diplay AM or PM if clock set to 12h type Or nothing if is the Timer diplay
	if (clockType && !Timer)
	{
		if (ClockOrAlarm)
		{
			if (ampm)
			{
				ampmText = " AM";
			}
			else
			{
				ampmText = " PM";
			}
		}
		else if (!ClockOrAlarm)
		{
			if (ampmA)
			{
				ampmText = " AM";
			}
			else
			{
				ampmText = " PM";
			}
		}
	}
	else
	{
		ampmText = "";
	}

	return hourD + hD + clockS + minD + mD + clockS + secD + sD + ampmText;	// Create Display string
}

// Isolate a button, return true when all the other button are not press except the one you've chosen
boolean NoButton()
{
	if (arduboy.notPressed(A_BUTTON) && arduboy.notPressed(B_BUTTON) && arduboy.notPressed(UP_BUTTON) && arduboy.notPressed(DOWN_BUTTON) && arduboy.notPressed(LEFT_BUTTON) && arduboy.notPressed(RIGHT_BUTTON))
	{
		return true;
	}
	return false;
}

// Isolate a button, return true when all the other button are not press except the one you've chosen
boolean SingleButton(String chosenButton)
{
	if (chosenButton == "A")
	{
		if (arduboy.notPressed(B_BUTTON) && arduboy.notPressed(UP_BUTTON) && arduboy.notPressed(DOWN_BUTTON) && arduboy.notPressed(LEFT_BUTTON) && arduboy.notPressed(RIGHT_BUTTON))
		{
			return true;
		}
	}
	else if (chosenButton == "B")
	{
		if (arduboy.notPressed(A_BUTTON) && arduboy.notPressed(UP_BUTTON) && arduboy.notPressed(DOWN_BUTTON) && arduboy.notPressed(LEFT_BUTTON) && arduboy.notPressed(RIGHT_BUTTON))
		{
			return true;
		}
	}
	else if (chosenButton == "UP")
	{
		if (arduboy.notPressed(B_BUTTON) && arduboy.notPressed(A_BUTTON) && arduboy.notPressed(DOWN_BUTTON) && arduboy.notPressed(LEFT_BUTTON) && arduboy.notPressed(RIGHT_BUTTON))
		{
			return true;
		}
	}
	else if (chosenButton == "DOWN")
	{
		if (arduboy.notPressed(B_BUTTON) && arduboy.notPressed(UP_BUTTON) && arduboy.notPressed(A_BUTTON) && arduboy.notPressed(LEFT_BUTTON) && arduboy.notPressed(RIGHT_BUTTON))
		{
			return true;
		}
	}
	else if (chosenButton == "LEFT")
	{
		if (arduboy.notPressed(B_BUTTON) && arduboy.notPressed(UP_BUTTON) && arduboy.notPressed(DOWN_BUTTON) && arduboy.notPressed(A_BUTTON) && arduboy.notPressed(RIGHT_BUTTON))
		{
			return true;
		}
	}
	else if (chosenButton == "RIGHT")
	{
		if (arduboy.notPressed(B_BUTTON) && arduboy.notPressed(UP_BUTTON) && arduboy.notPressed(DOWN_BUTTON) && arduboy.notPressed(LEFT_BUTTON) && arduboy.notPressed(A_BUTTON))
		{
			return true;
		}
	}
	return false;
}

// Change to ALARM SETTINGS, Detect for down button held long enough
boolean HeldDownButton()
{
	if (arduboy.pressed(DOWN_BUTTON) && SingleButton("DOWN") && !timerSetting)
	{
		if (millis() >= timeHeld && !startCounting && buttonHeld)
		{
			buttonHeld = false;
			timeHeld = 0;
			arduboy.digitalWriteRGB(RGB_OFF, RGB_ON, RGB_OFF);
			if (alarmSetting)
			{
				alarmSetting = false;
				return false;
			}
			else
			{
				alarmSetting = true;
				return true;
			}				
		}
		if (startCounting)
		{
			timeHeld = millis() + heldTime;
			startCounting = false;
			arduboy.digitalWriteRGB(RGB_ON, RGB_OFF, RGB_OFF);
		}
	}
	if (NoButton())
	{
		buttonHeld = true;
		startCounting = true;
		arduboy.digitalWriteRGB(RGB_OFF, RGB_OFF, RGB_OFF);
		return false;
	}
}

//Change to TIMER SETTINGS, Detect for DOWN button held long enough
boolean HeldUpButton()
{
	if (arduboy.pressed(UP_BUTTON) && SingleButton("UP") && !alarmSetting)
	{
		if (millis() >= timeHeld && !startCounting && buttonHeld)
		{
			buttonHeld = false;
			timeHeld = 0;
			arduboy.digitalWriteRGB(RGB_OFF, RGB_ON, RGB_OFF);
			if (timerSetting)
			{
				timerSetting = false;
				return false;
			}
			else
			{
				timerSetting = true;
				return true;
			}
		}
		if (startCounting)
		{
			timeHeld = millis() + heldTime;
			startCounting = false;
			arduboy.digitalWriteRGB(RGB_ON, RGB_ON, RGB_OFF);
		}
	}
	if (NoButton())
	{
		buttonHeld = true;
		startCounting = true;
		arduboy.digitalWriteRGB(RGB_OFF, RGB_OFF, RGB_OFF);
		return false;
	}
}

// SET to ALARM ON or OFF, Detect for DOWN button held long enough
boolean HeldLeftButton()
{
	if (arduboy.pressed(LEFT_BUTTON) && SingleButton("LEFT") && !timerSetting)
	{
		if (ardtune.playing())
		{
			ardtune.stopScore();
		}
		if (millis() >= timeHeld && !startCounting && buttonHeld)
		{
			buttonHeld = false;
			timeHeld = 0;
			arduboy.digitalWriteRGB(RGB_OFF, RGB_ON, RGB_OFF);
			if (alarmOnSetting)
			{
				alarmOnSetting = false;
				return false;
			}
			else
			{
				alarmOnSetting = true;
				alarmSetting = false;
				return true;
			}
		}
		if (startCounting)
		{
			timeHeld = millis() + heldTime;
			startCounting = false;
			arduboy.digitalWriteRGB(RGB_OFF, RGB_OFF, RGB_ON);
		}
	}
	if (NoButton())
	{
		buttonHeld = true;
		startCounting = true;
		arduboy.digitalWriteRGB(RGB_OFF, RGB_OFF, RGB_OFF);
		//return false; removed for alarm on setting to stay even if button is released.
	}
}

// Set START OR STOP TIMER, Detect for down button held long enough
boolean HeldRightButton()
{
	
	if (arduboy.pressed(RIGHT_BUTTON) && SingleButton("RIGHT") && !alarmSetting)
	{
		if (ardtune.playing())
		{
			ardtune.stopScore();
		}
		if (millis() >= timeHeld && !startCounting && buttonHeld)
		{
			buttonHeld = false;
			timeHeld = 0;
			arduboy.digitalWriteRGB(RGB_OFF, RGB_ON, RGB_OFF);
			if (timerOnSetting)
			{
				timerOnSetting = false;
				return false;
			}
			else
			{
				timerOnSetting = true;
				timerSetting = false;
				return true;
			}
		}
		if (startCounting)
		{
			timeHeld = millis() + heldTime;
			startCounting = false;
			arduboy.digitalWriteRGB(RGB_OFF, RGB_ON, RGB_ON);
		}
	}
	if (NoButton())
	{
		buttonHeld = true;
		startCounting = true;
		arduboy.digitalWriteRGB(RGB_OFF, RGB_OFF, RGB_OFF);
		return false;
	}
}

//  Display the clock on screen
void DisplayClock()
{
	if (timerOnSetting)
	{
		arduboy.setCursor(locX - 32, locY + 12);
		arduboy.print("Hold RIGHT to stop");
		arduboy.setCursor(locX, locY + 22);
		arduboy.print(CreateDisplayText(sT, mT, hT, false, true));
	}
	else
	{
		arduboy.setCursor(locX - 32, locY + 12);
		arduboy.print("Hold UP for Timer");
	}
	if (alarmOnSetting)
	{
		arduboy.setCursor(locX - 32, locY + 32);
		arduboy.print("Hold LEFT to turn OFF");
		arduboy.setCursor(locX, locY + 42);
		arduboy.print(CreateDisplayText(sA, mA, hA, false, false));
	}
	else
	{
		arduboy.setCursor(locX - 32, locY + 32);
		arduboy.print("Hold DOWN for Alarm");
	}
	

	arrD = AdjustTime(s, m, h, true, false);
	s = *(arrD);
	m = *(arrD + 1);
	h = *(arrD + 2);
	arduboy.setCursor(locX, locY);	// Set location for clock
	clockText = CreateDisplayText(s, m, h, true, false);
	arduboy.print(clockText); // Print clock
}

// Display the Alarm setting on screen.
void DisplayAlarm()
{
	String alarmStatusText;
	if (alarmOnSetting)
	{

		alarmStatusText = "Alarm ON\n\rHold LEFT to turn OFF";
	}
	else
	{
		alarmStatusText = "Alarm OFF\n\rHold LEFT to turn ON";
	}

	// Select clock type to display
	if (clockType)
	{
		clockTypeText = "12h";
	}
	else
	{
		clockTypeText = "24h";
	}

	arduboy.setCursor(0, 0);	// Print clock type top left corner
	arduboy.print(clockTypeText + "  ALARM SETTING\n\r" + alarmStatusText);

	arduboy.setCursor(locX, locY + 32);
	arrD = AdjustTime(sA, mA, hA, false, false);
	sA = *(arrD);
	mA = *(arrD + 1);
	hA = *(arrD + 2);
	arduboy.print(CreateDisplayText(sA, mA, hA, false, false));
}

void DisplayTimer()
{
	String timerStatusText;
	if (timerOnSetting)
	{
		timerStatusText = " Hold RIGHT to Stop Timer";
	}
	else
	{
		timerStatusText = " Hold RIGHT to Start";
	}

	arduboy.setCursor(0, 0);
	arduboy.print(" TIMER SETTINGS\n\r" + timerStatusText);

	
	if (!timerOnSetting)
	{
		arrD = AdjustTime(sT, mT, hT, false, true);
		sT = *(arrD);
		mT = *(arrD + 1);
		hT = *(arrD + 2);
	}
	arduboy.setCursor(locX, locY + 32);
	arduboy.print(CreateDisplayText(sT, mT, hT, false, true));
}

// If 'timerOnSetting' is TRUE the time will start counting down.
void TimerCountDown()
{
	sT--;

	// Timer Decrementation
	if (sT < 0)
	{
		if (mT != 0)
		{
			sT = 59;
			mT--;
		}
		else if(hT != 0)
		{
			sT = 59;
			mT = 59;
			hT--;

		}
		else
		{
			sT = 0;
			ardtune.playScore(score);
			timerOnSetting = false;
		}
		
	}
}
