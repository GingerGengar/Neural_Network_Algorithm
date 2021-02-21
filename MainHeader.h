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
#include "Eigen/Core"
#include "Eigen/Dense"

//File Writing Functions
#include "FilePrint.cpp"
#include "TerminalPrint.cpp"
#include "Logging.cpp"

//File Reading Functions
#include "LoggingInv.cpp"

//Activation Function Algorithms
#include "Sigmoid.cpp"
#include "DSigmoid.cpp"

//Feed Forward Operation
#include "Perform.cpp"

//BackPropagation Algorithms
#include "GradientDescent.cpp"
#include "Learn.cpp"

//Miscellaneous
#include "Compare.cpp"

#endif