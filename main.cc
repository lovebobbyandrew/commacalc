// Bobby Love
// December 17, 2021
// GNU GPL

#include "commacalc.h"
#include <iostream> //REMOVE ONCE FINISHED DEBUGGING

#define MAX_LENGTH 50

int main() {
	bool loop = true;
	std::string input_string;
	do {
		commacalc::PrintMenu();
		//READ INPUT STRING
		//CHECK VALIDITY OF INPUT STRING LENGTH
		//CLEAR INPUT BUFFER
		if (!commacalc::ReadInput(input_string, MAX_LENGTH)) { //If readInput returns false, there is no length error.			
			//CHECK FOR "EXIT" (ANY CASE)
			//CHECK FOR "HISTORY" (ANY CASE) 
			switch (commacalc::Option(input_string)) {
				case 1: //Expression entered by user.
					//FORMAT STRING FOR SIMPLE PARSING
					input_string = commacalc::ReplaceSpace(input_string);
					input_string = commacalc::RemoveSpace(input_string);
					std::cout << "String is \"" << input_string << "\"" << std::endl;
					//CHECK VALIDITY OF INPUT STRING EXPRESSION
					if(!commacalc::CheckExpr(input_string)) {
						std::cout << "Valid expression." << std::endl;
						//EVALUATE EXPRESSION
						//OUTPUT RESULT
						//STORE EXPRESSION AND RESULT IN HISTORY
					}
					else std::cout << "Invalid expression." << std::endl;
					break;
				case 2: //"HISTORY" entered by user
					//PRINT LAST 5 EXPRESSIONS AND RESULTS
					std::cout << "HISTORY coming soon!" << std::endl;
					//LOOP TO START
					break;
				case 3: //"EXIT" entered by user
					loop = false;
					break;
			}
		}
	}while (loop);
	return 0;
}