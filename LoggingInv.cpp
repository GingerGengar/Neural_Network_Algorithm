#include "MainHeader.h"

/*
Function Header: Logging Inverse
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
General Purpose: It reads 2 files. First file is the layer dimensions file and the second file is the Matrix file of interest. It first checks if the dimensions it was given in main and the dimensions in the dimensions files match or not. After a match, it will proceed to populate the matrix vector it was given in accordance to the file it was specified to take data from.
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
Input Parameters: 5 Arguments. Dimensions is the dimiensions of each layer given through Main. FileName is the name of the file that it is supposed to populate the matrix with data from. VerifyName is the name of the Layers of dimension file. ProcessName is just a string that would be printed out in case an error occurs. 
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
Output Parameters: Boolean. If the data fetching process is correct, the boolean returned would be true. If the process had failed, the boolean returned would be false. 
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
Dependencies: NON 
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
Example of Function Call: FileRead<std::vector<Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic> *>>(Dimensions, WeightPoint, std::string("Weight_Matrices.txt"), std::string("Layer_Dimensions.txt"), std::string("Gradient Descent, Weight Matrices"));
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
*/

template <class datatype>
datatype FileRead (std::vector<int> Dimensions, datatype vector, std::string FileName, std::string VerifyName, bool Secure, bool* Flag, std::string ProcessName)
{
	//Function Specific Variable Declarations
	*Flag = true; //Determines if Data Fetching is succesful or not
	bool Verification = true; //Determines if  Matching with Layer Dimensions is a success or not 
	int SizeVec = vector.size(); //Getting the size of the vector
	int rows = 0, cols = 0; //Declaration of the rows and columns of the matrix
	int MatrixNum = Dimensions.size(); //The size of the Layer Vectors

	//Declaration of Placeholder Variables
	std::string Garbage; //Placeholder for irrelevant information that is ignored
	int DimensionNumber; //Placeholder for Dimension integers read from a file

	//Initial File Delcaraions
	std::ifstream InputFile; //Declaration of the matrix file pointer
	std::ifstream Verify; //Declaration of Dimension file pointer
	Verify.open(VerifyName); //Opening the Dimension File
  	InputFile.open(FileName); //Opening the matrix file of interest

  	//Checking Whether the Dimensions fed through main and the Dimensions in the .txt file matches or not
  	if (Verify)
  	{	
  		//Loop to Check Each Element inside the Dimension File
  		for (int i = 0; i < MatrixNum; i++)
  		{
 			//Ignore every 2 messages
			Verify >> Garbage;
			Verify >> Garbage;

			//Conditional Statement to Ensure Dimension Matching is succesful
			Verify >> DimensionNumber;
			if (DimensionNumber != Dimensions[i])
			{
				*Flag = false; //Notifies an Error has been made and Data Fetching failed
				Verification = false; //Ensures Input File is not even read
				std::cout << "ERROR: Dimension Mismatch" << std::endl;
				i = SizeVec; //Jumps out of the loop
			} 			
  		}

		//Conditional Statment to Fetch Data from the specified Matrix File
		if (InputFile && Verification)
		{
			if (Secure) //If it is Secure, Ignore the first line
				InputFile >> Garbage;

			//Loop for each Matrix inside the Matrix File
			for (int k = 0; k < SizeVec; k++)
			{
				//For the Dimensions of each matrix for the elements of vector
				rows = vector[k].rows();
				cols = vector[k].cols();

				//Every Ignore eveny 2 messages
				InputFile >> Garbage;
				InputFile >> Garbage;

				for (int i = 0; i < rows; i++)
					for (int j = 0; j < cols; j++)
					{
						InputFile >> vector[k](i,j);
					}
				
			}
		}
		else
		{
			*Flag = false; //Notifies an Error has been made and Data Fetching failed
			std::cout << "ERROR: Input File Not Valid" << std::endl;
  			std::cout << "DETAILS: " << ProcessName << std::endl;
		}
  	}
  	else
  	{
  		*Flag = false; //Notifies an Error has been made and Data Fetching failed
  		std::cout << "ERROR: Incorrect Dimension File Name, Dimension File Does not Exist, or Dimension Mismatch" << std::endl;
  		std::cout << "DETAILS: " << ProcessName << std::endl;
  	}

	return vector;
}

/*
for (int i = 0; i < SizeVec; i++)
		{
			//Ignore every 2 messages
			Verify >> Garbage;
			Verify >> Garbage;

			//Conditional Statement to Ensure Dimension Matching is succesful
			Verify >> DimensionNumber;
			std::cout << "Read: " << "Dimension Number:" << DimensionNumber << "Dimension:" << Dimensions[i] << std::endl;
			if (DimensionNumber != Dimensions[i])
			{
				*Flag = false; //Notifies an Error has been made and Data Fetching failed
				Verification = false; //Ensures Input File is not even read
				std::cout << "ERROR: Dimension Mismatch" << std::endl;
				i = SizeVec; //Jumps out of the loop
			}
		}
*/