/****************************************************************************************************************/
/*                                                                                                              */
/*   Morphomotion: A project researching on how morphology influences locomotion in robots.                     */
/*                                                                                                              */
/*   G R A P H F I L  E   C L A S S   H E A D E R                                                               */
/*                                                                                                              */
/*   Avinash Ranganath                                                                                          */
/*   Robotics Lab, Department of Systems Engineering and Automation                                             */
/*   University Carlos III de Mardid(UC3M)                                                                      */
/*   Madrid, Spain                                                                                              */
/*   E-mail: avinash.ranganath@uc3m.es                                                                          */
/*   http://roboticslab.uc3m.es/roboticslab/persona.php?id_pers=104                                             */
/*                                                                                                              */
/****************************************************************************************************************/


#ifndef GRAPHFILE_H
#define GRAPHFILE_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

class GraphFile
{
  private:
    string graphFile_name;
    fstream fp;

  public:
    GraphFile();
    GraphFile(const std::string&);
    GraphFile(const std::string&, const std::string&, const std::string&);
   ~GraphFile();

    void write(int x, double y);
    void write(double x, double y);
    void write(int x, double y, double z);
    void write(int w, double x, double y, double z);
    void write(std::stringstream&);
};

#endif
