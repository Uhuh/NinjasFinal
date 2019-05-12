#include <iostream>
#include <fstream>
#include <cmath>

double func(double x, double y) { return (sin(x)*sinh(M_PI-y)+sin(y)*sinh(M_PI-x))/sinh(M_PI); }

int main(int argc, char** argv)
{
  int size = std::stoi(argv[1]);
  std::ofstream out("output2.txt");
  
  for(double y = 0; y <= M_PI; y+=M_PI/size)
  {
    for(double x = 0; x <= M_PI; x+=M_PI/size)
    {
      double d = func(x, y);
      d = (std::abs(d)<0.00000001)?0:d;
      if(x>M_PI/size*(size-1)) out << d;
      else out << d << " ";
    }
    out << std::endl;
  }
  out.close();
}