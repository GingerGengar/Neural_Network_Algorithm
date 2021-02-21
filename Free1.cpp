#include <iostream>
#include <vector>	
#include "Eigen/Core"
#include "Eigen/Dense"
#include "Logging.h"
#include "GradientDescent.h"
#include "Sigmoid.h"
#include "DSigmoid.h"
#include "Compare.h"
#define CYCLELIMIT 2

//The following is proof that indeed the algorithm ouptuts the correct collection of variables.

int main(void)
{
	enum Printoption {Terminal, File, Both} PrintMode;

	std::vector<int> Dimensions = {2,3,3,2};

	int MatrixNum = Dimensions.size() - 1;
	
	std::vector<Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic>> LayerVec ,WeightVec, BiasVec, PreActVec, DLayerVec, WGradVec, BGradVec, TrainingInput, TrainingOutput;
	
	for (int i = 0; i < MatrixNum; i++)
	{
		LayerVec.emplace_back(Dimensions[i + 1], 1); //Expansion of the layers
		PreActVec.emplace_back(Dimensions[i + 1], 1); //Expansion of the pre activation layers
		DLayerVec.emplace_back(Dimensions[i + 1], 1); //Expansion of the Derivative Layer Vector
		WGradVec.emplace_back(Dimensions[i + 1], Dimensions[i]); //Weight Gradient Descent Vector
		BGradVec.emplace_back(Dimensions[i + 1], 1); //Bias Gradient Descent Vector
		WeightVec.emplace_back(Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>::Random(Dimensions[i + 1], Dimensions[i])); //Expansion and randomizing the Weights
		BiasVec.emplace_back(Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>::Random(Dimensions[i + 1], 1)); //Expansion and randomizing the Biases
	}

//Declaration of Function Specific Variables
	double ErrorStart = 0, ErrorEnd = 0; //The Error Function for multiple datas
	int TrainingSize = TrainingOutput.size(); //The size of the Each Training Cluster
	std::vector<int> ElemIndex; //Used to temporarily store the "Pathway"
	std::vector<int> MaxIndex; //The maximum allowable values for the "Pathway"

	//Declaration of Placeholder Variables of Primitive Data Types
	int WRows = 0, WCols = 0, BRows = 0, BCols = 0; //Used to temporarily store Dimensions of Matrices of Interest
	int size = 0; //Used for the sizes of ElemIndex and MaxIndex
	int Directory = 0; //Used for the Layer Directory
	int MaxPos = 0; //What is the index of 1 less from the last maximum value of the vector in a row
	bool agree = false; //Used to Determine if the Directory Vector Agree
	bool FirstTime = false;
	double Dummy = 0, DDummy = 0; //Used to Modify Each Element of Matrices

	//Loading the Training Data
	bool Secure = true;
	bool InputSuccess = false, OutputSuccess = false;

	//Machine Learning Loops
	for (int Cycles = 0; Cycles < CYCLELIMIT; Cycles++)
	{
		for (int Iteration = 0; Iteration < 2; Iteration++)
		{	
			for (int VecIndex = 0; VecIndex < MatrixNum; VecIndex++)
			{
				//For the vector containing the Weight Matrices
				WRows = WeightVec[VecIndex].rows(); //Setting Bounds for the Rows of the Matrix of interest
				WCols = WeightVec[VecIndex].cols(); //Setting Bounds for the Columns of the Matrix of interest
				
				//Setting the size of ElemIndex to be 1 less than the amount of remaining matrices left till the last layer
				size = MatrixNum - VecIndex - 1;
				
				//Resizing Both matrices to size
				ElemIndex.resize(size);
				MaxIndex.resize(size);
				
				//Setting Each Element in MaxIndex to the corresponding Dimension elements 
				for (int i = 0; i < size; i++)
				{
					ElemIndex[i] = 0;
					MaxIndex[i] = Dimensions[MatrixNum - size + 1 + i] - 1; 
				}

				//Places the Directory at the back-most end of the ElemIndex
				Directory = size - 1;

				for (int cols = 0; cols < WCols; cols++)
				{
					for (int rows = 0; rows < WRows; rows++)
					{
						//Resets the Placeholder Variables Dummy for each Matrix Element Change
						Dummy = 0;

						//Resets the ElemIndex for next element of the matrix
						for (int i = 0; i < size; i++)
						{
							ElemIndex[i] = 0; 
						}
						
						//Sets the Loop in Motion for each time the VecIndex has changed
						agree = false;
						
						//Sets the special First Time Condition
						FirstTime = false;
						
						while (!agree && (VecIndex != MatrixNum - 1))
						{
							//Conditioning that Allows "Pathway" Creation:
							Directory = size - 1; //Resetting the Directory to maximum possible for each rows and cols

							if (FirstTime)
							{
								//Setting the Directory to when the Elements of ElemIndex are no longer the same with MaxIndex
								while(ElemIndex[Directory] == MaxIndex[Directory])
									Directory--;

								//Modification of ElemIndex
								if (Directory != (size - 1))
								{
									ElemIndex[Directory]++;
									for (int i = Directory + 1; i < size; i++)
										ElemIndex[i] = 0;
								}
								else
									ElemIndex[Directory]++;
							}
							else
								FirstTime = true;

							//Resetting the Placeholder Variable DDummy whenever "Pathway" changes
							DDummy = 1;	

							Dummy += DDummy; //Stores the information produced by DDummy After Pathway Change


							//DEBUG printing
							std::cout << std::endl <<"-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << std::endl;
							std::cout << "Cycles: " << Cycles << std::endl;
							std::cout << "Iteration: " << Iteration << std::endl;
							std::cout << "VectorIndex: " << VecIndex << std::endl;
							std::cout << "Columns: " << cols << std::endl;
							std::cout << "Rows: " << rows << std::endl;
							std::cout << "ElemIndex: ";
							for (int gargoyle = 0; gargoyle < ElemIndex.size(); gargoyle++)
								std::cout << ElemIndex[gargoyle] << ", ";
							std::cout << std::endl;
							std::cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << std::endl;

							//Checking if indeed ElemIndex and MaxIndex are correct element by element
							agree = true; //Assume that the vectors now agree
							for(int i = 0; i < size; i++) //Iterating through each Element of ElemIndex
								if (MaxIndex[i] != ElemIndex[i]) //If a single element is not the same, set agree to false
									agree = false;
								
						}
					}
				}
			}
		}
	}

	std::cout  << "End of Program Reached" << std::endl;
	std::cin.get();

	return 0;
}

/*

*/ 