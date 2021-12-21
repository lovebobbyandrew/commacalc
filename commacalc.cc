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

bool ReadInput(std::string& input_string, const int maxLength) {
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
}

void ClearStdin(void) {
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int Option(const std::string input_string) {
	int choice;
	std::string input_copy = input_string;
	for (int i = 0; i < input_copy.length(); ++i) {
		input_copy[i] = std::toupper(input_copy[i]);
	}
	if ("EXIT" == input_copy) {
		choice = 3;
	} else if ("HISTORY" == input_copy) {
			choice = 2;
	} else choice = 1;
	return choice;
}

void PrintHistory(const std::deque<std::string> history_deque) {
  for (int i = 0; i < history_deque.size(); ++i) {
    std::cout << history_deque.at(i) << std::endl;
  }
}


std::string RemoveSpace(std::string input_string) {
	input_string.erase(std::remove_if(input_string.begin(), input_string.end(),
		 								isspace), input_string.end());
	return input_string;
}

std::string ReplaceSpace(std::string input_string) {
	for (int i = 0; i < input_string.length(); ++i) {
		if (isdigit(input_string[i])) {
			if (i + 1 < input_string.length()) {
				if (isspace(input_string[i + 1])) {
					if (i + 1 == input_string.length() - 1) {
						break;
					}
					for (int j = i + 1; j < input_string.length(); ++j) {
						if (!isspace(input_string[j])) {
							break;
						} else if (isdigit(input_string[j + 1]) || '.' == input_string[j + 1]) {
							input_string[j] = '*';
							break;
						}
					}
				}
			}
		}
	}
	return input_string;
}

std::string DecimalMult(std::string input_string) {
	for (int i = 0; i < input_string.length(); ++i) {
		if ('.' == input_string[i]) {
			if (i - 1 >= 0 && i + 2 < input_string.length()) {
				if ('.' == input_string[i + 1] && isdigit(input_string[i - 1]) && isdigit(input_string[i + 2])) {
					input_string.insert(i + 1, 1, '*');
				}
			}
		}
	}
	return input_string;
}

bool CheckDecimal(std::string input_string){
	bool error = false;
	for (int i = 0; i < input_string.length(); ++i) {
		if (1 == input_string.length() && '.' == input_string[0]) { // Checks if string is a lone '.'.
			error = true;
			break;
		}
		if (i - 1 > 0 && i + 1 < input_string.length()) { // Checks if both adjacent indexes to '.' are operators.
			if (!isdigit(input_string[i - 1]) && '.' == input_string[i] &&
					!isdigit(input_string[i + 1])) {
				error = true;
				break;
			}
		}
		if (i + 1 < input_string.length()) { // Checks if there are 2 or more decimal points in a row.
			if ('.' == input_string[i] && '.' == input_string[i + 1]) {
				error = true;
				break;
			}
		}
		if ('.' == input_string[i]) {
			for (int j = i + 1; j < input_string.length(); ++j) {
				if ('(' == input_string[j] || ')' == input_string[j] ||
						'^' == input_string[j] || '*' == input_string[j] ||
						'/' == input_string[j] || '+' == input_string[j] ||
						'-' == input_string[j]) {
					break;
				} else if ('.' == input_string[j]) { // Checks if there are 2 '.' in a row (only valid if formatting function called prior).
					error = true;
					break;
				}
			}
		}
	}
	return error;
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
				input_string[i] != '-' && input_string[i] != '.' &&
				input_string[i] != '\n') {
			error = true;
			break;
		}
	}
	return error;
}

