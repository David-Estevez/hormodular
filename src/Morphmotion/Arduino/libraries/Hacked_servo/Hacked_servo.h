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

#ifndef Hacked_servo_h
#define Hacked_servo_h

#include <Servo.h>
#include "Arduino.h"

class Hacked_servo
{
	public:
	
	//- Constructor
	Hacked_servo();
	
	//- Standard Servo library functions:
	void write(int value);
	void writeMicroseconds(int ms);

	int read();
		    
	bool attached();
	void detach();

	//- New functions:
	void attach( int pin_servo, int pin_analog);
	int readPos();
	double readPos_raw(); //Returns the value of the potenciometer
	
	private:
	int _pin_servo;
	int _pin_analog;
	
	Servo servo;

};

#endif
