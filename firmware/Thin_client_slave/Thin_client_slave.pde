/*
    Modular thin client - slave
    Proyect Hormodular
    Author: David Estevez Fernandez
    Licence: GPLv3 
    
*/

//-- Dependencies
#include <Servo.h>
#include <Wire.h>

//-- Definitions of configuration parameters
#define N_SERVOS 8

static const uint8_t pin_map[N_SERVOS] = { 8, 9, 10, 11, A0, A1, A2, A3 };
static const uint8_t initial_pos[N_SERVOS] = { 90, 90, 90, 90, 90, 90, 90, 90};

#define LED_PIN 13

//-- Create global objects:
#define BUFF_SIZE 16

Servo servo[N_SERVOS];
char buffer[BUFF_SIZE];

//-- Hardware setup
void setup()
{
    //-- Setup the signal LED
    pinMode( LED_PIN, OUTPUT);
    digitalWrite( LED_PIN, LOW);
    
    //-- Initialize the servos:
    for( uint8_t i = 0; i < N_SERVOS; i++)
    {
      servo[i].attach( pin_map[i] );
      servo[i].write( initial_pos[i] );
    }
    
    //-- Setup the serial port:
    Wire.begin(2);
    Wire.onReceive(commandHandler);
    
    //-- Clear the buffer:
    memset( buffer, 0, BUFF_SIZE * sizeof( char) );
}

//-- Main loop
void loop()
{
 
  
}

char readNext( )
{
  while ( Wire.available() == 0 ) {}
  
  return Wire.receive();
}

void commandHandler(int numReceived)
{
   
  //-- Read command
  char command = readNext();
  
  if ( command >= 0x50 && command <= 0x5F )
  {
    //-- Correct command
    switch ( command )
    {
      case 0x50:
        //-- Set position of all joints
        posAllJointsHandler();
        break;
                      
      case 0x51:
        //-- Set position of a single joint
        posSingleJointHandler();
        break;
                      
      case 0x5F:
        //-- Toggle LED (test command)
        toggleLEDHandler();
        break;
      }
  }  
}

void posAllJointsHandler()
{       
  //-- Joint pos to every joint
  for ( uint8_t i = 0; i < N_SERVOS; i++)
  {
    uint8_t joint_pos = readNext();
    servo[i].write( joint_pos);
  }
}
       
void posSingleJointHandler()
{
  //-- Joint pos to a single joint
  uint8_t joint_id = readNext();
  uint8_t joint_pos = readNext();
  servo[joint_id].write( joint_pos);
}

void toggleLEDHandler()
{
  digitalWrite(LED_PIN, !digitalRead(LED_PIN));
}
