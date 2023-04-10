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

/* ----------------------------- RUN ALL TESTS ------------------------------ */
int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}