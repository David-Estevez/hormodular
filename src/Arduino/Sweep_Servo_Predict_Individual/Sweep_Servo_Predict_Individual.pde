#include <Hacked_servo.h>
#include <Servo.h>

#define NUMBER_OF_SERVOS 1
#define SWEEP_RANGE_MIN 0
#define SWEEP_RANGE_MAX 180

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
  
  //unsigned int raw_data[SWEEP_RANGE_MAX];
  unsigned int raw_data;
  double angle;
  unsigned int i=0;
  int predicted_angle = 0;
  
  
  myservo[0].write(0);
  delay(3000);

  
  for(i=0, angle=0; angle<SWEEP_RANGE_MAX; i++, angle++)
  {
    raw_data = myservo[0].readPos_raw();
    delay(300);
    myservo[0].write(angle);
        
    predicted_angle = theta_0[SERVO_THETA_INDEX] + (theta_1[SERVO_THETA_INDEX] * raw_data);
    Serial.print(i);
    Serial.print(' ');
    Serial.print(angle);
    Serial.print(' ');
    Serial.print(predicted_angle);
    Serial.println(' ');
  }
  
  myservo[0].write(180);
  delay(1000);
  
  for(i, angle=180; angle>=SWEEP_RANGE_MIN; i++, angle--)
  {
    raw_data = myservo[0].readPos_raw();
    delay(300);
    myservo[0].write(angle);
        
    predicted_angle = theta_0[SERVO_THETA_INDEX] + (theta_1[SERVO_THETA_INDEX] * raw_data);
    Serial.print(i);
    Serial.print(' ');
    Serial.print(angle);
    Serial.print(' ');
    Serial.print(predicted_angle);
    Serial.println(' ');
  }
        
  while(1);
}
