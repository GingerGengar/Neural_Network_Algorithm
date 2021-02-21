#pragma once
#include <iostream>
#include <vector>
#include "Logging.h"
#include "Eigen/Core"
#include "Eigen/Dense"
#include "LoggingInv.h"
#define DESCENTPOWER 2

template <class datatype>
void Learn(datatype LayerVec, datatype WeightVec, datatype BiasVec, datatype PreActVec, datatype WGradVec, datatype BGradVec, std::vector<int> Dimensions)
{
	//Enumeration for the type of printing
	enum Printoption {Terminal, File, Both} PrintMode;	
	
	//Declaration of Function Specific Variables
	int MatrixNum = Dimensions.size() - 1;

	//Declaration of Placeholder Variables of Primitive Data Types
	int WRows, WCols, BRows, BCols = 0; //Used to temporarily store Dimensions of Matrices of Interest
	int size = 0; //Used for the sizes of ElemIndex and MaxIndex
	int Directory = 0; //Used for the Layer Directory
	int MaxPos = 0; //What is the index of 1 less from the last maximum value of the vector in a row
	bool agree = false; //Used to Determine if the Directory Vector Agree
	double Dummy, DDummy = 0; //Used to Modify Each Element of Matrices
	std::vector<int> ElemIndex; //Used to temporarily store the "Pathway"
	std::vector<int> MaxIndex; //The maximum allowable values for the "Pathway"

	//Main Body
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
			MaxIndex[i] = Dimensions[MatrixNum - size + 1 + i]; 
		}

		//Places the Directory at the back-most end of the ElemIndex
		Directory = size - 1;

		//Special Case for the first one, wherein ElemIndex is {1,1,1...1}, Part of construction

		PrintMode = Terminal; // Delete this
		
		for (int cols = 1; cols <= WCols; cols++)
			for (int rows = 1; rows <= WRows; rows++)
			{
				//Resets the ElemIndex for next element of the matrix
				for (int i = 0; i < size; i++)
				{
					ElemIndex[i] = 1; 
				}
				
				//Sets the Loop in Motion for each time the VecIndex has changed
				agree = false;
				
				while (!agree && (VecIndex != MatrixNum - 1))
				{
					//Conditioning that Allows "Pathway" Creation
					Directory = size - 1;
					while(ElemIndex[Directory] == MaxIndex[Directory])
					{
						Directory--;
					}
					if (Directory != (size - 1))
					{
						ElemIndex[Directory]++;
						for (int i = Directory + 1; i < size; i++)
							ElemIndex[i] = 1;
					}
					else
					{
						ElemIndex[Directory]++;
					}

					//Part of Construction:
					std::cout << "Directory: " << Directory << std::endl;
					Print <std::vector<int>> (ElemIndex,PrintMode, std::string("ElemIndex"));
					Print <std::vector<int>> (MaxIndex,PrintMode, std::string("MaxIndex"));

					agree = true; //Assume that the vectors now agree
					for(int i = 0; i < size; i++) //Iterating through each Element of ElemIndex
						if (MaxIndex[i] != ElemIndex[i]) //If a single element is not the same, set agree to false
						{
							agree = false;
						}
				}
				std::cout <<"Jump Achieved" << std::endl;
			}
	}






	//Logging the Learning Data into Files
	PrintMode = File;
	Print <std::vector<int>> (Dimensions,PrintMode, std::string("Layer_Dimensions.txt"));
	Print<std::vector<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>>>(WeightVec, PrintMode, std::string("Weight_Matrices.txt"));
	Print<std::vector<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>>>(BiasVec, PrintMode, std::string("Bias_Vectors.txt"));

	return;
}

/*
while (!agree)
				{

					//DEBUG
					//for(int i = 0; i < ElemIndex.size(); i++)
					//	std::cout << "Index: " << i << ", ElemIndex: " << ElemIndex[i] << std::endl;
					std::cout << Directory << std::endl;


					//Special Conditioning Statements that Allow "Pathway" Creations
					if (Directory == (size - 1))
					{
						ElemIndex[Directory]++;
					}
					else if ((ElemIndex[Directory - 1] == MaxIndex[Directory - 1]) && (ElemIndex[Directory] == MaxIndex[Directory]))
					{
						Directory--;
					}
					else if (ElemIndex[Directory] == MaxIndex[Directory])
					{
						for (int i = Directory + 1; i < size; i++)
							ElemIndex[i] = 1;
						Directory--;
						ElemIndex[Directory]++;
					}
					else
						Directory++;

					agree = true; //Assume that the vectors now agree
					for(int i = 0; i < size; i++) //Iterating through each Element of ElemIndex
						if (!(MaxIndex[i] == ElemIndex[i])) //If a single element is not the same, set agree to false
							agree = false;
				}



//Special Conditioning Statements that Allow "Pathway" Creations
					if ((ElemIndex[Directory - 1] == MaxIndex[Directory - 1]) && (ElemIndex[Directory] == MaxIndex[Directory]))
					{
						Directory--;
					}
					else if (ElemIndex[Directory] == MaxIndex[Directory])
					{
						for (int i = Directory; i < size; i++)
							ElemIndex[i] = 1;
						Directory--;
						if(ElemIndex[Directory] != MaxIndex[Directory])
							ElemIndex[Directory]++;
					}
					else if (Directory == (size - 1))
					{
						ElemIndex[Directory]++;
					}
					else
						Directory++;


std::cout << "Vector Index" << VecIndex << std::endl;
std::cout << "i: " << cols << std::endl;
std::cout << "j: " << rows << std::endl;
Print <std::vector<int>> (ElemIndex,PrintMode, std::string("ElemIndex"));
Print <std::vector<int>> (MaxIndex,PrintMode, std::string("MaxIndex"));






*/