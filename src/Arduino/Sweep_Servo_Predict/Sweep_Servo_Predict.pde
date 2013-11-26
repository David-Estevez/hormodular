#include <Hacked_servo.h>
#include <Servo.h>

#define NUMBER_OF_SERVOS 1
#define BUFFER_SIZE 250

#define SAMPLE_SIZE 11

#define SERVO_THETA_INDEX 4

Hacked_servo myservo[NUMBER_OF_SERVOS];

double theta_0[8] = {-45.033886, -45.819169, -45.812751, 0.0, -45.731538, -45.916238, -45.435066, -45.107922};
double theta_1[8] = {0.65493, 0.64441, 0.651827, 0.0, 0.661175, 0.643767, 0.660404, 0.68851};

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


void loop() // Sweep the servo, read the pot oupput and save the value throughout, then predict the angle.
{
  delay(3000);
  
  unsigned int raw_data[BUFFER_SIZE];
  //unsigned int raw_data;
  double angle;
  unsigned int i=0;
  
  //-- Init all servos to 0º
  /*for(int servo=0; servo<NUMBER_OF_SERVOS; servo++)
  {
    myservo[servo].write(0);
  }*/
  
  myservo[0].write(20);
  delay(3000);
  
  myservo[0].write(120);
  //delay(200);
  
  for(i; i<BUFFER_SIZE; i++)
  {
    /*Serial.print(i);
    Serial.print(' ');*/
    
    raw_data[i] = myservo[0].readPos_raw();
    //raw_data[i] = mode_filter();
    //angle = theta_0[SERVO_THETA_INDEX] + (theta_1[SERVO_THETA_INDEX] * raw_data);
    
    /*Serial.println(raw_data[i]);
    Serial.println(' ');*/
  }
  
  Serial.println(' ');
  Serial.println(' ');
  Serial.println("Plot data");
  Serial.println("Time Raw_Data Angle");
  Serial.println(' ');
  for(i=0; i<BUFFER_SIZE; i++)
  {
    angle = theta_0[SERVO_THETA_INDEX] + (theta_1[SERVO_THETA_INDEX] * raw_data[i]);
    Serial.print(i);
    Serial.print(' ');
    Serial.print(raw_data[i]);
    Serial.print(' ');
    Serial.print(angle);
    Serial.println(' ');
  }
  
  myservo[0].write(20);
  
  for(i=0; i<BUFFER_SIZE; i++)
  {
    raw_data[i] = mode_filter();
  }
  
  for(i=0; i<BUFFER_SIZE; i++)
  {
    angle = theta_0[SERVO_THETA_INDEX] + (theta_1[SERVO_THETA_INDEX] * raw_data[i]);
    Serial.print(i+(BUFFER_SIZE * 1));
    Serial.print(' ');
    Serial.print(raw_data[i]);
    Serial.print(' ');
    Serial.print(angle);
    Serial.println(' ');
  }
  
  myservo[0].write(120);
  
  for(i=0; i<BUFFER_SIZE; i++)
  {
    raw_data[i] = mode_filter();
  }
  
  for(i=0; i<BUFFER_SIZE; i++)
  {
    angle = theta_0[SERVO_THETA_INDEX] + (theta_1[SERVO_THETA_INDEX] * raw_data[i]);
    Serial.print(i+(BUFFER_SIZE * 2));
    Serial.print(' ');
    Serial.print(raw_data[i]);
    Serial.print(' ');
    Serial.print(angle);
    Serial.println(' ');
  }
  
  myservo[0].write(20);
  
  for(i=0; i<BUFFER_SIZE; i++)
  {
    raw_data[i] = mode_filter();
  }
  
  for(i=0; i<BUFFER_SIZE; i++)
  {
    angle = theta_0[SERVO_THETA_INDEX] + (theta_1[SERVO_THETA_INDEX] * raw_data[i]);
    Serial.print(i+(BUFFER_SIZE * 3));
    Serial.print(' ');
    Serial.print(raw_data[i]);
    Serial.print(' ');
    Serial.print(angle);
    Serial.println(' ');
  }
  
  myservo[0].write(120);
  
  for(i=0; i<BUFFER_SIZE; i++)
  {
    raw_data[i] = mode_filter();
  }
  
  for(i=0; i<BUFFER_SIZE; i++)
  {
    angle = theta_0[SERVO_THETA_INDEX] + (theta_1[SERVO_THETA_INDEX] * raw_data[i]);
    Serial.print(i+(BUFFER_SIZE * 4));
    Serial.print(' ');
    Serial.print(raw_data[i]);
    Serial.print(' ');
    Serial.print(angle);
    Serial.println(' ');
  }
  
  myservo[0].write(20);
  
  for(i=0; i<BUFFER_SIZE; i++)
  {
    raw_data[i] = mode_filter();
  }
  
  for(i=0; i<BUFFER_SIZE; i++)
  {
    angle = theta_0[SERVO_THETA_INDEX] + (theta_1[SERVO_THETA_INDEX] * raw_data[i]);
    Serial.print(i+(BUFFER_SIZE * 5));
    Serial.print(' ');
    Serial.print(raw_data[i]);
    Serial.print(' ');
    Serial.print(angle);
    Serial.println(' ');
  }
  
  /*for(i=0; i<BUFFER_SIZE; i++)
  {
    raw_data = myservo[0].readPos_raw();
    angle = theta_0[SERVO_THETA_INDEX] + (theta_1[SERVO_THETA_INDEX] * raw_data);
    //angle = -45.731538 + (0.661175 * raw_data);
  }*/
    
  while(1);
}

