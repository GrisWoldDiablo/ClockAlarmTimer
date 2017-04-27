

/*
Clock Alarm Timer 12h or 24h, Screensaver with Pong.
Version : 3.0,  April 26, 2017
Author: GrisWold Diablo
Twitter: @GrisWoldDiablo

NOTES:
Feel free to use this code, no need to give me credit.

APPLICATION CONTROL INFORMATION

MAIN SCREEN:
Press UP or DOWN to cycle between screens
Bottom left show Alarm time
Bottom right show Timer time

TURNING ON OR OFF DISPLAY:
Press LEFT and RIGHT to turn screen OFF, clock still run in the background
Press UP and DOWN to turn screen ON

12H or 24H:
Press LEFT and DOWN to set clock type to 12h AM/PM (Default)
Press RIGHT and UP to set clock type to 24h

ADJUST TIME:
Hours: hold A, press UP or DOWN
Minutes: hold B, press UP or DOWN
Seconds: hold A and B, press UP or DOWN

ALARM SETTING:
Hold LEFT to turn the Alarm ON
Tap LEFT or RIGHT to turn the Alarm music off while its playing

TIMER SETTING:
Hold RIGHT to turn the Timer ON
Tap LEFT to reset the Timer while its not running
Tap LEFT or RIGHT to turn the Timer music off while its playing

PAUSE CLOCK:
Pause clock hold A and B, Only works with screen ON

SCREENSAVER SETTING:
Press A to turn ON or OFF
Tap LEFT for Pong, Hold LEFT to start playing
Tap RIGHT for Blank screen

PONG:
Hold LEFT to start playing while in Screensaver setting
AI plays automaticaly
Hold A to take control of the left PAD
UP and DOWN control PAD while in control
Tap B to reset Score
Hold RIGHT to exit and turn OFF screensaver

*/

#include <Arduboy2.h>
#include <ArduboyPlaytune.h>
#include <Tinyfont.h>

Arduboy2 arduboy;
Tinyfont ardTiny = Tinyfont(arduboy.sBuffer, Arduboy2::width(), Arduboy2::height());
#define ARDBITMAP_SBUF arduboy.getBuffer()
#include <ArdBitmap.h>
ArdBitmap<WIDTH, HEIGHT> ardbitmap;

const unsigned char PROGMEM FRAME[] = {
	0xc0, 0x60, 0xb8, 0x4c, 0xb4, 0xb6, 0x4b, 0xb5, 0xb5, 0x4b, 0xff, 0x49, 0xb7, 0x81, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x05, 0xdb, 0x25, 0xdb, 0x25,
	0x25, 0xdb, 0x25, 0xdb, 0x05, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x01, 0x01, 0x81, 0xb7, 0x49, 0xff, 0x4b, 0xb5, 0xb5, 0x4b, 0xb6, 0xb4, 0x4c, 0xb8, 0x60, 0xc0,
	0xff, 0x16, 0x15, 0x0e, 0x15, 0x15, 0x0e, 0x35, 0xb5, 0x4e, 0xff, 0x4e, 0xb5, 0xb5, 0x4e, 0xb5,
	0xb5, 0x4e, 0x35, 0x35, 0x0e, 0x35, 0x35, 0x0e, 0x15, 0x16, 0x0d, 0x16, 0x16, 0x0e, 0x14, 0x14,
	0x0c, 0x14, 0x14, 0x0c, 0x14, 0x14, 0x0c, 0x14, 0x14, 0x0c, 0x14, 0x0c, 0x0c, 0x0c, 0x04, 0x04,
	0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x06, 0x05, 0x06, 0x05, 0x06, 0x05,
	0x05, 0x06, 0x05, 0x06, 0x05, 0x06, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
	0x04, 0x04, 0x0c, 0x0c, 0x0c, 0x14, 0x0c, 0x14, 0x14, 0x0c, 0x14, 0x14, 0x0c, 0x14, 0x14, 0x0c,
	0x14, 0x14, 0x0e, 0x16, 0x16, 0x0d, 0x16, 0x15, 0x0e, 0x35, 0x35, 0x0e, 0x35, 0x35, 0x4e, 0xb5,
	0xb5, 0x4e, 0xb5, 0xb5, 0x4e, 0xff, 0x4e, 0xb5, 0x35, 0x0e, 0x15, 0x15, 0x0e, 0x15, 0x16, 0xff,
	0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xad, 0x52, 0xff, 0x92, 0x6d, 0x6d, 0x02, 0x01,
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
	0x01, 0x02, 0x6d, 0x6d, 0x92, 0xff, 0x52, 0xad, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
	0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xa4, 0x5b, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x5b, 0xa4, 0xff, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
	0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xff, 0x24, 0xdb, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xdb, 0x24, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
	0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb5, 0x4a, 0xff, 0x49, 0xb6, 0xb6, 0x40, 0x80,
	0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
	0x80, 0x40, 0xb6, 0xb6, 0x49, 0xff, 0x4a, 0xb5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
	0xff, 0x68, 0xa8, 0x70, 0xa8, 0xa8, 0x70, 0xac, 0xad, 0x72, 0xff, 0x72, 0xad, 0xad, 0x72, 0xad,
	0xad, 0x72, 0xac, 0xac, 0x70, 0xac, 0xac, 0x70, 0xa8, 0x68, 0xb0, 0x68, 0x68, 0x70, 0x28, 0x28,
	0x30, 0x28, 0x28, 0x30, 0x28, 0x28, 0x30, 0x28, 0x28, 0x30, 0x28, 0x30, 0x28, 0x30, 0x30, 0x30,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x60, 0xa0, 0x60, 0xa0, 0x60, 0xa0,
	0xa0, 0x60, 0xa0, 0x60, 0xa0, 0x60, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x30, 0x30, 0x30, 0x28, 0x30, 0x28, 0x30, 0x28, 0x28, 0x30, 0x28, 0x28, 0x30, 0x28, 0x28, 0x30,
	0x28, 0x28, 0x70, 0x68, 0x68, 0xb0, 0x68, 0xa8, 0x70, 0xac, 0xac, 0x70, 0xac, 0xac, 0x72, 0xad,
	0xad, 0x72, 0xad, 0xad, 0x72, 0xff, 0x72, 0xad, 0xac, 0x70, 0xa8, 0xa8, 0x70, 0xa8, 0x68, 0xff,
	0x03, 0x06, 0x1d, 0x32, 0x2d, 0x6d, 0xd2, 0xad, 0xad, 0xd2, 0xff, 0x92, 0xed, 0x81, 0x80, 0x80,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xc0, 0xa0, 0xdb, 0xa4, 0xdb, 0xa4,
	0xa4, 0xdb, 0xa4, 0xdb, 0xa0, 0xc0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	0x80, 0x80, 0x81, 0xed, 0x92, 0xff, 0xd2, 0xad, 0xad, 0xd2, 0x6d, 0x2d, 0x32, 0x1d, 0x06, 0x03,
};


ArduboyPlaytune ardtune(arduboy.audio.enabled);

