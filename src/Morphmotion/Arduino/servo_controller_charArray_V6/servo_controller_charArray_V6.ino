// Move the servo to a specified value 
// by Avinash Ranganath <nash911@gmx.com> 

/* V6 -- Inherited from V5 -- Added new message types: 3 --> Requesting time [PC to Skymega].
                                                       4 --> Message containing current time [Skymega to PC]. */

#include <stdio.h>
#include <Servo.h> 
#include <stdlib.h>
#include <math.h>

#include <Hacked_servo.h>

#define NO_OF_SERVOS 4

#define ANGLE_MAX 90.0
#define ANGLE_MIN -90.0

Hacked_servo myservo[4];

double myservo_previous_input[NO_OF_SERVOS];

/*double theta_0 = -46.301508;
double theta_1 = 0.627103;*/

/*double S1_theta_0 = -46.369200;
double S1_theta_1 = 0.623388;

double S2_theta_0 = -46.322743;
double S2_theta_1 = 0.631292;*/

double theta_0 = -45.731538;
double theta_1 = 0.661175;


void setup() 
{ 
  myservo[0].attach(8,A0); // attaches the servo object 0 to pin A0 and 8 on ports 1 and 2 respectiverly.
  myservo[1].attach(9,A1); // attaches the servo object 1 to pin A1 and 9 on ports 3 and 4 respectiverly.
  myservo[2].attach(10,A2); // attaches the servo object 1 to pin A1 and 9 on ports 3 and 4 respectiverly.
  myservo[3].attach(11,A3); // attaches the servo object 1 to pin A1 and 9 on ports 3 and 4 respectiverly.
  
  for(int servo=0; servo<NO_OF_SERVOS; servo++)
  {
    myservo_previous_input[servo] = 0;
  }
  // start serial port at 115200 bps:
  //Serial.begin(38400);
  //Serial.begin(57600);
  //Serial.begin(111111);  // Baud Rate on the rest [PC, Xbee_Source, Xbee_Dest] should be 115200 kbps. Reason explained here
  Serial.begin(115200);
} 


