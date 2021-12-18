#include <string>

void printMenu( void ); //Prints options

std::string readString( void ); //Reads from stdin

void clearStdin( void ); //Clears input buffer

bool checkLength( std::string ); //Checks validity of string length

int choice( std::string ); //Checks for keywords "HISTORY" and "EXIT"

void printHistory( void ); //Prints last 5 expressions and results

bool checkExpression( std::string ); //Checks that string is valid math expression

std::string formatExpression( std::string ); //Formats input string

double calculate( std::string ); //Calls primitive math functions

void storeExpression( std::string, double ); //Stores expression and result

double exponentiation( double, double ); //Performs exponentiation

double multiplication( double, double ); //Performs multiplication

double division( double, double ); //Performs division

double addition( double, double ); //Performs addition

double subtraction( double, double ); //Performs subtraction