const int frameRate = 15;	// Frame rate, default 15 to save battery
int sc = frameRate; // Frame counter used for Pause and AM/PM swap

long milSec = 1000;	// Second counter, 1 second = 1000 milliseconds
long fullSec = 1000;// Incrematation of second counter

/* OFFSET currently not working, Need to create a function to tweek the clock per device.
long timeOffsetCalc = 0;	// Time offset variable for calculation
long timeOffsetMillis = 18;	// 18 Milliseconds Offset every 10 seconds for time accuracy
*/

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

int locX = 0, locY = 0;	// Clock location on display Default locX = 0, locY = 0
int sAv, mAv, hAv; // Variable used to adjust time. Seconds, Minutes, Hours.
int * arrD; // Display Array pointer Seconds[0], Minutes[1], Hours[2]

// Counter used for when a button is held down.
long heldTime = 1500;	// Default 1.5 seconds button held down, count milliseconds
long timeHeld = 0;	// Used for counting
bool startCounting = true;	// Determin if its start counting for a button held, TRUE = Not Start counting, FALSE = Start counting
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
int hTS, mTS, sTS; // Variable Set for when you reset the timer

// Return to Main screen
long returnCountDown = 10000; // 10 Second count down
long returnCount = 0;	// Used for count down
bool returnCounting = true;	// Counting down or not

// Store the music score, (Music from the Arduboy Playtune example)
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

// 1 PONG ADDON CODE

int xDir = WIDTH / 2, yDir = HEIGHT / 2;
int xMove = 1, yMove = 1;
int xSpeed = 3, ySpeed = 3;
int bounces = 0;
int ballRadius = 2;
int xP1 = 4, yP1 = (HEIGHT / 2) - 7;
int	xP2 = WIDTH - 5, yP2 = (HEIGHT / 2) - 7;
int yPL = 15;
int aiWin = 0;
int p1Score = 0, p2Score = 0, p1Wins = 0, p2Wins = 0;

bool screenSaverSetting = false;
bool screenSaverType = true;	// TRUE = Blank, FALSE = Pong
bool direction = true;
// count down screen saver
bool PongScreenSaver = false;
bool ssONOFF = false; // TRUE = Screen saver ON, FALSE = Screen saver OFF
long ssCD = 0;
long ssCDT = 30000; // 30 Seconds




// 1 PONG ADDON CODE

void setup()
{
	ardtune.initChannel(PIN_SPEAKER_1);	// Initialise first speaker pin
	ardtune.initChannel(PIN_SPEAKER_2);	// Initialise second speaker pin
	arduboy.boot();	// Boot the Arduboy with not logo. Straight to the App.
	arduboy.setFrameRate(frameRate);	// Time calculated based on set variable frames per second
	arduboy.clear();	// Clear display buffer
	arduboy.audio.on();	// Turn on Audio.

	// 2 PONG ADDON CODE
	if (rand() % 1 == 0)
	{
		direction = !direction;
		xMove = -xMove;
	}
	// 2 PONG ADDON CODE
}

void loop()
{	

	// Second incrementation, every 1000 millisecond 1 second is added
	if (millis() >= milSec)
	{
		milSec += fullSec;	// Add 1 second to the variable.

		// Verify if Timer should be ON
		if (timerOnSetting)
		{
			TimerCountDown();	// Call the TimerCountDown function to decrement the time every second.
		}

		/* Function to be revisited. currently not effective.
		// Time Offset calculation for clock accuracy, every 10 sec add the Offset
		timeOffsetCalc++;
		if (timeOffsetCalc == 10)
		{
			timeOffsetCalc = 0; // Reset calculation variable
			milSec += timeOffsetMillis;	// Add the Offset to delay time
		}*/

		// Pause clock hold A and B, Only works with screen ON
		if (arduboy.pressed(A_BUTTON) && arduboy.pressed(B_BUTTON) && diplayOnOff && !alarmSetting && !timerSetting)
		{
			sc = frameRate;
			return;
		}
		
		s++;	// Increase Second by 1
	}
	

	// Verify if its time for next frame if not exit the loop.
	if (!arduboy.nextFrame())
	{
		return;
	}

	arduboy.clear();	// Clear display buffer at the beginning of each frame
	arduboy.setTextSize(1);	// Set the font size back to default once a frame starts anew

	clock();	// Call Function, Calculate time and store it

	// Verify if Alarm is on and start playing Music
	if (sA == s && mA == m && hA == h && ampmA == ampm && alarmOnSetting)
	{
		ardtune.playScore(score);	// Play the stored score
		alarmOnSetting = false;	// Turn off the Alarm setting to OFF
	}
	
	if (PongScreenSaver)
	{
		if (ssONOFF)
		{
			if (!screenSaverType)
			{
				Pong();
				if (HeldRightButton())
				{
					PongScreenSaver = false;
				}
				return;
			}
		}
		else if (!screenSaverType)
		{
			Pong();
			if (HeldRightButton())
			{
				PongScreenSaver = false;
			}
			return;
		}

	}
	ShowDisplay();	// Call function and verify if the used is trying to turn ON or OFF the display

	// Exit loop function if screen should be OFF
	if (!diplayOnOff)
	{
		arduboy.display();
		return;
	}
	
	HeldLeftButton();	// Call function and verify if user want to turn the Alarm ON or OFF
	HeldRightButton();	// Call function and verify if user want to Start or Stop the Timer
	HeldDownButton();
	HeldUpButton();

	// Change to the Alarm setting Screen
	if (/*HeldDownButton() || */alarmSetting)
	{
		arduboy.clear();	// Clear the display buffer
		DisplayAlarm();		// Call the function to show the Alarm setting screen
	}
	// Change to the Timer setting Screen
	else if (/*HeldUpButton() || */timerSetting)
	{
		arduboy.clear();	// Clear the display buffer
		DisplayTimer();		// Call the function to show the Timer setting screen
	}
	// 3 PONG ADDON CODE
	else if (screenSaverSetting)
	{
		DisplayPong();
	}
	// 3 PONG ADDON CODE
	// Show main Screen if no other Screen are called
	else
	{	
		DisplayMain();	// Call function to show the Main screen
	}

	
	arduboy.display();	// Display on screen what is currently in the disply buffer
}

