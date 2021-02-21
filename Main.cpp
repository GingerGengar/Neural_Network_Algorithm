#pragma once
#include <iostream>
#include <vector>
#include "Eigen/Core"
#include "Eigen/Dense"
#include "Logging.cpp"
#include "LoggingInv.cpp"
#include "Perform.cpp"
#include "Compare.cpp"
#include "Learn.cpp"
#define DEBUG 0

int main()
{
	//Dimensions hold the mapping of the vectors. The first element is dimension of the input vector meanwhile the last element is dimension of the output vectors. The elements in between the first and last element are the represent dimension of hidden layers 
	std::vector<int> Dimensions = {2,6,6,6,2};

	//Enumeration for what is the objective of the current code
	enum OperationMode {DoNothing ,Normal, Training} Operation;

	Operation = Normal; //Delete this later

	//User Input Reading
	
	//Enumeration for the type of printing
	enum Printoption {Terminal, File, Both} PrintMode;

	//The number of transformation matrices exist to map each hidden layers to each other
	int MatrixNum = Dimensions.size() - 1;

	//Declaration of vector types containing matrices of dynamic sizes. LayerVec is for containing the activations of the neurons in each layer. WeightVec contains the transformation matrices that map one layer to the other layers. BiasVec contains the bias vectors that is applied to the layers before the function is applied. PreActVec contains the pre activation values of the layer vector before function has been applied. WGradVec is a placeholder that is used to alter the weightVec during Gradient Descent. BGradVec is a palceholdler that is used to alter the BiasVec during the Gradient Descent.  
	std::vector<Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic>> LayerVec ,WeightVec, BiasVec, PreActVec, DLayerVec, WGradVec, BGradVec, WGradVecfin, BGradVecfin, TrainingInput, TrainingOutput;

	//Declaration of a vector type containing pointers pointing towards the vectors reprsented above. Each element of LayerPoint are pointers to the element LayerVec, WeightPoint to WeightVec, BiasPoint to BiasVec, PreActPoint to PreActVec, WGradPoint to WGradVec, BGradPoint to BGradVec.   
	std::vector<Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic> * > LayerPoint, WeightPoint, BiasPoint, PreActPoint, DLayerPoint, WGradPoint, BGradPoint, TrInPoint, TrOutPoint;

	//Expanding the vector and allocating new matrices produced on heap memory as well as initializing all biases and weights to random values.
	for (int i = 0; i < MatrixNum; i++)
	{
		LayerVec.emplace_back(Dimensions[i + 1], 1); //Expansion of the layers
		WeightVec.emplace_back(Dimensions[i + 1], Dimensions[i]); //Expansion and randomizing the Weights
		BiasVec.emplace_back(Dimensions[i + 1], 1); //Expansion and randomizing the Biases
		PreActVec.emplace_back(Dimensions[i + 1], 1); //Expansion of the pre activation layers
		DLayerVec.emplace_back(Dimensions[i + 1], 1); //Expansion of the Derivative Layer Vector
		WGradVec.emplace_back(Dimensions[i + 1], Dimensions[i]); //Weight Gradient Descent Vector
		BGradVec.emplace_back(Dimensions[i + 1], 1); //Bias Gradient Descent Vector
		WGradVecfin.emplace_back(Dimensions[i + 1], Dimensions[i]); //Weight Gradient Descent Vector
		BGradVecfin.emplace_back(Dimensions[i + 1], 1); //Bias Gradient Descent Vector
	}

	//For loop that sets the pointers to point towards the weights and biases
	for (int j = 0; j < MatrixNum; j++)
	{
		LayerPoint.emplace_back(&LayerVec[j]); //Expansion of the pointers towards the Layers
		WeightPoint.emplace_back(&WeightVec[j]); //Expansion of the pointers towards the Weights
		BiasPoint.emplace_back(&BiasVec[j]); //Expansion of the pointers towards the Biases
		PreActPoint.emplace_back(&PreActVec[j]); //Expansion of the pointers towards pre-activation
		DLayerPoint.emplace_back(&DLayerVec[j]); //Expansion of the pointer towards Derivative LayerVector
		WGradPoint.emplace_back(&WGradVec[j]); //Expansion of the pointers towards Weight Gradient Descent Vector
		BGradPoint.emplace_back(&BGradVec[j]);	//Expansion of the pointers towards the Bias Gradient Descent Vector
	}

	//Training Data Validation
	int LengthTraining; //The length of the training Data
	bool VerifTrain = Compare(std::string("TrainingInput.txt"), std::string("TrainingOutput.txt"), Dimensions, &LengthTraining); //Assume that the training files provided have no problem with them first
	

	//Expanding vector for the Training Inputs and Outputs. They have different lengths than the other vector matrices.
	for (int i = 0; i < LengthTraining; i++)
	{
		TrainingInput.emplace_back(Dimensions[0], 1);
		TrainingOutput.emplace_back(Dimensions[MatrixNum], 1);
	}

	//Expanding vector pointer for the Training Inputs and Outputs. Needing Seperate Loop to expand Pointers
	for (int j = 0; j < LengthTraining; j++)
	{
		TrInPoint.emplace_back(&TrainingInput[j]);
		TrOutPoint.emplace_back(&TrainingOutput[j]);
	}

	//Loading Previous Weights and Biases Data
	bool Secure = false;
	bool FileFlagW = false, FileFlagB = false;
	WeightVec = FileRead<std::vector<Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic>>>(Dimensions, WeightVec, std::string("Weight_Matrices.txt"), std::string("Layer_Dimensions.txt"), Secure, &FileFlagW, std::string("Loading Initial Weight Matrices")); //FileFlagW would be false if the WeightVec Data is not fetched properly
	BiasVec = FileRead<std::vector<Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic>>>(Dimensions, BiasVec, std::string("Bias_Vectors.txt"), std::string("Layer_Dimensions.txt"), Secure, &FileFlagB, std::string("Loading Initial Bias Matrices")); //FileFlagB would be false if the BiasVec Data is not fetched properly

	switch(Operation)
	{
		case Normal:
		//Printing Status of Data Loading and then Running Operations if Data is Valid
		if(FileFlagW && FileFlagB)
		{
			std::cout << "Weights and Biases Data Succesfully Loaded..." << std::endl;
			//Function call for Perform. This function 
			Perform <std::vector<Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic>>>(LayerVec, WeightVec, BiasVec, Dimensions);
		}
		else
			std::cout << "Weights and Biases Data Failed Loading, Please Generate Data Prior to Performing Mode..." << std::endl;
		
		break;
		case Training:
		//Printing Status of Data Loading
		if(FileFlagW && FileFlagB)
			std::cout << "Weights and Biases Data Succesfully Loaded..." << std::endl;
		else
		{
			std::cout << "Weights and Biases Data Failed Loading, Generating New Data..." << std::endl;
			for(int i = 0; i < MatrixNum; i++)
			{
				WeightVec[i] = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>::Random(Dimensions[i + 1], Dimensions[i]); //Expansion and randomizing the Weights
				BiasVec[i] = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>::Random(Dimensions[i + 1], 1); //Expansion and randomizing the Biases
			}
		}
		
		//Function call for the Learn function. The Learn Function uses pre-generated data when the data is valid. If not, it will generate its own data
		if (VerifTrain)
			Learn <std::vector<Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic>>>(LayerVec, WeightVec, BiasVec, PreActVec, DLayerVec, WGradVec, BGradVec, WGradVecfin, BGradVecfin, TrainingInput, TrainingOutput, Dimensions);
		else
			std::cout << "The Training Data has Errors. Training Interrupted..." << std::endl;
		break;
	}

	//Freeing Previously Declared Pointers

	//Customary End to Program
	std::cout << std::endl << "When the sun rises in the east and sets in the west..." << std::endl;
	std::cin.get();

	return 0;
}


/*
	PrintMode = Terminal;
	Print<std::vector<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>>>(WeightVec, PrintMode, std::string("Ignore this crap"));


	int size = WeightPoint.size();
	for(int i = 0; i < size; i++)
			std::cout << std::endl << "Element: "<< i << std::endl << *WeightPoint[i] << std::endl;
*/