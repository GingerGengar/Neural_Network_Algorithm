#pragma once
#include <iostream>
#include <vector>
#include "Logging.cpp"
#include "Eigen/Core"
#include "Eigen/Dense"
#include "LoggingInv.cpp"
#include "GradientDescent.cpp"
#include "Sigmoid.cpp"
#include "DSigmoid.cpp"
#define CYCLELIMIT 100000

/*
Function Header: Learn
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
General Purpose: It allows the neural network to find biases and weights that is optimal for the thousands of cycles it is assigned to. After finding the optimal weights and biases after its pre assigned cycle limit, it will then output its findings into the files.
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
Input Parameters: 7 inputs. LayerVec represents a standard vector containing the neuron activations for all the hidden layers of the neural network. WeightVec represents a standard vector containing all of the Weights needed for the neural network. BiasVec is a standard vector containing all the bias vectors that is applied before passing through the Function, either sigmoid, RElU or some other type. PreActVec represents the Data held inside LayerVec but before it is passed through the sigmoid function. PreActVec is the standard vector containing pre activation neurons. WGradVec is a placeholder standard vector the same size with WeightVec but contains the information that is the gradient of the Weights. BGradVec is a standard vector the same size with BiasVec, but contains the information that is the gradient of the Biases. 
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
Output Parameters: Void Function
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
Dependencies: "Sigmoid.h", "DSigmoid.h"
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
Example of Function Call: Learn <std::vector<Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic>>>(LayerVec, WeightVec, BiasVec, PreActVec, WGradVec, BGradVec, Dimensions);
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
*/


