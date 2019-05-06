/**
  * @file   dense.h
  * @author Dylan Warren, Section A
  * @brief  The dense class is a dense matrix. It is row * col size matrix.
*/
/**
  * @class  DenseMatrix
  * @brief  DenseMatrix Allows us to do add/sub/mult of DenseMatrix
*/

#ifndef DENSE_H
#define DENSE_H

#include "./upper.h"
#include "./lower.h"
#include "./symmetric.h"
#include "./tridiagonal.h"

template<class T>
class DenseMatrix : public matrix<DenseMatrix<T>, T>
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
    DenseMatrix() : m_rows(0), m_cols(0), ptr_to_data(vector<vector<T>>()) {};
    /**
      * @brief   Confirms DenseMatrix row and col are proper values
                  then initialises ptr_to_vector
      * @pre     rows and cols must be greater than zero
      * @post    Creates a fresh DenseMatrix of size rows and cols
      * @param   r - How tall the DenseMatrix should be
      * @param   c - How many vectors wide it should be
      * @return  None
      * @throw   If r or r is 0 or less
    */
    DenseMatrix(const int r, const int c);
    /**
      * @brief   Sets ptr_to_vector equal to sources after seting row and col
      * @pre     None
      * @post    Creates a new DenseMatrix object that is identical to source
      * @param   source - DenseMatrix to copy
      * @return  None
    */
    DenseMatrix(const DenseMatrix& source) = default;
    /**
      * @brief   Sets ptr_to_vector equal to other after seting row and col
      * @pre     None
      * @post    Moves other's data into C.O
      * @param   other - DenseMatrix to move
      * @return  None
    */
    DenseMatrix(DenseMatrix&& other) = default;
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
      * @brief   Sets DenseMatrix row size
      * @pre     request sized must be greater than zero
      * @post    m_rows is set
      * @param   r - desired amount of rows
      * @return  None
      * @throw   If r is less than 1
    */
    void setRow(const int r);
    /**
      * @brief   Sets DenseMatrix col size
      * @pre     request sized must be greater than zero
      * @post    m_cols is set
      * @param   c - desired amount of cols
      * @return  None
      * @throw   If c is less than 1
    */
    void setCol(const int c);
    /**
      * @brief   Copies content from rhs into the calling object
      * @pre     None
      * @post    The C.O is identical to the source
      * @param   rhs - The DenseMatrix to copy
      * @return  *this as the C.O is being altered
    */
    DenseMatrix& operator=(const DenseMatrix& rhs) = default;
    /**
      * @brief   Move content from other into the calling object
      * @pre     None
      * @post    The C.O is identical to the source
      * @param   other - the DenseMatrix to move
      * @return  *this as the C.O is being altered
    */
    DenseMatrix& operator=(DenseMatrix&& other) = default;
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
      * @brief   Allows the ability to read from ptr_to_vector
      * @pre     index must be greater than or equal to zero and less than m_cols
      * @post    None
      * @param   index - Used to access ptr_to_vector
      * @return  A vector from ptr_to_vector
      * @throw   If index is lower than zero or larger than m_cols
    */
    const vector<T>& operator[](const int index) const;
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
      * @brief   Checks if the current DenseMatrix is an upper matrix
      * @pre     None
      * @post    None
      * @return  True if the DenseMatrix is upper, otherwise false
    */
    bool isUpper() const;
    /**
      * @brief   Checks if the current DenseMatrix is a lower matrix
      * @pre     None
      * @post    None
      * @return  True if the DenseMatrix is lower, otherwise false
    */
    bool isLower() const;
    /**
      * @brief   Checks if the current DenseMatrix is a Sym matrix
      * @pre     None
      * @post    None
      * @return  True if the DenseMatrix is lower, otherwise false
    */
    bool isSym() const;
    /**
      * @brief   Checks if the current DenseMatrix is a TriDiag matrix
      * @pre     None
      * @post    None
      * @return  True if the DenseMatrix is lower, otherwise false
    */
    bool isTri() const;
    /**
      * @brief   Converts the current DenseMatrix into a UpperTriangle
      * @pre     isUpper() is true
      * @post    None
      * @return  A new UpperTriangle
    */
    UpperTriangle<T> toUpper() const;
    /**
      * @brief   Converts current DenseMatrix into a LowerTriangle
      * @pre     isLower() is true
      * @post    None
      * @return  A new LowerTriangle
    */
    LowerTriangle<T> toLower() const;
    /**
      * @brief   Converts current DenseMatrix into a SymMatrix
      * @pre     isLower() is true
      * @post    None
      * @return  A new LowerTriangle
    */
    SymMatrix<T> toSym() const;
    /**
      * @brief   Converts current DenseMatrix into a TriDiag
      * @pre     isLower() is true
      * @post    None
      * @return  A new LowerTriangle
    */
    TriDiag<T> toTri() const;

};

