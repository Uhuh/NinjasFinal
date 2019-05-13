#include <exception>
#include <iostream>
#include "partial.h"
#include "dense.h"
#include "solver.h"

template <typename T>
PartialDiff<T>::PartialDiff(const T lower, const T upper)
{
  if(upper < lower)
  {
    throw std::out_of_range("Invalid bounds, upper is less than lower");
  }

  upperBound = upper;
  lowerBound = lower;
}

template <typename T>
vector<T> PartialDiff<T>::operator()(FunctPtr xUpper, FunctPtr xLower, 
                    FunctPtr yUpper, FunctPtr yLower, ForcedFunct Forced,
                    const int partitions, const bool choleskySolver)
{
  if(xUpper == NULL || xLower == NULL || yUpper == NULL || yLower == NULL)
  {
    std::cout << "Missing bound function" << std::endl;
    throw std::out_of_range("Someone forgot to pass a bound function tsk tsk");
  }
  if(partitions <= 0)
  {
    throw std::out_of_range("Invalid partition size given");
  }
  // (N-1)^2
  const int SIZE = (partitions-1)*(partitions-1);

  DenseMatrix<double> AMatrix(SIZE, SIZE);
  vector<Point> XVec(SIZE);
  vector<double> BVec(SIZE);
  vector<double> FVec(SIZE);

  // All the x and y shifted points. "Main" is just u(xj, yk)
  vector<Point> notMain(4);
  
  const double FRACT = static_cast<double>(upperBound - lowerBound) / partitions;

  // Make vector X
  int index = 0;
  for(int y = 1; y < partitions; y++)
  {
    for(int x = 1; x < partitions; x++)
    {
      XVec[index] = Point(x*FRACT, y*FRACT);
      index++;
    }
  }

  // Determine rows for matrix
  int row = 0;
  for(int y = 1; y < partitions; y++)
  {
    for(int x = 1; x < partitions; x++)
    {
      // Generate all the u() - 1/n [u()..... + u()] crap
      const Point mainPoint(x*FRACT, y*FRACT);
      notMain[0] = Point((x-1)*FRACT, y*FRACT);
      notMain[1] = Point((x+1)*FRACT, y*FRACT);
      notMain[2] = Point(x*FRACT, (y-1)*FRACT);
      notMain[3] = Point(x*FRACT, (y+1)*FRACT);

      // Loop over the other points from the formula and find what index they belong to.
      // -1/n[u() + .... u()] points will just be -1/partitions
      for(int i = 0; i < SIZE; i++)
      {
        if(mainPoint == XVec[i])
        {
          AMatrix[i][row] = 1;
          break;
        }
      }

      for(int i = 0; i < 4; i++)
      {
        for(int j = 0; j < SIZE; j++)
        {
          FVec[i] += (*Forced)(notMain[i].m_x, notMain[i].m_y);
          if(notMain[i] == XVec[j])
          {
            AMatrix[j][row] = -0.25;
            break;
          }
          else if(notMain[i].m_x == lowerBound)
          {
            BVec[row] += (*yLower)(notMain[i].m_y);
            break;
          }
          else if(notMain[i].m_y == lowerBound)
          {
            BVec[row] += (*xLower)(notMain[i].m_x);
            break;
          }
          else if(notMain[i].m_y == upperBound)
          {
            BVec[row] += (*xUpper)(notMain[i].m_x);
            break;
          }
          else if(notMain[i].m_x == upperBound)
          {
            BVec[row] += (*yUpper)(notMain[i].m_y);
            break;
          }
        }
      }

      row++;
    }
  }

  BVec = BVec * 0.25;
  FVec = FVec * ((partitions * partitions)/4.0);
  BVec = BVec + FVec;
  
  GaussianSolver<double> solver;

  if(choleskySolver)
  {
    return solver(AMatrix.toSym(), BVec);
  }

  return solver(AMatrix, BVec);
}
