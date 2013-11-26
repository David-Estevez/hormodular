/****************************************************************************************************************/
/*                                                                                                              */
/*   Morphomotion: A project researching on how morphology influences locomotion in robots.                     */
/*                                                                                                              */
/*   S E R I A L   C O M M U N I C A T I O N   E V A L U A T O R                                                                */
/*                                                                                                              */
/*   Avinash Ranganath                                                                                          */
/*   Robotics Lab, Department of Systems Engineering and Automation                                             */
/*   University Carlos III de Mardid(UC3M)                                                                      */
/*   Madrid, Spain                                                                                              */
/*   E-mail: avinash.ranganath@uc3m.es                                                                          */
/*   http://roboticslab.uc3m.es/roboticslab/persona.php?id_pers=104                                             */
/*                                                                                                              */
/****************************************************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <vector>


#include "SerialCommunication.h"

#define BAUD_RATE 115200

//#define MAX_POLL_TRIALS 10  //-- For Wired-Communication between PC and Skymega
#define MAX_POLL_TRIALS 20  //-- For XBEE-Communication between PC and Skymega

unsigned int set_serial_port(const std::string& new_serial_port, int baud_rate)
{
  unsigned int serial_port=0;

  if(new_serial_port == "/dev/ttyUSB0")
  {
    serial_port = 16;
    if(OpenComport(serial_port, baud_rate))
    {
      serial_port = 0;
      exit(1);
    }
  }
  else if(new_serial_port == "/dev/ttyUSB1")
  {
    serial_port = 17;
    if(OpenComport(serial_port, baud_rate))
    {
      serial_port = 0;
      exit(1);
    }
  }
  else if(new_serial_port == "/dev/ttyUSB2")
  {
    serial_port = 18;
    if(OpenComport(serial_port, baud_rate))
    {
      serial_port = 0;
      exit(1);
    }
  }
  else if(new_serial_port == "/dev/ttyUSB3")
  {
    serial_port = 19;
    if(OpenComport(serial_port, baud_rate))
    {
      serial_port = 0;
      exit(1);
    }
  }
  else
  {
    std::cout << "Unknown Serial Port: " << new_serial_port << "." <<std::endl;

    exit(1);
  }

  return serial_port;
}

int main(int argc, char* argv[])
{
  int poll_counter = 0, n, comm_id = 0;
  unsigned int i=0;
  bool foundEndBit = false;

  unsigned int serial_port=0;

  serial_port = set_serial_port(argv[1], BAUD_RATE);

  if(serial_port == 0)
  {
    printf("Can not open comport\n");

    return(0);
  }

  usleep(2000000);
  printf("Serial port open and initialised!\n");

  while(i < 1000000)
  {
    //flush_cport(serial_port, 1);
    unsigned char outBuf[20] = {'#','%','1','%','&','4','&','*','4','5','.','0','*','$'};  // To request current servo position of all modules [PC to Skymega].
    cprintf(serial_port, (char *)outBuf); // Send message requesting currnt servo position of all modules to Skymega.

    poll_counter=0;
    unsigned char message[50];
    unsigned int message_size=0;

    do
    {
      foundEndBit = false;
      unsigned char inBuf[70] = {'x','x','x','x','x','x','x','x','x','x',
                                 'x','x','x','x','x','x','x','x','x','x',
                                 'x','x','x','x','x','x','x','x','x','x',
                                 'x','x','x','x','x','x','x','x','x','x',
                                 'x','x','x','x','x','x','x','x','x','x',
                                 'x','x','x','x','x','x','x','x','x','x',
                                 'x','x','x','x','x','x','x','x','x','x'};

      n = PollComport(serial_port, inBuf, 4095);
      inBuf[n] = '\0'; // always put a "null" at the end of a string!

      for(unsigned int j=0; j<n; j++)
      {
        message[message_size++] = inBuf[j];
      }

      //std::cout << "n = " << n << " --> " << inBuf << std::endl;

      if(inBuf[n-1] == '$')
      {
        foundEndBit = true;
      }
      poll_counter++;
    //}while(foundEndBit != true);
    }while(foundEndBit != true && poll_counter <= MAX_POLL_TRIALS);

    message[message_size] = '\0'; // always put a "null" at the end of a string!

    //std::cout << std::endl << std::endl << "Poll Counter = " << poll_counter << " --> " << message << std::endl << std::endl << std::endl;
    std::cout << "Message " << i << " --> Poll Counter = " << poll_counter << " --> " << message << std::endl;
    //std::cout << std::endl << message << std::endl << std::endl;

    i++;
  }

  return 1;
}
