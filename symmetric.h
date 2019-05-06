/**
  * @file   symmetric.h
  * @author Dylan Warren, Section A
  * @brief  The Sym class is a Sym matrix. It is row * col size matrix.
*/
/**
  * @class  SymMatrix
  * @brief  SymMatrix Allows us to do add/sub/mult of SymMatrix
*/

#ifndef SYMMETRIC_H
#define SYMMETRIC_H

#include "./upper.h"

template<typename T>
class SymMatrix : public matrix<SymMatrix<T>, T>
{
  private:
    int m_rows;
    int m_cols;
    vector<vector<T>> ptr_to_data;
  public:
    /**
      * @brief   Sets row and col to 0 and sets our point to nullptr
      * @pre     None
      * @post    All member variables are set.
      * @return  None
    */
    SymMatrix() : m_rows(0), m_cols(0), ptr_to_data(vector<vector<T>>()) {};
    /**
      * @brief   Confirms SymMatrix row and col are proper values
                  then initialises ptr_to_vector
      * @pre     rows and cols must be greater than zero
      * @post    Creates a fresh SymMatrix of size rows and cols
      * @param   r - How tall the SymMatrix should be
      * @param   c - How many vectors wide it should be
      * @return  None
      * @throw   If r or r is 0 or less
    */
    SymMatrix(const int r, const int c);
    /**
      * @brief   Sets ptr_to_vector equal to other after seting row and col
      * @pre     None
      * @post    Moves other's data into C.O
      * @param   other - SymMatrix to move
      * @return  None
    */
    SymMatrix(SymMatrix&& other) = default;
    /**
      * @brief   Sets ptr_to_vector equal to sources after seting row and col
      * @pre     None
      * @post    Creates a new SymMatrix object that is identical to source
      * @param   source - SymMatrix to copy
      * @return  None
    */
    SymMatrix(const SymMatrix& source) = default;
    /**
      * @brief   Move content from other into the calling object
      * @pre     None
      * @post    The C.O is identical to the source
      * @param   other - the SymMatrix to move
      * @return  *this as the C.O is being altered
    */
    SymMatrix& operator=(SymMatrix&& other) = default;
    /**
      * @brief   Copies content from rhs into the calling object
      * @pre     None
      * @post    The C.O is identical to the source
      * @param   source - The SymMatrix to copy
      * @return  *this as the C.O is being altered
    */
    SymMatrix& operator=(const SymMatrix& source) = default;
    /**
      * @brief   Allows access to matrix elements.
      * @pre     col and row must be within bounds 
      * @post    None
      * @param   col - column of the matrix
      * @param   row - row of the matrix
      * @return  Value from the vector at index col
      * @throw   IF col or row are out of bounds
    */
    T operator()(const int col, const int row) const;
    /**
      * @brief   Allows access to matrix elements.
      * @pre     col and row must be within bounds 
      * @post    Allows the index to be changed
      * @param   col - column of the matrix
      * @param   row - row of the matrix
      * @return  Reference of the vector at index col
      * @throw   If col or row are out of bounds
    */
    T& operator()(const int col, const int row);
    /**
      * @brief   Gets the SymMatrix row size
      * @pre     None
      * @post    None
      * @return  m_rows
    */
    int getRow() const { return m_rows; }
    /**
      * @brief   Gets the SymMatrix col size
      * @pre     None
      * @post    None
      * @return  m_cols
    */
    int getCol() const { return m_cols; }
};

/**
  * @brief   Add two matrices together
  * @pre     None
  * @post    None
  * @param   lhs - Matrix left of +
  * @param   rhs - Martix right of +
  * @return  New SymMatrix that is lhs and rhs added together
  * @throw   If matrices are not same dimensions
*/
template<typename T>
SymMatrix<T> operator+(const SymMatrix<T>& lhs, const SymMatrix<T>& rhs);

/**
  * @brief   Subtract two matrices
  * @pre     None
  * @post    None
  * @param   lhs - Matrix left of -
  * @param   rhs - Matrix right of -
  * @return  New SymMatrix that is rhs subtracted from lhs
  * @throw   If matrices are not same dimensions
*/
template<typename T>
SymMatrix<T> operator-(const SymMatrix<T>& lhs, const SymMatrix<T>& rhs);

/**
  * @brief   Multiply two matrices together
  * @pre     None
  * @post    None
  * @param   lhs - Matrix left of *
  * @param   rhs - Matrix right of *
  * @return  New SymMatrix that is lhs times rhs
  * @throw   If matrices are not same dimensions
*/
template<typename T>
SymMatrix<T> operator*(const SymMatrix<T>& lhs, const SymMatrix<T>& rhs);

/**
  * @brief   Multiply a SymMatrix by a vector
  * @pre     Vector size must match SymMatrix cols
  * @post    None
  * @param   rhs - vector to multiply by 
  * @param   lhs - The SymMatrix to multiply
  * @return  New vector
  * @throw   If vector size doesn't match SymMatrix m_cols
*/
template<typename T>
vector<T> operator*(const SymMatrix<T>& lhs, const vector<T>& rhs);

#include "./symmetric.hpp"

#endif