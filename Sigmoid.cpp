#pragma once
#include <iostream>
#include <math.h>
#include <vector>
#include "Eigen/Core"
#include "Eigen/Dense"
#include "Logging.cpp"

template<class datatype>
datatype sigmoid(datatype matrix)
{
	int rows = matrix.rows();
	int columns = matrix.cols();
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
			matrix(i,j) = 1 / (1 + exp(-matrix(i,j)));

	return matrix;
}