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
	const std::vector<std::string> expected{"",	  "",	"",	  "17",		"18",
											"19", "ab", "bc", "z98;as", "_=~"};

	ASSERT_EQ(output, expected);
}

TEST(BasicSplitTest, DotSeparator)
{
	const std::string input{"  192     .      158 .      10 =^^@$&(#) . 12"};

	const std::vector<std::string> output = utils::split(input, '.');
	const std::vector<std::string> expected{"  192     ", "      158 ",
											"      10 =^^@$&(#) ", " 12"};

	ASSERT_EQ(output, expected);
}

/* ---------------------Тестирование функции split -------------------------- */
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

/* ----------------------------- RUN ALL TESTS ------------------------------ */
int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}