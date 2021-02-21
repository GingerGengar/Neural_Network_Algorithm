#pragma once
#include <iostream>
#include <vector>
#include "Eigen/Core"
#include "Eigen/Dense"
#include "Sigmoid.cpp"
#include "Logging.cpp"

template <class datatype>
void Perform(datatype LayerVec, datatype WeightVec, datatype BiasVec, std::vector<int> Dimensions)
{
	//Input Initialization
	Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> Input (Dimensions[0], 1);

	//The total Number of Transformations expected in total since Input to Output
	int IterNum = Dimensions.size() - 1;

	int Continue = 1; //For continued operation or not

	std::cout << "Begin Normal Operation Mode" << std::endl;
	while(Continue)
	{
		//User Input:
		for (int j = 0; j < Dimensions[0]; j++)
		{
			std::cout << "Input " << j + 1 << ": ";
			std::cin >> Input(j,0);
		}

		//For the Transformation from the Input to the first Hidden Layer
		LayerVec[0] =  sigmoid <Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>> (WeightVec[0] * Input + BiasVec[0]);

		//For the hidden layers
		for (int i = 1; i < IterNum; i++)
		LayerVec[i] = sigmoid <Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>> (WeightVec[i] * LayerVec[i - 1] + BiasVec[i]);

		//Print Results of Neural Network
		std::cout << "Results: " << std::endl;
		std::cout << LayerVec[IterNum - 1] << std::endl; 

		//User Exit Option
		std::cout << "Continue? (0 = No, 1 = Yes) ";
		std::cin >> Continue;
	} 

	return;
}