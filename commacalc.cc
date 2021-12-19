//#include <cctype>
#include <iostream>
#include <string>
#include <cmath>
//#include <cstring>
#include <fstream>
#include <ios>
#include <algorithm>
#include <cctype>
#include <limits>
#include "commacalc.h"

namespace commacalc {

void printMenu(void){
	std::cout << "Enter expression to perform calculation." << std::endl;
	std::cout << "Enter \"HISTORY\" to print previous expressions." << std::endl;
	std::cout << "Enter \"EXIT\" to exit program." << std::endl;
}

bool readInput(std::string& inputString, int maxLength){
	bool error = false;
	char inputArray[maxLength];
	if( std::cin.getline(inputArray, maxLength).fail()){ //If failbit true, input too long
		error = true;
		std::cout << "Expression too long." << std::endl;
		clearStdin(); //Clear input buffer
	}
	else{ //No length error
		inputString = inputArray;
	}
	return error;
} //ask user if they want truncated string instead?

void clearStdin(void){
	std::cin.clear();
	std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
}

unsigned short option(std::string inputString){
	unsigned short choice;
	for(int i = 0; i < inputString.length(); ++i){
		inputString[i] = std::toupper( inputString[i]);
	}
	if("EXIT" == inputString){
		choice = 3;
	}
	else{
		if("HISTORY" == inputString){
			choice = 2;
		}
		else choice = 1;
	}
	return choice;
}

void printHistory(void){
	//Print last 5 expression and results
}

std::string removeSpace(std::string inputString){
	inputString.erase(std::remove_if(inputString.begin(), inputString.end(),
		 								isspace), inputString.end());
	return inputString;
}

bool checkExpression(std::string inputString){
	bool error = false;
	unsigned short leftParen = 0;
	unsigned short rightParen = 0;
	if(0 == inputString.length()){ //Empty string
		error = true;
	}
	if(! isdigit(inputString[0]) && 1 == inputString.length()){ //!digit and length 1
		error = true;
		std::cout << "length 1 non digit err" << std::endl; //testing remove when done
	}
	for(int i = 0; i < inputString.length(); ++i){
		if(! isdigit( inputString[i]) && //If !digit, operator, or newline
			inputString[i] != '(' && inputString[i] != ')' &&
			inputString[i] != '^' && inputString[i] != '*' &&
			inputString[i] != '/' && inputString[i] != '+' &&
			inputString[i] != '-' && inputString[i] != '\n'){
			error = true;
			std::cout << "not digit, operator, or nl err" << std::endl; //testing purposes remove
		}
		if(i + 1 < inputString.length()){ //Prevent out of bounds index
			if( inputString[i] == inputString [i + 1] && //If double occurrence of operator
				( inputString[i] == '^' || inputString[i] == '*' ||
				inputString[i] == '/' || inputString[i] == '+' ||
				inputString[i] == '-')){
				error = true;
				std::cout << "i is: " << i << " string[i] is: " << inputString[i] << " string[i + 1] is: " << inputString[i + 1] << std::endl;
				std::cout << "double occur error" << std::endl; //testing purposes remove this line and the one above too when done
			}
		}
	}
	for(int i = 0; i < inputString.length(); ++i){ //Check for closing parenthesis
		if('(' == inputString[i]){
			++leftParen; //Count # of left parenthesis
			error = true; //Assume no closing parenthesis
			for(int j = i + 1; j < inputString.length(); ++j){
				if(')' == inputString[j]){ //If closing parenthesis found
					inputString[j] = '~'; //Placeholder to prevent a ')' from being counted repeatedly
					error = false;
					break;
				}
			}
		}
	} //iterate through once, save parenthesis indexes, make sure each left parenthesis has a matching right with a greater index

	for(int i = 0; i < inputString.length(); ++i){ //Replace all '~' with ')'
		if('~' == inputString[i]){
			inputString[i] = ')';
		}
		if(')' == inputString[i]){ //Count # of right parenthesis
			++rightParen;
		}
	}
	if(leftParen != rightParen){ //Compare # of left parenthesis and right
		error = true;
	}
	if(true == error){
		std::cout << "Expression invalid." << std::endl;
	}
	return error;
}

std::string formatExpression(std::string inputString){
	//Formats good input string
	return inputString;
}

double calculate(std::string){
	//calcuates expression and returns result
	double result;
	return result;
}

void storeExpression(std::string, double){
	//stores expression and result into history array
}

double exponentiation(double base, double exponent){
	return(pow(base, exponent));
}

double multiplication(double multiplicand, double multiplier){
	return(multiplicand * multiplier);
}

double division(double dividend, double divisor){
	return(dividend / divisor);
}

double addition(double addend, double augend){
	return(addend + augend);
}

double subtraction(double minuend, double subtrahend){
	return(minuend - subtrahend);
}
} //End of namespace commacalc.