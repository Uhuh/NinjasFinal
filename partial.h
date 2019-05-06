#ifndef PARTIAL_H
#define PARTIAL_H

#include <iostream>
#include <cstddef>

using FunctPtr = double(*)(double);

class PartialDiff
{
  private:
    double upperBound;
    double lowerBound;
  public:
    PartialDiff(const double lower, const double upper);
    void solver(FunctPtr UpperBound = NULL, FunctPtr LowerBound = NULL, 
          FunctPtr LeftBound = NULL, FunctPtr RightBound = NULL, 
          const int partitions = 0) const;

};

struct Point
{
  Point(const double x = 0, const double y = 0) : m_x(x), m_y(y) {};
  Point& operator=(const Point& p)
  {
    m_x = p.m_x;
    m_y = p.m_y;
    return *this;
  }
  bool operator==(const Point& p) const { return (m_x == p.m_x && m_y == p.m_y); }
  friend std::ostream& operator<<(std::ostream& o, const Point& p)
  {
    o << "(" << p.m_x << ", " << p.m_y << ")";
    return o;
  }
  double m_x;
  double m_y;
};

#endif