// Calculate time and store it.
void clock()
{

	// Frame counter used for Pause and AM/PM swap
	if (sc == 0)
	{
		sc = frameRate;	// Reset the varible back to default frame rate
	}
	else
	{
		sc--;	// Decrement varible by 1
	}

	// Clock incrementation
	// Add 1 min every 60 seconds and reset second to 0
	if (s == 60)
	{
		s = 0;	// Reset second
		m++;	// Increment minute by 1
	}

	// Add 1 hour every 60 minutes and reset minute to 0
	if (m == 60 && s == 0)
	{
		m = 0;	// Reset minute
		h++;	// Increment hour by 1
	}

	// Turn over clock 
	// If the clock is set to 24h, turns the clock over once the hour hits 24.
	if (h == 24 && m == 0 && s == 0 && !clockType && sc == frameRate)
	{
		h = 0;	// Set hours to 0
		ampm = true;	// Set the clock to AM
	}
	// Turn to PM less than a second before it turns to 12:00 PM so the Alarm detects PM properly
	else if (h == 11 && m == 59 && s == 59 && clockType && ampm && sc == frameRate)
	{
		ampm = false;
	}
	// Turn to AM less than a second before it turns to 12:00 AM so the Alarm detects AM properly
	else if (h == 11 && m == 59 && s == 59 && clockType && !ampm && sc == frameRate)
	{
		ampm = true;
	}
	// If the clock is set to 12h turn to 1 instead of 13.
	if (h > 12 && m == 0 && s == 0 && clockType)
	{
		h = 1;
	}
	// If the clock is set 24h turn to PM once hours turn to 12
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
		arduboy.clear();	// Clear display buff
		arduboy.display();	// Show what is on the diplay buffer (nothing since it just go cleared)
		arduboy.digitalWriteRGB(RGB_OFF, RGB_OFF, RGB_OFF);	// Turn off LEDs if any were on while transitioning
		diplayOnOff = false;	// Set the variable that detects Display to be OFF
		startCounting = true;	// Reset the variable that detects how long a button has be held
		alarmSetting = false;	// Turn off the Alarm screen variable so when the user turn the screen back ON its back to Main screen
		timerSetting = false;	// Turn off the Timer screen variable so when the user turn the screen back ON its back to Main screen
		

	}
	// Press UP and DOWN to turn screen ON and display clock.
	else if (arduboy.pressed(UP_BUTTON) && arduboy.pressed(DOWN_BUTTON) && arduboy.notPressed(A_BUTTON) && arduboy.notPressed(B_BUTTON) && arduboy.notPressed(LEFT_BUTTON) && arduboy.notPressed(RIGHT_BUTTON))
	{
		arduboy.digitalWriteRGB(RGB_OFF, RGB_OFF, RGB_OFF);	// Turn off LEDs if any were on while transitioning
		diplayOnOff = true;	// Set the variable that detects Display to be ON
	}
	NoButton();
}

