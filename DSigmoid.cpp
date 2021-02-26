#include "MainHeader.h"

template<class datatype>
datatype Dsigmoid(datatype matrix)
{
	int rows = matrix.rows();
	int columns = matrix.cols();
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
			matrix(i,j) = exp(-matrix(i,j)) / pow((1 + exp(-matrix(i,j))), 2);

	return matrix;
}