void loop() 
{ 
  char in_char = 'X';
  char m_type[1];
  char to[1] = {0};
  char data[4][10] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  int i=0;
  int mType_i = 0;
  int to_i = 0;
  int data_i = 0;
  int servo = 0;
  
  enum message_type{Request_Servo, Command, Request_Time};
  message_type mType = Command;
  
  bool mType_available = false;
  bool to_available = false;
  bool data_available[4] = {false, false, false, false};
  
  
  if(Serial.available())
  {
    //blink();
    in_char = Serial.read();
    if(in_char == '#')
    { 
      do
      {
        while(!Serial.available());
        
        in_char = Serial.read();
        if(in_char == '$')
        {
          break;
        }
        else if(in_char == '*')
        {
          data_i = 0;
          do
          {
            while(!Serial.available());
            
            in_char = Serial.read();
            if(in_char == '*')
            {
              break;
            }
            else if(in_char == '$')
            {
              break;
            }
            else if(in_char == '<')
            {
              data_i = 0;
              do
              {
                while(!Serial.available());
                
                in_char = Serial.read();
                if(in_char == '>')
                {
                  if(data_i > 0)
                  {
                    data_available[servo] = true;
                  }
                  else
                  {
                    data_available[servo] = false;
                  }
                  break;
                }
                else if(in_char == '$')
                {
                  break;
                }
                else
                {
                  data[servo][data_i] = in_char;
                  data_i++;
                }
              }while(in_char != '>');
              servo++;
            }
          }while(in_char != '*');
        }
        else if(in_char == '&')
        {
          to_i = 0;
          do
          {
            while(!Serial.available());
            
            in_char = Serial.read();
            if(in_char == '&')
            {
              if(to_i > 0)
              {
                to_available = true;
              }
              else
              {
                to_available = false;
              }
              break;
            }
            else if(in_char == '$')
            {
              to_available = false;
              break;
            }
            else
            {
              to[to_i] = in_char;
              to_i++;
            }
          }while(in_char != '&');
        }
        else if(in_char == '%')
        {
          mType_i = 0;
          do
          {
            while(!Serial.available());
            
            in_char = Serial.read();
            if(in_char == '%')
            {
              if(mType_i > 0)
              {
                mType_available = true;
              }
              else
              {
                mType_available = false;
              }
              break;
            }
            else if(in_char == '$')
            {
              break;
            }
            else
            {
              switch(atoi(&in_char))
              {
                case 0: {
                  mType = Command;
                  mType_i++;
                  break;
                }
                case 1: {
                  mType = Request_Servo;
                  mType_i++;
                  break;
                }
                case 3: {
                  mType = Request_Time;
                  mType_i++;
                  break;
                }
                default: {mType_i++; break;}
              }
            }
          }while(in_char != '%');
        }
      }while(in_char != '$');
    }
    else
    {
      //blink();
    }
    
    if(mType_available && to_available)  // TODO: 'To' address should not be manditory. This should be changed in Y1ModularRobot::get_current_time(void) as well.
    {
      int servo_add = 0;
      servo_add = atoi(to);
      
      if(mType == Command)
      {
        float servo_value[4]={0,0,0,0};
        for(int i=0; i<servo; i++)
        {
          servo_value[i] = atof(data[i]);
          servo_value[i] = servo_value[i] + 90; // Scaling the input of the servo back to its original range of between 0º and 179º
        }
        
        switch(servo_add)
        {
          case 0: {
            if(myservo_previous_input[0] != servo_value[0])
            {
              myservo[0].write(servo_value[0]); // sets the servo position according to the scaled value
              myservo_previous_input[0] = servo_value[0];
            }
            else
            {
              //blink_long();
            }
            break;
          }
          case 1: {
            if(myservo_previous_input[1] != servo_value[1])
            {
              myservo[1].write(servo_value[1]); // sets the servo position according to the scaled value
              myservo_previous_input[1] = servo_value[1];
            }
            break;
          }
          case 2: {
            if(myservo_previous_input[2] != servo_value[2])
            {
              myservo[2].write(servo_value[2]); // sets the servo position according to the scaled value
              myservo_previous_input[2] = servo_value[2];
            }
            break;
          }
          case 3: {
            if(myservo_previous_input[3] != servo_value[3])
            {
              myservo[3].write(servo_value[3]); // sets the servo position according to the scaled value
              myservo_previous_input[3] = servo_value[3];
            }
            break;
          }
          case 4: {
            for(int i=0; i<servo; i++)
            {
              if(myservo_previous_input[i] != servo_value[i])
              {
                myservo[i].write(servo_value[i]); // sets the servo position according to the scaled value
                myservo_previous_input[i] = servo_value[i];
              }
            }
            break;
          }
          default: {
//---------------------------Debugger---------------------------//
            blink();
            String outString;
            unsigned char outBuf[100];
            outString = outString + servo_add;
            StringToCharArray(outString, outBuf);
            Serial.write(outBuf, servo_add);
            break;
//---------------------------Debugger---------------------------//
            break;
          }
        }
      }
      
      else if(mType == Request_Servo)
      {
        String outString;
        unsigned char outBuf[100];
        
        switch(servo_add)
        {
          case 0: {
            outString = OutputStringStream(servo_add, myservo[0].readPos_raw());
            StringToCharArray(outString, outBuf);
            Serial.write(outBuf, outString.length());
            break;
          }
          case 1: {
            outString = OutputStringStream(servo_add, myservo[1].readPos_raw());
            StringToCharArray(outString, outBuf);
            Serial.write(outBuf, outString.length());
            break;
          }
          case 2: {
            outString = OutputStringStream(servo_add, myservo[2].readPos_raw());
            StringToCharArray(outString, outBuf);
            Serial.write(outBuf, outString.length());
            break;
          }
          case 3: {
            outString = OutputStringStream(servo_add, myservo[3].readPos_raw());
            StringToCharArray(outString, outBuf);
            Serial.write(outBuf, outString.length());
            break;
          }
          case 4: {
            int n = OutputStringStream_All(servo_add,outBuf);
            Serial.write(outBuf, n);
            break;
          }
          default: {
//---------------------------Debugger---------------------------//
            blink();
            String outString;
            unsigned char outBuf[100];
            outString = outString + servo_add;
            StringToCharArray(outString, outBuf);
            Serial.write(outBuf, servo_add);
            break;
//---------------------------Debugger---------------------------//
            break;
          }
        }
      }
      
      else if(mType == Request_Time)
      {
        String outString;
        unsigned char outBuf[100];
        
        int n = OutputStringStream_Time(outBuf);
        Serial.write(outBuf, n);
      } 
    }
  }  

}


String OutputStringStream(int from, double rawData)
{
  String serialOut;
  int base10Exp = 2;
  
  double S1_theta_0 = -46.369200;
  double S1_theta_1 = 0.623388;

  double S2_theta_0 = -46.322743;
  double S2_theta_1 = 0.631292;
  
  double predictedAngle;
  
  if(from==0)
  {
    predictedAngle = (S1_theta_0 + (rawData * S1_theta_1)) - 90;
  }
  else if(from==1)
  {
    predictedAngle = (S2_theta_0 + (rawData * S2_theta_1)) - 90;
  }
  else
  {
    predictedAngle = (theta_0 + (rawData * theta_1)) - 90;
  }
  
  long longData = predictedAngle * pow(10, base10Exp);

  serialOut = serialOut + "#";
  serialOut = serialOut + "%" + "2" + "%";
  serialOut = serialOut + "&" + from + "&";
  serialOut = serialOut + "*<" + longData + "/" + base10Exp + ">*";
  serialOut = serialOut + "$";

  return serialOut;
}


