/**
  * @file   vector.hpp
  * @author Dylan Warren, Section A
  * @brief  Implements the vector class functions.
*/

#include <exception>
#include <cmath>

template<typename T>
vector<T>::vector(const vector<T>& source)
{
  m_size = source.m_size;
  ptr_to_data = std::make_unique<T[]>(m_size);

  for(int i = 0; i < source.m_size; i++)
  {
    ptr_to_data[i] = source.ptr_to_data[i];
  }
}

template<typename T>
vector<T>::vector(const int size)
{
  if(size < 1)
  {
    std::cerr << "Tried to set vector size less than 1" << std::endl;
    throw std::out_of_range("Size less than 1");
  }
  m_size = size;
  ptr_to_data = std::make_unique<T[]>(m_size);
}

template<typename T>
vector<T>::vector(vector<T>&& other): 
          ptr_to_data(std::move(other.ptr_to_data)),
          m_size(other.m_size)
{
  // Release the data pointer from the source object so that
  // the destructor does not free the memory multiple times.
  other.ptr_to_data = nullptr;
  other.m_size = 0;
}

template<typename T>
vector<T>& vector<T>::operator=(const vector<T>& rhs)
{
  m_size = rhs.m_size;
  ptr_to_data.reset(new T[m_size]);

  for(int i = 0; i < rhs.m_size; i++)
  {
    ptr_to_data[i] = rhs.ptr_to_data[i];
  }

  return *this;
}

template<typename T>
vector<T>& vector<T>::operator=(vector<T>&& other)
{
  m_size = other.m_size;
  ptr_to_data.reset(new T[m_size]);
  ptr_to_data = std::move(other.ptr_to_data);

  // Release the data pointer from the source object so that
  // the destructor does not free the memory multiple times.
  other.ptr_to_data = nullptr;
  other.m_size = 0;

  return *this;
}

template<typename T>
bool operator==(const vector<T>& lhs, const vector<T>& rhs)
{
  if(lhs.getSize() != rhs.getSize())
  {
    std::cout << "Two different sized vectors (==)" << std::endl;
    throw std::out_of_range("Vectors of differing sizes");
  }
  for(int i = 0; i < rhs.getSize(); i++)
  {
    if(lhs[i] != rhs[i])
    {
      return false;
    }
  }

  return true;
}

template<typename T>
int maxIndex(const vector<T>& v, const int index)
{
  if(index < 0 || index >= v.getSize())
  {
    std::cerr << "Index outside of vectors bounds" << std::endl;
    throw std::out_of_range("OUT OF VECTOR BOUNDS");
  }
  int retIndex = 0;
  T max = 0;
  for(int i = index; i < v.getSize(); i++)
  {
    if(std::abs(v[i]) > max)
    {
      max = std::abs(v[i]);
      retIndex = i;
    }
  }

  return retIndex;
}

template<typename T>
vector<T> operator+(const vector<T>& lhs, const vector<T>& rhs)
{
  if(lhs.getSize() != rhs.getSize())
  {
    std::cerr << "Vectors of different sizes, cannot add" << std::endl;
    throw std::out_of_range("DIFFERENT SIZES");
  }
  vector<T> temp(lhs.getSize());
  for(int i =0; i < lhs.getSize(); i++)
  {
    temp[i] = lhs[i] + rhs[i];
  }

  return temp;
}


template<typename T>
vector<T> operator-(const vector<T>& lhs, const vector<T>& rhs)
{
  if(lhs.getSize() != rhs.getSize())
  {
    std::cerr << "Vectors of different sizes, cannot subtract" << std::endl;
    throw std::out_of_range("DIFFERENT SIZES");
  }
  vector<T> temp(lhs.getSize());
  for(int i =0; i < lhs.getSize(); i++)
  {
    temp[i] = lhs[i] - rhs[i];
  }

  return temp;
}

template<typename T>
T operator*(const vector<T>& lhs, const vector<T>& rhs)
{
  if(lhs.getSize() != rhs.getSize())
  {
    std::cerr << "Vectors of different sizes, cannot multiply" << std::endl;
    throw std::out_of_range("DIFFERENT SIZES");
  }
  T sum = 0;
  for(int i =0; i < lhs.getSize(); i++)
  {
    sum += lhs[i] * rhs[i];
  }

  return sum;
}

template<typename T>
vector<T> operator*(const vector<T>& lhs, const T rhs)
{
  vector<T> temp(lhs.getSize());
  for(int i = 0; i < lhs.getSize(); i++)
  {
    temp[i] = rhs * lhs[i];
  }

  return temp;
}

template<typename T>
const T& vector<T>::operator[](const int index) const
{
  if(index >= m_size || index < 0)
  {
    std::cerr << "index out of vector bounds [] const" << std::endl;
    throw std::out_of_range("Out of bounds: tried to reach out of const[]");
  }
  return ptr_to_data[index];
}

template<typename T>
T& vector<T>::operator[](const int index)
{
  if(index >= m_size || index < 0)
  {
    std::cerr << "index out of vector bounds [] non-const" << std::endl;
    throw std::out_of_range("Out of bounds: tried to reach out of non-const[]");
  }

  return ptr_to_data[index];
}

template<typename T>
vector<T> operator-(const vector<T>& rhs)
{
  vector<T> temp(rhs.getSize());
  for(int i = 0; i < rhs.getSize(); i++)
  {
    temp[i] = -rhs[i];
  }

  return temp;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const vector<T>& v)
{
  for(int i = 0; i < v.getSize(); i++)
  {
    out << v[i] << "\n";
  }

  return out;
}

template<typename T>
std::istream& operator>>(std::istream& in, vector<T>& v)
{
  for(int i = 0; i < v.getSize(); i++)
  {
    if(!(in >> v[i]))
    {
      throw std::runtime_error("Not enough data to fill vector");
    }
  }

  return in;
}