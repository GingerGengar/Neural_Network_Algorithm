#include "MainHeader.h"

/*
Function Header: Compare
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
General Purpose: It Compares a few things about the input training data. Compares whether the elements of each of the input has an element in each of the output of the training files. Compares whether the input of the training files will fit into the input of the neural network, Compares whether the output of the training files will fit into the output of the neural network. If any of these conditions are violated, an error would be thrown and boolean returned would be false.
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
Input Parameters: 4 arguments. 2 of the arguments are the name of the input and output files. The third argument is a standard vector of the dimensions that is fed through main. The Dimensions is used to then compare whether the training data is suitable or not. The pointer integer length is also passed to show the length of the data entries. Length is set to 0 if the files are not suitable for training. 
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
Output Parameters: boolean, which determines if the training files are valid and usable for training
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
Dependencies: Non
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
Example of Function Call: Print <std::vector<int>> (Dimensions, std::string("Neural_Network_Base_Dimensions.txt"));
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
*/

bool Compare(std::string FileName1, std::string FileName2, std::vector<int> Dimensions, int* Length)
{
	//Declaration of Function Specific Variables
	bool Flag = true;
	std::string Supposed ("Element:");
	int Last = Dimensions.size() - 1;
	
	//Declaration of Placeholder Variables
	int FileLength1 = 0; 
	int FileLength2 = 0;
	std::string Proxy1, Proxy2;

	//Construction of File Objects
	std::ifstream File1;
	std::ifstream File2;

	//Opening of File Objects
	File1.open(FileName1);
	File2.open(FileName2);

	if (File1 && File2)
	{
		//Gets the Dimensions of the training inputs and training outputs
		File1 >> Proxy1;
		File2 >> Proxy2;

		if ((Proxy1 != std::to_string(Dimensions[0])) || (Proxy2 != std::to_string(Dimensions[Last])))
		{
			Flag = false;
			std::cout << "ERROR: The Training Data Does not Fit into the Inputs or Outputs of the Network..." << std::endl;
		}

		while(File1)
		{
			File1 >> Proxy1;
			if (!Proxy1.compare(Supposed))
				FileLength1++;
		}
		while(File2)
		{	
			File2 >> Proxy2;
			if (!Proxy2.compare(Supposed))
				FileLength2++;
		}
	}
	else
	{
		if ((!File1) && (!File2))
			std::cout << "ERROR: Both Files Cannot be Opened..." << std::endl;
		else if (!File1)
			std::cout << "ERROR: First File Cannot be Opened..." << std::endl;
		else
			std::cout << "ERROR: Second File Cannot be Opened..." << std::endl;
	}

	*Length = 0; //If Files are unsuitable, Length is set to 0

	if ((FileLength1 != FileLength2) || (FileLength1 == 0))
	{
		Flag = false;
		std::cout << "The length of the training Inputs and Outputs do not Match Element-wise" << std::endl;
	}
	else
		*Length = FileLength1;

	return Flag;
}