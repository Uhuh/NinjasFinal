/**
  * @file   diagonal.h
  * @author Dylan Warren, Section A
  * @brief  The Diag class is a Diag matrix. It is row * col size matrix.
*/
/**
  * @class  DiagMatrix
  * @brief  DiagMatrix Allows us to do add/sub/mult of DiagMatrix
*/

#ifndef DIAGONAL_H
#define DIAGONAL_H

#include "./matrix.h"

template<class T>
class DiagMatrix : public matrix<DiagMatrix<T>, T>
{
  private:
    int m_rows;
    int m_cols;
    vector<vector<T>> ptr_to_data;
    const vector<T>& operator[](const int index) const;
  public:
    /**
      * @brief   Sets row and col to 0 and sets our point to nullptr
      * @pre     None
      * @post    All member variables are set.
      * @return  None
    */
    DiagMatrix() : m_rows(0), m_cols(0), ptr_to_data(vector<vector<T>>()) {};
    /**
      * @brief   Confirms DiagMatrix row and col are proper values
                  then initialises ptr_to_vector
      * @pre     rows and cols must be greater than zero
      * @post    Creates a fresh DiagMatrix of size rows and cols
      * @param   r - How tall the DiagMatrix should be
      * @param   c - How many vectors wide it should be
      * @return  None
      * @throw   If r or r is 0 or less
    */
    DiagMatrix(const int r, const int c);
    /**
      * @brief   Sets ptr_to_vector equal to other after seting row and col
      * @pre     None
      * @post    Moves other's data into C.O
      * @param   other - DiagMatrix to move
      * @return  None
    */
    DiagMatrix(DiagMatrix&& other) = default;
    /**
      * @brief   Sets ptr_to_vector equal to sources after seting row and col
      * @pre     None
      * @post    Creates a new Diag object that is identical to source
      * @param   source - Diag to copy
      * @return  None
    */
    DiagMatrix(const DiagMatrix& source) = default;
    /**
      * @brief   Move content from other into the calling object
      * @pre     None
      * @post    The C.O is identical to the source
      * @param   other - the DiagMatrix to move
      * @return  *this as the C.O is being altered
    */
    DiagMatrix& operator=(DiagMatrix&& other) = default;
    /**
      * @brief   Copies content from rhs into the calling object
      * @pre     None
      * @post    The C.O is identical to the source
      * @param   source - The DiagMatrix to copy
      * @return  *this as the C.O is being altered
    */
    DiagMatrix& operator=(const DiagMatrix& source) = default;
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
      * @brief   Gets the DiagMatrix row size
      * @pre     None
      * @post    None
      * @return  m_rows
    */
    int getRow() const { return m_rows; }
    /**
      * @brief   Gets the DiagMatrix col size
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
  * @return  New DiagMatrix that is lhs and rhs added together
  * @throw   If matrices are not same dimensions
*/
template<typename T>
DiagMatrix<T> operator+(const DiagMatrix<T>& lhs,
                        const DiagMatrix<T>& rhs);

/**
  * @brief   Subtract two matrices
  * @pre     None
  * @post    None
  * @param   lhs - Matrix left of -
  * @param   rhs - Matrix right of -
  * @return  New DiagMatrix that is rhs subtracted from lhs
  * @throw   If matrices are not same dimensions
*/
template<typename T>
DiagMatrix<T> operator-(const DiagMatrix<T>& lhs,
                        const DiagMatrix<T>& rhs);

/**
  * @brief   Multiply two matrices together
  * @pre     None
  * @post    None
  * @param   lhs - Matrix left of *
  * @param   rhs - Matrix right of *
  * @return  New DiagMatrix that is lhs times rhs
  * @throw   If matrices are not same dimensions
*/
template<typename T>
DiagMatrix<T> operator*(const DiagMatrix<T>& lhs,
                        const DiagMatrix<T>& rhs);

#include "./diagonal.hpp"

#endif