#include <Hacked_servo.h>
#include <Servo.h>

#define NUMBER_OF_SERVOS 3
#define SAMPLE_SIZE 4

Hacked_servo myservo[NUMBER_OF_SERVOS];

void setup() 
{ 
  if(NUMBER_OF_SERVOS >= 1)
  {
    myservo[0].attach(8,A0); // attaches the servo object 0 to pin A0 and 8 on ports 1 and 2 respectiverly.
  }
  
  if(NUMBER_OF_SERVOS >= 2)
  {
    myservo[1].attach(9,A1); // attaches the servo object 1 to pin A1 and 9 on ports 3 and 4 respectiverly.
  }
  
  if(NUMBER_OF_SERVOS >= 3)
  {
    myservo[2].attach(10,A2); // attaches the servo object 1 to pin A1 and 9 on ports 3 and 4 respectiverly.
  }
  
  if(NUMBER_OF_SERVOS >= 4)
  {
    myservo[3].attach(11,A3); // attaches the servo object 1 to pin A1 and 9 on ports 3 and 4 respectiverly.
  }
  
  Serial.begin(115200);
}


void loop() // Sweep the servo and read the pot oupput throughout.
{
  delay(3000);
  
  int angle=0;
  double raw_data[NUMBER_OF_SERVOS];
  
  //-- Init all servos to 0º
  for(int servo=0; servo<NUMBER_OF_SERVOS; servo++)
  {
    myservo[servo].write(0);
  }
  delay(3000);
  
  Serial.println("Angle Servo-1 Servo-2 Servo-5");
  //Serial.println("Angle Servo-1");
  Serial.println(' ');
  
  for(unsigned int itr=0; itr<SAMPLE_SIZE; itr++)
  {
    for(angle=0; angle<=180; angle++)
    {
      Serial.print(angle);
      Serial.print(' ');
      for(int servo=0; servo<NUMBER_OF_SERVOS; servo++)
      {
        myservo[servo].write(angle);
        delay(200);
        raw_data[servo] = myservo[servo].readPos_raw();
        Serial.print(raw_data[servo]);
        Serial.print(' ');
      }
      Serial.println(' ');
    }
  
    for(angle=180; angle>=0; angle--)
    {
      Serial.print(angle);
      Serial.print(' ');
      for(int servo=0; servo<NUMBER_OF_SERVOS; servo++)
      {
        myservo[servo].write(angle);
        delay(200);
        raw_data[servo] = myservo[servo].readPos_raw();
        Serial.print(raw_data[servo]);
        Serial.print(' ');
      }
      Serial.println(' ');
    }
    
    Serial.println(' ');
    Serial.println(' ');
  }
  
  while(1);
}
