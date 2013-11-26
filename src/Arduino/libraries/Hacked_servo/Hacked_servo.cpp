//--------------------------------------------------
//- Hacked_servo.h
//-                        Library for hacked servo
//--------------------------------------------------
//- This library is almost identical to the Servo 
//- library of Arduino, but adds extra funcionalities
//- for reading the actual position of the servo.
//--------------------------------------------------
//- Author: David Estévez
//- GPL license
//--------------------------------------------------


#include <Hacked_servo.h>
#include <Servo.h>
#include "Arduino.h"

//- Constructor

Hacked_servo::Hacked_servo()
{
	_pin_servo = -1;
	_pin_analog = -1;
}

//- Standard Servo library functions:

void Hacked_servo::write( int value) { servo.write(value); }
void Hacked_servo::writeMicroseconds(int ms) { servo.write(ms); }

int Hacked_servo::read() { return servo.read(); }

bool Hacked_servo::attached() { return servo.attached(); }
void Hacked_servo::detach() { if (_pin_servo != -1) servo.detach(); }

//- New functions

//Attachs a servo to pin_servo, sets pin_analog as analog input
void Hacked_servo::attach( int pin_servo, int pin_analog)
{
	_pin_servo = pin_servo;
	_pin_analog  = pin_analog;

	servo.attach(pin_servo);
}

int  Hacked_servo::readPos()   //Calculates and returns the actual angular position
{
	float value = analogRead( _pin_analog);
	int angle = map(value, 85, 450, 0, 180);
        return angle;
}

double Hacked_servo::readPos_raw()  //Returns the value of the potenciometer
{
	return analogRead( _pin_analog);
}

