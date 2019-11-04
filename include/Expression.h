#ifndef __EXPRESSION_H__
#define __EXPRESSION_H__
#include <string>
#include <vector>
#include<stack>
#include<iostream>
#include <math.h>
#include "UStack.h"
int Priority(std::string s);
bool IsFunction(std::string A);
bool IsBinary(std::string A);
bool IsNumber(std::string A);
bool IsVariable(std::string _A);
bool IsLeftAssoc(std::string _A);
std::vector<std::string> ExpressionCheckAndTransition(std::string A);
std::vector<std::string> ExpressionIntoPolsca(std::vector<std::string> _A);
double ExpressiongCalculate(std::vector<std::string> _A);
double ExpressiongSolve(std::string _A);

int Priority(char s);
bool ExpressionCheck(std::string _A);
std::string ExpressionParse(std::string _A);
double ExpressionSolveV2(std::string _A);
#endif