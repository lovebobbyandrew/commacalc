#include "commacalc.h"
#include <iostream>

#define MAX_LENGTH 10

int main(){
	
	bool loop = true;
	unsigned short choice;
	std::string inputString;

	//START
	do{

		//PRINT INSTRUCTIONS
		printMenu();

		//READ INPUT STRING
		//CHECK VALIDITY OF INPUT STRING LENGTH
		//CLEAR INPUT BUFFER
		if ( ! readInput( inputString, MAX_LENGTH ) ){ //If readInput returns false, no length error

			//CHECK FOR "EXIT" (ANY CASE)
			//CHECK FOR "HISTORY" (ANY CASE) 
			choice = option( inputString );

			switch( choice ){

				case 1: //Expression entered by user
	
					//PARSE EXPRESSION FROM STRING

					//CHECK VALIDITY OF INPUT STRING EXPRESSION

					//FORMAT STRING FOR SIMPLE PARSING

					//EVALUATE EXPRESSION
	
					//OUTPUT RESULT

					//STORE EXPRESSION AND RESULT IN HISTORY

					break;

				case 2: //"HISTORY" entered by user

					//PRINT LAST 5 EXPRESSIONS AND RESULTS

					//LOOP TO START
					break;

				case 3: //"EXIT" entered by user

					//BREAK
					loop = false;
					break;

			}

		}

		//LOOP TO START

	}while( loop );
	
	return 0;

}
