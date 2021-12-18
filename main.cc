#include "commacalc.h"
#include <iostream>

#define MAX_LENGTH 10

//NOTE FOR FUTURE ME: CONSIDER USING A NAMESPACE FOR GLOBAL HISTORY VARIABLE(S)

int main(){
	
	bool loop = true;
	std::string inputString;

	//START
	do{

		//PRINT INSTRUCTIONS
		printMenu();

		//READ INPUT STRING
		//CHECK VALIDITY OF INPUT STRING LENGTH
		//CLEAR INPUT BUFFER
		if ( ! readInput( inputString, MAX_LENGTH ) ){ //If readInput returns false, no length error

			//CHECK FOR "EXIT" (ANY CASE) -> BREAK

			//CHECK FOR "HISTORY" (ANY CASE) -> PRINT LAST 5 EXPRESSIONS AND RESULTS -> LOOP TO START

			//PARSE EXPRESSION FROM STRING

			//CHECK VALIDITY OF INPUT STRING EXPRESSION

			//FORMAT STRING FOR SIMPLE PARSING

			//EVALUATE EXPRESSION
	
			//OUTPUT RESULT

			//STORE EXPRESSION AND RESULT IN HISTORY

		}

		//LOOP TO START

	}while( loop );
	
	return 0;

}
