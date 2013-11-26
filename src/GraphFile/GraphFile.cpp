/****************************************************************************************************************/
/*                                                                                                              */
/*   Morphomotion: A project researching on how morphology influences locomotion in robots.                     */
/*                                                                                                              */
/*   G N U P L O T   C L A S S                                                                                  */
/*                                                                                                              */
/*   Avinash Ranganath                                                                                          */
/*   Robotics Lab, Department of Systems Engineering and Automation                                             */
/*   University Carlos III de Mardid(UC3M)                                                                      */
/*   Madrid, Spain                                                                                              */
/*   E-mail: avinash.ranganath@uc3m.es                                                                          */
/*   http://roboticslab.uc3m.es/roboticslab/persona.php?id_pers=104                                             */
/*                                                                                                              */
/****************************************************************************************************************/


#include "GraphFile.h"

GraphFile::GraphFile()
{
  time_t rawtime;
  struct tm * timeinfo;
  char filename[100];

  time ( &rawtime );
  timeinfo = localtime ( &rawtime );
  strftime (filename, 100, "graph/%m_%d_%H_%M_plot.dat", timeinfo);
  graphFile_name = filename;
  cout <<" Opening GraphFile: " << graphFile_name << endl;
  fp.open(graphFile_name.c_str(), fstream::in | fstream::out | fstream::app);
}

GraphFile::GraphFile(const std::string& filename)
{
  graphFile_name = filename;
  fp.open(graphFile_name.c_str(), fstream::in | fstream::out | fstream::app);

  if(!fp.is_open())
  {
    std::cerr << "Morphomotion Error: GraphFile class." << std::endl
              << "GraphFile(const std::string&) Constructor." << std::endl
              << "Cannot open file:"  << filename << std::endl;
    exit(1);
  }
  else
  {
    cout <<" Opening GraphFile: " << graphFile_name << endl;
  }
}


GraphFile::GraphFile(const std::string& environmentType, const std::string& robotType, const std::string& controllerType)
{
  time_t rawtime;
  struct tm * timeinfo;
  char filename[100];
  stringstream ss;
  string file_name;

  time ( &rawtime );
  timeinfo = localtime ( &rawtime );
  strftime (filename, 100, "/FitnessGraph_Files/%m_%d_%H_%M_FitnessGraph.dat", timeinfo);
  ss << "../Evolution_Files/" << environmentType << "/" << robotType << "/" << controllerType << filename;

  graphFile_name = ss.str();
  cout <<" Opening GraphFile: " << graphFile_name << endl;
  fp.open(graphFile_name.c_str(), fstream::in | fstream::out | fstream::app);
}


GraphFile::~GraphFile()
{
  fp.close();
}

void GraphFile::write(int x, double y)
{
  cout << "Writing " << x <<":" << y  << endl;
  fp << x << " " << y << endl;
}

void GraphFile::write(double x, double y)
{
  fp << x << " " << y << endl;
}

void GraphFile::write(int x, double y, double z)
{
  cout << "Writing " << x << ":" << y << ":" << z << endl;
  fp <<x << " " << y << " " << z << endl;
}

void GraphFile::write(int w, double x, double y, double z)
{
  cout << "Writing " << w << " : " << x << " : " << y << " : " << z << endl;
  fp << w << " " << x << " " << y << " " << z << endl;
}

void GraphFile::write(std::stringstream &data)
{
  int n;
  double value;
  data >> n;

  for(int i=0; i<n; i++)
  {
    data >> value;
    fp << value << " ";
  }
  fp << endl;
}

