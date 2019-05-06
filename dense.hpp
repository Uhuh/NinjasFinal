/**
  * @file   dense.hpp
  * @author Dylan Warren, Section A
  * @brief  Implements DenseMatrix operators
*/

#include <exception>
#include <cmath>

template<typename T>
DenseMatrix<T>::DenseMatrix(const int rows, const int cols)
{
  if(rows < 0 || cols < 0)
  {
    std::cerr << "Row or Cols set less than zero" << std::endl;
    throw std::out_of_range("Tried to set illegal bounds of DenseMatrix");
  }
  m_rows = rows;
  m_cols = cols;
  
  ptr_to_data = vector<vector<T>>(m_cols);

  for(int i = 0; i < m_cols; i++)
  {
    ptr_to_data[i] = vector<T>(m_rows);
  }
}

template<typename T>
void DenseMatrix<T>::setRow(const int r)
{
  if(r <= 0)
  {
    std::cerr << "Tried to set row less than or equal to zero" << std::endl;
    throw std::out_of_range("SET ROW LESS THAN 1");
  }

  m_rows = r;
}

template<typename T>
void DenseMatrix<T>::setCol(const int c)
{
  if(c <= 0)
  {
    std::cerr << "Tried to set col less than or equal to zero" << std::endl;
    throw std::out_of_range("SET COL LESS THAN 1");
  }

  m_cols = c;
}

template<typename T>
vector<T>& DenseMatrix<T>::operator[](const int index)
{
  if(index < 0 || index > (m_cols-1))
  {
    std::cerr << "Out of bounds in non const []" << std::endl;
    throw std::out_of_range("OUT OF BOUNDS");
  }

  return ptr_to_data[index];
}

template<typename T>
const vector<T>& DenseMatrix<T>::operator[](const int index) const
{
  if(index < 0 || index > (m_cols-1))
  {
    std::cerr << "Out of bounds in non const []" << std::endl;
    throw std::out_of_range("OUT OF BOUNDS");
  }

  return ptr_to_data[index];
}

template<typename T>
T DenseMatrix<T>::operator()(const int col, const int row) const
{
  if(col < 0 || col >= m_cols || row < 0 || row >= m_rows)
  {
    std::cerr << "Out of bounds ()" << std::endl;
    throw std::out_of_range("OUT OF BOUNDS");
  }

  return ptr_to_data[col][row];
}

template<typename T>
bool DenseMatrix<T>::isUpper() const
{
  for(int i = 0; i < m_rows; i++)
  {
    if(i < m_cols && ptr_to_data[i][i] == 0)
    {
      return false;
    }
  }

  for(int i = 0; i < m_rows; i++)
  {
    for(int j = 0; j < i; j++)
    {
      if(ptr_to_data[j][i] != 0)
      {
        return false;
      }
    }
  }

  return true;
}

template<typename T>
bool DenseMatrix<T>::isLower() const
{
  for(int i = 0; i < m_rows; i++)
  {
    if(i < m_cols && ptr_to_data[i][i] == 0)
    {
      return false;
    }
  }

  for(int i = 0; i < m_rows; i++)
  {
    for(int j = i + 1; j < m_cols; j++)
    {
      if(ptr_to_data[j][i] != 0)
      {
        return false;
      }
    }
  }

  return true;
}

template<typename T>
bool DenseMatrix<T>::isSym() const
{
  for(int i = 0; i < m_rows; i++)
  {
    for(int j = i; j < m_cols; j++)
    {
      if(ptr_to_data[i][j] != ptr_to_data[j][i])
      {
        return false;
      }
    }
  }

  return true;
}

template<typename T>
bool DenseMatrix<T>::isTri() const
{
  for(int i = 0; i < m_rows; i++)
  {
    for(int j = 0; j < m_cols; j++)
    {
      if(abs(j - i) > 1 && ptr_to_data[j][i] != 0)
      {
        return false;
      }
    }
  }

  return true;
}

template<typename T>
UpperTriangle<T> DenseMatrix<T>::toUpper() const
{
  UpperTriangle<T> UMatrix(m_rows, m_cols);

  for(int i = 0; i < m_rows; i++)
  {
    for(int j = i; j < m_cols; j++)
    {
      UMatrix(j, i) = ptr_to_data[j][i];
    }
  }

  return UMatrix;
}

template<typename T>
LowerTriangle<T> DenseMatrix<T>::toLower() const
{
  LowerTriangle<T> LMatrix(m_rows, m_cols);

  for(int i = 0; i < m_rows; i++)
  {
    for(int j = 0; j <= i; j++)
    {
      LMatrix(j, i) = ptr_to_data[j][i];
    }
  }

  return LMatrix;
}

template<typename T>
SymMatrix<T> DenseMatrix<T>::toSym() const
{
  SymMatrix<T> SMatrix(m_rows, m_cols);

  for(int i = 0; i < m_rows; i++)
  {
    for(int j =0; j <= i; j++)
    {
      SMatrix(j, i) = ptr_to_data[j][i];
    }
  }

  return SMatrix;
}

template<typename T>
TriDiag<T> DenseMatrix<T>::toTri() const
{
  TriDiag<T> TMatrix(m_rows, m_cols);

  for(int i = 0; i < m_rows; i++)
  {
    if((i + 1) < m_cols)
    {
      TMatrix(i + 1, i) = ptr_to_data[i + 1][i];
    }
    TMatrix(i, i) = ptr_to_data[i][i];
    if((i + 1) < m_rows)
    {
      TMatrix(i, i + 1) = ptr_to_data[i][i + 1];
    }
  }

  return TMatrix;
}

