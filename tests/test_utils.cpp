#include "utils.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

/* ---------------------Тестирование функции split -------------------------- */
TEST(BasicSplitTest, EmptyString)
{
	const std::string input;

	const std::vector<std::string> output = utils::split(input, ';');
	const std::vector<std::string> expected{};

	ASSERT_EQ(output, expected);
}

TEST(BasicSplitTest, SeparatorNoInString)
{
	const std::string input{"asfas 978a3kbfsd )(*^ ()*^)"};

	const std::vector<std::string> output = utils::split(input, '~');
	const std::vector<std::string> expected{"asfas 978a3kbfsd )(*^ ()*^)"};

	ASSERT_EQ(output, expected);
}

TEST(BasicSplitTest, SpaceSeparator)
{
	const std::string input{"   17 18 19 ab bc z98;as _=~"};

	const std::vector<std::string> output = utils::split(input, ' ');
	const std::vector<std::string> expected{
		"", "", "", "17", "18", "19", "ab", "bc", "z98;as", "_=~"};

	ASSERT_EQ(output, expected);
}

TEST(BasicSplitTest, DotSeparator)
{
	const std::string input{"  192     .      158 .      10 =^^@$&(#) . 12"};

	const std::vector<std::string> output = utils::split(input, '.');
	const std::vector<std::string> expected{
		"  192     ", "      158 ", "      10 =^^@$&(#) ", " 12"};

	ASSERT_EQ(output, expected);
}

/* ------------------ Тестирование функции isNumber ------------------------- */
TEST(BasicIsNumberTest, Number)
{
	const std::string input{"123"};

	const bool output = utils::isNumber(input);

	ASSERT_EQ(output, true);
}

TEST(BasicIsNumberTest, NegativeNumber)
{
	const std::string input{"-123"};

	const bool output = utils::isNumber(input);

	ASSERT_EQ(output, true);
}

TEST(BasicIsNumberTest, FractionalNumber)
{
	const std::string input{".0115"};

	const bool output = utils::isNumber(input);

	ASSERT_EQ(output, true);
}

TEST(BasicIsNumberTest, NegativeFractionalNumber)
{
	const std::string input{"-.0115"};

	const bool output = utils::isNumber(input);

	ASSERT_EQ(output, true);
}

TEST(BasicIsNumberTest, NegativeFractionalNotNumber)
{
	const std::string input{".-0115"};

	const bool output = utils::isNumber(input);

	ASSERT_EQ(output, false);
}

TEST(BasicIsNumberTest, FractionalNumberWithZero)
{
	const std::string input{"0.10115"};

	const bool output = utils::isNumber(input);

	ASSERT_EQ(output, true);
}

TEST(BasicIsNumberTest, NegativeFractionalNumberWithZero)
{
	const std::string input{"-0.10115"};

	const bool output = utils::isNumber(input);

	ASSERT_EQ(output, true);
}
TEST(BasicIsNumberTest, NegativeFractionalNumberWithNumber)
{
	const std::string input{"-1520.10115"};

	const bool output = utils::isNumber(input);

	ASSERT_EQ(output, true);
}

TEST(BasicIsNumberTest, OnlyMinus)
{
	const std::string input{"-"};

	const bool output = utils::isNumber(input);

	ASSERT_EQ(output, false);
}

TEST(BasicIsNumberTest, OnlyDot)
{
	const std::string input{"."};

	const bool output = utils::isNumber(input);

	ASSERT_EQ(output, false);
}

TEST(BasicIsNumberTest, MinusChar)
{
	const std::string input{"-a"};

	const bool output = utils::isNumber(input);

	ASSERT_EQ(output, false);
}

TEST(BasicIsNumberTest, OnlyChar)
{
	const std::string input{"a"};

	const bool output = utils::isNumber(input);

	ASSERT_EQ(output, false);
}

TEST(BasicIsNumberTest, OneCharsAndNumber)
{
	const std::string input{"1245a45"};

	const bool output = utils::isNumber(input);

	ASSERT_EQ(output, false);
}

TEST(BasicIsNumberTest, OneCharAndNegativeNumberWithDot)
{
	const std::string input{"-12.4545a"};

	const bool output = utils::isNumber(input);

	ASSERT_EQ(output, false);
}

TEST(BasicIsNumberTest, EmptyString)
{
	const std::string input{""};

	const bool output = utils::isNumber(input);

	ASSERT_EQ(output, false);
}

TEST(BasicIsNumberTest, OneSpace)
{
	const std::string input{" "};

	const bool output = utils::isNumber(input);

	ASSERT_EQ(output, false);
}

TEST(BasicIsNumberTest, FewSpaces)
{
	const std::string input{"    "};

	const bool output = utils::isNumber(input);

	ASSERT_EQ(output, false);
}

TEST(BasicIsNumberTest, OneSpaceAndNumber)
{
	const std::string input{"45 45"};

	const bool output = utils::isNumber(input);

	ASSERT_EQ(output, false);
}

TEST(BasicIsNumberTest, OneSpaceAndNegativeNumber)
{
	const std::string input{"45 -45"};

	const bool output = utils::isNumber(input);

	ASSERT_EQ(output, false);
}

