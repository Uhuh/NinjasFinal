/**
  * @file   solver.hpp
  * @author Dylan Warren, Section A
  * @brief  Defines the () operator to solve a system of equations
*/
#include <limits>
#include <cmath>

template<typename T>
vector<T> GaussianSolver<T>::operator()(const DenseMatrix<T>& source,
                                               const vector<T>& B) const
{
  DenseMatrix<T> augMatrix;
  try
  {
    augMatrix = makeAug(source, B);
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  vector<T> x(augMatrix.getRow());
  vector<T> rowVector(augMatrix.getCol()); // Helps make swapping rows easy
  vector<T> scale_factor(augMatrix.getRow());
  vector<T> ratio_vector(augMatrix.getRow());

  // Time to fill out the scale factor
  for(int i = 0; i < augMatrix.getCol() - 1; i++)
  {
    T maxValue = std::numeric_limits<T>::lowest();
    for(int j = 0; j < augMatrix.getRow(); j++)
    {
      if(std::abs(augMatrix[j][i]) > maxValue)
      {
        maxValue = std::abs(augMatrix[j][i]);
      }
    }
    scale_factor[i] = maxValue;
    maxValue = std::numeric_limits<T>::lowest();
  }

  for(int i = 0; i < augMatrix.getRow(); i++)
  {
    int index = 0;
    //Calculate ratio vector
    for(int k = 0; k < scale_factor.getSize(); k++)
    {
      ratio_vector[k] = std::abs(augMatrix[i][k]) / scale_factor[k];
    }

    // This index determines the "highest" level rows can swap with.
    index = maxIndex(ratio_vector, i);

    for(int col = 0; col < augMatrix.getCol(); col++)
    {
      rowVector[col] = augMatrix[col][i];
    }
    // Swap rows
    if((index - i) != 0)
    { 
      for(int col = 0; col < augMatrix.getCol(); col++)
      {
        augMatrix[col][i] = augMatrix[col][index];
        augMatrix[col][index] = rowVector[col];
      }
      // Since our "top" rowVector changed have to adjust for the new top vec.
      for(int col = 0; col < augMatrix.getCol(); col++)
      {
        rowVector[col] = augMatrix[col][i];
      }
    }

    for(int j = i + 1; j < augMatrix.getRow(); j++)
    {
      double co_ef;
      co_ef = augMatrix[i][j] / rowVector[i];

      for(int col = i; col < augMatrix.getCol(); col++)
      {
        augMatrix[col][j] -= co_ef * rowVector[col];
        if(augMatrix[col][j] < EPSILON && augMatrix[col][j] > -EPSILON)
        {
          augMatrix[col][j] = 0;
        }
      }
    }
  }

  for(int i = augMatrix.getRow() - 1; i >= 0; i--)
  {
    double sum = 0;
    double sumCheck = 0;
    for(int j = i + 1; j <= augMatrix.getRow() - 1; j++)
    {
      sum += augMatrix[j][i] * x[j];
    }
    sum = augMatrix[augMatrix.getCol()-1][i] - sum;
    sumCheck = sum / static_cast<double>(augMatrix[i][i]);
    x[i] = ((sumCheck < EPSILON && sumCheck > -EPSILON) ? 0 : sumCheck);
  }

  return x;
}

template<typename T>
vector<T> GaussianSolver<T>::operator()(const UpperTriangle<T>& source,
                                        const vector<T>& B) const
{
  if(source.getRow() != B.getSize())
  {
    std::cerr << "Upper row size does not match vector size" << std::endl;
    throw std::out_of_range("Upper row size does not match vector size");
  }

  vector<T> x(source.getRow());

  for(int i = source.getRow() - 1; i >= 0; i--)
  {
    double sum = 0;
    double sumCheck = 0;
    for(int j = i + 1; j <= source.getRow() - 1; j++)
    {
      sum += source(j, i) * x[j];
    }
    sum = B[i] - sum;
    sumCheck = sum / static_cast<double>(source(i, i));
    x[i] = ((sumCheck < EPSILON && sumCheck > -EPSILON) ? 0 : sumCheck);
  }

  return x;
}

template<typename T>
vector<T> GaussianSolver<T>::operator()(const LowerTriangle<T>& source,
                                        const vector<T>& B) const
{
  if(source.getRow() != B.getSize())
  {
    std::cerr << "Upper row size does not match vector size" << std::endl;
    throw std::out_of_range("Upper row size does not match vector size");
  }

  vector<T> x(source.getRow());

  for(int i = 0; i < source.getRow(); i++)
  {
    double sum = 0;
    double sumCheck = 0;
    for(int j = 0; j < i; j++)
    {
      sum += source(j, i) * x[j];
    }
    sum = B[i] - sum;
    sumCheck = sum / static_cast<double>(source(i, i));
    x[i] = ((sumCheck < EPSILON && sumCheck > -EPSILON) ? 0 : sumCheck);
  }

  return x;
}

template<typename T>
vector<T> GaussianSolver<T>::operator()(const SymMatrix<T>& source,
                                        const vector<T>& B) const
{
  if(source.getRow() != B.getSize())
  {
    std::cerr << "Sym row size does not match vector size" << std::endl;
    throw std::out_of_range("SYM ROW SIZE DOES NOT MATCH VECTOR SIZE");
  }

  LowerTriangle<T> temp(source.getRow(), source.getCol());

  for(int k = 0; k < source.getRow(); k++)
  {
    for(int i = 0; i <= k; i++)
    {
      if(k != i)
      {
        if(temp(i, i) == 0)
        {
          std::cerr << "Trying to divide by zero" << std::endl;
          throw std::out_of_range("TRIED TO DIVIDE BY 0");
        }
        double sum = 0;
        for(int j = 0; j < i; j++)
        {
          sum += temp(j, i) * temp(j, k);
        }
        temp(i, k) = (source(i, k) - sum) / temp(i, i);
      }
      else
      {
        double sum = 0;
        for(int j = 0; j < k; j++)
        {
          sum += temp(j, k) * temp(j, k);
        }
        temp(k, k) = sqrt(source(k, k) - sum);
      }
    }
  }
  
  return this->operator()(transpose(temp), this->operator()(temp, B));
}

template<typename T>
vector<T> GaussianSolver<T>::operator()(const TriDiag<T>& source, const vector<T>& B) const
{
  if(source.getRow() != B.getSize())
  {
    std::cerr << "Tri row size does not match vector size" << std::endl;
    throw std::out_of_range("TRI ROW SIZE DOES NOT MATCH VECTOR SIZE");
  }

  TriDiag<T> temp(source);
  vector<T> tempVec(B);
  vector<T> x(B.getSize());

  for(int i = 1; i < source.getRow(); i++)
  {
    // Ai = Ai/Bi-1
    temp(i - 1, i) /= temp(i - 1, i - 1);
    // Bi = Bi - Ai * Ci-1
    temp(i, i) -= temp(i - 1, i) * temp(i , i - 1);
    // Ri = Ri  Ai * Ri-1
    tempVec[i] -= temp(i - 1, i) * tempVec[i - 1];
  }

  x[x.getSize() - 1] = tempVec[x.getSize() - 1] / temp(x.getSize() -1, x.getSize() - 1);

  for(int i = source.getRow() - 2; i >= 0; i--)
  {
    x[i] = (tempVec[i] - temp(i + 1, i) * x[i + 1]) / temp(i, i);
  }

  return x;
}