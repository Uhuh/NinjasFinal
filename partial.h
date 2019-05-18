/**
  * @file   partial.h
  * @author Dylan Warren, Oscar Lewzcuk, Section A
  * @brief  The partial class is a partial matrix.
*/
/**
  * @class  PartialDiff
  * @brief  PartialDiff Allows us to solve Poisson's equation
*/

#ifndef PARTIAL_H
#define PARTIAL_H

#include <iostream>
#include <cstddef>
#include "vector.h"

using FunctPtr = double(*)(double);
using ForcedFunct = double(*)(double, double);

template <class T>
class PartialDiff
{
  private:
    T upperBound;
    T lowerBound;
  public:
    /**
      * @brief   Confirms LowerTriangle row and col are proper values
                  then initialises ptr_to_vector
      * @pre     upper must be greater than lower
      * @post    Create a PDE with the bounds set
      * @param   lower - Lower bound 
      * @param   upper - Upper bound
      * @return  None
      * @throw   If upper is lower than lower
    */
    PartialDiff(const T lower, const T upper);
    /**
      * @brief   Generates the X vector for the correlating mesh interior points
      * @pre     All function pointers must be passed in.
      * @post    None
      * @param   UpperBound - This is when x is equal to the upper bound; u(UPPER, y)
      * @param   LowerBound - When x is equal to the lower bound; u(LOWER, y)
      * @param   LeftBound - When y is equal to upper bound; u(x, UPPER)
      * @param   RightBound - When y is equal to lower bound; u(x, LOWER)
      * @param   Forced - The forced function; f(x, y)
      * @param   partitions - Our N.
      * @param   choleskySolver - Determines if choleski or if Gaussian is used.
      * @return  The real x vector values
      * @throw   If none of the function ptrs are passed in.
    */
    vector<T> operator()(const FunctPtr UpperBound = NULL, const FunctPtr LowerBound = NULL, 
          const FunctPtr LeftBound = NULL, const FunctPtr RightBound = NULL,  const ForcedFunct Forced = NULL,
          const int partitions = 0, const bool choleskySolver = 1) const;

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

#include "partial.hpp"

#endif