TEST(BasicIsNumberTest, Expression)
{
	const std::string input{"45-45"};

	const bool output = utils::isNumber(input);

	ASSERT_EQ(output, false);
}

/* ------------------ Тестирование функции isVariable ----------------------- */
TEST(BasicIsVariableTest, EmptyString)
{
	const std::string input{""};

	const bool output = utils::isVariable(input);

	ASSERT_EQ(output, false);
}

TEST(BasicIsVariableTest, TooMuchSymbols)
{
	bool output = utils::isVariable("Z");
	ASSERT_EQ(output, true);

	output = utils::isVariable("ZZZ");
	ASSERT_EQ(output, false);

	output = utils::isVariable("aZ");
	ASSERT_EQ(output, false);
}

TEST(BasicIsVariableTest, CharacterIsVariable)
{
	bool output = utils::isVariable("A");
	ASSERT_EQ(output, true);

	output = utils::isVariable("Z");
	ASSERT_EQ(output, true);

	output = utils::isVariable("a");
	ASSERT_EQ(output, true);

	output = utils::isVariable("z");
	ASSERT_EQ(output, true);
}

TEST(BasicIsVariableTest, CharacterIsNotVariable)
{
	bool output = utils::isVariable("+");
	ASSERT_EQ(output, false);

	output = utils::isVariable("@");
	ASSERT_EQ(output, false);

	output = utils::isVariable("~");
	ASSERT_EQ(output, false);

	output = utils::isVariable("0");
	ASSERT_EQ(output, false);

	output = utils::isVariable("7");
	ASSERT_EQ(output, false);
}

/* --------------- Тестирование функции isLeftParenthesis ------------------- */
TEST(BasicIsLeftParenthesisTest, EmptyString)
{
	const std::string input{""};

	const bool output = utils::isLeftParenthesis(input);
	ASSERT_EQ(output, false);
}

TEST(BasicIsLeftParenthesisTest, TooMuchSymbols)
{
	bool output = utils::isLeftParenthesis("()");
	ASSERT_EQ(output, false);

	output = utils::isLeftParenthesis("(+");
	ASSERT_EQ(output, false);

	output = utils::isLeftParenthesis("(a");
	ASSERT_EQ(output, false);
}

TEST(BasicIsLeftParenthesisTest, CharacterIsLeftParenthesis)
{
	const std::string input{"("};

	bool output = utils::isLeftParenthesis(input);
	ASSERT_EQ(output, true);
}

TEST(BasicIsLeftParenthesisTest, CharacterIsNoLeftParenthesis)
{
	bool output = utils::isLeftParenthesis(")");
	ASSERT_EQ(output, false);

	output = utils::isLeftParenthesis("@");
	ASSERT_EQ(output, false);

	output = utils::isLeftParenthesis("+");
	ASSERT_EQ(output, false);

	output = utils::isLeftParenthesis("7");
	ASSERT_EQ(output, false);
}

/* --------------- Тестирование функции isRightParenthesis ------------------ */
TEST(BasicIsRightParenthesisTest, EmptyString)
{
	const std::string input{""};

	const bool output = utils::isRightParenthesis(input);
	ASSERT_EQ(output, false);
}

TEST(BasicIsRightParenthesisTest, TooMuchSymbols)
{
	bool output = utils::isRightParenthesis("()");
	ASSERT_EQ(output, false);

	output = utils::isRightParenthesis("+)");
	ASSERT_EQ(output, false);

	output = utils::isRightParenthesis("X)");
	ASSERT_EQ(output, false);
}

TEST(BasicIsRightParenthesisTest, CharacterIsRightParenthesis)
{
	const std::string input{")"};

	bool output = utils::isRightParenthesis(input);
	ASSERT_EQ(output, true);
}

TEST(BasicIsRightParenthesisTest, CharacterIsNotRightParenthesis)
{
	bool output = utils::isRightParenthesis("(");
	ASSERT_EQ(output, false);

	output = utils::isRightParenthesis("@");
	ASSERT_EQ(output, false);

	output = utils::isRightParenthesis("+");
	ASSERT_EQ(output, false);

	output = utils::isRightParenthesis("7");
	ASSERT_EQ(output, false);
}

/* ---------------- Тестирование функции isPlus ----------------------------- */
TEST(BasicIsPlusTest, EmptyString)
{
	const std::string input{""};

	const bool output = utils::isPlus(input);
	ASSERT_EQ(output, false);
}

TEST(BasicIsPlusTest, TooMuchSymbols)
{
	bool output = utils::isPlus("x+y");
	ASSERT_EQ(output, false);

	output = utils::isPlus("+x");
	ASSERT_EQ(output, false);

	output = utils::isPlus("++");
	ASSERT_EQ(output, false);
}

TEST(BasicIsPlusTest, CharacterIsPlus)
{
	const std::string input{"+"};

	bool output = utils::isPlus(input);
	ASSERT_EQ(output, true);
}

