/**
  * @file   main.cpp
  * @author Dylan Warren, Section A
  * @brief  Acting as the driver to test the matrix class
*/
#include "partial.h"
#include <iostream>
#include <chrono> 
#include <iomanip>
#include <cmath>

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

  PDE(xUp, xLow, yUp, yLow, std::stoi(argv[1]));

  return 0;
}
