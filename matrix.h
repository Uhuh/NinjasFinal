/**
  * @file   matrix.h
  * @author Dylan Warren, Section A
  * @brief  The matrix class is a very basic abstract class.
*/
/**
  * @class  matrix
  * @brief  An abstract class for a matrix.
*/
#ifndef MATRIX_H
#define MATRIX_H
#include <memory>
#include "./vector.h"

template<class ChildClass, typename ChildType>
class matrix
{
  public:
    /**
       * A pure virtual member.
       * @param source - Value to store into C.O
       * @return New object of ChildClass type
    */
    virtual ChildClass& operator=(const ChildClass& source) = 0;
    /**
       * A pure virtual member.
       * @param   row - Row in matrix
       * @param   col - Col in matrix
       * @return  Value at row, col 
    */
    virtual ChildType operator()(const int row, const int col) const = 0;
    /**
      * A pure virtual member
      * @return  The row size of the matrix
    */
    virtual int getRow() const = 0;
    /**
      * A pure virtual member
      * @return  The col size of the matrix
    */
    virtual int getCol() const = 0;
};

#endif