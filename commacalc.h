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

void PrintHistory(const std::deque<std::string>&); // Prints last 5 expressions and results.

void ReplaceSpace(std::string&); // Replaces whitespace between numbers with a single '*' (same as TI-89).

void RemoveSpace(std::string&); // Removes all whitespace from input string.

void DecimalSeparated(std::string&); // Inserts a '*' when 2 numbers are separated by 2 '.'.

void KeepChangeChange(std::string&); // Replaces double '-' directly before a digit with a single '+'.

bool CheckExpression(const std::string&); // Checks that string is valid math expression using other functions.

bool CheckChar(const std::string&); // Checks that string contains no invalid characters.

bool CheckDecimal(const std::string&); // Checks whether decimals used correctly.

bool CheckOperator(const std::string&); // Checks contents of indexes adjacent to an operator.

bool CheckDoubleOp(const std::string&); // Checks that string contains no double occurrences of operators other than '-'.

bool CheckParen(const std::string&); // Checks that string has matching parenthesis pairs.

bool CheckInsideParen(const std::string&); // Checks whether invalid operators are adjacent to a parenthesis.

bool CheckEmpty(const std::string&); // Checks whether string is empty.

bool CheckStartEnd(const std::string&); // Checks whether a string begins or ends with an valid operator.

bool CheckOperator(const std::string&); // Checks whether an operator has numbers on both sides.

double Calculate(const std::string&); // Calls primitive math functions.

void MakeEquation(std::string&, const double&); // Uses whitespace-less expression and result to output an equation string.

void StoreEquation(std::deque<std::string>&, const std::string&); // Stores equation string into history dequeue.

void Parenthesis(std::string&, const long unsigned int); // Evaluates parenthesis.

void Exponentiaion(std::string&); // Performs exponentiation.

void Multplication(std::string&); // Performs multiplication.

void Division(std::string&); // Performs division.

void Addition(std::string&); // Performs addition.

void Subtraction(std::string&); // Performs subtraction.

//CONSIDER ADDING SUPPORT FOR FACTORIALS
} // End of namespace "commacalc".