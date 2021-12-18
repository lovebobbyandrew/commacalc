#include <iostream>
#include <string>
#include <fstream>
#include <ios>
#include <limits>
#include "commacalc.h"

void printMenu( void ){

	std::cout << "Enter expression to perform calculation." << std::endl;
	std::cout << "Enter \"HISTORY\" to print previous expressions." << std::endl;
	std::cout << "Enter \"EXIT\" to exit program." << std::endl;

}

bool readInput( std::string& inputString, int maxLength ){

	bool error = false;
	char inputArray[ maxLength ];
	
	if( std::cin.getline( inputArray, maxLength ).fail() ){ //If failbit true, input too long

		error = true;
		std::cout << "Expression too long." << std::endl;
		clearStdin(); //Clear input buffer
	}

	else{ //No length error

		inputString = inputArray;

	}

	return error;

}

void clearStdin( void ){

	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

}		