// Modify time sA=Seconds, mA=Minutes, hA=Hours, 'ClockOrAlarm' TRUE=Setting Clock, FALSE=Setting Alarm, 'SetTimer' TRUE=Setting Timer
int * AdjustTime(int sAA, int mAA, int hAA, bool ClockOrAlarm, bool SetTimer)
{
	sAv = sAA;	// Set the received varible while calling the function to a public one so it can be used outside this function
	mAv = mAA;	// Set the received varible while calling the function to a public one so it can be used outside this function
	hAv = hAA;	// Set the received varible while calling the function to a public one so it can be used outside this function
	static int adjT[3];	// Create a array to return 3 variable from this function
	
	// Disable changing clocktype if your are setting up Timer.
	if (!SetTimer)
	{
		// Press RIGHT and UP to set clock type to 24h
		if (arduboy.pressed(RIGHT_BUTTON) && arduboy.pressed(UP_BUTTON) && clockType&& arduboy.notPressed(A_BUTTON) && arduboy.notPressed(B_BUTTON) && arduboy.notPressed(LEFT_BUTTON) && arduboy.notPressed(DOWN_BUTTON))
		{
			clockType = false;	// Change the clock type to 24h

			// Verify the time for the Main clock and also the Alarm clock and change the time accordingly
			// Set Hours according to AM PM
			if (hAv == 12)
			{
				// Change hours to 0 if its 12 AM
				if (ClockOrAlarm && ampm) // Verify Main clock
				{
					hAv = 0;
				}
				else if (h == 12 && ampm)
				{
					h = 0;
				}

				if (!ClockOrAlarm && ampmA)	// Verify Alarm clock
				{
					hAv = 0;
				}
				else if (hA == 12 && ampmA)
				{
					hA = 0;
				}
			}
			// Add 12 to the hour if its PM
			else if (hAv != 12)
			{
				if (ClockOrAlarm && !ampm)	// Verify Main clock
				{
					hAv += 12;
				}
				else if (h != 12 && !ampm)
				{
					h += 12;
				}
				else if (h == 12 && ampm)
				{
					h = 0;
				}

				if (!ClockOrAlarm && !ampmA)	// Verify Alarm clock
				{
					hAv += 12;
				}
				else if(hA != 12 && !ampmA)
				{
					hA += 12;
				}
				else if (hA == 12 && ampmA)
				{
					hA = 0;
				}
			}
		}
		// Press LEFT and DOWN to set clock type to 12h AM/PM
		if (arduboy.pressed(LEFT_BUTTON) && arduboy.pressed(DOWN_BUTTON) && !clockType&& arduboy.notPressed(A_BUTTON) && arduboy.notPressed(B_BUTTON) && arduboy.notPressed(RIGHT_BUTTON) && arduboy.notPressed(UP_BUTTON))
		{
			clockType = true;	// Change the clock type to 12h

			// Verify the time for the Main clock and also the Alarm clock and change the time accordingly
			// Set Hours according to AM PM
			if (hAv > 12)
			{
				// If the hours is is above 12 therefore PM, reduce the hours by 12 and make sure the AM/PM variable is properly set to PM
				if (ClockOrAlarm)	// Verify Main clock
				{
					hAv -= 12;
					ampm = false;
				}
				else if (h > 12)
				{
					h -= 12;
					ampm = false;
				}

				if (!ClockOrAlarm)	// Verify Alarm clock
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
			// Check if its bettwen 0 and 12, then make sure the AM/PM variable is properly set to AM
			else if (hAv != 0 && hAv < 12)
			{
				if (ClockOrAlarm)	// Verify Main clock
				{
					ampm = true;
				}
				else if (h != 0 && hAv < 12)
				{
					ampm = true;
				}

				if (!ClockOrAlarm)	// Verify Alarm clock
				{
					ampmA = true;
				}	
				else if (hA != 0 && hAv < 12)
				{
					ampmA = true;
				}
			}
			// Check if the hour is 0 therefore change it to 12
			if (hAv == 0)
			{
				if (ClockOrAlarm)	// Verify Main clock
				{
					hAv = 12;
					ampm = true;
				}
				else if (h == 0)
				{
					h = 12;
					ampm = true;
				}

				if (!ClockOrAlarm)	// Verify Alarm clock
				{
					hAv = 12;
					ampmA = true;
				}
				else if (hA == 0)
				{
					hA = 12;
					ampmA = true;
				}
			}
		}
	}

	// Adjust Hours hold A, press UP or DOWN
	if (arduboy.pressed(A_BUTTON) && arduboy.pressed(UP_BUTTON) && arduboy.notPressed(B_BUTTON))
	{
		HourTurn(true, ClockOrAlarm, SetTimer);	// Call the function to change the hours, (Increment)
	}
	else if (arduboy.pressed(A_BUTTON) && arduboy.pressed(DOWN_BUTTON) && arduboy.notPressed(B_BUTTON))
	{
		HourTurn(false, ClockOrAlarm, SetTimer);	// Call the function to change the hours, (Decrement)
	}
	// Adjust Minutes hold B, press UP or DOWN
	else if (arduboy.pressed(B_BUTTON) && arduboy.pressed(UP_BUTTON) && arduboy.notPressed(A_BUTTON))
	{
		MinuteTurn(true, ClockOrAlarm, SetTimer);	// Call the function to change the minutes, (Increment)
	}
	else if (arduboy.pressed(B_BUTTON) && arduboy.pressed(DOWN_BUTTON) && arduboy.notPressed(A_BUTTON))
	{
		MinuteTurn(false, ClockOrAlarm, SetTimer);	// Call the function to change the minutes, (Decrement)
	}
	// Adjust Seconds hold A and B, press UP or DOWN
	else if (arduboy.pressed(A_BUTTON) && arduboy.pressed(B_BUTTON) && arduboy.pressed(UP_BUTTON))
	{
		SecondTurn(true, ClockOrAlarm, SetTimer);	// Call the function to change the seconds, (Increment)
	}
	else if (arduboy.pressed(A_BUTTON) && arduboy.pressed(B_BUTTON) && arduboy.pressed(DOWN_BUTTON))
	{
		SecondTurn(false, ClockOrAlarm, SetTimer);	// Call the function to change the seconds, (Decrement)
	}

	adjT[0] = sAv;	// Set the modified seconds to the array
	adjT[1] = mAv;	// Set the modified minutes to the array
	adjT[2] = hAv;	// Set the modified hours to the array

	return adjT;	// Return the array out of this function 
}

// Swap AM/PM depending of which time your are adjusting, 'ClockOrAlarm' TRUE=Clock, FALSE=Alarm
boolean AmPmSwap(bool ClockOrAlarm) 
{	
	// Change Main clock AM/PM variable
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
	// Change Alarm clock AM/PM variable
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
	ResetReturnCount(); // Reset return to main screen countdown
	// Enter the increment section
	if (changeH)
	{
		hAv++;	// Increment hours by 1
		// Disregard if user is setting up the timer
		if (!setTimer)
		{
			// Turn the hours from 13 to 1 if the clock type is 12h
			if (clockType && hAv > 12)
			{
				hAv = 1;
			}
			// Swap AM/PM if hour is 12 and the clock type is 24h
			else if (hAv == 12)
			{
				AmPmSwap(ClockOrAlarm);
			}
			// Swap AM/PM and change from 24 to 0 if clock type is 24h
			else if (!clockType && hAv == 24)
			{
				hAv = 0;
				AmPmSwap(ClockOrAlarm);
			}
		}
		else
		{
			if (hAv > 99)
			{
				hAv = 99;
			}
		}
	}
	// Enter the decrement section
	else
	{
		hAv--;	// Decrement hours by 1
		// Disregard if user is setting up the timer
		if (!setTimer)
		{
			// Turn the hours from 0 to 12 if the clock type is 12h
			if (clockType && hAv < 1)
			{
				hAv = 12;
			}
			// Swap AM/PM if hour goes down to 11
			else if (hAv == 11)
			{
				AmPmSwap(ClockOrAlarm);
			}
			// Turn the hours from -1 to 23 if the clock type is 24h
			else if (!clockType && hAv < 0)
			{
				hAv = 23;
				AmPmSwap(ClockOrAlarm);
			}
		}
		// If user is setting up Timer, block hours at 0
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
	ResetReturnCount(); // Reset return to main screen countdown
	// Enter the increment section
	if (changeM)
	{
		mAv++;	// Increment minutes by 1
		// Return the minutes to 0 if it goes above 59
		if (mAv > 59)
		{
			// Disregard affecting hours if user is setting up Timer
			if (!setTimer)
			{
				mAv = 0;
				HourTurn(true, ClockOrAlarm, setTimer);	// Turn the Hours
			}
			else
			{
				mAv = 0;
			}
			
		}
	}
	// Enter the decrement section
	else
	{
		mAv--;	// Decrement minutes by 1
		// Return the minutes to 59 if it goes under 0
		if (mAv < 0)
		{
			// Disregard affecting hours if user is setting up Timer
			if (!setTimer)
			{
				mAv = 59;
				HourTurn(false, ClockOrAlarm, setTimer);	// Turn the Hours
			}
			else
			{
				mAv = 59;
			}
			
		}
	}
}

// 'changeS' Increment(TRUE) or Decrement(FALSE) seconds, 'ClockOrAlarm' TRUE=Setting Clock, FALSE=Setting Alarm, 'setTimer' TRUE=Setting Timer
int SecondTurn(bool changeS, bool ClockOrAlarm, bool setTimer)
{
	ResetReturnCount(); // Reset return to main screen countdown
	// Enter the increment section
	if (changeS)
	{
		sAv++;	// Increment seconds by 1
		// Return the seconds to 0 if it goes above 59
		if (sAv > 59)
		{
			// Disregard affecting minutes if user is setting up Timer
			if (!setTimer)
			{
				sAv = 0;
				MinuteTurn(true, ClockOrAlarm, setTimer);	// Turn over minutes
			}
			else
			{
				sAv = 0;
			}
			
		}
	}
	// Enter the decrement section
	else
	{
		sAv--;	// Decrement seconds by 1
		// Return the seconds to 59 if it goes under 0
		if (sAv < 0)
		{
			// Disregard affecting minutes if user is setting up Timer
			if (!setTimer)
			{
				sAv = 59;
				MinuteTurn(false, ClockOrAlarm, setTimer);	// Turn over minutes
			}
			else
			{
				sAv = 59;
			}
			
		}
	}
}


// Combine necessary strings to present the time, 'ClockOrAlarm' TRUE=Clock, FALSE=Alarm, 'Timer' TRUE=Timer Display
String CreateDisplayText(int sD, int mD, int hD, bool ClockOrAlarm, bool Timer, bool Pong)
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

	if (Timer)
	{
		if (hD < 10)
		{
			hourD = "0";
		}
		else
		{
			hourD = "";
		}
	}

	// Diplay AM or PM if clock set to 12h type Or nothing if is the Timer diplay
	if (clockType && !Timer)
	{
		if (ClockOrAlarm)
		{
			if (ampm)
			{
				ampmText = "AM";
			}
			else
			{
				ampmText = "PM";
			}
		}
		else if (!ClockOrAlarm)
		{
			if (ampmA)
			{
				ampmText = "AM";
			}
			else
			{
				ampmText = "PM";
			}
		}
	}
	else
	{
		ampmText = "";
	}
	if (!Pong)
	{
		return hourD + hD + clockS + minD + mD + clockS + secD + sD;	// Create Display string
	}
	return hourD + hD + clockS + minD + mD;	// Create Display string
}

// Verify if no button has been pressed and return true if it is the case
boolean NoButton()
{
	if (arduboy.notPressed(A_BUTTON) && arduboy.notPressed(B_BUTTON) && arduboy.notPressed(UP_BUTTON) && arduboy.notPressed(DOWN_BUTTON) && arduboy.notPressed(LEFT_BUTTON) && arduboy.notPressed(RIGHT_BUTTON))
	{
		if (ssONOFF)
		{
			if (millis() >= ssCD)
			{
				if (screenSaverType)
				{
					diplayOnOff = false;
				}
				else
				{
					PongScreenSaver = true;
				}
			}
			else if (ssCD == -1)
			{
				ssCD = millis() + ssCDT;
			}
		}
		buttonHeld = true;
		return true;

	}

	ssCD = -1;
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
/*boolean*/void HeldDownButton()
{
	// Check if proper buttons has been pressed and the user is not at the Timer screen
	if (arduboy.pressed(DOWN_BUTTON) && SingleButton("DOWN") && buttonHeld/*&& !timerSetting*/)
	{
		buttonHeld = false;
		returnCounting = true;
		if (!alarmSetting && !timerSetting && !screenSaverSetting)
		{
			alarmSetting = true;
		}
		else if (alarmSetting)
		{
			alarmSetting = false;
			timerSetting = true;
		}
		else if (timerSetting)
		{
			timerSetting = false;
			screenSaverSetting = true;
		}
		else if (screenSaverSetting)
		{
			screenSaverSetting = false;
		}
	}
	// Check if no button has been pressed
	if (NoButton())
	{
		ResetButtonHeldCounter();	// Call function to reset ligth and multiple variables
	}
}

//Change to TIMER SETTINGS, Detect for DOWN button held long enough
/*boolean*/void HeldUpButton()
{
	// Check if proper buttons has been pressed and the user is not the Alarm screen
	if (arduboy.pressed(UP_BUTTON) && SingleButton("UP") && buttonHeld/*&& !alarmSetting*/)
	{
		buttonHeld = false;
		returnCounting = true;
		if (!alarmSetting && !timerSetting && !screenSaverSetting)
		{
			screenSaverSetting = true;
		}
		else if (screenSaverSetting)
		{
			screenSaverSetting = false;
			timerSetting = true;
		}
		else if (timerSetting)
		{
			timerSetting = false;
			alarmSetting = true;
		}
		else if (alarmSetting)
		{
			alarmSetting = false;
		}
		// PONG ADDON CODE
	}
	if (NoButton())
	{
		ResetButtonHeldCounter();	// Call function to reset ligth and multiple variables
	}
}

// SET to ALARM ON or OFF, Detect for DOWN button held long enough
boolean HeldLeftButton()
{
	// Check if proper buttons has been pressed 
	if (arduboy.pressed(LEFT_BUTTON) && SingleButton("LEFT"))
	{
		ResetReturnCount(); // Reset return to main screen countdown
		// Check if music is playing
		if (ardtune.playing())
		{
			ardtune.stopScore();	// Turn off music
		}

		// Count if user is not at the Timer screen
		if (!timerSetting && !screenSaverSetting || (screenSaverSetting && !screenSaverType))
		{
			// Check if proper time has past while the button is held
			if (millis() >= timeHeld && !startCounting && buttonHeld)
			{

				buttonHeld = false;	// Reset the variable
				timeHeld = 0;	// Reset the 
				arduboy.digitalWriteRGB(RGB_OFF, RGB_ON, RGB_OFF);	// Turn on light to indicate the button was held long enough
				if (!screenSaverSetting)
				{
					//	Swap between Alarm ON or OFF
					if (alarmOnSetting)
					{
						alarmOnSetting = false;	// Set Alarm OFF
						return false;
					}
					else
					{
						alarmOnSetting = true;	// Set Alarm ON
						//alarmSetting = false;	// Exit Alarm setting screen
						return true;
					}
				}
				else
				{
					screenSaverSetting = false;
					PongScreenSaver = true;
				}

			}
			// Start the count down for how long the button has been held
			if (startCounting)
			{
				timeHeld = millis() + heldTime;	// Set the varible for the counter with how long button should be held as per 'heldTime'
				startCounting = false;	// Set variable to indicate the countdown just started
				arduboy.digitalWriteRGB(RGB_OFF, RGB_OFF, RGB_ON);	// Turn on light to indicate the button is being held
			}
		}
		else
		{
			if (timerSetting)
			{
				if (!timerOnSetting)
				{
					ResetTimer();
				}
			}
			else if (screenSaverSetting)
			{
				screenSaverType = false;
			}
		}
		
	}
	// Check if no button has been pressed
	if (NoButton())
	{
		ResetButtonHeldCounter();	// Call function to reset ligth and multiple variables
		return false;
	}
}

// Set START OR STOP TIMER, Detect for down button held long enough
boolean HeldRightButton()
{
	// Check if proper buttons has been pressed and the user is not at the main screen
	if (arduboy.pressed(RIGHT_BUTTON) && SingleButton("RIGHT"))
	{
		ResetReturnCount(); // Reset return to main screen countdown
		// Check if music is playing
		if (ardtune.playing())
		{
			ardtune.stopScore();	// Turn off music
		}

		// Count if user is not at the Alarm screen
		if (!alarmSetting && !screenSaverSetting)
		{
			// Check if proper time has past while the button is held
			if (millis() >= timeHeld && !startCounting && buttonHeld)
			{
				buttonHeld = false;	// Reset the variable
				timeHeld = 0;	// Reset the variable
				arduboy.digitalWriteRGB(RGB_OFF, RGB_ON, RGB_OFF);	// Turn on light to indicate the button was held long enough

				if (!PongScreenSaver)
				{
					//	Swap Timer status, Running or Not
					if (timerOnSetting)
					{
						timerOnSetting = false;	// Stop timer
						return false;
					}
					else
					{
						timerOnSetting = true;	// Start timer
						sTS = sT;
						mTS = mT;
						hTS = hT;
						//timerSetting = false;	// Exit Timer setting screen
						return true;
					}
				}
				else
				{
					return true;
				}
			}
			// Start the count down for how long the button has been held
			if (startCounting)
			{
				timeHeld = millis() + heldTime;	// Set the varible for the counter with how long button should be held as per 'heldTime'
				startCounting = false;	// Set variable to indicate the countdown just started
				arduboy.digitalWriteRGB(RGB_OFF, RGB_ON, RGB_ON);	// Turn on light to indicate the button is being held
			}
		}
		else if (screenSaverSetting)
		{
			screenSaverType = true;
		}
	}
	// Check if no button has been pressed
	if (NoButton())
	{
		ResetButtonHeldCounter();	// Call function to reset ligth and multiple variables
		return false;
	}
}

//  Display the Main screen
void DisplayMain()
{
	String alarmClock;
	String timerClock;

	DrawFrame();
	ardTiny.setCursor(15, 2);
	ardTiny.print("ALARM");
	ardTiny.setCursor(90, 2);
	ardTiny.print("TIMER");

	// Display Timer if running
	if (timerOnSetting)
	{
		arduboy.setCursor(74, 2);
		arduboy.setTextSize(1);
		arduboy.print("ON");
	}
	// Display how to access Timer screen
	else
	{
		arduboy.setCursor(71, 2);
		arduboy.setTextSize(1);
		arduboy.print("OFF");
	}

	// Display Alarm if its ON
	if (alarmOnSetting)
	{
		arduboy.setCursor(44, 2);
		arduboy.setTextSize(1);
		arduboy.print("ON");
	}
	// Diplay how to access Alarm screen
	else
	{
		arduboy.setCursor(41, 2);
		arduboy.setTextSize(1);
		arduboy.print("OFF");
	}
	

	arrD = AdjustTime(s, m, h, true, false);	// Call funtion to change time if user choose to
	s = *(arrD);	// Extract seconds from array as per previous function
	m = *(arrD + 1);	// Extract minutes from array as per previous function
	h = *(arrD + 2);	// Extract hours from array as per previous function
	arduboy.setTextSize(2);	// Increase font size
	arduboy.setCursor(17, 25);	// Set location for clock
	clockText = CreateDisplayText(s, m, h, true, false, false);	// Add to display buffer by calling function to create the time text
	arduboy.print(clockText); // Print clock
	
	ardTiny.setCursor(55, 13);
	ardTiny.print("TIME");

	if (clockType)
	{
		if (ampm)
		{
			arduboy.setCursor(59, 44); // +3 ON
			arduboy.setTextSize(1);
			arduboy.print("AM");
		}
		else
		{
			arduboy.setCursor(59, 44); // +3 ON
			arduboy.setTextSize(1);
			arduboy.print("PM");
		}

		alarmClock = CreateDisplayText(sA, mA, hA, false, false, false);
		ardTiny.setCursor(14, 57);
		if (ampmA)
		{
			ardTiny.print(alarmClock + "A");
		}
		else
		{
			ardTiny.print(alarmClock + "P");
		}
	}
	else
	{
		alarmClock = CreateDisplayText(sA, mA, hA, false, false, false);
		ardTiny.setCursor(14, 57);
		if (ampmA)
		{
			ardTiny.print(alarmClock);
		}
		else
		{
			ardTiny.print(alarmClock);
		}
	}
	timerClock = CreateDisplayText(sT, mT, hT, false, true, false);
	ardTiny.setCursor(70, 57);
	ardTiny.print(timerClock);
	
	if (ardtune.playing())
	{
		// Left border
		ardTiny.setCursor(02, 22);
		ardTiny.print("M");
		ardTiny.setCursor(02, 27);
		ardTiny.print("U");
		ardTiny.setCursor(02, 32);
		ardTiny.print("T");
		ardTiny.setCursor(02, 37);
		ardTiny.print("E");

		// Left border
		ardTiny.setCursor(122, 22);
		ardTiny.print("M");
		ardTiny.setCursor(122, 27);
		ardTiny.print("U");
		ardTiny.setCursor(122, 32);
		ardTiny.print("T");
		ardTiny.setCursor(122, 37);
		ardTiny.print("E");
	}
}

// Display the Alarm setting screen
void DisplayAlarm()
{
	DrawFrame();
	ardTiny.setCursor(15, 2);
	ardTiny.print("ALARM");
	ardTiny.setCursor(90, 2);
	ardTiny.print("TIMER");

	ardTiny.setCursor(34, 57);
	ardTiny.print("ALARM");
	ardTiny.setCursor(70, 57);
	ardTiny.print("SETTING");

	// Display Timer if running
	if (timerOnSetting)
	{
		arduboy.setCursor(74, 2); // +3 ON
		arduboy.setTextSize(1);
		arduboy.print("ON");

	}
	else
	{
		arduboy.setCursor(71, 2); // +3 ON
		arduboy.setTextSize(1);
		arduboy.print("OFF");
	}
	// Display Alarm if its ON
	if (alarmOnSetting)
	{
		arduboy.setCursor(44, 2); // +3 ON
		arduboy.setTextSize(1);
		arduboy.print("ON");
		// Left border
		ardTiny.setCursor(02, 14);
		ardTiny.print("T");
		ardTiny.setCursor(02, 19);
		ardTiny.print("U");
		ardTiny.setCursor(02, 24);
		ardTiny.print("R");
		ardTiny.setCursor(02, 29);
		ardTiny.print("N");
		ardTiny.setCursor(02, 36);
		ardTiny.print("O");
		ardTiny.setCursor(02, 41);
		ardTiny.print("F");
		ardTiny.setCursor(02, 46);
		ardTiny.print("F");
	}
	else
	{
		arduboy.setCursor(41, 2); // +3 ON
		arduboy.setTextSize(1);
		arduboy.print("OFF");
		// Left border
		ardTiny.setCursor(02, 14);
		ardTiny.print("T");
		ardTiny.setCursor(02, 19);
		ardTiny.print("U");
		ardTiny.setCursor(02, 24);
		ardTiny.print("R");
		ardTiny.setCursor(02, 29);
		ardTiny.print("N");
		ardTiny.setCursor(02, 36);
		ardTiny.print("O");
		ardTiny.setCursor(02, 41);
		ardTiny.print("N");
	}
	
	

	/*
	String alarmStatusText;	// Used for displaying if Alarm if ON or OFF
	// Verify Alarm status and set string accordingly
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
	arduboy.print(clockTypeText + "  ALARM SETTING\n\r" + alarmStatusText);	// Add to display buffer 
	*/
	arduboy.setCursor(17, 25);	// Set location for text
	arrD = AdjustTime(sA, mA, hA, false, false);	// Call funtion to change time if user choose to
	sA = *(arrD);	// Extract seconds from array as per previous function
	mA = *(arrD + 1);	// Extract minutes from array as per previous function
	hA = *(arrD + 2);	// Extract hours from array as per previous function
	arduboy.setTextSize(2);	// Increase font size
	arduboy.print(CreateDisplayText(sA, mA, hA, false, false, false));	// Add to display buffer by calling function to create the time text
	arduboy.setTextSize(1);	// Reset font size

	if (clockType)
	{
		if (ampmA)
		{
			arduboy.setCursor(59, 44);
			arduboy.setTextSize(1);
			arduboy.print("AM");
		}
		else
		{
			arduboy.setCursor(59, 44);
			arduboy.setTextSize(1);
			arduboy.print("PM");
		}
	}	
}

// Display the Timer setting screen
void DisplayTimer()
{	
	DrawFrame();
	ardTiny.setCursor(15, 2);
	ardTiny.print("ALARM");
	ardTiny.setCursor(90, 2);
	ardTiny.print("TIMER");

	ardTiny.setCursor(34, 57);
	ardTiny.print("TIMER");
	ardTiny.setCursor(70, 57);
	ardTiny.print("SETTING");

	// Display Timer if running
	if (timerOnSetting)
	{
		arduboy.setCursor(74, 2); // +3 ON
		arduboy.setTextSize(1);
		arduboy.print("ON");

		// Right border
		ardTiny.setCursor(122, 22);
		ardTiny.print("S");
		ardTiny.setCursor(122, 27);
		ardTiny.print("T");
		ardTiny.setCursor(122, 32);
		ardTiny.print("O");
		ardTiny.setCursor(122, 37);
		ardTiny.print("P");
	}
	else
	{
		arduboy.setCursor(71, 2); // +3 ON
		arduboy.setTextSize(1);
		arduboy.print("OFF");
		// Left border
		ardTiny.setCursor(02, 20);
		ardTiny.print("R");
		ardTiny.setCursor(02, 25);
		ardTiny.print("E");
		ardTiny.setCursor(02, 30);
		ardTiny.print("S");
		ardTiny.setCursor(02, 35);
		ardTiny.print("E");
		ardTiny.setCursor(02, 40);
		ardTiny.print("T");
		// Right border
		ardTiny.setCursor(122, 20);
		ardTiny.print("S");
		ardTiny.setCursor(122, 25);
		ardTiny.print("T");
		ardTiny.setCursor(122, 30);
		ardTiny.print("A");
		ardTiny.setCursor(122, 35);
		ardTiny.print("R");
		ardTiny.setCursor(122, 40);
		ardTiny.print("T");
	}
	// Display Alarm if its ON
	if (alarmOnSetting)
	{
		arduboy.setCursor(44, 2); // +3 ON
		arduboy.setTextSize(1);
		arduboy.print("ON");
	}
	else
	{
		arduboy.setCursor(41, 2); // +3 ON
		arduboy.setTextSize(1);
		arduboy.print("OFF");
	}

	if (!timerOnSetting)
	{
		arrD = AdjustTime(sT, mT, hT, false, true);	// Call funtion to change time if user choose to
		sT = *(arrD);	// Extract seconds from array as per previous function
		mT = *(arrD + 1);	// Extract minutes from array as per previous function
		hT = *(arrD + 2);	// Extract hours from array as per previous function
	}
	arduboy.setCursor(17, 25);	// Set location for text
	arduboy.setTextSize(2);	// Increase font size
	arduboy.print(CreateDisplayText(sT, mT, hT, false, true, false));	// Add to display buffer by calling function to create the time text
	arduboy.setTextSize(1);	// Reset font size

}

// At every calls the Timer decrement.
void TimerCountDown()
{
	sT--;	// Decrement Timer's second by 1

	// Check if timer second goes below 0
	if (sT < 0)
	{
		// Check if minutes are at 0
		if (mT != 0)
		{
			sT = 59;	// Reset seconds at the top
			mT--;	// Decrement Timer's minutes by 1
		}
		// Check if hours are at 0
		else if(hT != 0)
		{
			sT = 59;	// Reset seconds at the top
			mT = 59;	// Reset minutes at the top
			hT--;	// Decrement Timer's hours by 1

		}
		// So if everything is false that means the timer hit the end
		else
		{
			sT = 0;	// Reset seconds
			ardtune.playScore(score);	// Start the music
			timerOnSetting = false;	// Set Timer status to OFF
			ResetTimer();
		}
		
	}
}

// Reset the counter and turn off light when user stop holding a button.
void ResetButtonHeldCounter()
{
	buttonHeld = true;	// Reset variable confirming a button is being held
	startCounting = true;	// Set variable to indicate to reset the countdown
	arduboy.digitalWriteRGB(RGB_OFF, RGB_OFF, RGB_OFF);	// Turn off lights when no button is being held

	if (millis() >= returnCount && !returnCounting)
	{
		
		timerSetting = false;
		alarmSetting = false;
		screenSaverSetting = false;
		
		returnCount = 0;	// Reset the 
	}
	if (returnCounting)
	{
		ResetReturnCount();	// Set the varible for the counter with how long button should be held as per 'heldTime'
		returnCounting = false;	// Set variable to indicate the countdown just started
	}
}

void ResetReturnCount() 
{
	returnCount = millis() + returnCountDown;
}

void DrawFrame() 
{
	ardbitmap.drawBitmap(64, 32, FRAME, 128, 64, WHITE, ALIGN_CENTER, MIRROR_NONE);
}

void ResetTimer()
{
	sT = sTS;
	mT = mTS;
	hT = hTS;
}


// PONG ADDON CODE

void DisplayPong()
{
	DrawFrame();
	ardTiny.setCursor(15, 2);
	ardTiny.print("ALARM");
	ardTiny.setCursor(90, 2);
	ardTiny.print("TIMER");
	// Display Timer if running
	if (timerOnSetting)
	{
		arduboy.setCursor(74, 2); // +3 ON
		arduboy.setTextSize(1);
		arduboy.print("ON");

	}
	else
	{
		arduboy.setCursor(71, 2); // +3 ON
		arduboy.setTextSize(1);
		arduboy.print("OFF");
	}
	// Display Alarm if its ON
	if (alarmOnSetting)
	{
		arduboy.setCursor(44, 2); // +3 ON
		arduboy.setTextSize(1);
		arduboy.print("ON");
	}
	else
	{
		arduboy.setCursor(41, 2); // +3 ON
		arduboy.setTextSize(1);
		arduboy.print("OFF");
	}

	// Left border
	ardTiny.setCursor(02, 22);
	ardTiny.print("P");
	ardTiny.setCursor(02, 27);
	ardTiny.print("O");
	ardTiny.setCursor(02, 32);
	ardTiny.print("N");
	ardTiny.setCursor(02, 37);
	ardTiny.print("G");

	// Right border
	ardTiny.setCursor(122, 20);
	ardTiny.print("B");
	ardTiny.setCursor(122, 25);
	ardTiny.print("L");
	ardTiny.setCursor(122, 30);
	ardTiny.print("A");
	ardTiny.setCursor(122, 35);
	ardTiny.print("N");
	ardTiny.setCursor(122, 40);
	ardTiny.print("K");

	// Bottom
	ardTiny.setCursor(29, 57);
	ardTiny.print("SCREEN");
	ardTiny.setCursor(70, 57);
	ardTiny.print("SAVER");

	// Top 
	ardTiny.setCursor(37, 14);
	ardTiny.print("30SEC DELAY");
	if (!screenSaverType)
	{
		arduboy.drawFastHLine(40, 18, 47, WHITE);
		arduboy.drawFastVLine(40, 18, 31, WHITE);
		arduboy.drawFastHLine(40, 49, 47, WHITE);
		arduboy.drawFastVLine(87, 18, 31, WHITE);
		arduboy.drawFastVLine(42, 23, 6, WHITE);
		arduboy.drawFastVLine(85, 39, 6, WHITE);
		arduboy.drawCircle(63, 32, 1, WHITE);
		ardTiny.setCursor(52, 20);
		ardTiny.print("12:00");
		ardTiny.setCursor(55, 43);
		ardTiny.print("PONG");
		
	}
	else
	{
		arduboy.drawFastHLine(40, 18, 47, WHITE);
		arduboy.drawFastVLine(40, 18, 31, WHITE);
		arduboy.drawFastHLine(40, 49, 47, WHITE);
		arduboy.drawFastVLine(87, 18, 31, WHITE);
		ardTiny.setCursor(52, 32);
		ardTiny.print("BLANK");
	}

	if (arduboy.pressed(A_BUTTON) && SingleButton("A") && buttonHeld)
	{
		ssONOFF = !ssONOFF;
		buttonHeld = false;
	}
	if (ssONOFF)
	{
		ardTiny.setCursor(98, 57);
		ardTiny.print("ON");
	}
	else
	{
		ardTiny.setCursor(98, 57);
		ardTiny.print("OFF");
	}
	
}


void Pong()
{
	DrawPlayArea();
	PlayGame();
	MoveBall();
	ballBounce();
	MovePad();
	PadBoundary();
	DrawPad();
	AIPad();
	ScoreDisplay();
	arduboy.display();
}

void PlayGame()
{
	if (arduboy.pressed(A_BUTTON))
	{
		arduboy.setFrameRate(60);
		xSpeed = 1;
	}
	else
	{
		arduboy.setFrameRate(15);
	}
}

void MoveBall()
{
	xDir += xMove * xSpeed;
	yDir += yMove * ySpeed;
}


void ballBounce()
{
	if (xDir > WIDTH - ballRadius && (yDir > yP2 + yPL || yDir < yP2))
	{
		ResetPlay(true);
		p1Score++;
	}
	if (xDir < 0 + ballRadius && (yDir > yP1 + yPL || yDir < yP1))
	{
		ResetPlay(true);
		p2Score++;
	}

	if (yDir + ballRadius >= HEIGHT - ballRadius)
	{
		yMove = -yMove;
	}

	if (yDir - ballRadius <= 0 + ballRadius)
	{
		yMove = -yMove;
	}

	// P1 Side
	if ((yDir >= yP1 - ballRadius && yDir <= yP1 + yPL + ballRadius) && xDir <= xP1 + ballRadius)
	{
		if (!direction)
		{
			xMove = -xMove;
			direction = !direction;
		}

		aiWin = rand() % 5;
		AdjustSpeed();
	}

	// P2 Side
	if ((yDir >= yP2 - ballRadius && yDir <= yP2 + yPL + ballRadius) && xDir >= xP2 - ballRadius)
	{
		if (direction)
		{
			xMove = -xMove;
			direction = !direction;
		}
		aiWin = rand() % 5;
		AdjustSpeed();
	}
}

// Reset Play 'RoundOrGame' TRUE = Round, FALSE = Game
void ResetPlay(bool RoundOrGame)
{
	xDir = WIDTH / 2;
	yDir = HEIGHT / 2;
	aiWin = 5;
	xMove = -xMove;
	if (xMove > 0)
	{
		direction = true;
	}
	else
	{
		direction = false;
	}
	if (!RoundOrGame)
	{
		xSpeed = 3;
		ySpeed = 3;
		p1Wins = 0;
		p2Wins = 0;
		p1Score = 0;
		p2Score = 0;
	}
}
void AdjustSpeed()
{
	if (rand() % 5 != 0)
	{
		xSpeed = rand() % 5 + 1;
	}
	if (rand() % 5 != 0)
	{
		ySpeed = rand() % 4;
	}
}
void DrawPad()
{
	arduboy.drawFastVLine(xP1, yP1, yPL, WHITE);
	arduboy.drawFastVLine(xP1 - 1, yP1, yPL, WHITE);
	arduboy.drawFastVLine(xP2, yP2, yPL, WHITE);
	arduboy.drawFastVLine(xP2 + 1, yP2, yPL, WHITE);
}

void MovePad()
{
	if (arduboy.pressed(UP_BUTTON) && arduboy.pressed(A_BUTTON))
	{
		yP1 -= 3;
	}
	else if (arduboy.pressed(DOWN_BUTTON) && arduboy.pressed(A_BUTTON))
	{
		yP1 += 3;
	}
}

void AIPad()
{
	if (xMove < 0 && aiWin != 0 && arduboy.notPressed(A_BUTTON))
	{
		yP1 = yDir - 7;
	}
	else if (xMove < 0 && arduboy.notPressed(A_BUTTON))
	{
		yP1 = yDir + 7;
	}

	if (xMove > 0 && aiWin != 0)
	{
		yP2 = yDir - 7;
	}
	else if (xMove > 0)
	{
		yP2 = yDir + 7;
	}
}

void PadBoundary()
{
	if (yP1 <= 1)
	{
		yP1 = 1;
	}
	else if (yP1 + yPL >= HEIGHT - 1)
	{
		yP1 = HEIGHT - 1 - yPL;
	}

	if (yP2 <= 1)
	{
		yP2 = 1;
	}
	else if (yP2 + yPL >= HEIGHT - 1)
	{
		yP2 = HEIGHT - 1 - yPL;
	}
}

void ScoreDisplay()
{

	for (size_t i = 0; i < 10 - p1Score; i++)
	{
		arduboy.drawPixel(60, 57 - (i * 2), WHITE);
	}

	for (size_t i = 0; i < 10 - p2Score; i++)
	{
		arduboy.drawPixel(66, 57 - (i * 2), WHITE);
	}

	for (size_t i = 0; i < 10 - p1Wins; i++)
	{
		arduboy.drawCircle(60 - (i * 4), 60, 1, WHITE);
	}

	for (size_t i = 0; i < 10 - p2Wins; i++)
	{
		arduboy.drawCircle(66 + (i * 4), 60, 1, WHITE);
	}

	arduboy.setCursor(49, 02);
	arduboy.print(CreateDisplayText(s, m, h, false, false, true));

	if (p1Score > 10)
	{
		p1Wins++;
		p1Score = 0;
		p2Score = 0;
		xSpeed = 1;
		ySpeed = 1;
	}
	else if (p2Score > 10)
	{
		p2Wins++;
		p1Score = 0;
		p2Score = 0;
		xSpeed = 1;
		ySpeed = 1;
	}

	if (p1Wins > 10 || p2Wins > 10 || arduboy.pressed(B_BUTTON))
	{
		ResetPlay(false);
	}

}

void DrawPlayArea()
{
	arduboy.drawCircle(xDir, yDir, ballRadius, WHITE);
	arduboy.drawTriangle(xDir - 1, yDir + 1, xDir, yDir - 1, xDir + 1, yDir + 1, WHITE);


	arduboy.drawFastHLine(0, 0, WIDTH, WHITE);	// top
	arduboy.drawFastHLine(0, HEIGHT - 1, WIDTH, WHITE);	// bottom
	arduboy.drawFastVLine(0, 0, HEIGHT, WHITE);	// left
	arduboy.drawFastVLine(WIDTH - 1, 0, HEIGHT, WHITE);	// right
	arduboy.drawFastVLine(WIDTH / 2 - 1, 0, HEIGHT, WHITE); // center
	arduboy.drawCircle(-1, HEIGHT / 2 - 1, HEIGHT / 2, WHITE);
	arduboy.drawCircle(WIDTH + 1, HEIGHT / 2 - 1, HEIGHT / 2, WHITE);

}