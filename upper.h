/**
  * @file   upper.h
  * @author Dylan Warren, Section A
  * @brief  The upper class is a upper matrix.
*/
/**
  * @class  UpperTriangle
  * @brief  UpperTriangle Allows us to do add/sub/mult of UpperTriangle
*/

#ifndef UPPER_H
#define UPPER_H

#include "./matrix.h"

template <class T>
class UpperTriangle : public matrix<UpperTriangle<T>, T>
{
  private:
    int m_rows;
    int m_cols;
    vector<vector<T>> ptr_to_data;
    /**
      * @brief   Allows the ability to change the vector returned from using []
      * @pre     index must be greater than or equal to zero and less than m_cols
      * @post    The vector accessed is able to be changed
      * @param   index - Used to access ptr_to_vector
      * @return  A position in ptr_to_vector
      * @throw   If index is lower than zero or larger than m_cols
    */
    vector<T>& operator[](const int index) { return ptr_to_data[index]; }
  public:
    /**
      * @brief   Allows the ability to read from ptr_to_vector
      * @pre     index must be greater than or equal to zero and less than m_cols
      * @post    None
      * @param   index - Used to access ptr_to_vector
      * @return  A vector from ptr_to_vector
      * @throw   If index is lower than zero or larger than m_cols
    */
    const vector<T>& operator[](const int index) const { return ptr_to_data[index]; }
    /**
      * @brief   Sets row and col to 0 and sets our point to nullptr
      * @pre     None
      * @post    All member variables are set.
      * @return  None
    */
    UpperTriangle() : m_rows(0), m_cols(0), ptr_to_data(vector<vector<T>>()) {};
    /**
      * @brief   Confirms UpperTrianle row and col are proper values
                  then initialises ptr_to_vector
      * @pre     rows and cols must be greater than zero
      * @post    Creates a fresh UpperTrianle of size rows and cols
      * @param   r - How tall the UpperTrianle should be
      * @param   c - How many vectors wide it should be
      * @return  None
      * @throw   If r or r is 0 or less
    */
    UpperTriangle(const int r, const int c);
    /**
      * @brief   Sets ptr_to_vector equal to sources after seting row and col
      * @pre     None
      * @post    Creates a new UpperTriangle object that is identical to source
      * @param   source - UpperTriangle to copy
      * @return  None
    */
    UpperTriangle(const UpperTriangle& source) = default;
    /**
      * @brief   Sets ptr_to_vector equal to other after seting row and col
      * @pre     None
      * @post    Moves other's data into C.O
      * @param   other - UpperTriangle to move
      * @return  None
    */
    UpperTriangle(UpperTriangle&& other) = default;
    /**
      * @brief   Gets the UpperTriangle row size
      * @pre     None
      * @post    None
      * @return  m_rows
    */
    int getRow() const { return m_rows; }
    /**
      * @brief   Gets the UpperTriangle col size
      * @pre     None
      * @post    None
      * @return  m_cols
    */
    int getCol() const { return m_cols; }
    /**
      * @brief   Copies content from rhs into the calling object
      * @pre     None
      * @post    The C.O is identical to the source
      * @param   rhs - The UpperTriangle to copy
      * @return  *this as the C.O is being altered
    */
    UpperTriangle& operator=(const UpperTriangle& rhs) = default;
    /**
      * @brief   Move content from other into the calling object
      * @pre     None
      * @post    The C.O is identical to the source
      * @param   other - the UpperTriangle to move
      * @return  *this as the C.O is being altered
    */
    UpperTriangle& operator=(UpperTriangle&& other) = default;
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
};

/**
  * @brief   Add two UpperTriangle together
  * @pre     None
  * @post    None
  * @param   lhs - Matrix left of +
  * @param   rhs - Martix right of +
  * @return  New UpperTriangle that is lhs and rhs added together
  * @throw   If UpperTriangle are not same dimensions
*/
template<typename T>
UpperTriangle<T> operator+(const UpperTriangle<T>& lhs, 
                            const UpperTriangle<T>& rhs);

/**
  * @brief   Subtract two UpperTriangle
  * @pre     None
  * @post    None
  * @param   lhs - Matrix left of -
  * @param   rhs - Matrix right of -
  * @return  New UpperTriangle that is rhs subtracted from lhs
  * @throw   If UpperTriangle are not same dimensions
*/
template<typename T>
UpperTriangle<T> operator-(const UpperTriangle<T>& lhs, 
                            const UpperTriangle<T>& rhs);

/**
  * @brief   Multiply two UpperTriangle together
  * @pre     None
  * @post    None
  * @param   lhs - Matrix left of *
  * @param   rhs - Matrix right of *
  * @return  New UpperTriangle that is lhs times rhs
  * @throw   If UpperTriangle are not same dimensions
*/
template<typename T>
UpperTriangle<T> operator*(const UpperTriangle<T>& lhs, 
                            const UpperTriangle<T>& rhs);

/**
  * @brief   Multiply a UpperTriangle by a vector
  * @pre     Vector size must match UpperTriangle cols
  * @post    None
  * @param   rhs - vector to multiply by 
  * @param   lhs - The UpperTriangle to multiply
  * @return  New vector
  * @throw   If vector size doesn't match UpperTriangle m_cols
*/
template<typename T>
vector<T> operator*(const UpperTriangle<T>& lhs, const vector<T>& rhs);

/**
  * @brief   Displays the entries of the UpperTriangle
  * @pre     None
  * @post    Displays the UpperTriangle
  * @param   out - ostream object used to display the UpperTriangle
  * @param   m - UpperTriangle object to read data in from
  * @return  The modified ostream object
*/
template<typename T>
std::ostream& operator<<(std::ostream& out, const UpperTriangle<T>& m);

#include "./upper.hpp"

#endif