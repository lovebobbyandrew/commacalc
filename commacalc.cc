// Bobby Love
// December 17, 2021
// GNU GPL

#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <ios>
#include <algorithm>
#include <cctype>
#include <limits>
#include "commacalc.h"

namespace commacalc {

void PrintMenu(void) {
	std::cout << "Enter expression to perform calculation." << std::endl;
	std::cout << "Enter \"HISTORY\" to print previous expressions." << std::endl;
	std::cout << "Enter \"EXIT\" to exit program." << std::endl;
}

bool ReadInput(std::string& input_string, int maxLength) {
	bool error = false;
	char input_array[maxLength];
	if (std::cin.getline(input_array, maxLength).fail()) { // If failbit is true, then the user's input string is too long.
		error = true;
		std::cout << "Expression too long." << std::endl;
		ClearStdin(); // Clear the input buffer.
	} else { // Failbit is false, so user's input string is valid.
		input_string = input_array;
	}
	return error;
} // SHOULD I ASK THE USER IF THEY WOULD LIKE TO CONTINUE WITH A TRUNCATED STRING AS OPPOSED TO FORCING THEM TO TRY AGAIN?

void ClearStdin(void) {
	std::cin.clear();
	std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
}

unsigned short Option(std::string input_string) {
	unsigned short choice;
	for (int i = 0; i < input_string.length(); ++i) {
		input_string[i] = std::toupper( input_string[i]);
	}
	if ("EXIT" == input_string) {
		choice = 3;
	} else if ("HISTORY" == input_string) {
			choice = 2;
	} else choice = 1;
	return choice;
}

void PrintHist(void){
	// Print the previous 5 expression and results.
}

std::string RemoveSpace(std::string input_string) {
	input_string.erase(std::remove_if(input_string.begin(), input_string.end(),
		 								isspace), input_string.end());
	return input_string;
}

bool CheckExpr(std::string input_string) {
	bool error = false;
	unsigned short left_paren = 0;
	unsigned short right_paren = 0;
	if (0 == input_string.length()) { // If the user's input string is empty.
		error = true;
	}
	if (!isdigit(input_string[0]) && 1 == input_string.length()) { // If length of the string is 1 and the 1 character is not a number.
		error = true;
		std::cout << "length 1 non digit err" << std::endl; // testing remove when done
	}
	for (int i = 0; i < input_string.length(); ++i) {
		if (!isdigit( input_string[i]) && // If !digit, operator, or newline
			input_string[i] != '(' && input_string[i] != ')' &&
			input_string[i] != '^' && input_string[i] != '*' &&
			input_string[i] != '/' && input_string[i] != '+' &&
			input_string[i] != '-' && input_string[i] != '\n') {
			error = true;
			std::cout << "not digit, operator, or nl err" << std::endl; // testing purposes remove when done
		}
		if (i + 1 < input_string.length()) { // Condition prevents out of bounds index for final iteration.
			if ( input_string[i] == input_string [i + 1] && // If double occurrence of operator exists.
				( input_string[i] == '^' || input_string[i] == '*' ||
				input_string[i] == '/' || input_string[i] == '+' ||
				input_string[i] == '-')) {
				error = true;
				std::cout << "i is: " << i << " string[i] is: " << input_string[i] << " string[i + 1] is: " << input_string[i + 1] << std::endl; // test remove when done
				std::cout << "double occur error" << std::endl; // testing purposes remove this line and the one above too when done
			}
		}
	}
	for (int i = 0; i < input_string.length(); ++i) { // Check for closing parenthesis.
		if ('(' == input_string[i]) {
			++left_paren; // Count the number of left parenthesises.
			error = true; // Assume there is no closing (right) parenthesis.
			for (int j = i + 1; j < input_string.length(); ++j) {
				if (')' == input_string[j]) { // If a closing (right) parenthesis is found.
					input_string[j] = '~'; // Placeholder to prevent a single ')' occurrence from being counted in future iterations.
					error = false;
					break;
				}
			}
		}
	} // CONSIDER: iterate through once, save parenthesis indexes, make sure each left parenthesis has a matching right with a greater index

	for (int i = 0; i < input_string.length(); ++i) { // Replace all placeholder '~' with ')'.
		if ('~' == input_string[i]) {
			input_string[i] = ')';
		}
		if (')' == input_string[i]) { // Count the number of right parenthesises.
			++right_paren;
		}
	}
	if (left_paren != right_paren) { // Compare the number of left parenthesises and right parenthesises.
		error = true;
	}
	if (true == error) {
		std::cout << "Expression invalid." << std::endl;
	}
	return error;
}

std::string FormatExpr(std::string input_string) {
	//Formats good input string
	return input_string;
}

double Calc(std::string) {
	//calcuates expression and returns result
	double result;
	return result;
}

void StoreExpr(std::string, double) {
	//stores expression and result into history array
}

double Expo(double base, double exponent) {
	return(pow(base, exponent));
}

double Mult(double multiplicand, double multiplier) {
	return(multiplicand * multiplier);
}

double Div(double dividend, double divisor) {
	return(dividend / divisor);
}

double Add(double addend, double augend) {
	return(addend + augend);
}

double Sub(double minuend, double subtrahend) {
	return(minuend - subtrahend);
}
} //End of namespace commacalc.