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

int main()
{
  std::cout << "[STARTING]" << std::endl;
  auto start = high_resolution_clock::now();
  std::cout << std::setprecision(2) << std::fixed;
  PartialDiff<double> PDE(0, M_PI);
  FunctPtr xUp = xU;
  FunctPtr xLow = xL;
  FunctPtr yUp = yU;
  FunctPtr yLow = yL;

  PDE(xUp, xLow, yUp, yLow, 60);

  auto end = high_resolution_clock::now();
  auto duration = duration_cast<seconds>(end - start);
  std::cout << "[ENDING]: " << duration.count() << std::endl;

}
