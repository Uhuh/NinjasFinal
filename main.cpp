/**
  * @file   main.cpp
  * @author Dylan Warren, Section A
  * @brief  Acting as the driver to test the matrix class
*/
#include "partial.h"
#include <iostream>
#include <iomanip>
#include <cmath>

#define PI 3.141592653

double xU(double x) { return 0; }
double xL(double x) { return sin(x);}
double yU(double y) { return 0;}
double yL(double y) { return sin(y);}


int main()
{
  std::cout << std::setprecision(8) << std::fixed;
  PartialDiff solve(0, PI);
  FunctPtr xUp = xU;
  FunctPtr xLow = xL;
  FunctPtr yUp = yU;
  FunctPtr yLow = yL;
  solve.solver(xUp, xLow, yUp, yLow, 10);
}