/**
  * @brief   Add two matrices together
  * @pre     None
  * @post    None
  * @param   lhs - Matrix left of +
  * @param   rhs - Martix right of +
  * @return  New DenseMatrix that is lhs and rhs added together
  * @throw   If matrices are not same dimensions
*/
template<typename T>
DenseMatrix<T> operator+(const DenseMatrix<T>& lhs, const DenseMatrix<T>& rhs);

/**
  * @brief   Subtract two matrices
  * @pre     None
  * @post    None
  * @param   lhs - Matrix left of -
  * @param   rhs - Matrix right of -
  * @return  New DenseMatrix that is rhs subtracted from lhs
  * @throw   If matrices are not same dimensions
*/
template<typename T>
DenseMatrix<T> operator-(const DenseMatrix<T>& lhs, const DenseMatrix<T>& rhs);

/**
  * @brief   Multiply two matrices together
  * @pre     None
  * @post    None
  * @param   lhs - Matrix left of *
  * @param   rhs - Matrix right of *
  * @return  New DenseMatrix that is lhs times rhs
  * @throw   If matrices are not same dimensions
*/
template<typename T>
DenseMatrix<T> operator*(const DenseMatrix<T>& lhs, const DenseMatrix<T>& rhs);

/**
  * @brief   Multiply a DenseMatrix by a scalar
  * @pre     None
  * @post    None
  * @param   scalar - Any number to multiply the DenseMatrix by
  * @param   rhs - The DenseMatrix to multiply
  * @return  New DenseMatrix were all entries are larger by "scalar" times
*/
template<typename U, typename T>
DenseMatrix<T> operator*(const U scalar, const DenseMatrix<T>& rhs);

/**
  * @brief   Multiply a DenseMatrix by a scalar
  * @pre     None
  * @post    None
  * @param   scalar - Any number to multiply the DenseMatrix by
  * @param   lhs - The DenseMatrix to multiply
  * @return  New DenseMatrix were all entries are larger by "scalar" times
*/
template<typename T, typename U>
DenseMatrix<T> operator*(const DenseMatrix<T>& lhs, const U scalar);

/**
  * @brief   Multiply a DenseMatrix by a vector
  * @pre     Vector size must match DenseMatrix cols
  * @post    None
  * @param   rhs - vector to multiply by 
  * @param   lhs - The DenseMatrix to multiply
  * @return  New vector
  * @throw   If vector size doesn't match DenseMatrix m_cols
*/
template<typename T, typename U>
vector<T> operator*(const DenseMatrix<T>& lhs, const vector<U>& rhs);

/**
  * @brief   Transposes the DenseMatrix, easier than multiplying by the ident DenseMatrix
  * @pre     None
  * @post    None
  * @param   source - The DenseMatrix to transpose, or "flip"
  * @return  New DenseMatrix were entries have been moved
*/
template<typename T>
DenseMatrix<T> transpose(const DenseMatrix<T>& source);

/**
  * @brief   Combines a DenseMatrix A and vector B and makes an augmented DenseMatrix
  * @pre     B must be the same size as the matrice's rows
  * @post    None
  * @param   source - Matrix to combine with B
  * @param   B - The vector to attach to source
  * @return  Matrix that is source and B combined where B is on the right side
  * @throw   If B size does not match source's row size
*/
template<typename T>
DenseMatrix<T> makeAug(const DenseMatrix<T>& source, const vector<T>& B);

/**
  * @brief   Displays the entries of the DenseMatrix
  * @pre     None
  * @post    Displays the DenseMatrix
  * @param   out - ostream object used to display the DenseMatrix
  * @param   m - DenseMatrix object to read data in from
  * @return  The modified ostream object
*/
template<typename T>
std::ostream& operator<<(std::ostream& out, const DenseMatrix<T>& m);

/**
  * @brief   Reads in the DenseMatrix data
  * @pre     Must have valid input file open to read data from
  * @post    None
  * @param   in - istream object to read data in with
  * @param   m - DenseMatrix object to store data in to
  * @return  The modified istream object
*/
template<typename T>
std::istream& operator>>(std::istream& in, DenseMatrix<T>& m);


#include "./dense.hpp"

#endif