bool CheckOperator(std::string input_string) {
	bool error = false;
	for (int i = 0; i < input_string.length(); ++i) {
		if (0 < i) {
			if (('^' == input_string[i] || '*' == input_string[i] ||
					'/' == input_string[i] || '+' == input_string[i] ||
					'-' == input_string[i]) && ('^' == input_string[i - 1] ||
					'*' == input_string[i - 1] || '/' == input_string[i - 1] ||
					'+' == input_string[i - 1] || '-' == input_string[i - 1])) {
				error = true;
				if ('-' == input_string[i]) {
					error = false;
				} else break;
			}	
		}
		if (i < input_string.length() - 1) { // Prevents out of bounds index for final iteration.
			if ('-' == input_string[i] && (!isdigit(input_string[i + 1]) && // Checks if '-' operator is followed by a '(', '.', or number.
					'(' != input_string[i + 1] && '-' != input_string[i + 1]) &&
					'.' != input_string[i + 1]) {
				error = true;
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
			if (input_string[i] == input_string [i + 1] && // If double occurrence of operator exists.
				(input_string[i] == '^' || input_string[i] == '*' ||
				input_string[i] == '/' || input_string[i] == '+')) {
				error = true;
				break;
			}
			if ('-' == input_string[i - 1] && '-' == input_string[i]
					&& '-' == input_string[i + 1]) {
				error = true;
				break;
			}
		}
	}
	return error;
}

bool CheckParen(std::string input_string) {
	bool error = false;
	int left_paren = 0;
	int right_paren = 0;
	for (int i = 0; i < input_string.length(); ++i) {
		if ('(' == input_string[i]) {
			++left_paren; // Count the number of left parenthesises.
			error = true; // Assume there is no closing (right) parenthesis.
			for (int j = i + 1; j < input_string.length(); ++j) {
				if (')' == input_string[j]) {
					input_string[j] = '~'; // Placeholder to prevent a single ')' occurrence from being counted in future iterations of loop.
					error = false;
					break;
				}
			}
		}
	}
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

bool CheckInsideParen(std::string input_string) {
	bool error = false;
	for (int i = 0; i < input_string.length(); ++i) {
		if (i < input_string.length() - 1) { // Prevents out of bounds indexing.
			if ('(' == input_string[i] && ('^' == input_string[i + 1] || // Checks that left parenthesises do not have invalid internally adjacent operator.
					'*' == input_string[i + 1] || '/' == input_string[i + 1] ||
					'+' == input_string[i + 1] || ')' == input_string[i + 1])) {
				error = true;
				break;
			}
		}
		if (0 < i) { // Prevents out of bounds indexing
			if (')' == input_string[i] && ('^' == input_string[i - 1] || // Checks that right parenthesises do not have invalid internally adjacent operator.
					'*' == input_string[i - 1] || '/' == input_string[i - 1] ||
					'+' == input_string[i - 1] || '-' == input_string[i - 1] ||
					'(' == input_string[i - 1])) {
				error = true;
				break;
			}
		}
	}
	return error;
}

bool CheckStartEnd(std::string input_string) {
	bool error = false;
	for (int i = 0; i < input_string.length(); ++i) {
				if ('^' == input_string[0] || '*' == input_string[0] || // Checks if invalid operator is present at start of string.
				'/' == input_string[0] || '+' == input_string[0] ||
				')' == input_string[0]) {
			error = true;
			break;
		}
		if ('^' == input_string[input_string.length() - 1] || // Checks if invalid operator is present at end of string.
				'*' == input_string[input_string.length() - 1] ||
				'/' == input_string[input_string.length() - 1] ||
				'+' == input_string[input_string.length() - 1] ||
				'-' == input_string[input_string.length() - 1] ||
				'(' == input_string[input_string.length() - 1]) {
			error = true;
			break;
		}
	}
	return error;
}

bool CheckExpression(std::string input_string) {
	bool error = false;
	bool loop = true;
	while (loop) {
std::cout << "Made it to CheckEmpty." << std::endl;
		error = CheckEmpty(input_string);
		if (error == true) break;
std::cout << "Made it to CheckChar." << std::endl;
		error = CheckChar(input_string);
		if (error == true) break;
std::cout << "Made it to CheckDecimal." << std::endl;
		error = CheckDecimal(input_string);
		if (error == true) break;
std::cout << "Made it to CheckOperator." << std::endl;
		error = CheckOperator(input_string);
		if (error == true) break;
std::cout << "Made it to CheckDoubleOp." << std::endl;
		error = CheckDoubleOp(input_string);
		if (error == true) break;
std::cout << "Made it to CheckParen." << std::endl;
		error = CheckParen(input_string);
		if (error == true) break;
std::cout << "Made it to CheckInsideParen." << std::endl;
		error = CheckInsideParen(input_string);
		if (error == true) break;
std::cout << "Made it to CheckStartEnd." << std::endl;
		error = CheckStartEnd(input_string);
		loop = false;
	}
	return error;
}

double Calculate(std::string) {
	//calcuates expression and returns result
	double result;
	return result;
}

std::string MakeEquation(std::string input_string, double result) {
	int new_length = input_string.length();
	std::string result_string = std::to_string(result);
	for (int i = result_string.length() - 1; i > 0; --i) { // Removes trailing zeroes after decimal point inside string.
		if ('0' == result_string[i]) {
			result_string.erase(i, i);
		} else break;
	}
	for (int i = 0; i < input_string.length(); ++i) { // Inserts " " before and after specified operators.
		if('*' == input_string[i] || '/' == input_string[i] ||
 				'+' == input_string[i] || '-' == input_string[i]) {
			input_string.insert(i, " ");
			i = i + 1;
			input_string.insert(i + 1, " ");
			i = i + 1;
		}
	}
	return (input_string + " = " + result_string);
}

std::deque<std::string> StoreEquation(std::deque<std::string> history_deque, std::string equation) {
	if (history_deque.size() < 5) {
 		history_deque.push_front(equation);
	} else { // Prevents deque from growing greater than 5 indexes large.
		history_deque.pop_back();
		history_deque.push_front(equation);
	}
	return history_deque;
}


double Exponentiation(double base, double exponent) {
	return (pow(base, exponent));
}

double Multiplication(double multiplicand, double multiplier) {
	return (multiplicand * multiplier);
}

double Division(double dividend, double divisor) {
	return (dividend / divisor);
}

double Addition(double addend, double augend) {
	return (addend + augend);
}

double Subtraction(double minuend, double subtrahend) {
	return (minuend - subtrahend);
}
} //End of namespace commacalc.