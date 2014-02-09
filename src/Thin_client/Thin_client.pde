/*
    Modular thin client
    Proyect Hormodular
    Author: David Estevez Fernandez
    Licence: GPLv3 
    
*/

//-- Dependencies
#include <Servo.h>

//-- Definitions of configuration parameters
#define N_SERVOS 8
#define BAUD_RATE 9600

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
    Serial.begin( BAUD_RATE );
    Serial.flush();
    Serial.println( "[Debug] Ok!");
    
    //-- Clear the buffer:
    memset( buffer, 0, BUFF_SIZE * sizeof( char) );
}

//-- Main loop
void loop()
{
  
  //-- Wait for input
  if ( Serial.available() > 0 )
  {
    //-- Read into the buffer
    uint8_t i = 0;
    while ( Serial.available() > 0 || i > BUFF_SIZE )
    {
      buffer[i] = Serial.read();
      i++;  
    }
    
    for ( int j = 0; j < i; j++)
      Serial.print( *(buffer+j) );
    Serial.print('\n');
    
    //-- Look for the start packet 0101 0000 -> 0x50 to 0101 1111 -> 0x5F
    uint8_t command_start = 0;
    uint8_t command_found = 0;
    while( ! command_found && command_start < BUFF_SIZE)
    {
      if ( *(buffer+command_start) >= 0x50 && *(buffer+command_start) <= 0x5F )
      {
        command_found = 1;
      }
    }
    
    //-- Interpret the command:
    switch ( *(buffer+command_start))
    {
      case 0x50:
      {
          //-- Joint pos to every joint
          for ( uint8_t i = 0; i < N_SERVOS; i++)
          {
            uint8_t joint_pos = *(buffer+i+1);
            servo[i].write( joint_pos);
          }
      }   
          break;
          
      case 0x51:
      {
          //-- Joint pos to a single joint
          uint8_t joint_id = *(buffer+1);
          uint8_t joint_pos = *(buffer+2);
          servo[joint_id].write( joint_pos);
      }
          break;
          
      case 0x5F:
          //-- Toggle LED (test command)
          digitalWrite(LED_PIN, !digitalRead(LED_PIN));
          break;
    }
    
    memset( buffer, 0, BUFF_SIZE * sizeof( char) );
    Serial.flush();
    Serial.println("Ok!");
  }  
  
}

char readNext( )
{
  while ( Serial.available() == 0 ) {}
  
  return Serial.read();
}

