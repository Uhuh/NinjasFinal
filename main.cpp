/**
  * @file   main.cpp
  * @author Dylan Warren, Section A
  * @brief  Acting as the driver to test the matrix class
*/
#include "partial.h"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <fstream>
#include <cmath>
#include "vector.h"

using namespace std::chrono;

double xU(double x) { return 0*x; }
double xL(double x) { return sin(x);}
double yU(double y) { return 0*y;}
double yL(double y) { return sin(y);}

int main(int argc, char** argv)
{
  std::cout << std::setprecision(2) << std::fixed;
  PartialDiff<double> PDE(0, M_PI);
  FunctPtr xUp = xU;
  FunctPtr xLow = xL;
  FunctPtr yUp = yU;
  FunctPtr yLow = yL;

  if(argc < 2)
  {
    return 1;
  }

  int size = std::stoi(argv[1]);
  std::ofstream out("output.txt");

  //Gets Data to "output.txt"
  vector<double> v = PDE(xUp, xLow, yUp, yLow, size);
  for(int y = 0; y < size+1; y++)
  {
    for(int x = 0; x < size+1; x++)
    {
      if(y == 0 && x != size) out << sin(3.14159/(size)*x) << " ";
      else if(y == 0 && x == size) out << sin(3.14159/(size)*x);
      else if(x == 0) out << sin(3.14159/(size)*y) << " ";
      else if(x == size) out << 0.0;
      else if(y == size) out << 0.0 << " ";
      else out << v[(y-1)*(size-1)+(x-1)] << " ";
    }
    out << std::endl;
  }
  out.close();

  return 0;
}
