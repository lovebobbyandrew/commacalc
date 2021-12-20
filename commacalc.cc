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

bool CheckEmpty(std::string input_string) {
	bool error = true;
	if (0 != input_string.length()) { // If the user's input string is not empty.
		error = false;
	}
	return error;
}

bool CheckChar(std::string input_string) {
	bool error = false;
	for (int i = 0; i < input_string.length(); ++i) {
		if (!isdigit( input_string[i]) && // If an index is !digit, !operator, and !newline, then an invalid character is present.
				input_string[i] != '(' && input_string[i] != ')' &&
				input_string[i] != '^' && input_string[i] != '*' &&
				input_string[i] != '/' && input_string[i] != '+' &&
				input_string[i] != '-' && input_string[i] != '\n') {
			error = true;
			break;
		}
	}
	return error;
}

bool CheckOperator(std::string input_string) {
	bool error = false;
	for (int i = 0; i < input_string.length(); ++i) {
		if (0 < i && input_string.length() - 1 > i) { // Checks if numbers or proper parenthesises surround both sides of a given operator.
			if ((input_string[i] == '^' || input_string[i] == '*' ||
					input_string[i] == '/' || input_string[i] == '+') &&
					(!isdigit(input_string[i - 1]) && ')' != input_string[i - 1]) &&
					(!isdigit(input_string[i + 1]) && '(' != input_string[i + 1])) {
				error = true;
				std::cout << "third if" << "i is " << input_string[i] << " bfore is " << input_string[i-1] << " after is " << input_string[i+1] << std::endl;
				break;
			}
		}
		if (i < input_string.length() - 1) { // Prevents out of bounds index for final iteration.
			if ('-' == input_string[i] && (!isdigit(input_string[i + 1]) && // Checks if '-' operator is followed by a '(' or number.
					'(' != input_string[i + 1])) {
				error = true;
				std::cout << "fourth if";
				break;
			}
		}
	}
	return error;
}

bool CheckDoubleOp(std::string input_string) {
	bool error = false;
	for (int i = 0; i < input_string.length(); ++i) {
		if (i + 1 < input_string.length()) { // Prevents out of bounds index for final iteration.
			if ( input_string[i] == input_string [i + 1] && // If double occurrence of operator exists.
				( input_string[i] == '^' || input_string[i] == '*' ||
				input_string[i] == '/' || input_string[i] == '+' ||
				input_string[i] == '-')) {
				error = true;
				break;
			}
		}
	}
	return error;
}

bool CheckParen(std::string input_string) {
	bool error = false;
	unsigned short left_paren = 0;
	unsigned short right_paren = 0;
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
	return error;
}

bool CheckParenOp(std::string input_string) {
	return false;
}

bool CheckStartEnd(std::string input_string) {
	bool error = false;
	for (int i = 0; i < input_string.length(); ++i) {
				if ('^' == input_string[0] || '*' == input_string[0] || // Checks if invalid operator is present at start of string.
				'/' == input_string[0] || '+' == input_string[0] ||
				')' == input_string[0]) {
			error = true;
			std::cout << "first if";
			break;
		}
		if ('^' == input_string[input_string.length() - 1] || // Checks if invalid operator is present at end of string.
				'*' == input_string[input_string.length() - 1] ||
				'/' == input_string[input_string.length() - 1] ||
				'+' == input_string[input_string.length() - 1] ||
				'-' == input_string[input_string.length() - 1] ||
				'(' == input_string[input_string.length() - 1]) {
			error = true;
			std::cout << "second if";
			break;
		}
	}
	return error;
}

bool CheckExpr(std::string input_string) {
	bool error = false;
	bool loop = true;
	while (loop) {
std::cout << "made it to empty" << std::endl;
		error = CheckEmpty(input_string);
		if (error == true) break;
std::cout << "made it to char" << std::endl;
		error = CheckChar(input_string);
		if (error == true) break;
std::cout << "made it to op" << std::endl;
		error = CheckOperator(input_string);
		if (error == true) break;
std::cout << "made it to doubleop" << std::endl;
		error = CheckDoubleOp(input_string);
		if (error == true) break;
std::cout << "made it to paren" << std::endl;
		error = CheckParen(input_string);
		if (error == true) break;
std::cout << "made it to parenop" << std::endl;
		//error = CheckParenOp(input_string);
		if (error == true) break;
std::cout << "made it to startend" << std::endl;
		error = CheckStartEnd(input_string);
		loop = false;
	}
	return error;
}
/*bool CheckExpr(std::string input_string) {
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
		if (!isdigit( input_string[i]) && // If !digit, !operator, and !newline, invalid character is present.
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
}*/

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