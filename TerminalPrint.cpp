#include "MainHeader.h"

template <class datatype>
void TerminalPrinting(datatype vector, int size, bool Secure, std::string message)
{
	//Printing Message
	std::cout << message << std::endl;

	//Printing option for secure printing
	std::cout << "Secure Printing: ";
	if (Secure)
		std::cout << "ON";
	else
		std::cout << "OFF";
	std::cout << std::endl;

	//Loop to print contents
	for(int i = 0; i < size; i++)
			std::cout << std::endl << "Element: "<< i << std::endl << vector[i] << std::endl;

	return;
}