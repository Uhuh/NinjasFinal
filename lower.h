/**
  * @file   lower.h
  * @author Dylan Warren, Section A
  * @brief  The lower class is a lower matrix.
*/
/**
  * @class  LowerTriangle
  * @brief  LowerTriangle Allows us to do add/sub/mult of LowerTriangle
*/

#ifndef LOWER_H
#define LOWER_H

#include "./matrix.h"

template<class T>
class LowerTriangle : public matrix<LowerTriangle<T>, T>
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
    /**
      * @brief   Allows the ability to read from ptr_to_vector
      * @pre     index must be greater than or equal to zero and less than m_cols
      * @post    None
      * @param   index - Used to access ptr_to_vector
      * @return  A vector from ptr_to_vector
      * @throw   If index is lower than zero or larger than m_cols
    */
    const vector<T>& operator[](const int index) const { return ptr_to_data[index]; }
  public:
    /**
      * @brief   Sets row and col to 0 and sets our point to nullptr
      * @pre     None
      * @post    All member variables are set.
      * @return  None
    */
    LowerTriangle() : m_rows(0), m_cols(0), ptr_to_data(vector<vector<T>>()) {};
    /**
      * @brief   Confirms LowerTriangle row and col are proper values
                  then initialises ptr_to_vector
      * @pre     rows and cols must be greater than zero
      * @post    Creates a fresh LowerTriangle of size rows and cols
      * @param   r - How tall the LowerTriangle should be
      * @param   c - How many vectors wide it should be
      * @return  None
      * @throw   If r or r is 0 or less
    */
    LowerTriangle(const int r, const int c);
    /**
      * @brief   Sets ptr_to_vector equal to other after seting row and col
      * @pre     None
      * @post    Moves other's data into C.O
      * @param   other - LowerTriangle to move
      * @return  None
    */
    LowerTriangle(LowerTriangle<T>&& other) = default;
    /**
      * @brief   Sets ptr_to_vector equal to sources after seting row and col
      * @pre     None
      * @post    Creates a new LowerTriangle object that is identical to source
      * @param   source - LowerTriangle to copy
      * @return  None
    */
    LowerTriangle(const LowerTriangle& source) = default;
    /**
      * @brief   Move content from other into the calling object
      * @pre     None
      * @post    The C.O is identical to the source
      * @param   other - the LowerTriangle to move
      * @return  *this as the C.O is being altered
    */
    LowerTriangle& operator=(LowerTriangle&& other) = default;
    /**
      * @brief   Copies content from rhs into the calling object
      * @pre     None
      * @post    The C.O is identical to the source
      * @param   rhs - The LowerTriangle to copy
      * @return  *this as the C.O is being altered
    */
    LowerTriangle& operator=(const LowerTriangle& rhs) = default;
    /**
      * @brief   Gets the DenseMatrix row size
      * @pre     None
      * @post    None
      * @return  m_rows
    */
    int getRow() const { return m_rows; }
    /**
      * @brief   Gets the DenseMatrix col size
      * @pre     None
      * @post    None
      * @return  m_cols
    */
    int getCol() const { return m_cols; }
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
  * @brief   Add two LowerTriangles together
  * @pre     None
  * @post    None
  * @param   lhs - Matrix left of +
  * @param   rhs - Martix right of +
  * @return  New LowerTriangle that is lhs and rhs added together
  * @throw   If LowerTriangle are not same dimensions
*/
template<typename T>
LowerTriangle<T> operator+(const LowerTriangle<T>& lhs, 
                            const LowerTriangle<T>& rhs);

/**
  * @brief   Subtract two LowerTriangle
  * @pre     None
  * @post    None
  * @param   lhs - Matrix left of -
  * @param   rhs - Matrix right of -
  * @return  New LowerTriangle that is rhs subtracted from lhs
  * @throw   If LowerTriangle are not same dimensions
*/
template<typename T>
LowerTriangle<T> operator-(const LowerTriangle<T>& lhs, 
                            const LowerTriangle<T>& rhs);

/**
  * @brief   Multiply two LowerTriangle together
  * @pre     None
  * @post    None
  * @param   lhs - Matrix left of *
  * @param   rhs - Matrix right of *
  * @return  New LowerTriangle that is lhs times rhs
  * @throw   If LowerTriangle are not same dimensions
*/
template<typename T>
LowerTriangle<T> operator*(const LowerTriangle<T>& lhs, 
                            const LowerTriangle<T>& rhs);

/**
  * @brief   Multiply a LowerTriangle by a vector
  * @pre     Vector size must match LowerTriangle cols
  * @post    None
  * @param   rhs - vector to multiply by 
  * @param   lhs - The LowerTriangle to multiply
  * @return  New vector
  * @throw   If vector size doesn't match LowerTriangle m_cols
*/
template<typename T>
vector<T> operator*(const LowerTriangle<T>& lhs, const vector<T>& rhs);

/**
  * @brief   Transposes the LowerTriangle, easier than multiplying by the ident LowerTriangle
  * @pre     None
  * @post    None
  * @param   source - The LowerTriangle to transpose, or "flip"
  * @return  New UpperTriangle were entries have been moved
*/
template<typename T>
UpperTriangle<T> transpose(const LowerTriangle<T>& source);

/**
  * @brief   Displays the entries of the LowerTriangle
  * @pre     None
  * @post    Displays the LowerTriangle
  * @param   out - ostream object used to display the LowerTriangle
  * @param   m - LowerTriangle object to read data in from
  * @return  The modified ostream object
*/
template<typename T>
std::ostream& operator<<(std::ostream& out, const LowerTriangle<T>& m);

#include "./lower.hpp"

#endif