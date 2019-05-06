
template<typename T>
TriDiag<T>::TriDiag(const int r, const int c)
{
  if(r < 0 || c < 0)
  {
    std::cerr << "Tried to set size less than zero; Tri" << std::endl;
    throw std::out_of_range("INVALID SIZES GIVEN");
  }

  m_rows = r;
  m_cols = c;

  ptr_to_data = vector<vector<T>>(m_cols);
  ptr_to_data[0] = vector<T>(2);

  for(int i = 1; i < m_cols - 1; i++)
  {
    ptr_to_data[i] = vector<T>(3);
  }

  ptr_to_data[m_cols-1] = vector<T>(2);
}

template<typename T>
vector<T> TriDiag<T>::operator[](const int index) const
{
  if(index < 0 || index > m_cols)
  {
    std::cerr << "Out of bounds []" << std::endl;
    throw std::out_of_range("OUT OF BOUNDS [] TRI;");
  }

  return ptr_to_data[index];
}

template<typename T>
vector<T>& TriDiag<T>::operator[](const int index)
{
  if(index < 0 || index > m_cols)
  {
    std::cerr << "Out of bounds []" << std::endl;
    throw std::out_of_range("OUT OF BOUNDS [] TRI;");
  }

  return ptr_to_data[index];
}

template<typename T>
T TriDiag<T>::operator()(const int col, const int row) const
{
  if(col < 0 || col >= m_cols || row < 0 || row >= m_rows)
  {
    std::cerr << "Tried to access out of bounds" << std::endl;
    throw std::out_of_range("OUT OF BOUNDS; TRI");
  }

  // If the difference is greater than 1 then we are "outside" of the actual data.
  const int DIFF = abs(row - col);

  if(DIFF > 1)
  {
    return 0;
  }

  if(col == 0)
  {
    return ptr_to_data[col][row];
  }

  if(col == (m_cols - 1))
  {
    return ptr_to_data[col][row-(m_rows-2)];
  }

  const int ROW_DIFF = (row - (col - 1));

  return ptr_to_data[col][ROW_DIFF];
}

template<typename T>
T& TriDiag<T>::operator()(const int col, const int row)
{
  if(col < 0 || col >= m_cols || row < 0 || row >= m_rows)
  {
    std::cerr << "Tried to access out of bounds" << std::endl;
    throw std::out_of_range("OUT OF BOUNDS; TRI");
  }

  // If the difference is greater than 1 then we are "outside" of the actual data.
  const int DIFF = abs(row - col);

  if(DIFF > 1)
  {
    std::cerr << "TRIED TO CHANGE TRI TO NON TRI" << std::endl;
    throw std::out_of_range("TRIED TO CHANGE 0 IN TRIDIAG");
  }

  if(col == 0)
  {
    return ptr_to_data[col][row];
  }

  if(col == (m_cols - 1))
  {
    return ptr_to_data[col][row-(m_rows-2)];
  }

  const int ROW_DIFF = (row - (col - 1));

  return ptr_to_data[col][ROW_DIFF];
}

template<typename T>
TriDiag<T> operator+(const TriDiag<T>& lhs, const TriDiag<T>& rhs)
{
  if(lhs.getRow() != rhs.getRow() || lhs.getCol() != rhs.getCol())
  {
    std::cerr << "Cannot add different size matrices. Tri" << std::endl;
    throw std::out_of_range("DIFFERENT SIZE MATRICES CANNOT ADD; TRI");
  }

  TriDiag<T> temp(lhs.getRow(), lhs.getCol());

  for(int i = 0; i < lhs.getCol(); i++)
  {
    temp[i] = lhs[i] + rhs[i];
  }

  return temp;
}

template<typename T>
TriDiag<T> operator-(const TriDiag<T>& lhs, const TriDiag<T>& rhs)
{
  if(lhs.getRow() != rhs.getRow() || lhs.getCol() != rhs.getCol())
  {
    std::cerr << "Cannot sub different size matrices. Tri" << std::endl;
    throw std::out_of_range("DIFFERENT SIZE MATRICES CANNOT SUB; TRI");
  }

  TriDiag<T> temp(lhs.getRow(), lhs.getCol());

  for(int i = 0; i < lhs.getCol(); i++)
  {
    temp[i] = lhs[i] - rhs[i];
  }

  return temp;
}


template<typename T>
vector<T> operator*(const TriDiag<T>& lhs, const vector<T>& rhs)
{
  if(lhs.getRow() != rhs.getSize())
  {
    throw std::out_of_range("VECTOR SIZE AND TRI ROW DO NOT MATCH");
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
std::ostream& operator<<(std::ostream& out, const TriDiag<T>& m)
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