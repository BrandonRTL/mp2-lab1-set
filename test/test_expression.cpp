#include "Expression.h"
#include <gtest.h>

TEST(TExpression, can_calculate_some_easy_expression_1)
{
	std::string A = "2+3";
	std::string B = ExpressionParse(A);

	EXPECT_EQ(ExpressionCheck(A), 1);
	EXPECT_EQ(ExpressionSolveV2(B), 5);
}
TEST(TExpression, can_calculate_some_easy_expression_2)
{
	std::string A = "(2+3)*6/3+1";
	std::string B = ExpressionParse(A);

	EXPECT_EQ(ExpressionCheck(A), 1);
	EXPECT_EQ(ExpressionSolveV2(B), 11);
}
TEST(TExpression, can_calculate_some_easy_expression_3)
{
	std::string A = "(2^2+1)+3*((5+1)/2)";
	std::string B = ExpressionParse(A);

	EXPECT_EQ(ExpressionCheck(A), 1);
	EXPECT_EQ(ExpressionSolveV2(B), 14);
}
TEST(TExpression, can_calculate_some_easy_expression_4)
{
	std::string A = "3+4*2/(1-5)^2^3";
	std::string B = ExpressionParse(A);

	EXPECT_EQ(ExpressionCheck(A), 1);
	EXPECT_EQ(ExpressionSolveV2(B), 3.0001220703125);
}
TEST(TExpression, can_calculate_some_easy_expression_5)
{
	std::string A = "5^2^(2+2)";
	std::string B = ExpressionParse(A);

	EXPECT_EQ(ExpressionCheck(A), 1);
	EXPECT_EQ(ExpressionSolveV2(B), 152587890625);
}
TEST(TExpression, can_calculate_expression_with_unar_operators_1)
{
	std::string A = "e(0)";
	EXPECT_EQ(ExpressionCheck(A), 1);

	if (ExpressionCheck(A))
	{
		std::string B = ExpressionParse(A);

		EXPECT_EQ(ExpressionSolveV2(B), 1);
	}
}
TEST(TExpression, can_calculate_expression_with_unar_operators_2)
{
	std::string A = "e(e(0)-e(0))";
	EXPECT_EQ(ExpressionCheck(A), 1);

	if (ExpressionCheck(A))
	{
		std::string B = ExpressionParse(A);

		EXPECT_EQ(ExpressionSolveV2(B), 1);
	}
}
TEST(TExpression, returns_NULL_when_incorrect_expression_1)
{
	std::string A = "1,";

	EXPECT_EQ(ExpressionCheck(A), 0);
}
TEST(TExpression, returns_NULL_when_incorrect_expression_2)
{
	std::string A = "(1+2))";

	EXPECT_EQ(ExpressionCheck(A), 0);
}
TEST(TExpression, returns_NULL_when_incorrect_expression_3)
{
	std::string A = "(1,2*2,,1))";

	EXPECT_EQ(ExpressionCheck(A), 0);
}
TEST(TExpression, returns_NULL_when_incorrect_expression_4)
{
	std::string A = "(1,2*2,,1)),";

	EXPECT_EQ(ExpressionCheck(A), 0);
}
TEST(TExpression, returns_NULL_when_incorrect_expression_5)
{
	std::string A = "a";

	EXPECT_EQ(ExpressionCheck(A), 0);
}
TEST(TExpression, returns_NULL_when_incorrect_expression_6)
{
	std::string A = "a+b,23as";

	EXPECT_EQ(ExpressionCheck(A), 0);
}
TEST(TExpression, returns_1_when_correct_expression_1)
{
	std::string A = "1,1";

	EXPECT_EQ(ExpressionCheck(A), 1);
}
TEST(TExpression, returns_1_when_correct_expression_2)
{
	std::string A = "(1+2)";

	EXPECT_EQ(ExpressionCheck(A), 1);
}
TEST(TExpression, returns_1_when_correct_expression_3)
{
	std::string A = "(1,2*2,1)";

	EXPECT_EQ(ExpressionCheck(A), 1);
}