int OutputStringStream_All(int from, unsigned char* charBuf)
{
  String fromString;
  String timeString;
  int base10Exp = 2;  // TODO: This parameter can be fixed both here and the PC code, and the message frame can be reduced by 8 bytes.
  unsigned int charBufLength = 0;
  unsigned long time=0;
  double rawData[NO_OF_SERVOS];
  double predictedAngle = 0;
  unsigned int n, i;
  
  /*double S0_theta_0 = -46.494264;
  double S0_theta_1 = 0.624130;

  double S1_theta_0 = -46.373543;
  double S1_theta_1 = 0.631597;*/
  
  charBuf[charBufLength++] = '#';
  
  charBuf[charBufLength++] = '%';
  charBuf[charBufLength++] = '2'; // Message Type 2 --> Send Servo with Time
  charBuf[charBufLength++] = '%';
  
  charBuf[charBufLength++] = '&';
  fromString = fromString + from;
  for(i=0;i<fromString.length();i++)
  {
    charBuf[charBufLength++] = fromString[i];
  }
  charBuf[charBufLength++] = '&';
  
  //-- Read Time (Milliseconds).
  time = micros();
  
  //-- Read Servo positions.
  for(n=0; n<NO_OF_SERVOS; n++)
  {
    rawData[n] = myservo[n].readPos_raw();
  }

//----------------TIME-(MILLISECONDS)-RELATED----------------//
  charBuf[charBufLength++] = '[';
  //time = micros(); // This have been moved up.
  timeString = timeString + time;
  for(i=0; i<timeString.length(); i++)
  {
    charBuf[charBufLength++] = timeString[i];
  }
  charBuf[charBufLength++] = ']';
//----------------TIME-(MILLISECONDS)-RELATED----------------//
  
  charBuf[charBufLength++] = '*';
  for(unsigned int n=0;n<4;n++)
  {
    charBuf[charBufLength++] = '<';
        
    predictedAngle = (theta_0 + (rawData[n] * theta_1)) - 90; // TODO: This is the correct code, and must be uncommented.
    
    if(predictedAngle > ANGLE_MAX)
    {
      predictedAngle = ANGLE_MAX;
    }
    else if(predictedAngle < ANGLE_MIN)
    {
      predictedAngle = ANGLE_MIN;
    }
    
    long longServoData = predictedAngle * pow(10, base10Exp);
    
    String dataString;
    dataString = dataString + longServoData + '/' + base10Exp;
    for(i=0;i<dataString.length();i++)
    {
      charBuf[charBufLength++] = dataString[i];
    }
   
    charBuf[charBufLength++] = '>';
  }
  charBuf[charBufLength++] = '*';
  
  charBuf[charBufLength++] = '$';

  return charBufLength;
}


int OutputStringStream_Time(unsigned char* charBuf)
{
  String timeString;
  unsigned int charBufLength = 0;
  unsigned long time=0;
  unsigned int i;
    
  charBuf[charBufLength++] = '#';
  
  charBuf[charBufLength++] = '%';
  charBuf[charBufLength++] = '4'; // Message Type 4 --> Send Time
  charBuf[charBufLength++] = '%';
    
  //-- Read Time (Milliseconds).
  time = micros();

//----------------TIME-(MILLISECONDS)-RELATED----------------//
  charBuf[charBufLength++] = '[';
  timeString = timeString + time;
  for(i=0; i<timeString.length(); i++)
  {
    charBuf[charBufLength++] = timeString[i];
  }
  charBuf[charBufLength++] = ']';
//----------------TIME-(MILLISECONDS)-RELATED----------------//
    
  charBuf[charBufLength++] = '$';

  return charBufLength;
}


void StringToCharArray(String sourceString, unsigned char* charBuf)
{
  for(int i=0; i<sourceString.length(); i++)
  {
    charBuf[i] = sourceString[i];
  }
}


void blink() {
  for(int i=0; i<2; i++)
  {
    digitalWrite(13, HIGH);   // set the LED on
    delay(10);              // wait for a second
    digitalWrite(13, LOW);    // set the LED off
    delay(10);    // wait for a second
  }
  //digitalWrite(13, HIGH);
}


void blink_long() {
  for(int i=0; i<10; i++)
  {
    digitalWrite(13, HIGH);   // set the LED on
    delay(50);              // wait for a second
    digitalWrite(13, LOW);    // set the LED off
    delay(50);    // wait for a second
  }
  digitalWrite(13, HIGH);
}
