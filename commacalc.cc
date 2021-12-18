//#include <cctype>
#include <iostream>
#include <string>
//#include <cstring>
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
	std::cin.ignore( std::numeric_limits< std::streamsize >::max(), '\n' );

}

unsigned short option( std::string inputString ){

	unsigned short choice;
	std::hash< std::string > hasher;

	for( int i = 0; i < inputString.length(); ++i ){

		inputString[ i ] = std::toupper( inputString[ i ] );

	}

	const int inputHash = hasher( inputString );

	switch( inputHash ){

		case 2055804650: //Found via hasher( "EXIT" )

			choice = 3; //EXIT entered by user
			break;

		case -102179798: //Found via hasher( "HISTORY" )

			choice = 2; //HISTORY entered by user
			break;

		default:

			choice = 1;

	}

	return choice;

}
