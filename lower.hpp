/**
  * @file   lower.hpp
  * @author Dylan Warren, Section A
  * @brief  Implements LowerTriangle operators
*/

template<typename T>
LowerTriangle<T>::LowerTriangle(const int r, const int c)
{
  if(r < 0 || c < 0)
  {
    std::cerr << "Row or Cols set less than zero" << std::endl;
    throw std::out_of_range("Tried to set illegal bounds of matrix");
  }
  m_rows = r;
  m_cols = c;

  ptr_to_data = vector<vector<T>>(m_cols);

  int rowReducer = 0;

  for(int i = 0; i < m_cols; i++)
  {
    ptr_to_data[i] = vector<T>(m_rows - rowReducer);
    rowReducer++;
  }
}

template<typename T>
UpperTriangle<T> transpose(const LowerTriangle<T>& source)
{
  UpperTriangle<T> temp(source.getRow(), source.getCol());

  for(int i = 0; i < source.getRow(); i++)
  {
    for(int j = i; j < source.getCol(); j++)
    {
      temp(j, i) = source(i, j);
    }
  }

  return temp;
}

template<typename T>
LowerTriangle<T> operator+(const LowerTriangle<T>& lhs, 
                            const LowerTriangle<T>& rhs)
{
  if(lhs.getCol() != rhs.getCol() || lhs.getRow() != rhs.getRow())
  {
    std::cerr << "Matrices not same size, cannot add." << std::endl;
  }

  LowerTriangle<T> temp(lhs.getRow(), lhs.getCol());

  for(int i = 0; i < temp.getRow(); i++)
  {
    for(int j = 0; j <= i; j++)
    {
      temp(j, i) = lhs(j, i) + rhs(j, i);
    }
  }

  return temp;
}

template<typename T>
LowerTriangle<T> operator-(const LowerTriangle<T>& lhs, 
                            const LowerTriangle<T>& rhs)
{
  if(lhs.getCol() != rhs.getCol() || lhs.getRow() != rhs.getRow())
  {
    std::cerr << "Matrices not same size, cannot subtract." << std::endl;
  }

  LowerTriangle<T> temp(lhs.getRow(), lhs.getCol());

  for(int i = 0; i < temp.getRow(); i++)
  {
    for(int j = 0; j <= i; j++)
    {
      temp(j, i) = lhs(j, i) - rhs(j, i);
    }
  }

  return temp;
}

template<typename T>
LowerTriangle<T> operator*(const LowerTriangle<T>& lhs, 
                            const LowerTriangle<T>& rhs)
{
  if(lhs.getCol() != rhs.getRow())
  {
    std::cerr << "lhs column doesn't match rhs row size" << std::endl;
  }

  LowerTriangle<T> temp(lhs.getRow(), rhs.getCol());
  vector<T> rowVec(lhs.getCol());

  for(int row = 0; row < lhs.getRow(); row++)
  {
    for(int k = 0; k < lhs.getCol(); k++)
    {
      rowVec[k] = lhs(k, row);
    }

    for(int col = 0; col <= row; col++)
    {
      double sum = 0;
      for(int i = col; i <= row; i++)
      {
        sum += rowVec[i] * rhs(col, i);
      }
      temp(col, row) = sum;
    }
  }

  return temp;
}

template<typename T>
vector<T> operator*(const LowerTriangle<T>& lhs, const vector<T>& rhs)
{
  if(lhs.getCol() != rhs.getSize())
  {
    std::cerr << "vector size does not match lower col" << std::endl;
    throw std::out_of_range("MISMATCHED VECTOR AND MATRIX SIZE");
  }
  
  vector<T> temp(rhs.getSize());
  vector<T> rowVec(rhs.getSize());

  for(int row = 0; row < lhs.getRow(); row++)
  {
    for(int k = 0; k < lhs.getCol(); k++)
    {
      rowVec[k] = lhs(k, row);
    }

    for(int col = row; col < lhs.getCol(); col++)
    {
      double sum = 0;
      for(int i = row; i <= col; i++)
      {
        sum += rowVec[i] * rhs[i];
      }
      temp[row] = sum;
    }
  }

  return temp;
}

template<typename T>
T LowerTriangle<T>::operator()(const int col, const int row) const
{
  if(col < 0 || col >= m_cols || row < 0 || row >= m_rows)
  {
    std::cerr << "Out of bounds () call" << std::endl;
  }

  if(col > row)
  {
    return 0;
  }

  return ptr_to_data[col][row-col];
}

template<typename T>
T& LowerTriangle<T>::operator()(const int col, const int row)
{
  if(col < 0 || col >= m_cols || row < 0 || row >= m_rows)
  {
    std::cerr << "Out of bounds () call" << std::endl;
  }

  if(col > row)
  {
    std::cerr << "Tried to make an lower not an lower matrix" << std::endl;
    throw std::out_of_range("Tried to set 0 to a value");
  }

  return ptr_to_data[col][row-col];
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const LowerTriangle<T>& m)
{
  for(int i = 0; i < m.getRow(); i++)
  {
    for(int j = 0; j < m.getCol(); j++)
    {
      out << m(j, i) << " ";
    }
    out << std::endl;
  }

  return out;
}