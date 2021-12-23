// Bobby Love
// December 17, 2021
// GNU GPL

#include "commacalc.h"
#include <iostream> //ONLY USED FOR TEST COUT STATEMENTS: REMOVE ONCE FINISHED DEBUGGING

#define MAX_LENGTH 50

int main() {
	bool loop = true;
	double result;
	std::string input_string;
	std::deque<std::string> history_deque;
	do {
		commacalc::PrintMenu();
		// READ INPUT STRING
		// CHECK VALIDITY OF INPUT STRING LENGTH
		// CLEAR INPUT BUFFER
		if (!commacalc::ReadInput(input_string, MAX_LENGTH)) { // If ReadInput returns false, there is no length error.			
			// CHECK FOR "EXIT" (ANY CASE)
			// CHECK FOR "HISTORY" (ANY CASE) 
			switch (commacalc::Option(input_string)) {
				case 1: // Expression entered by user.
					// FORMAT STRING FOR SIMPLE PARSING
					std::cout << "input_string before modification is \"" << input_string << "\"." << std::endl;
					commacalc::ReplaceSpace(input_string);
					commacalc::RemoveSpace(input_string);
					commacalc::DecimalSeparated(input_string);
					commacalc::KeepChangeChange(input_string);
					std::cout << "input_string after modification is \"" << input_string << "\"." << std::endl;
					// CHECK VALIDITY OF INPUT STRING EXPRESSION
					if(!commacalc::CheckExpression(input_string)) { // If CheckExpr returns false, there is no expression error.
						std::cout << "Valid expression." << std::endl;
						// PARSE VALUES AND OPERATIONS FROM STRING
						// EVALUATE EXPRESSION
						// OUTPUT RESULT
						result = commacalc::Calculate(input_string);
						// STORE EXPRESSION AND RESULT IN HISTORY
						commacalc::MakeEquation(input_string, result);
						std::cout << "equation_string is \"" << input_string << "\"." << std::endl;
						commacalc::StoreEquation(history_deque, input_string);
					}
					else std::cout << "Invalid expression." << std::endl;
					break;
				case 2: // "HISTORY" entered by user.
					// PRINT LAST 5 EXPRESSIONS AND RESULTS
					commacalc::PrintHistory(history_deque);
					// LOOP TO START
					break;
				case 3: // "EXIT" entered by user.
					loop = false;
					// EXIT LOOP
					break;
			}
		}
	} while (loop);
	return 0;
}