template<typename T>
DenseMatrix<T> operator+(const DenseMatrix<T>& lhs, const DenseMatrix<T>& rhs)
{
  if(!(lhs.getRow() == rhs.getRow() && lhs.getCol() == lhs.getCol()))
  {
    std::cerr << "Matrix's of different sizes cannot add" << std::endl;
    throw std::out_of_range("DIFFERENT SIZES"); // CHANGE THIS THROW TYPE
  }

  DenseMatrix<T> temp(lhs.getRow(), lhs.getCol());

  for(int i = 0; i < lhs.getCol(); i++)
  {
    temp[i] = lhs[i] + rhs[i];
  }

  return temp;
}

template<typename T>
DenseMatrix<T> operator-(const DenseMatrix<T>& lhs, const DenseMatrix<T>& rhs)
{
  if(!(lhs.getRow() == rhs.getRow() && lhs.getCol() == lhs.getCol()))
  {
    std::cerr << "Matrix's of different sizes cannot subtract" << std::endl;
    throw std::out_of_range("DIFFERENT SIZES"); // CHANGE THIS THROW TYPE
  }

  DenseMatrix<T> temp(lhs.getRow(), lhs.getCol());

  for(int i = 0; i < lhs.getCol(); i++)
  {
    temp[i] = lhs[i] - rhs[i];
  }

  return temp;
}

template<typename T>
DenseMatrix<T> operator*(const DenseMatrix<T>& lhs, const DenseMatrix<T>& rhs)
{
  if(lhs.getCol() != rhs.getRow())
  {
    std::cerr << "Cannot multiply two DenseMatrix's if the lhs cols doesn't"
              << " match rhs rows." << std::endl;
    throw std::out_of_range("MATRIX'S DIFFERENT COL AND ROWS"); // change the throw type
  }

  DenseMatrix<T> temp(lhs.getRow(), rhs.getCol());
  vector<T> rowVec(lhs.getCol());

  for(int i = 0; i < rhs.getCol(); i++)
  {
    for(int j = 0; j < lhs.getRow(); j++)
    {
      for(int k = 0; k < lhs.getCol(); k++)
      {
        rowVec[k] = lhs[k][j];
      }
      temp[i][j] = rowVec * rhs[i];
    }
  }

  return temp;
}

template<typename U, typename T>
DenseMatrix<T> operator*(const U scalar, const DenseMatrix<T>& rhs)
{
  DenseMatrix<T> temp(rhs.getRow(), rhs.getCol());

  for(int i = 0; i < temp.getRow(); i++)
  {
    for(int j = 0; j < temp.getCol(); j++)
    {
      temp[i][j] = scalar * rhs[i][j];
    }
  }
  
  return temp;
}

template<typename T, typename U>
DenseMatrix<T> operator*(const DenseMatrix<T>& lhs, const U scalar)
{
  return scalar * lhs;
}

template<typename T, typename U>
vector<T> operator*(const DenseMatrix<T>& lhs, const vector<U>& rhs)
{
  if(rhs.getSize() != lhs.getCol())
  {
    std::cerr << "Vector size and DenseMatrix row size do not match" << std::endl;
    throw std::out_of_range("MISMATCHED VECTOR SIZE AND MATRIX ROW SIZE");
  }

  vector<T> temp(rhs.getSize());
  T sum = 0;

  for(int i = 0; i < lhs.getCol(); i++)
  {
    for(int j = 0; j < lhs.getRow(); j++)
    {
      sum += lhs[j][i] * rhs[j];
    }
    temp[i] = sum;
    sum = 0;
  }

  return temp;
}

template<typename T>
DenseMatrix<T> transpose(const DenseMatrix<T>& source)
{
  DenseMatrix<T> temp(source.getCol(), source.getRow());

  for(int i = 0; i < source.getCol(); i++)
  {
    for(int j = 0; j < source.getRow(); j++)
    {
      temp[j][i] = source(i, j);
    }
  }

  return temp;
}

template<typename T>
DenseMatrix<T> makeAug(const DenseMatrix<T>& source, const vector<T>& B)
{

  if(source.getRow() != B.getSize())
  {
    std::cerr << "Vector B size does not match Matrix row size." << std::endl;
    // change throw type
    throw std::out_of_range("MISS MATCHING VECTOR AND MATRIX SIZE");
  }

  DenseMatrix<T> temp(source.getRow(), source.getCol()+1);
  for(int i = 0; i < source.getCol(); i++)
  {
    temp[i] = source[i];
  }

  temp[temp.getCol()-1] = B;

  return temp;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const DenseMatrix<T>& m)
{
  for(int i = 0; i < m.getRow(); i++)
  {
    for(int j = 0; j < m.getCol(); j++)
    {
      out << m[j][i] << " ";
    }
    out << std::endl;
  }

  return out;
}

template<typename T>
std::istream& operator>>(std::istream& in, DenseMatrix<T>& m)
{
  for(int i = 0; i < m.getCol(); i++)
  {
    for(int j = 0; j < m.getRow(); j++)
    {
      if(!(in >> m[j][i]))
      {
        throw std::runtime_error("Not enough data in file to fill DenseMatrix");
      }
    }
  }
  return in;
}
