#include "Expression.h"
std::string Functions[4] = { "cos", "sin", "exp", "ln" };
int Priority(std::string s)
{
	switch (s[0])
	{
	case '+': return 2;
	case '-': return 3;
	case '*': return 4;
	case '/': return 4;
	case '(': return 0;
	case ')': return 1;
	case '^': return 7;
	case 's': return 8;
	case 'c': return 8;
	case 'e': return 10;
	case 'U': return 6;
	default:
		return -1;
	}
}
bool IsFunction(std::string A)
{
	bool flag = 0;
	for (int i = 0; i < 3; i++)
	{
		if (A == Functions[i])
			flag = 1;
	}
	return flag;
}
bool IsBinary(std::string A)
{
	bool flag = 0;
	if (A == "+" || A == "-" || A == "^" || A == "*" || A == "/")
		flag = 1;
	return flag;
}
bool IsNumber(std::string A)
{
	bool flag = 0;
	if ((A[0] == '-' && A[1] >= 48 && A[1] <= 57) || ((A[0] >= 48 && A[0] <= 57)))
		flag = 1;
	return flag;
}
bool IsVariable(std::string _A)
{
	bool flag = 0;
	if (!IsFunction(_A) && (_A[0] >= 97 && _A[0] <= 122))
		flag = 1;
	return flag;

}
bool IsLeftAssoc(std::string _A)
{
	bool flag = 1;
	if (_A == "Unirminus-" || _A == "^")
		flag = 0;
	return flag;
}
std::vector<std::string> ExpressionCheckAndTransition(std::string A)
{
	std::vector<std::string> Result;
	std::string Tmp;
	int Status = 0;
	int BracketCounter = 0;
	int PointCounter = 0;
	bool Check = 0;
	for (int i = 0; i < A.size(); i++)
	{
		if ((A[i] >= 48 && A[i] <= 59) || A[i] == '.')
		{
			if (A[i] == '.')
			{
				PointCounter++;
				if (A[i + 1] < 48 || A[i + 1] > 59)
					Status = 4;
			}
			if (PointCounter > 1)
				Status = 4;
			Tmp = Tmp + A[i];
			if ((A[i + 1] < 48 || A[i + 1] > 59) && A[i + 1] != '.')
			{
				Result.push_back(Tmp);
				PointCounter = 0;
				Tmp.clear();
			}
		}
		else if (A[i] == '(')
		{
			Result.push_back("(");
		}
		else if (A[i] == ')')
		{
			Result.push_back(")");
		}
		else if ((A[i] == 'e') && (A[i + 1] == 'x') && (A[i + 2] == 'p'))
		{
			Result.push_back("exp");
			i = i + 2;
		}
		else if ((A[i] == 's') && (A[i + 1] == 'i') && (A[i + 2] == 'n'))
		{
			Result.push_back("sin");
			i = i + 2;
		}
		else if ((A[i] == 'c') && (A[i + 1] == 'o') && (A[i + 2] == 's'))
		{
			Result.push_back("cos");
			i = i + 2;
		}
		else if (A[i] >= 97 && A[i] <= 122)
		{
			Tmp = Tmp + A[i];
			while ((A[i + 1] >= 97 && A[i + 1] <= 122) || (A[i + 1] >= 48 && A[i + 1] <= 57))
			{
				Tmp = Tmp + A[i + 1];
				i++;
			}
			Result.push_back(Tmp);
			Tmp.clear();
		}
		else if (A[i] == '+' || A[i] == '-' || A[i] == '*' || A[i] == '/' || A[i] == '^')
		{
			Tmp = Tmp + A[i];
			Result.push_back(Tmp);
			Tmp.clear();
		}
		else
		{
			std::cout << "Symbol " << A[i] << " is not correct" << std::endl;
			Status = 4;
		}
	}
	if (Status == 4)
		throw "Not correct";
	for (int i = 0; i < Result.size(); i++)
	{
		if (Status == 4)
			throw "Not correct";
		else if (Status == 0)
		{
			if (Result[i] == "(")
			{
				BracketCounter++;
				Status = 0;
			}
			else if (IsNumber(Result[i]) || IsVariable(Result[i]))
			{
				Status = 1;
			}
			else if (IsFunction(Result[i]))
			{
				Status = 2;
				if (i == Result.size() - 1)
					Status = 4;
			}
			else if (Result[i] == "-")
			{
				Result[i] = "Unarminus-"; // если читать как одно слово с ударением на А, то похоже на заклинание
				Status = 3;
				if (i == Result.size() - 1)
					Status = 4;
			}
			else
			{
				Status = 4;
			}
		}
		else if (Status == 1)
		{
			if (Result[i] == ")")
			{
				BracketCounter--;
				if (BracketCounter < 0)
					Status = 4;
			}
			else if (IsBinary(Result[i]))
			{
				Status = 0;
			}
			else
			{
				Status = 4;
			}
		}
		else if (Status == 2)
		{
			if (Result[i] == "(")
			{
				BracketCounter++;
				Status = 0;
			}
			else
				throw "function operator should be written in brackets";
		}
		else if (Status == 3)
		{
			if (Result[i] == "(")
			{
				BracketCounter++;
				Status = 0;
			}
			else if (Result[i] == "-")
			{
				Status = 4;
			}
			else if (IsBinary(Result[i]))
			{
				Status = 0;
			}
			else if (IsFunction(Result[i]))
			{
				Status = 2;
				if (i == Result.size() - 1)
					Status = 4;
			}
			else if (IsNumber(Result[i]) || IsVariable(Result[i]))
			{
				Status = 1;
			}
			else
				Status = 4;
		}
	}
	//	for (int i = 0; i < Result.size(); i++)
	//		std::cout << Result[i] << std::endl;
	if (Status == 4)
		throw "Something in your expressiong is wrong";
	return Result;
}
std::vector<std::string> ExpressionIntoPolsca(std::vector<std::string> _A)
{
	std::vector<std::string> Result;
	std::stack<std::string> Funcs;
	std::string Tmp;
	//	std::cout  << std::endl << std::endl << std::endl << std::endl;
	for (int i = 0; i < _A.size(); i++)
	{
		//		std::cout << _A[i] << "  "<< i << std::endl;
		if (_A[i] == "(")
		{
			Funcs.push(_A[i]);
		}
		if (_A[i] == ")")
		{
			while (Funcs.top() != "(")
			{
				Result.push_back(Funcs.top());
				Funcs.pop();
			}
			Funcs.pop();
		}
		if ((IsNumber(_A[i]) || (IsVariable(_A[i]))))
		{
			Result.push_back(_A[i]);
		}
		if (IsBinary(_A[i]) || IsFunction(_A[i]) || _A[i] == "Unarminus-")
		{
			if (Funcs.empty())
			{
				Funcs.push(_A[i]);
			}
			else
			{
				while (!Funcs.empty() && (IsLeftAssoc(_A[i]) && Priority(_A[i]) <= Priority(Funcs.top()))
					|| (!IsLeftAssoc(_A[i]) && Priority(_A[i]) < Priority(Funcs.top())))
				{
					Result.push_back(Funcs.top());
					Funcs.pop();
				}
				Funcs.push(_A[i]);
			}
		}
	}
	while (!Funcs.empty())
	{
		Result.push_back(Funcs.top());
		Funcs.pop();
	}
	return Result;
}
double ExpressiongCalculate(std::vector<std::string> _A)
{
	double tmp;
	std::stack<double> NumbersStack;
	int count = 0;
	for (int i = 0; i < _A.size(); i++)
	{
		if (IsVariable(_A[i]))
		{
			std::cout << "What is the value of: " << _A[i] << std::endl;
			std::cin >> tmp;
			for (int j = i + 1; j < _A.size(); j++)
			{
				if (_A[i] == _A[j])
				{
					_A[j] = std::to_string(tmp);
				}
			}
			_A[i] = std::to_string(tmp);
		}
	}
	for (int i = 0; i < _A.size(); i++)
	{
		if (IsNumber(_A[i]))
		{
			tmp = stod(_A[i]);
			NumbersStack.push(tmp);
		}
		if (_A[i] == "+")
		{
			tmp = NumbersStack.top();
			NumbersStack.pop();
			tmp = tmp + NumbersStack.top();
			NumbersStack.pop();
			NumbersStack.push(tmp);
		}
		if (_A[i] == "-")
		{
			tmp = NumbersStack.top();
			NumbersStack.pop();
			tmp = -tmp + NumbersStack.top();
			NumbersStack.pop();
			NumbersStack.push(tmp);
		}
		if (_A[i] == "*")
		{
			tmp = NumbersStack.top();
			NumbersStack.pop();
			tmp = tmp * NumbersStack.top();
			NumbersStack.pop();
			NumbersStack.push(tmp);
		}
		if (_A[i] == "/")
		{
			tmp = NumbersStack.top();
			if (tmp == 0)
				throw "Division by zero";
			NumbersStack.pop();
			tmp = NumbersStack.top() / tmp;
			NumbersStack.pop();
			NumbersStack.push(tmp);
		}
		if (_A[i] == "^")
		{
			tmp = NumbersStack.top();
			NumbersStack.pop();
			tmp = pow(NumbersStack.top(), tmp);
			NumbersStack.pop();
			NumbersStack.push(tmp);
		}
		if (_A[i] == "Unarminus-")
		{
			tmp = -(NumbersStack.top());
			NumbersStack.pop();
			NumbersStack.push(tmp);
		}
		if (_A[i] == "sin")
		{
			tmp = sin(NumbersStack.top());
			NumbersStack.pop();
			NumbersStack.push(tmp);
		}
		if (_A[i] == "cos")
		{
			tmp = cos(NumbersStack.top());
			NumbersStack.pop();
			NumbersStack.push(tmp);
		}
		if (_A[i] == "exp")
		{
			tmp = exp(NumbersStack.top());
			NumbersStack.pop();
			NumbersStack.push(tmp);
		}
	}
	return NumbersStack.top();
}
double ExpressiongSolve(std::string _A)
{
	std::vector<std::string> B = ExpressionCheckAndTransition(_A);
	B = ExpressionIntoPolsca(B);
	return ExpressiongCalculate(B);
}
int Priority(char s)
{
	switch (s)
	{
	case '+': return 2;
	case '-': return 3;
	case '*': return 3;
	case '/': return 5;
	case '(': return 0;
	case ')': return 1;
	case '^': return 7;
	case 's': return 8;
	case 'e': return 10;
	default:
		return -1;
	}
}
bool ExpressionCheck(std::string _A)
{
	int Status = 0;
	int BracketCounter = 0;
	int PointCounter = 0;
	bool Check = 0;
	for (int i = 0; i <= _A.size(); i++)
	{
		if (Status == 4)
			return 1;
		if (Status == 3)
			return 0;
		if (Status == 2)
		{
			if ((BracketCounter == 0) && (PointCounter == 0))
				return 1;
			else
				return 0;
		}
		if (Status == 1)
		{
			if (PointCounter > 1)
			{
				Status = 3;
			}
			else if (_A[i] == 0)
			{
				Status = 2;
				PointCounter = 0;
			}
			else if (_A[i] == 41)
			{
				BracketCounter--;
				if (BracketCounter >= 0)
					Status = 1;
				else Status = 3;
				PointCounter = 0;
			}
			else if ((_A[i] >= 48 && _A[i] <= 59))
			{
				Status = 1;
				PointCounter = 0;
			}
			else if (_A[i] == 44)
			{
				PointCounter++;
				Status = 1;
				if (_A[i + 1] == 0)
					Status = 3;
			}
			else if (_A[i] == '+' || _A[i] == '-' || _A[i] == '^' || _A[i] == '/' || _A[i] == '*')
			{
				Status = 0;
				PointCounter = 0;
			}
			else Status = 3;
		}
		else if (Status == 0)
		{
			if (_A[i] == 10)
			{
				Status = 2;
			}
			else if (_A[i] == 40)
			{
				BracketCounter++;
				Status = 0;

			}
			else if ((_A[i] >= 48) && (_A[i] <= 57))
			{
				Status = 1;
			}
			else if (_A[i] == 'e' || _A[i] == 's' || _A[i] == 'c')
			{
				if (_A[i + 1] == 0)
					Status = 4;
				else Status = 0;
			}
			else Status = 3;
		}
	}
	if (Status != 3)
		Check = 1;
	return Check;
}
std::string ExpressionParse(std::string _A)
{
	TStack<char> Polska;
	char tmp;
	std::string Result;
	for (int i = 0; i < _A.size(); i++)
	{
		if (_A[i] == '(')
		{
			Polska.Push(_A[i]);
		}
		if (_A[i] == ')')
		{
			while (Polska.Top() != '(')
			{
				tmp = Polska.Pop();
				Result = Result + tmp;
			}
			Polska.Pop();
		}
		if (((_A[i] >= 48 && _A[i] <= 59)) || (_A[i] == 44))
		{
			Result = Result + _A[i];
			if ((_A[i + 1] < 48 || _A[i + 1] > 59) && (_A[i + 1] != 44))
			{
				Result = Result + '|';
			}

		}
		if (_A[i] == '+' || _A[i] == '-' || _A[i] == 'e' || _A[i] == '^' || _A[i] == '/' || _A[i] == '*')
		{
			if (Polska.IsEmpty())
			{
				Polska.Push(_A[i]);
			}
			else
			{
				while (!Polska.IsEmpty() && (Priority(_A[i])) < Priority(Polska.Top()))
				{
					Result = Result + Polska.Pop();
				}
				Polska.Push(_A[i]);
			}
		}
	}
	while (!Polska.IsEmpty())
	{
		Result = Result + Polska.Pop();
	}
	return Result;
}
double ExpressionSolveV2(std::string _A)
{
	double tmp;
	TStack<double> NumbersStack;
	int count = 0;
	int IntegerPart = 1;
	double mult = 0.1;
	for (int i = 0; i < _A.size(); i++)
	{
		//std::cout << "TOP " << NumbersStack.Top() << std::endl;
		switch (_A[i])
		{
		case '+':
			NumbersStack.Push((NumbersStack.Pop()) + (NumbersStack.Pop()));

			break;
		case '-':
			tmp = NumbersStack.Pop();
			NumbersStack.Push((NumbersStack.Pop()) - tmp);
			break;
		case '*':
			NumbersStack.Push((NumbersStack.Pop())*(NumbersStack.Pop()));
			break;
		case '/':
			tmp = NumbersStack.Pop();
			NumbersStack.Push((NumbersStack.Pop()) / tmp);
			break;
		case 'e':
			NumbersStack.Push(exp(NumbersStack.Pop()));
			break;
		case 's':
			NumbersStack.Push(sin(NumbersStack.Pop()));
			break;
		case 'c':
			NumbersStack.Push(cos(NumbersStack.Pop()));
			break;
		case '^':
			NumbersStack.Push(pow(NumbersStack.Pop(), NumbersStack.Pop()));
			break;
		case '|':
			break;
		case ',':
			IntegerPart = 0;
			break;
		default:
			if (count == 0)
				tmp = _A[i] - 48;
			else
			{
				if (IntegerPart)
				{
					tmp = tmp * 10 + _A[i] - 48;
				}
				else
				{
					tmp = tmp + mult * (_A[i] - 48);
					mult = mult / 10;
				}
			}
			if ((_A[i + 1] < 48 || _A[i + 1] > 59) && (_A[i + 1] != 44))
			{
				NumbersStack.Push(tmp);
				count = -1;
				tmp = 0;
				mult = 0.1;
			}
			count++;
		}
	}
	return NumbersStack.Top();
}