TEST(BasicIsPlusTest, CharacterIsNotPlus)
{
	bool output = utils::isPlus("(");
	ASSERT_EQ(output, false);

	output = utils::isPlus("@");
	ASSERT_EQ(output, false);

	output = utils::isPlus("-");
	ASSERT_EQ(output, false);

	output = utils::isPlus("7");
	ASSERT_EQ(output, false);
}

/* ---------------- Тестирование функции isMinus ---------------------------- */
TEST(BasicIsMinusTest, EmptyString)
{
	const std::string input{""};

	const bool output = utils::isMinus(input);
	ASSERT_EQ(output, false);
}

TEST(BasicIsMinusTest, TooMuchSymbols)
{
	bool output = utils::isMinus("x-y");
	ASSERT_EQ(output, false);

	output = utils::isMinus("-x");
	ASSERT_EQ(output, false);

	output = utils::isMinus("--");
	ASSERT_EQ(output, false);
}

TEST(BasicIsMinusTest, CharacterIsMinus)
{
	const std::string input{"-"};

	bool output = utils::isMinus(input);
	ASSERT_EQ(output, true);
}

TEST(BasicIsMinusTest, CharacterIsNotMinus)
{
	bool output = utils::isMinus("(");
	ASSERT_EQ(output, false);

	output = utils::isMinus("@");
	ASSERT_EQ(output, false);

	output = utils::isMinus("+");
	ASSERT_EQ(output, false);

	output = utils::isMinus("7");
	ASSERT_EQ(output, false);
}

/* ---------------- Тестирование функции isMultiplication ------------------- */
TEST(BasicIsMultiplicationTest, EmptyString)
{
	const std::string input{""};

	const bool output = utils::isMultiplication(input);
	ASSERT_EQ(output, false);
}

TEST(BasicIsMultiplicationTest, TooMuchSymbols)
{
	bool output = utils::isMultiplication("x*y");
	ASSERT_EQ(output, false);

	output = utils::isMultiplication("*x*");
	ASSERT_EQ(output, false);

	output = utils::isMultiplication("**");
	ASSERT_EQ(output, false);
}

TEST(BasicIsMultiplicationTest, CharacterIsMultiplication)
{
	const std::string input{"*"};

	bool output = utils::isMultiplication(input);
	ASSERT_EQ(output, true);
}

TEST(BasicIsMultiplicationTest, CharacterIsNotMultiplication)
{
	bool output = utils::isMultiplication("(");
	ASSERT_EQ(output, false);

	output = utils::isMultiplication("@");
	ASSERT_EQ(output, false);

	output = utils::isMultiplication("/");
	ASSERT_EQ(output, false);

	output = utils::isMultiplication("7");
	ASSERT_EQ(output, false);
}

/* ---------------- Тестирование функции isDivision ------------------------- */
TEST(BasicIsDivisionTest, EmptyString)
{
	const std::string input{""};

	const bool output = utils::isDivision(input);
	ASSERT_EQ(output, false);
}

TEST(BasicIsDivisionTest, TooMuchSymbols)
{
	bool output = utils::isDivision("x/y");
	ASSERT_EQ(output, false);

	output = utils::isDivision("/x");
	ASSERT_EQ(output, false);

	output = utils::isDivision("//");
	ASSERT_EQ(output, false);
}

TEST(BasicIsDivisionTest, CharacterIsDivision)
{
	const std::string input{"/"};

	bool output = utils::isDivision(input);
	ASSERT_EQ(output, true);
}

TEST(BasicIsDivisionTest, CharacterIsNotDivision)
{
	bool output = utils::isDivision("(");
	ASSERT_EQ(output, false);

	output = utils::isDivision("@");
	ASSERT_EQ(output, false);

	output = utils::isDivision("*");
	ASSERT_EQ(output, false);

	output = utils::isDivision("7");
	ASSERT_EQ(output, false);
}

/* ---------------- Тестирование функции isExponentiation ------------------- */
TEST(BasicIsExponentiationTest, EmptyString)
{
	const std::string input{""};

	const bool output = utils::isExponentiation(input);
	ASSERT_EQ(output, false);
}

TEST(BasicIsExponentiationTest, TooMuchSymbols)
{
	bool output = utils::isExponentiation("x^y");
	ASSERT_EQ(output, false);

	output = utils::isExponentiation("^x");
	ASSERT_EQ(output, false);

	output = utils::isExponentiation("^^");
	ASSERT_EQ(output, false);
}

TEST(BasicIsExponentiationTest, CharacterIsExponentiation)
{
	const std::string input{"^"};

	bool output = utils::isExponentiation(input);
	ASSERT_EQ(output, true);
}

TEST(BasicIsExponentiationTest, CharacterIsNotExponentiation)
{
	bool output = utils::isExponentiation("(");
	ASSERT_EQ(output, false);

	output = utils::isExponentiation("@");
	ASSERT_EQ(output, false);

	output = utils::isExponentiation("*");
	ASSERT_EQ(output, false);

	output = utils::isExponentiation("7");
	ASSERT_EQ(output, false);
}

/* ----------------------------- RUN ALL TESTS ------------------------------ */
int main (int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}