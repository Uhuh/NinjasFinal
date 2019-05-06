/**
  * @file   vector.h
  * @author Dylan Warren, Section A
  * @brief  The vector class keeps data stored in its smart pointer. With the help o
*/
/**
  * @class  vector
  * @brief  vector class implements methods that make adding / subtracting
  *         / multiplaying my vectors/scalars much easier.
*/
#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>
#include <memory>

template<class T>
class vector
{
private:
  std::unique_ptr<T[]> ptr_to_data;
  int m_size;
public:
  /**
    * @brief   Sets size to 1 and points data to nullptr (0)
    * @pre     None
    * @post    All member variables are set.
    * @return  None
  */
  vector(): ptr_to_data(nullptr), m_size(0) {};
  /**
    * @brief   Sets the m_size and points ptr_to_data to new memory or m_size
    * @pre     Size must be 1 or greater
    * @post    Creates a new vector object. Else throw error if the size passed
    *          is less than 1.
    * @param   size - the desired size of the vector
    * @return  None
  */
  vector(const int size);
  /**
    * @brief   Takes a vector object, copies the size and reallocates memory
    *           to set ptr_to_data
    * @pre     None
    * @post    Creates a new vector object that is identical to source
    * @param   source - The object to be copied
    * @return  None
  */
  vector(const vector& source);
  /**
    * @brief   Takes a vector object, copies the size and reallocates memory
    *           to set ptr_to_data
    * @pre     None
    * @post    Moves a vector object into C.O
    * @param   other - The object to move into C.O
    * @return  None
  */
  vector(vector&& other);
  /**
    * @brief   Replaces the calling objects variable values with source's
    * @pre     None
    * @post    Changes the calling objects m_size, ptr_to_data
    * @param   rhs - The vector object to copy values from
    * @return  All of the calling objects member variables are replaced
  */
  vector& operator=(const vector& rhs);
  /**
    * @brief   Moves other's content into C.O's
    * @pre     None
    * @post    Changes the calling objects m_size, ptr_to_data
    * @param   other - The vector object to move values from
    * @return  All of the calling objects member variables are replaced
  */
  vector& operator=(vector&& other);
  /**
    * @brief   Allows user to read from ptr_to_data easily.
    * @pre     Must be between 0 and m_size - 1
    * @post    Throws an error if out_of_bounds is reached.
    * @param   index - used to index the ptr_to_data
    * @return  Whatever value is at ptr_to_data[index]
  */
  const T& operator[](const int index) const;
  /**
    * @brief   Allows the user to change the value of the returned index
    * @pre     None
    * @post    Could change the index' part of ptr_to_data
    * @param   index - used to index the ptr_to_data
    * @return  A reference to the pointers value.
  */
  T& operator[](const int index);
  /**
    * @brief   Gets the vectors m_size
    * @pre     None
    * @post    None
    * @return  Returns m_size
  */
  int getSize() const { return m_size; }
};

/**
  * @brief   Negates all values of the vector rhs
  * @pre     None
  * @post    None
  * @param   rhs - The vector to be negated
  * @return  A vector that has had it's values negated
*/
template<typename T>
vector<T> operator-(const vector<T>& rhs);

/**
  * @brief   Adds two vectors
  * @pre     None
  * @post    None
  * @param   lhs - Left hand operand
  * @param   rhs - Right hand operand
  * @return  A vector that is the added values of lhs and rhs
*/
template<typename T>
vector<T> operator+(const vector<T>& lhs, const vector<T>& rhs);

/**
  * @brief   Subtracts two vectors
  * @pre     None
  * @post    None
  * @param   lhs - Left hand operand
  * @param   rhs - Right hand operand
  * @return  A vector that is the subtracted values of lhs and rhs
*/
template<typename T>
vector<T> operator-(const vector<T>& lhs, const vector<T>& rhs);

/**
  * @brief   Multiplies a scalar by a vector
  * @pre     None
  * @post    None
  * @param   lhs - Left hand operand
  * @param   rhs - Scalar to multiply by the vector
  * @return  A vector that has rhs times the values of lhs
*/
template<typename T>
vector<T> operator*(const vector<T>& lhs, const T rhs);

/**
  * @brief   Multiplies two vectors
  * @pre     None
  * @post    None
  * @param   lhs - Left hand operand
  * @param   rhs - Right hand operand
  * @return  A value made by multiplying two vectors
*/
template<typename T>
T operator*(const vector<T>& lhs, const vector<T>& rhs);

/**
  * @brief   Compares two vectors ptr_to_data
  * @pre     None
  * @post    None
  * @param   lhs - Left hand operand
  * @param   rhs - Right hand operand
  * @return  If vectors are equal return true
*/
template<typename T>
bool operator==(const vector<T>& lhs, const vector<T>& rhs);

/**
  * @brief   Compares the magnitude of the vectors entries keeps track of index
  * @pre     None
  * @post    None
  * @param   v - vector to compare entries
  * @param   index - useed to start search from a certain part in the vector
  * @return  index of the max value in the vector
  * @throw   If index is outside of bounds
*/
template<typename T>
int maxIndex(const vector<T>& v, const int index);

/**
  * @brief   Outputs the vector
  * @pre     None
  * @post    Displays the vector
  * @param   out - ostream object used to display the vector
  * @param   v - vector object to read data in from
  * @return  The modified ostream object
*/
template<typename T>
std::ostream& operator<<(std::ostream& out, const vector<T>& v);

/**
  * @brief   Reads in the vector data
  * @pre     Must have a valid input file open to read data
  * @post    None
  * @param   in - istream object to change to read data in
  * @param   v - vector object to store data in to
  * @return  The modified istream object
*/
template<typename T>
std::istream& operator>>(std::istream& in, vector<T>& v);

#include "./vector.hpp"

#endif