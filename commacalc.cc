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
	for (long unsigned int i = 0; i < input_copy.length(); ++i) {
		input_copy[i] = std::toupper(input_copy[i]);
	}
	if ("EXIT" == input_copy) {
		choice = 3;
	} else if ("HISTORY" == input_copy) {
			choice = 2;
	} else choice = 1;
	return choice;
}

void PrintHistory(const std::deque<std::string>& history_deque) {
  for (long unsigned int i = 0; i < history_deque.size(); ++i) {
    std::cout << history_deque.at(i) << std::endl;
  }
}

void RemoveSpace(std::string& input_string) {
	input_string.erase(std::remove_if(input_string.begin(), input_string.end(),
		 									isspace), input_string.end());
}

void ReplaceSpace(std::string& input_string) {
	for (long unsigned int i = 0; i < input_string.length(); ++i) {
		if (isdigit(input_string[i])) {
			if (i + 1 < input_string.length()) {
				if (isspace(input_string[i + 1])) {
					if (i + 1 == input_string.length() - 1) {
						break;
					}
					for (long unsigned int j = i + 1; j < input_string.length(); ++j) {
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
}

void DecimalSeparated(std::string& input_string) {
	for (long unsigned int i = 0; i < input_string.length(); ++i) {
		if ('.' == input_string[i]) {
			if (i - 1 >= 0 && i + 2 < input_string.length()) {
				if ('.' == input_string[i + 1] && isdigit(input_string[i - 1]) &&
						isdigit(input_string[i + 2])) {
					input_string.insert(i + 1, 1, '*'); // Inserts a single '*' when a '.' is separated from another '.' or digit by whitespace.
				}
			}
		}
	}
}

void KeepChangeChange(std::string& input_string) {
	for (long unsigned int i = 0; i < input_string.length(); ++i) {
		if (i + 2 < input_string.length()) {
			if ('-' == input_string[i] && '-' == input_string[i + 1] &&
					(isdigit(input_string[i + 2]) || '.' == input_string[i + 2])) {
				input_string.replace(i, 2, 1, '+'); // Replace the final 2 '-' with a '+'.
			}
		}
	}
}

bool CheckDecimal(const std::string& input_string){
	bool error = false;
	for (long unsigned int i = 0; i < input_string.length(); ++i) {
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
			for (long unsigned int j = i + 1; j < input_string.length(); ++j) {
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

bool CheckEmpty(const std::string& input_string) {
	bool error = true;
	if (0 != input_string.length()) { // If the user's input string is not empty.
		error = false;
	}
	return error;
}

bool CheckChar(const std::string& input_string) {
	bool error = false;
	for (long unsigned int i = 0; i < input_string.length(); ++i) {
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

bool CheckOperator(const std::string& input_string) {
	bool error = false;
	for (long unsigned int i = 0; i < input_string.length(); ++i) {
		if (0 < i) {
			if (('^' == input_string[i] || '*' == input_string[i] || // Checks if 2 operators (other than '-') are adjacent.
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
			if ('-' == input_string[i] && (!isdigit(input_string[i + 1]) && // Checks if '-' operator is followed by a '(', '.', or digit.
					'(' != input_string[i + 1] && '-' != input_string[i + 1]) &&
					'.' != input_string[i + 1]) {
				error = true;
				break;
			}
		}
	}
	return error;
}

bool CheckDoubleOp(const std::string& input_string) {
	bool error = false;
	for (long unsigned int i = 0; i < input_string.length(); ++i) {
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

bool CheckParen(const std::string& input_string) {
	bool error = false;
	std::string local_copy = input_string;
	int left_paren = 0;
	int right_paren = 0;
	for (long unsigned int i = 0; i < local_copy.length(); ++i) {
		if ('(' == local_copy[i]) {
			++left_paren; // Count the amount of left parenthesises.
			error = true; // Assume there is no closing (right) parenthesis.
			for (long unsigned int j = i + 1; j < local_copy.length(); ++j) {
				if (')' == local_copy[j]) {
					local_copy[j] = '~'; // Placeholder to prevent a single ')' occurrence from being counted in future iterations of loop.
					error = false;
					break;
				}
			}
		}
	}
	for (long unsigned int i = 0; i < local_copy.length(); ++i) { // Replace all placeholder '~' with ')'.
		if ('~' == local_copy[i]) {
			local_copy[i] = ')';
		}
		if (')' == local_copy[i]) { // Count the amount of right parenthesises.
			++right_paren;
		}
	}
	if (left_paren != right_paren) { // Compare the count of left parenthesises and right parenthesises.
		error = true;
	}
	return error;
}

bool CheckInsideParen(const std::string& input_string) {
	bool error = false;
	for (long unsigned int i = 0; i < input_string.length(); ++i) {
		if (i < input_string.length() - 1) { // Prevents out of bounds indexing.
			if ('(' == input_string[i] && ('^' == input_string[i + 1] || // Checks that left parenthesises do not have invalid internally adjacent operator.
					'*' == input_string[i + 1] || '/' == input_string[i + 1] ||
					'+' == input_string[i + 1] || ')' == input_string[i + 1])) {
				error = true;
				break;
			}
		}
		if (0 < i) { // Prevents out of bounds indexing.
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

bool CheckStartEnd(const std::string& input_string) {
	bool error = false;
	for (long unsigned int i = 0; i < input_string.length(); ++i) {
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

bool CheckExpression(const std::string& input_string) {
	bool error = false;
	bool loop = true;
	while (loop) {
		error = CheckEmpty(input_string);
		if (error == true) break;
		error = CheckChar(input_string);
		if (error == true) break;
		error = CheckDecimal(input_string);
		if (error == true) break;
		error = CheckOperator(input_string);
		if (error == true) break;
		error = CheckDoubleOp(input_string);
		if (error == true) break;
		error = CheckParen(input_string);
		if (error == true) break;
		error = CheckInsideParen(input_string);
		if (error == true) break;
		error = CheckStartEnd(input_string);
		loop = false;
	}
	return error;
}

void FindOperands(const std::string& input_string,
									const unsigned int operator_index, double& left_operand,
									double& right_operand, unsigned int& left_operand_start,
									unsigned int& right_operand_end) {
  std::string left_operand_string;
  std::string right_operand_string;
  for (long unsigned int i = operator_index - 1; i >= 0; --i) {
    if (!isdigit(input_string[i]) && '.' != input_string[i]) {
      break;
    } else {
			std::cout << "ith index is " << input_string[i] << std::endl;
			left_operand_start = i;
      left_operand_string.insert(0, 1, input_string[i]);
    }
  }
  left_operand = stod(left_operand_string);
	std::cout << left_operand << std::endl;
  for (long unsigned int i = operator_index + 1; i < input_string.length(); ++i) {
		if (!isdigit(input_string[i]) && '.' != input_string[i]) {
    	break;
    }
		right_operand_end = i;
  	right_operand_string = right_operand_string + input_string[i];
	}
	right_operand = stod(right_operand_string);     
}


void Exponentiation(std::string& input_string, unsigned int operator_index) {
	double base;
	double exponent;
	unsigned int base_start;
	unsigned int exponent_end;
	FindOperands(input_string, operator_index, base, exponent, base_start, exponent_end);
	input_string.replace(base_start, exponent_end - base_start, std::to_string(pow(base, exponent)));
}

void Multiplication(std::string& input_string, unsigned int operator_index) {
	double multiplicand;
	double multiplier;
	unsigned int multiplicand_start;
	unsigned int multiplier_end;
	FindOperands(input_string, operator_index, multiplicand, multiplier, multiplicand_start, multiplier_end);
	input_string.replace(multiplicand_start, multiplier_end - multiplicand_start, std::to_string(multiplicand * multiplier));
}

void Division(std::string& input_string, unsigned int operator_index) {
	double dividend;
	double divisor;
	unsigned int dividend_start;
	unsigned int divisor_end;
	FindOperands(input_string, operator_index, dividend, divisor, dividend_start, divisor_end);
	input_string.replace(dividend_start, divisor_end - dividend_start, std::to_string(dividend / divisor));
}

void Addition(std::string& input_string, unsigned int operator_index) {
	double addend;
	double augend;
	unsigned int addend_start;
	unsigned int augend_end;
	FindOperands(input_string, operator_index, addend, augend, addend_start, augend_end);
	std::cout << "input additon is " << input_string << std::endl;
	std::cout << "operator_index is " << operator_index << std::endl;
	std::cout << "start is " << addend_start << " and end is " << augend_end << std::endl;
	input_string.replace(addend_start, augend_end - addend_start, std::to_string(addend + augend));
	std::cout << "input addition 2 is " << input_string << std::endl;
}

void Subtraction(std::string& input_string, unsigned int operator_index) {
	double minuend;
	double subtrahend;
	unsigned int minuend_start;
	unsigned int subtrahend_end;
	FindOperands(input_string, operator_index, minuend, subtrahend, minuend_start, subtrahend_end);
	std::cout << "made it" << std::endl;
	input_string.replace(minuend_start, subtrahend_end - minuend_start, std::to_string(minuend - subtrahend));
	std::cout << "made it 2" << std::endl;
	std::cout << input_string << std::endl;
	std::cout << "made it 3" << std::endl;
	std::cout << stod(input_string) << std::endl;
}

double Calculate(std::string& input_string) { // NEED TO ADD PARENTHESIS SUPPORT AND DOES NOT FOLLOW ORDER OF OPERATIONS FOR EX: 32-3+7 YIELDS 23
	unsigned short highest_operator;
	unsigned int operator_index = 0;
	bool operators_remain = true;
	do {
		highest_operator = 0;
		for (long unsigned int i = 0; i < input_string.length(); ++i) { // Find what the operator of highest precendence is and its index within input_string.
			if (!isdigit(input_string[i]) && '.' != input_string[i]) {
				switch(input_string[i]) {
					case '^':
						highest_operator = 5;
						operator_index = i;
						break;
					case '*':
						if (highest_operator < 4) {
							highest_operator = 4;
							operator_index = i;
						}
						break;
					case '/':
						if (highest_operator < 3) {
							highest_operator = 3;
							operator_index = i;
						}
						break;
					case '+':
						if (highest_operator < 2) {
							highest_operator = 2;
							operator_index = i;
						}
						break;
					case '-':
						if (highest_operator < 1 && 0 != i) {
							highest_operator = 1;
							operator_index = i;
						}
						break;
				}
			}
		}
		switch (highest_operator) { // Using what the highest operator is and its location, perform an operation and store the data back into input_string for next iteration.
			case 1:
				Subtraction(input_string, operator_index);
				break;
			case 2:
				Addition(input_string, operator_index);
				break;
			case 3:
				Division(input_string, operator_index);
				break;
			case 4:
				Multiplication(input_string, operator_index);
				break;
			case 5:
				Exponentiation(input_string, operator_index);
				break;
		}
		if (0 == highest_operator) {
			operators_remain = false;
		}
	} while (operators_remain);
	return stod(input_string);
}

void MakeEquation(std::string& input_string, const double& result) {
	std::string result_string = std::to_string(result);
	for (long unsigned int i = result_string.length() - 1; i > 0; --i) { // Removes trailing zeroes after decimal point inside string.
		if ('0' == result_string[i]) {
			result_string.erase(i, i);
		} else if ('.' == result_string[i]) {
			result_string.erase(i, i);
			break;
		} else break;
	}
	for (long unsigned int i = 0; i < input_string.length(); ++i) { // Inserts " " before and after specified operators.
		if('*' == input_string[i] || '/' == input_string[i] ||
 				'+' == input_string[i] || '-' == input_string[i]) {
			input_string.insert(i, " ");
			i = i + 1;
			input_string.insert(i + 1, " ");
			i = i + 1;
		}
	}
	input_string = input_string + " = " + result_string;
}

void StoreEquation(std::deque<std::string>& history_deque, const std::string& equation) {
	if (history_deque.size() < 5) {
 		history_deque.push_front(equation);
	} else { // Prevents deque from growing greater than 5 indexes large.
		history_deque.pop_back();
		history_deque.push_front(equation);
	}
}

// ADD FACTORIAL SUPPORT?
} //End of namespace "commacalc".