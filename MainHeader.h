/*
This is where all the functions are included
*/
 
#ifndef MainIncludes
#define MainIncludes

//Standard File IO Libraries
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

//Including Eigen
#include <Eigen/Core>
#include <Eigen/Dense>

//File Writing Functions
template <class datatype> void FilePrinting(datatype vector, int n, bool Secure, int size, std::string name);
template <class datatype> void Print (datatype vector,int whereto,bool Secure, int size, std::string name);
template <class datatype> void TerminalPrinting(datatype vector, int size, bool Secure, std::string message);

//File Reading Functions
template <class datatype> datatype FileRead (std::vector<int> Dimensions, datatype vector, std::string FileName, std::string VerifyName, bool Secure, bool* Flag, std::string ProcessName);

//Activation Function Algorithms
template<class datatype> datatype sigmoid(datatype matrix);
template <class datatype> datatype Dsigmoid(datatype matrix);

//Feed Forward Operation
template <class datatype> void Perform(datatype LayerVec, datatype WeightVec, datatype BiasVec, std::vector<int> Dimensions);

//BackPropagation Algorithms
template <class InpType> InpType Gradient(InpType VectorMatrix, InpType Modifier);
template <class datatype> void Learn(datatype LayerVec, datatype WeightVec, datatype BiasVec, datatype PreActVec, datatype DLayerVec, datatype WGradVec, datatype BGradVec, datatype WGradVecfin, datatype BGradVecfin, datatype TrainingInput, datatype TrainingOutput, std::vector<int> Dimensions);

//Miscellaneous
bool Compare(std::string FileName1, std::string FileName2, std::vector<int> Dimensions, int* Length);

#endif