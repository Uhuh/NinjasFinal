
template<typename T>
SymMatrix<T>::SymMatrix(const int r, const int c)
{
  if(r < 0 || c < 0)
  {
    std::cerr << "Tried to set size < 0" << std::endl;
    throw std::out_of_range("LESS THAN ZERO SIZE SYM");
  }

  m_rows = r;
  m_cols = c;

  ptr_to_data = vector<vector<T>>(m_cols);

  int rowReducer = r-1;

  for(int i = 0; i < c; i++)
  {
    ptr_to_data[i] = vector<T>(r - rowReducer);
    rowReducer--;
  }
}

template<typename T>
T SymMatrix<T>::operator()(const int col, const int row) const
{
  if(col < 0 || row < 0 || col >= m_cols || row >= m_rows)
  {
    std::cerr << "Tried to access out of bounds; Sym" << std::endl;
    throw std::out_of_range("CANNOT ACCESS OUT OF BOUNDS; Sym");
  }

  if(row > col)
  {
    return ptr_to_data[row][col];
  }

  return ptr_to_data[col][row];
}

template<typename T>
T& SymMatrix<T>::operator()(const int col, const int row)
{
  if(col < 0 || row < 0 || col >= m_cols || row >= m_rows)
  {
    std::cerr << "Tried to access out of bounds; Sym" << std::endl;
    throw std::out_of_range("CANNOT ACCESS OUT OF BOUNDS; Sym");
  }

  if(row > col)
  {
    return ptr_to_data[row][col];
  }

  return ptr_to_data[col][row];
}

template<typename T>
SymMatrix<T> operator+(const SymMatrix<T>& lhs, const SymMatrix<T>& rhs)
{
  if(lhs.getRow() != rhs.getRow() || lhs.getCol() != rhs.getCol())
  {
    std::cerr << "Cannot add different sized SymMatrices" << std::endl;
    throw std::out_of_range("CANNOT ADD DIFFERENT SIZE; SYM");
  }

  SymMatrix<T> temp(lhs.getRow(), lhs.getCol());

  for(int i = 0; i < lhs.getRow(); i++)
  {
    for(int j = i; j < lhs.getCol(); j++)
    {
      temp(j, i) = lhs(j, i) + rhs(j, i);
    }
  }

  return temp;
}

template<typename T>
SymMatrix<T> operator-(const SymMatrix<T>& lhs, const SymMatrix<T>& rhs)
{
  if(lhs.getRow() != rhs.getRow() || lhs.getCol() != rhs.getCol())
  {
    std::cerr << "Cannot subtract different sized SymMatrices" << std::endl;
    throw std::out_of_range("CANNOT SUBTRACT DIFFERENT SIZE; SYM");
  }

  SymMatrix<T> temp(lhs.getRow(), lhs.getCol());

  for(int i = 0; i < lhs.getRow(); i++)
  {
    for(int j = i; j < lhs.getCol(); j++)
    {
      temp(j, i) = lhs(j, i) - rhs(j, i);
    }
  }

  return temp;
}

template<typename T>
SymMatrix<T> operator*(const SymMatrix<T>& lhs, const SymMatrix<T>& rhs)
{
  if(lhs.getCol() != rhs.getRow())
  {
    std::cerr << "Cannot multiply different col and row; SymMatrices" << std::endl;
    throw std::out_of_range("CANNOT MULTIPLY; SYM");
  }

  SymMatrix<T> temp(lhs.getRow(), rhs.getCol());
  vector<T> rowVec(lhs.getCol());

  for(int row = 0; row < lhs.getRow(); row++)
  {
    for(int i = 0; i < lhs.getCol(); i++)
    {
      rowVec[i] = lhs(i, row);
    }
    for(int col = 0; col < lhs.getCol(); col++)
    {
      double sum = 0;
      for(int i = 0; i < lhs.getRow(); i++)
      {
        sum += rowVec[i] * rhs(col, i);
      }
      temp(col, row) = sum;
    }
  }

  return temp;
}

template<typename T>
vector<T> operator*(const SymMatrix<T>& lhs, const vector<T>& rhs)
{
  if(lhs.getRow() != rhs.getSize())
  {
    throw std::out_of_range("VECTOR SIZE AND MATRIX DO NOT MATCH; SYM");
  }

  vector<T> temp(rhs.getSize());

  for(int i = 0; i < lhs.getRow(); i++)
  {
    double sum = 0;
    for(int j = 0; j < lhs.getCol(); j++)
    {
      sum += lhs(j, i) * rhs[j];
    }
    temp[i] = sum;
  }

  return temp;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const SymMatrix<T>& m)
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