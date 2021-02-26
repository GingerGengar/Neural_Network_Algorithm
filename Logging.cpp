#include "MainHeader.h"

/*
Function Header: Logging
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
General Purpose: It prints out all the contents of a vector whose elements contain an uncertain data type that is to be specified at compile time
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
Input Parameters: 3 arguments, the data type of the elements of the vector object, the vector object itself, a std::string("") containing the name of the file to be outputted
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
Output Parameters: Void Function
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
Dependencies: FilePrint.h , TerminalPrint.h
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
Example of Function Call: Print <std::vector<int>> (Dimensions, std::string("Neural_Network_Base_Dimensions.txt"));
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
*/

template <class datatype>
void Print (datatype vector,int whereto,bool Secure, int size, std::string name)
{
	//Initialization
	enum Printoption {Terminal, File, Both} PrintMode; //For printing options
	int sizeofvec = vector.size(); //Size of the vector for writing down the vector

	switch (whereto)
	{
		case Terminal:
		TerminalPrinting(vector, sizeofvec, Secure, name);
		break;
		case File:
		FilePrinting(vector, sizeofvec, Secure, size, name);
		break;
		case Both:
		TerminalPrinting(vector, sizeofvec, Secure, name);
		FilePrinting(vector, sizeofvec, Secure, size, name);
		break;
	}

	return;
}

