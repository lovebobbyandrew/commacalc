#include "commacalc.h"
#include <iostream>

#define MAX_LENGTH 10

int main(){
	bool loop = true;
	std::string inputString;
	do{
		commacalc::printMenu();
		//READ INPUT STRING
		//CHECK VALIDITY OF INPUT STRING LENGTH
		//CLEAR INPUT BUFFER
		if (! commacalc::readInput(inputString, MAX_LENGTH)){ //If readInput returns false, there is no length error.			
			//CHECK FOR "EXIT" (ANY CASE)
			//CHECK FOR "HISTORY" (ANY CASE) 
			switch(commacalc::option(inputString)){
				case 1: //Expression entered by user.
					//FORMAT STRING FOR SIMPLE PARSING
					inputString = commacalc::removeSpace(inputString);
					//CHECK VALIDITY OF INPUT STRING EXPRESSION
					if(! commacalc::checkExpression(inputString)){
						//EVALUATE EXPRESSION
						//OUTPUT RESULT
						//STORE EXPRESSION AND RESULT IN HISTORY
					}
					break;
				case 2: //"HISTORY" entered by user
					//PRINT LAST 5 EXPRESSIONS AND RESULTS
					//LOOP TO START
					break;
				case 3: //"EXIT" entered by user
					loop = false;
					break;
			}
		}
	}while(loop);
	return 0;
}
