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

double xU(double y) { return y*0.0; }
double xL(double y) { return sin(y); }
double yU(double x) { return x*0.0; }
double yL(double x) { return sin(x); }

int main(int argc, char** argv)
{
  double lowerb = 0;
  double upperb = M_PI;
  std::cout << std::setprecision(2) << std::fixed;
  PartialDiff<double> PDE(lowerb, upperb);
  FunctPtr xUp = xU;
  FunctPtr xLow = xL;
  FunctPtr yUp = yU;
  FunctPtr yLow = yL;

  if(argc < 2)
  {
    return 1;
  }

  int size = std::stoi(argv[1]);
  bool cholesky = std::stoi(argv[2]);
  std::ofstream out("output.txt");

  //Gets Data to "output.txt"
  vector<double> v = PDE(xUp, xLow, yUp, yLow, size, cholesky);
  
  for(int y = 0; y < size+1; y++)
  {
    for(int x = 0; x < size+1; x++)
    {
      if(y == 0 && x != size) out << xL(upperb/(size)*x) << " ";
      else if(y == 0 && x == size) out << xL(upperb/(size)*x);
      else if(x == 0) out << xL(upperb/(size)*y) << " ";
      else if(x == size) out << xU(lowerb/(size)*y);
      else if(y == size) out << yU(lowerb/(size)*x) << " ";
      else out << v[(y-1)*(size-1)+(x-1)] << " ";
    }
    out << std::endl;
  }
  out.close();

  return 0;
}