unsigned int mode_filter()
{
  unsigned int sample_data[SAMPLE_SIZE];
  
  bool unique_value[SAMPLE_SIZE];
  bool unique_flag;
  
  unsigned int unique_value_counter[SAMPLE_SIZE];
  unsigned int unique_value_counter_max = 0;
  
  unsigned int mode_index = 0;
  
  //-- Initialize unique_value and unique_value_counter.
  unique_value[0] = true;
  unique_value_counter[0] = 1;
  for(int n=1; n<SAMPLE_SIZE; n++)
  {
    unique_value[n] = false;
    unique_value_counter[n] = 0;
  }
  
  //-- Sample raw data continuously.
  for(int n=0; n<SAMPLE_SIZE; n++)
  {
    sample_data[n] = myservo[0].readPos_raw();
  }

  //--  Print sampled data.  
  /*for(int i=0; i<SAMPLE_SIZE; i++)
  {
    Serial.print(sample_data[i]);
    Serial.print(' ');
  }
  Serial.println(' ');
  Serial.print('+');
  Serial.print(' ');*/
  
  //-- Identify and mark unique data in the read sample data.
  for(int i=1; i<SAMPLE_SIZE; i++)
  {
    unique_flag = true;
    for(int j=i-1; j>=0; j--)
    {
      if(sample_data[i] == sample_data[j])
      {
        unique_flag = false;
        break;
      }
    }
    
    if(unique_flag)
    {
      unique_value[i] = true;
      unique_value_counter[i] = 1;
    }
  }
  
  //--  Print unique_value vector.  
  /*for(int i=0; i<SAMPLE_SIZE; i++)
  {
    Serial.print(unique_value[i]);
    Serial.print(' ');
  }
  Serial.println(' ');
  Serial.print('-');
  Serial.print(' ');*/
  
  //-- Performing statistical_mode [Counting each unique value].
  for(int i=0; i<SAMPLE_SIZE; i++)
  {
    if(unique_value[i])
    {
      for(int j=i+1; j<SAMPLE_SIZE; j++)
      {
        if(sample_data[i] == sample_data[j])
        {
          unique_value_counter[i]++;
        }
      }
    }
  }
  
  //--  Print unique_value vector.  
  /*for(int i=0; i<SAMPLE_SIZE; i++)
  {
    Serial.print(unique_value_counter[i]);
    Serial.print(' ');
  }
  Serial.print('*');
  Serial.print(' ');*/
  
  //-- Determining the value from sampled data which is the most common.
  unique_value_counter_max = unique_value_counter[0];
  for(int i=1; i<SAMPLE_SIZE; i++)
  {
    if(unique_value_counter[i] >= unique_value_counter_max)
    {
      mode_index = i;
      unique_value_counter_max = unique_value_counter[i];
    }
  }
  
  return(sample_data[mode_index]);
}
