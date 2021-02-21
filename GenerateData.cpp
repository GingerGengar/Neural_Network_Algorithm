#include <iostream>
#include <vector>
#include "Logging.cpp"
#include "Eigen/Core"
#include "Eigen/Dense"
#define SIZE 18
#define LOW 0.0001
#define HIGH 0.9999

int main(void)
{
	//Function specific variables
	int UpperBound1 = 9;
	int UpperBound2 = 9;
	int VecIndex = 0;
	int TotalElement = UpperBound1 * UpperBound2;

	//Placeholder variables
	int Dummy = 0;
	int pos1 = 0;
	int pos2 = 0;

	//Declaration of vector whose elements are matrices forming the training data
	std::vector<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>> Inputs;
	std::vector<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>> Outputs;

	for (int i = 0; i < TotalElement; i++)
	{
		Inputs.emplace_back(SIZE,1);
		Outputs.emplace_back(SIZE + 2,1);
	}

	for (int num1 = 1; num1 <= UpperBound1; num1++)
		for (int num2 = 1; num2 <= UpperBound2; num2++)
		{
			//Setting All Elements to low first
			for (int i = 0; i < SIZE; i++)
				Inputs[VecIndex](i, 0) = LOW;
			
			for (int i = 0; i < SIZE + 2; i++)
				Outputs[VecIndex](i, 0) = LOW;

			//Setting the Input vectors
			Inputs[VecIndex](num1 - 1, 0) = HIGH;
			Inputs[VecIndex](SIZE / 2 + num2 - 2, 0) = HIGH;

			//Processing
			Dummy = num1 * num2;
			pos1 = (Dummy % 10);
			pos2 = ((Dummy - (Dummy % 10)) / 10);
	
			//Setting the Output vectors
			Outputs[VecIndex](pos1, 0) = HIGH;
			Outputs[VecIndex](pos2, 0) = HIGH;

			VecIndex++;
		}

	//Logging Into Files
	enum Printoption {Terminal, File, Both} PrintMode; //For printing options
	PrintMode = File; //Printing to Files
	Print<std::vector<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>>>(Inputs, PrintMode, true, Inputs[0].rows(), std::string("TrainingInput.txt"));
	Print<std::vector<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>>>(Inputs, PrintMode, true, Outputs[0].rows(), std::string("TrainingOutput.txt"));

	//Customary End to the Program
	std::cout << "End of GenerateData.cpp reached..." << std::endl;
	std::cin.get();
	
	return 0;
}