TEST(TExpressionV2, can_calculate_simple_expression_1)
{
	std::string A = "(2^2+1)+3*((5+1)/2)";
	std::vector<std::string> B = ExpressionCheckAndTransition(A);
	B = ExpressionIntoPolsca(B);

	EXPECT_EQ(14, ExpressiongCalculate(B));
}
TEST(TExpressionV2, can_calculate_simple_expression_2)
{
	std::string A = "5^2^(2+2)";
	std::vector<std::string> B = ExpressionCheckAndTransition(A);
	B = ExpressionIntoPolsca(B);

	EXPECT_EQ(152587890625, ExpressiongCalculate(B));
}
TEST(TExpressionV2, can_calculate_simple_expression_3)
{
	std::string A = "exp(exp(0)-exp(0))";
	std::vector<std::string> B = ExpressionCheckAndTransition(A);
	B = ExpressionIntoPolsca(B);

	EXPECT_EQ(1, ExpressiongCalculate(B));
}
TEST(TExpressionV2, can_calculate_some_easy_expression_4)
{
	std::string A = "(5+6)*2";
	std::vector<std::string> B = ExpressionCheckAndTransition(A);
	B = ExpressionIntoPolsca(B);

	EXPECT_EQ(22, ExpressiongCalculate(B));
}
TEST(TExpressionV2, can_calculate_unarminus_expression_1)
{
	std::string A = "-(2.000+1)^3*(2+2)/(4*3)";
	std::vector<std::string> B = ExpressionCheckAndTransition(A);
	B = ExpressionIntoPolsca(B);

	EXPECT_EQ(-9, ExpressiongCalculate(B));
}
TEST(TExpressionV2, can_calculate_unarminus_expression_2)
{
	std::string A = "-(5+6)*2";
	std::vector<std::string> B = ExpressionCheckAndTransition(A);
	B = ExpressionIntoPolsca(B);

	EXPECT_EQ(-22, ExpressiongCalculate(B));
}
TEST(TExpressionV2, can_calculate_unarminus_expression_3)
{
	std::string A = "-sin(0)";
	std::vector<std::string> B = ExpressionCheckAndTransition(A);
	B = ExpressionIntoPolsca(B);

	EXPECT_EQ(0, ExpressiongCalculate(B));
}
TEST(TExpressionV2, can_calculate_unarminus_expression_4)
{
	std::string A = "exp(1)+(-exp(1))";
	std::vector<std::string> B = ExpressionCheckAndTransition(A);
	B = ExpressionIntoPolsca(B);

	EXPECT_EQ(0, ExpressiongCalculate(B));
}
TEST(TExpressionV2, can_calculate_expression_1)
{
	std::string A = "((2+3/4)/1.1+(3+1/3))/(2.5-0.4*10/3)*(7/5)-((2+1/6+4.5)*0.375)/(2.75-1-1/2)";
	std::vector<std::string> B = ExpressionCheckAndTransition(A);
	B = ExpressionIntoPolsca(B);

	EXPECT_EQ(5, ExpressiongCalculate(B));
}
TEST(TExpressionV2, can_calculate_expression_2)
{
	std::string A = "((2+38/45-1/15)/(13+8/9)+((3+3/65)*26/99))/((18.5-13-7/9)*1/85)*(1/9)+3";
	std::vector<std::string> B = ExpressionCheckAndTransition(A);
	B = ExpressionIntoPolsca(B);

	EXPECT_EQ(5, ExpressiongCalculate(B));
}
TEST(TExpressionV2, can_calculate_expression_3)
{
	std::string A = "((-65)^2-56^2)^(1/2)";
	std::vector<std::string> B = ExpressionCheckAndTransition(A);
	B = ExpressionIntoPolsca(B);

	EXPECT_EQ(33, ExpressiongCalculate(B));
}
TEST(TExpressionV2, can_calculate_expression_4)
{
	std::string A = "((2*7^(1/2))^2)/4";
	std::vector<std::string> B = ExpressionCheckAndTransition(A);
	B = ExpressionIntoPolsca(B);

	EXPECT_EQ(7, int(ExpressiongCalculate(B)));
}
TEST(TExpressionV2, cant_divide_by_zero)
{
	std::string A = "2/0";
	std::vector<std::string> B = ExpressionCheckAndTransition(A);
	B = ExpressionIntoPolsca(B);

	EXPECT_ANY_THROW(ExpressiongCalculate(B));
}

TEST(TExpressionV2, throws_when_incorrect_expression_1)
{
	std::string A = "(1.2*2.1))";

	EXPECT_ANY_THROW(std::vector<std::string> B = ExpressionCheckAndTransition(A));
}
TEST(TExpressionV2, throws_when_incorrect_expression_2)
{
	std::string A = "(1.2*2..1)).";

	EXPECT_ANY_THROW(std::vector<std::string> B = ExpressionCheckAndTransition(A));
}
TEST(TExpressionV2, throws_when_incorrect_expression_3)
{
	std::string A = "1.";

	EXPECT_ANY_THROW(std::vector<std::string> B = ExpressionCheckAndTransition(A));
}
TEST(TExpressionV2, throws_when_incorrect_expression_4)
{
	std::string A = "1+sin";

	EXPECT_ANY_THROW(std::vector<std::string> B = ExpressionCheckAndTransition(A));
}
TEST(TExpressionV2, throws_when_incorrect_expression_5)
{
	std::string A = "sin()+1";

	EXPECT_ANY_THROW(std::vector<std::string> B = ExpressionCheckAndTransition(A));
}
TEST(TExpressionV2, throws_when_incorrect_expression_6)
{
	std::string A = "sin1";

	EXPECT_ANY_THROW(std::vector<std::string> B = ExpressionCheckAndTransition(A));
}
TEST(TExpressionV2, throws_when_incorrect_expression_7)
{
	std::string A = "--1";

	EXPECT_ANY_THROW(std::vector<std::string> B = ExpressionCheckAndTransition(A));
}





