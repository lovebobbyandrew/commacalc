// Bobby Love
// December 17, 2021
// GNU GPL

#include "commacalc.h"
#include <iostream> //ONLY USED FOR TEST COUT STATEMENTS: REMOVE ONCE FINISHED DEBUGGING

#define MAX_LENGTH 50

int main() {
	bool loop = true;
	double result;
	std::string input_string; // User input string.
	std::string expression_string; // Formatted version of input_string used for parsing.
	std::string equation_string; // Combination of expression_string and to_string(result).
	std::deque<std::string> history_deque; //Holds up to 5 previous equation_string values.
	do {
		commacalc::PrintMenu();
		//READ INPUT STRING
		//CHECK VALIDITY OF INPUT STRING LENGTH
		//CLEAR INPUT BUFFER
		if (!commacalc::ReadInput(input_string, MAX_LENGTH)) { // If ReadInput returns false, there is no length error.			
			//CHECK FOR "EXIT" (ANY CASE)
			//CHECK FOR "HISTORY" (ANY CASE) 
			switch (commacalc::Option(input_string)) {
				case 1: //Expression entered by user.
					//FORMAT STRING FOR SIMPLE PARSING
					expression_string = commacalc::ReplaceSpace(input_string);
					expression_string = commacalc::RemoveSpace(expression_string);
					expression_string = commacalc::DecimalMult(expression_string);
					std::cout << "input_string is \"" << input_string << "\"." << std::endl;
					std::cout << "expression_string is \"" << expression_string << "\"." << std::endl;
					//CHECK VALIDITY OF INPUT STRING EXPRESSION
					if(!commacalc::CheckExpression(expression_string)) { // If CheckExpr returns false, there is no expression error.
						std::cout << "Valid expression." << std::endl;
						//PARSE VALUES AND OPERATIONS FROM STRING
						//EVALUATE EXPRESSION
						//OUTPUT RESULT
						result = commacalc::Calculate(expression_string);
						//STORE EXPRESSION AND RESULT IN HISTORY
						equation_string = commacalc::MakeEquation(expression_string, result);
						std::cout << "equation_string is \"" << equation_string << "\"." << std::endl;
						history_deque = commacalc::StoreEquation(history_deque, equation_string);
					}
					else std::cout << "Invalid expression." << std::endl;
					break;
				case 2: //"HISTORY" entered by user.
					//PRINT LAST 5 EXPRESSIONS AND RESULTS
					commacalc::PrintHistory(history_deque);
					//LOOP TO START
					break;
				case 3: //"EXIT" entered by user.
					loop = false;
					//EXIT LOOP
					break;
			}
		}
	}while (loop);
	return 0;
}