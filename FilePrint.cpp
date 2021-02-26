#include "MainHeader.h"

template <class datatype>
void FilePrinting(datatype vector, int n, bool Secure, int size, std::string name)
{
	enum Errortype {NoError, Opening, Closing}Error; //Error for the switch statements
	Error = NoError; //The default is no Error, no Print messages

	//File input/output
	std::ofstream filepointer; //Declaration of the file pointer
  	filepointer.open(name, std::ios::trunc);
	
  	//For Secure Printing
  	if (Secure)
  	{
  		//Printing the size of each "Chunk"
  		filepointer << size <<std::endl;
  	}

	//Process of this Function
	if (filepointer.is_open())
	{
		for (int i = 0; i < n; i++)
		{
			filepointer << std::endl << "Element: "<< i << std::endl << vector[i] << std::endl;
		}
	}
	else
		Error = Opening;

	filepointer.close(); //Closing the file
	
	if(filepointer.is_open()) //Checking that indeed file has been closed
		Error = Closing;

	//Statements to tell which error has occured just in case
	switch(Error)
	{
		case Opening:
		std::cout << "ERROR: The file cannot be opened" << std::endl;
		break;
		case Closing:
		std::cout << "ERROR: The file cannot be closed" << std::endl;
		break;
	}

	return;
}