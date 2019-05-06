/**
  * @file   solver.h
  * @author Dylan Warren, Section A
  * @brief  The solver class is a "functor" class, it has a single funct
            to solve a system of equations.
*/
/**
  * @class  GaussianSolver
  * @brief  GaussianSolver finds the x vector in a system of equations
*/
#ifndef SOLVER_H
#define SOLVER_H
/** Numbers can get tiny and it's basically 0 at that point */
#define EPSILON 0.00000001
#include "./dense.h"
#include "./upper.h"
#include "./lower.h"
#include "./symmetric.h"
#include "./tridiagonal.h"

template<class T>
class GaussianSolver
{
  public:
    /**
      * @brief   Solves the system of equations for the x vector by using the
                scaled partial pivoting method to make an upper triangle matrix
                that then determines the x vector from.
      * @pre     None
      * @post    None
      * @param   source - Matrix "A" in the equation
      * @param   B - Vector "B" in the equation
      * @return  the solved x vector
    */
    vector<T> operator()(const DenseMatrix<T>& source, const vector<T>& B) const;
    /**
      * @brief   Solves for x vector by back substituting
      * @pre     None
      * @post    None
      * @param   source - Matrix "A" in the equation
      * @param   B - Vector "B" in the equation
      * @return  The solved x vector
    */
    vector<T> operator()(const UpperTriangle<T>& source, const vector<T>& B) const;
    /**
      * @brief   Solves for x vector by back substituting
      * @pre     None
      * @post    None
      * @param   source - Matrix "A" in the equation
      * @param   B - Vector "B" in the equation
      * @return  The solved x vector
    */
    vector<T> operator()(const LowerTriangle<T>& source, const vector<T>& B) const;
    /**
      * @brief   Solves for x vector by using the Cholesky algo
      * @pre     None
      * @post    None
      * @param   source - Matrix "A" in the equation
      * @param   B - Vector "B" in the equation
      * @return  The solved x vector
    */
    vector<T> operator()(const SymMatrix<T>& source, const vector<T>& B) const;
    /**
      * @brief   Solves for x vector by using the Thomas Algo
      * @pre     None
      * @post    None
      * @param   source - Matrix "A" in the equation
      * @param   B - Vector "B" in the equation
      * @return  The solved x vector
    */
    vector<T> operator()(const TriDiag<T>& source, const vector<T>& B) const;
};

#include "./solver.hpp"

#endif