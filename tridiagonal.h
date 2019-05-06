/**
  * @file   tridiagonal.h
  * @author Dylan Warren, Section A
  * @brief  The Tri class is a Tri matrix. It is row * col size matrix.
*/
/**
  * @class  TriDiag
  * @brief  TriDiag Allows us to do add/sub/mult of TriDiag
*/

#ifndef TRIDIAGONAL_H
#define TRIDIAGONAL_H

#include "./matrix.h"

template<class T>
class TriDiag : public matrix<TriDiag<T>, T>
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
    TriDiag() : m_rows(0), m_cols(0), ptr_to_data(vector<vector<T>>()) {};
    /**
      * @brief   Confirms TriDiag row and col are proper values
                  then initialises ptr_to_vector
      * @pre     rows and cols must be greater than zero
      * @post    Creates a fresh TriDiag of size rows and cols
      * @param   r - How tall the TriDiag should be
      * @param   c - How many vectors wide it should be
      * @return  None
      * @throw   If r or r is 0 or less
    */
    TriDiag(const int r, const int c);
    /**
      * @brief   Sets ptr_to_vector equal to other after seting row and col
      * @pre     None
      * @post    Moves other's data into C.O
      * @param   other - TriDiag to move
      * @return  None
    */
    TriDiag(TriDiag&& other) = default;
    /**
      * @brief   Sets ptr_to_vector equal to sources after seting row and col
      * @pre     None
      * @post    Creates a new TriDiag object that is identical to source
      * @param   source - TriDiag to copy
      * @return  None
    */
    TriDiag(const TriDiag& source) = default;
    /**
      * @brief   Move content from other into the calling object
      * @pre     None
      * @post    The C.O is identical to the source
      * @param   other - the TriDiag to move
      * @return  *this as the C.O is being altered
    */
    TriDiag& operator=(TriDiag&& other) = default;
    /**
      * @brief   Copies content from rhs into the calling object
      * @pre     None
      * @post    The C.O is identical to the source
      * @param   source - The TriDiag to copy
      * @return  *this as the C.O is being altered
    */
    TriDiag& operator=(const TriDiag& source) = default;
    /**
      * @brief   Allows the ability to read from ptr_to_vector
      * @pre     index must be greater than or equal to zero and less than m_cols
      * @post    None
      * @param   index - Used to access ptr_to_vector
      * @return  A vector from ptr_to_vector
      * @throw   If index is lower than zero or larger than m_cols
    */
    vector<T> operator[](const int index) const;
    /**
      * @brief   Allows the ability to change the vector returned from using []
      * @pre     index must be greater than or equal to zero and less than m_cols
      * @post    The vector accessed is able to be changed
      * @param   index - Used to access ptr_to_vector
      * @return  A position in ptr_to_vector
      * @throw   If index is lower than zero or larger than m_cols
    */
    vector<T>& operator[](const int index);
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
      * @brief   Gets the TriDiag row size
      * @pre     None
      * @post    None
      * @return  m_rows
    */
    int getRow() const { return m_rows; }
    /**
      * @brief   Gets the TriDiag col size
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
  * @return  New TriDiag that is lhs and rhs added together
  * @throw   If matrices are not same dimensions
*/
template<typename T>
TriDiag<T> operator+(const TriDiag<T>& lhs, const TriDiag<T>& rhs);

/**
  * @brief   Subtract two matrices
  * @pre     None
  * @post    None
  * @param   lhs - Matrix left of -
  * @param   rhs - Matrix right of -
  * @return  New TriDiag that is rhs subtracted from lhs
  * @throw   If matrices are not same dimensions
*/
template<typename T>
TriDiag<T> operator-(const TriDiag<T>& lhs, const TriDiag<T>& rhs);

/**
  * @brief   Multiply two matrices together
  * @pre     None
  * @post    None
  * @param   lhs - Matrix left of *
  * @param   rhs - Matrix right of *
  * @return  New TriDiag that is lhs times rhs
  * @throw   If matrices are not same dimensions
*/
template<typename T>
TriDiag<T> operator*(const TriDiag<T>& lhs, const TriDiag<T>& rhs);

/**
  * @brief   Multiply a TriDiag by a vector
  * @pre     Vector size must match TriDiag cols
  * @post    None
  * @param   rhs - vector to multiply by 
  * @param   lhs - The TriDiag to multiply
  * @return  New vector
  * @throw   If vector size doesn't match TriDiag m_cols
*/
template<typename T>
vector<T> operator*(const TriDiag<T>& lhs, const vector<T>& rhs);

/**
  * @brief   Displays the entries of the TriDiag
  * @pre     None
  * @post    Displays the TriDiag
  * @param   out - ostream object used to display the TriDiag
  * @param   m - TriDiag object to read data in from
  * @return  The modified ostream object
*/
template<typename T>
std::ostream& operator<<(std::ostream& out, const TriDiag<T>& m);

#include "tridiagonal.hpp"

#endif