template <class datatype>
void Learn(datatype LayerVec, datatype WeightVec, datatype BiasVec, datatype PreActVec, datatype DLayerVec, datatype WGradVec, datatype BGradVec, datatype WGradVecfin, datatype BGradVecfin, datatype TrainingInput, datatype TrainingOutput, std::vector<int> Dimensions)
{
	//Enumeration for the type of printing
	enum Printoption {Terminal, File, Both} PrintMode;	
	
	//Declaration of Function Specific Variables
	int MatrixNum = Dimensions.size() - 1; //The Size of how many Transformation Matrices that Exist
	int TrainingSize = TrainingOutput.size(); //The size of the Each Training Cluster
	std::vector<int> ElemIndex; //Used to temporarily store the "Pathway"
	std::vector<int> MaxIndex; //The maximum allowable values for the "Pathway"

	std::cout << "Training Size: " << TrainingSize << std::endl; //DEBUG
	
	//Declaration of Placeholder Variables of Primitive Data Types
	int WRows = 0, WCols = 0, BRows = 0, BCols = 0; //Used to temporarily store Dimensions of Matrices of Interest
	int size = 0; //Used for the sizes of ElemIndex and MaxIndex
	int Directory = 0; //Used for the Layer Directoryam
	int MaxPos = 0; //What is the index of 1 less from the last maximum value of the vector in a row
	bool agree = false; //Used to Determine if the Directory Vector Agree
	bool FirstTime = false;
	double Dummy = 0, DDummy = 0; //Used to Modify Each Element of Matrices

	//Loading the Training Data
	bool Secure = true;
	bool InputSuccess = false, OutputSuccess = false;
	
	TrainingInput = FileRead<std::vector<Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic>>>(Dimensions, TrainingInput, std::string("TrainingInput.txt"), std::string("Layer_Dimensions.txt"), Secure, &InputSuccess, std::string("Learning, Training Inputs"));
	TrainingOutput = FileRead<std::vector<Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic>>>(Dimensions, TrainingOutput, std::string("TrainingOutput.txt"), std::string("Layer_Dimensions.txt"), Secure, &OutputSuccess, std::string("Learning, Training Outputs"));
	
	if (InputSuccess && OutputSuccess)
	{
		std::cout << "Training Inputs and Outputs Succesfully Loaded..." << std::endl;
		
		//Machine Learning Loops
		for (int Cycles = 0; Cycles < CYCLELIMIT; Cycles++)
		{
			//Setting The Gradient Descent Vector Matrices for Weights and Biases to zero
			for (int i = 0; i < MatrixNum; i++)
			{
				WGradVec[i] = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>::Zero(WGradVec[i].rows(), WGradVec[i].cols());
				BGradVec[i] = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>::Zero(BGradVec[i].rows(), BGradVec[i].cols()); 
			}

			for (int Iteration = 0; Iteration < TrainingSize; Iteration++)
			{	
				//For the first hidden Layer
				PreActVec[0] = WeightVec[0] * TrainingInput[Iteration] + BiasVec[0];
				LayerVec[0] = sigmoid<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>> (PreActVec[0]);
				DLayerVec[0] = Dsigmoid<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>> (PreActVec[0]);

				//For Subsequent Hidden Layers until the Last Layer which is Output Layer
				for (int i = 1; i < MatrixNum; i++)
				{
					PreActVec[i] = WeightVec[i] * LayerVec[i - 1] + BiasVec[i];
					LayerVec[i] = sigmoid<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>> (PreActVec[i]);
					DLayerVec[i] = Dsigmoid<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>> (PreActVec[i]);
				}

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

							//Resets the Placeholder Variable DDummy for each Matrix Element Change
							DDummy = 1;

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

								//The activation gradient, multiplied with the weights across the different layers
								for (int i = 0; i < size; i++)
								{
									if (i == 0)
										DDummy = DDummy * DLayerVec[VecIndex + i](rows, 0);
									else
										DDummy = DDummy * DLayerVec[VecIndex + i](ElemIndex[i - 1], 0);
									
									if (i == (size - 1)) //For the layer at the output
									{
										DDummy = DDummy * 2 * (LayerVec[MatrixNum - 1](ElemIndex[size - 1], 0) - TrainingOutput[Iteration](ElemIndex[size - 1], 0));
									}	
									else
									{
										if (i == 0)
											DDummy = DDummy * WeightVec[VecIndex + 1 + i](ElemIndex[i], rows);	
										else
											DDummy = DDummy * WeightVec[VecIndex + 1 + i](ElemIndex[i], ElemIndex[i - 1]);
									}	
								}	

								Dummy += DDummy; //Stores the information produced by DDummy After Pathway Change

								//Checking if indeed ElemIndex and MaxIndex are correct element by element
								agree = true; //Assume that the vectors now agree
								for(int i = 0; i < size; i++) //Iterating through each Element of ElemIndex
									if (MaxIndex[i] != ElemIndex[i]) //If a single element is not the same, set agree to false
										agree = false;
									
							}

							//For the case that ElemIndex is not clearly defined
							if (VecIndex == MatrixNum - 1)
							{
								DDummy = DDummy * DLayerVec[VecIndex](rows, 0);
								DDummy = DDummy * 2 * (LayerVec[VecIndex](rows, 0) - TrainingOutput[Iteration](rows, 0));
								Dummy = DDummy;
							}

							//Storing the Information prior to multiplication with activation to the Bias Gradient Descent vector
							BGradVec[VecIndex](rows, 0) = Dummy;

							//Multiplying Dummy to the activation to make the value of Dummy Correct for WeightVec
							if (VecIndex == 0) //For the case of taking the activation from the TrainingInputs
								Dummy = Dummy * TrainingInput[Iteration](cols, 0);
							else //For the case of taking the activation from the Layervectors
								Dummy = Dummy * LayerVec[VecIndex - 1](cols, 0);

							//Storing the Infromation of Dummy into gradient descent vector 
							WGradVec[VecIndex](rows, cols) = Dummy;
						}
					}
				}

				//Storing the Gradients over multiple training examples as a summation of each example
				for (int i = 0; i < MatrixNum; i++)
				{
					WGradVecfin[i] += WGradVec[i];
					BGradVecfin[i] += BGradVec[i];
				}	
			}
			//Dividing, so that WGradVec and BGradVec contains averages
			for (int j = 0; j < MatrixNum; j++)
			{
				WGradVecfin[j] /= TrainingSize;
				BGradVecfin[j] /= TrainingSize;
			}

			//Performing Gradient Descent
			WeightVec = Gradient<std::vector<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>>>(WeightVec, WGradVecfin);
			BiasVec = Gradient<std::vector<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>>>(BiasVec, BGradVecfin);
		}
	}
	else
		std::cout << "Training Inputs and Outputs Failed Loading, Results are not Valid..." << std::endl; 

	//Logging the Learning Data into Files
	PrintMode = Both;
	Secure = false;
	Print <std::vector<int>> (Dimensions,PrintMode, Secure, 0, std::string("Layer_Dimensions.txt"));
	Print<std::vector<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>>>(WeightVec, PrintMode, Secure, 0, std::string("Weight_Matrices.txt"));
	Print<std::vector<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>>>(BiasVec, PrintMode, Secure, 0, std::string("Bias_Vectors.txt"));

	PrintMode = Terminal;
	Print<std::vector<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>>>(BGradVec, PrintMode, Secure, 0, std::string("BGradVec"));
	Print<std::vector<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>>>(WGradVec, PrintMode, Secure, 0, std::string("WGradVec"));
	Print<std::vector<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>>>(LayerVec, PrintMode, Secure, 0, std::string("LayerVec: "));
	Print<std::vector<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>>>(PreActVec, PrintMode, Secure, 0, std::string("PreActVec:"));
	Print<std::vector<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>>>(TrainingInput, PrintMode, Secure, 0, std::string("TrainingInput:"));
	Print<std::vector<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>>>(TrainingOutput, PrintMode, Secure, 0, std::string("TrainingOutput:"));
	
	return;
}

/*
	//DEBUG
	PrintMode = Terminal;
	Print<std::vector<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>>>(BGradVec, PrintMode, std::string("BGradVec"));
	Print<std::vector<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>>>(WGradVec, PrintMode, std::string("WGradVec"));
	Print<std::vector<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>>>(LayerVec, PrintMode, std::string("LayerVec: "));
	Print<std::vector<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>>>(PreActVec, PrintMode, std::string("PreActVec:"));
	Print<std::vector<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>>>(TrainingInput, PrintMode, std::string("TrainingInput:"));
	Print<std::vector<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>>>(TrainingOutput, PrintMode, std::string("TrainingOutput:"));
*/