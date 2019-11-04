#include <iostream>
#include "Expression.h"

//---------------------------------------------------------------------------
using namespace std;
int main()
{
	string A = "((-65)^2-56^2)^(1/2)";
	cout << ExpressiongSolve(A);
	return 0;
}
//-----------------------------------------------------------------------------