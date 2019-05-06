template<typename T>
const vector<T>& DiagMatrix<T>::operator[](const int index) const
{
  if(index < 0 || index >= m_cols)
  {
    std::cerr << "Bad index, out of bounds" << std::endl;
    throw std::out_of_range("OUT OF BOUNDS []");
  }

  return ptr_to_data[index];
}

template<typename T>
DiagMatrix<T>::DiagMatrix(const int r, const int c)
{
  if(r <= 0 || c <= 0)
  {
    std::cerr << "Row or Col less than 0; Diag" << std::endl;
    throw std::out_of_range("CANNOT COSNTRUCT DIAG WITH NEGATIVE BOUNDS");
  }

  m_rows = r;
  m_cols = c;

  ptr_to_data = vector<vector<T>>(m_cols);

  for(int i = 0; i < m_cols; i++)
  {
    ptr_to_data[i] = vector<T>(1);
  }
}

template<typename T>
T DiagMatrix<T>::operator()(const int col, const int row) const
{
  if(col < 0 || row < 0 || col >= m_cols || row >= m_rows)
  {
    std::cerr << "Tried to access out of bounds; Diag" << std::end;
    throw std::out_of_range("CANNOT ACCESS OUT OF BOUNDS; DIAG");
  }

  if(col != row)
  {
    return 0;
  }

  return ptr_to_data[col][0];
}

template<typename T>
T& DiagMatrix<T>::operator()(const int col, const int row)
{
  if(col < 0 || row < 0 || col >= m_cols || row >= m_rows)
  {
    std::cerr << "Tried to access out of bounds; Diag" << std::end;
    throw std::out_of_range("CANNOT ACCESS OUT OF BOUNDS; DIAG");
  }

  if(col != row)
  {
    std::cerr << "Trying to change diag 0 value" << std::endl;
    throw std::out_of_range("CANNOT CHANGE DIAGS 0 VALUES");
  }

  return ptr_to_data[col][0];
}

template<typename T>
DiagMatrix<T> operator+(const DiagMatrix<T>& lhs,
                        const DiagMatrix<T>& rhs)
{
  if(lhs.getRow() != rhs.getRow() || lhs.getCol() != rhs.getCol())
  {
    std::cerr << "Cannot add two mismatched diagmatrixs" << std::endl;
    throw std::out_of_range("MISMATCHED SIZE DIAGMATRICES");
  }

  DiagMatrix<T> temp(lhs.getCol(), lhs.getRow());

  const int col = lhs.getCol();

  for(int i = 0; i < col; i++)
  {
    temp(i, i) = lhs(i, i) + rhs(i, i);
  }

  return temp;
}

template<typename T>
DiagMatrix<T> operator-(const DiagMatrix<T>& lhs,
                        const DiagMatrix<T>& rhs)
{
  if(lhs.getRow() != rhs.getRow() || lhs.getCol() != rhs.getCol())
  {
    std::cerr << "Cannot subtract two mismatched diagmatrixs" << std::endl;
    throw std::out_of_range("MISMATCHED SIZE DIAGMATRICES");
  }

  DiagMatrix<T> temp(lhs.getCol(), lhs.getRow());

  const int col = lhs.getCol();

  for(int i = 0; i < col; i++)
  {
    temp(i, i) = lhs(i, i) - rhs(i, i);
  }

  return temp;
}

template<typename T>
DiagMatrix<T> operator*(const DiagMatrix<T>& lhs,
                        const DiagMatrix<T>& rhs)
{
  if(lhs.getRow() != rhs.getRow() || lhs.getCol() != rhs.getCol())
  {
    std::cerr << "Cannot multiply two mismatched diagmatrixs" << std::endl;
    throw std::out_of_range("MISMATCHED SIZE DIAGMATRICES");
  }

  DiagMatrix<T> temp(lhs.getCol(), lhs.getRow());

  const int col = lhs.getCol();

  for(int i = 0; i < col; i++)
  {
    temp(i, i) = lhs(i, i) * rhs(i, i);
  }

  return temp;
}