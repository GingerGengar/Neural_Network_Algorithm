#pragma once
#include "Eigen/Core"
#include "Eigen/Dense"
#define DESCENTSCALE 1

template <class InpType>
InpType Gradient(InpType VectorMatrix, InpType Modifier)
{
	int MatrixNum = VectorMatrix.size();
	int Rows, Cols = 0;

	for (int VecIndex = 0; VecIndex < MatrixNum; VecIndex++)
		VectorMatrix[VecIndex] -= Modifier[VecIndex] * DESCENTSCALE;

	return VectorMatrix;
}