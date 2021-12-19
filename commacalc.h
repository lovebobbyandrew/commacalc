// Bobby Love
// December 17, 2021
// GNU GPL

#include <string>

namespace commacalc {

void PrintMenu(void); //Prints options

bool ReadInput(std::string&, int); //Reads from stdin and checks length

void ClearStdin(void); //Clears input buffer

unsigned short Option(std::string); //Checks for keywords "HISTORY" and "EXIT"

void PrintHist(void); //Prints last 5 expressions and results

std::string RemoveSpace(std::string); //Removes whitespace

bool CheckExpr(std::string); //Checks that string is valid math expression

std::string FormatExpr(std::string); //Formats input string

double Calc(std::string); //Calls primitive math functions

void StoreExpr(std::string, double); //Stores expression and result

double Expo(double, double); //Performs exponentiation

double Mult(double, double); //Performs multiplication

double Div(double, double); //Performs division

double Add(double, double); //Performs addition

double Sub(double, double); //Performs subtraction
} //End of namespace commacalc.