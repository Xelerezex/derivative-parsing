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

/* -------------------Тестирование класса UnitParser ------------------------ */
TEST(BasicUnitParser, ParseInteger)
{
	using namespace utils;

	std::stringstream stream{"47 -55 78"};
	UnitParser::Error error{UnitParser::Error::None};

	UnitParser unit{stream};

	int output{0};

	// Первая итерация
	error = unit.parseInteger(output);

	ASSERT_EQ(error, UnitParser::Error::None);
	ASSERT_EQ(unit.getLastError(), UnitParser::Error::None);
	ASSERT_EQ(output, 47);

	// Вторая итерация
	error = unit.parseInteger(output);

	ASSERT_EQ(error, UnitParser::Error::None);
	ASSERT_EQ(unit.getLastError(), UnitParser::Error::None);
	ASSERT_EQ(output, -55);

	// Третья итерация
	error = unit.parseInteger(output);

	ASSERT_EQ(error, UnitParser::Error::None);
	ASSERT_EQ(unit.getLastError(), UnitParser::Error::None);
	ASSERT_EQ(output, 78);
}

TEST(BasicUnitParser, ParseIntegerWithError)
{
	using namespace utils;

	{
		std::stringstream stream{"abc"};
		UnitParser::Error error{UnitParser::Error::None};

		UnitParser unit{stream};

		int output{0};
		error = unit.parseInteger(output);

		ASSERT_EQ(error, UnitParser::Error::ParsingError);
		ASSERT_EQ(unit.getLastError(), UnitParser::Error::ParsingError);
	}
	{
		std::stringstream stream{"-"};
		UnitParser::Error error{UnitParser::Error::None};

		UnitParser unit{stream};

		int output{0};
		error = unit.parseInteger(output);

		ASSERT_EQ(error, UnitParser::Error::ParsingError);
		ASSERT_EQ(unit.getLastError(), UnitParser::Error::ParsingError);
	}
}

/* ----------------------------- RUN ALL TESTS ------------------------------ */
int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}