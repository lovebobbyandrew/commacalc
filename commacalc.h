// Bobby Love
// December 17, 2021
// GNU GPL

#include <string>
#include <deque>

namespace commacalc {

void PrintMenu(void); // Prints menu options.

bool ReadInput(std::string&, const int); // Reads from stdin and checks length.

void ClearStdin(void); // Clears input buffer.

int Option(const std::string); // Checks for keywords "HISTORY" and "EXIT".

void PrintHistory(const std::deque<std::string>); // Prints last 5 expressions and results.

std::string ReplaceSpace(std::string); // Replaces whitespace between numbers with a single '*' (same as TI-89).

std::string RemoveSpace(std::string); // Removes all whitespace from input string.

std::string DecimalMult(std::string); // Inserts a '*' when 2 numbers are separated by 2 '.'.

bool CheckExpression(std::string); // Checks that string is valid math expression using other functions.

bool CheckChar(std::string); // Checks that string contains no invalid characters.

bool CheckDecimal(std::string); // Checks whether decimals used correctly.

bool CheckOperator(std::string); // Checks contents of indexes adjacent to an operator.

bool CheckDoubleOp(std::string); // Checks that string contains no double occurrences of operators other than '-'.

bool CheckParen(std::string); // Checks that string has matching parenthesis pairs.

bool CheckInsideParen(std::string); // Checks whether invalid operators are adjacent to a parenthesis.

bool CheckEmpty(std::string); // Checks whether string is empty.

bool CheckStartEnd(std::string); // Checks whether a string begins or ends with an valid operator.

bool CheckOperator(std::string); // Checks whether an operator has numbers on both sides.

double Calculate(std::string); // Calls primitive math functions.

std::string MakeEquation(std::string, double); // Uses whitespace-less expression and result to output an equation string.

std::deque<std::string> StoreEquation(std::deque<std::string>, std::string); // Stores equation string into history dequeue.

double Exponentiaion(double, double); // Performs exponentiation.

double Multplication(double, double); // Performs multiplication.

double Division(double, double); // Performs division.

double Addition(double, double); // Performs addition.

double Subtraction(double, double); // Performs subtraction.

//CONSIDER ADDING SUPPORT FOR FACTORIALS

} // End of namespace "commacalc".