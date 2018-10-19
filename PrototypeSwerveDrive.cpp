/*
 * PrototypeSwerveDrive.cpp
 * Created: 16-10-2018 18:48:07
 * Updated: 16-10-18 19:59	
 * //TODO:	1. Include servo.h
			2. Attach 2 servos on same pin
			3. Control angle using Android App
 */ 
/*************INDEX******************
*BUG – a known bug that should be corrected.
*FIXME – should be corrected.
*HACK – a workaround.
*TODO – something to be done.
*UNDONE – a reversal or "roll back" of previous code.
*XXX – warn other programmers of problematic or misguiding code
*/




#define F_CPU 1000000UL
#include <m2560/io.h>
#include <m2560/Servo.h>
//#include <ModularLibrary/Cytron.h>
Servo swerve1;
/*#include <avr/io.h>
#include <math.h>
#include <stdlib.h>
#include <util/delay.h>*/
int angle[4]={180,135,135,135};
	
void setup(){
int x;	
DDRB=0xff;
Serial.begin(4800);
swerve1.attach(11);
swerve2.attatch(12);
}
void loop()
{
	swerve2.write(angle[1]);
	swerve1.write(angle[0])
	}