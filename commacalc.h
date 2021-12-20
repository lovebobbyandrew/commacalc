// Bobby Love
// December 17, 2021
// GNU GPL

#include <string>

namespace commacalc {

void PrintMenu(void); // Prints menu options.

bool ReadInput(std::string&, int); // Reads from stdin and checks length.

void ClearStdin(void); // Clears input buffer.

int Option(std::string); // Checks for keywords "HISTORY" and "EXIT".

void PrintHist(void); // Prints last 5 expressions and results.

std::string ReplaceSpace(std::string input_string); // Replaces whitespace between numbers with a single '*' (same as TI-89).

std::string RemoveSpace(std::string); // Removes whitespace from input string.

bool CheckExpr(std::string); // Checks that string is valid math expression using other functions.

bool CheckChar(std::string); // Checks that string contains no invalid characters.

bool CheckDoubleOp(std::string); // Checks that string contains no double occurrences of operators.

bool CheckParen(std::string); // Checks that string has matching parenthesis pairs.

bool CheckInsideParen(std::string); // Checks whether invalid operators are adjacent to a parenthesis.

bool CheckEmpty(std::string); // Checks whether string is empty.

bool CheckStartEnd(std::string); // Checks whether a string begins or ends with an valid operator.

bool CheckOperator(std::string); // Checks whether an operator has numbers on both sides.

double Calc(std::string); // Calls primitive math functions.

void StoreExpr(std::string, double); // Stores expression and result in history variable.

double Expo(double, double); // Performs exponentiation.

double Mult(double, double); // Performs multiplication.

double Div(double, double); // Performs division.

double Add(double, double); // Performs addition.

double Sub(double, double); // Performs subtraction.
} // End of namespace "commacalc".