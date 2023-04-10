#include "token.hpp"
#include "utils.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace std;

/* ------------------ Тестирование сравнения типов токена ------------------- */
TEST(TokenTypeCreationTest, AllComparation)
{
	const unsigned int biggestPrecedence{10};

	const token::TokenType second{token::Type::Number, biggestPrecedence,
								  token::Association::Left};
	const token::TokenType first{token::Type::Number, biggestPrecedence,
								 token::Association::Left};
	ASSERT_TRUE(first == second);
}

TEST(TokenTypeCreationTest, NotEqualType)
{
	const unsigned int biggestPrecedence{10};

	const token::TokenType first{token::Type::Number, biggestPrecedence,
								 token::Association::Left};
	const token::TokenType second{token::Type::Variable, biggestPrecedence,
								  token::Association::Left};
	ASSERT_FALSE(first == second);
}

TEST(TokenTypeCreationTest, NotEqualPrecedence)
{
	const unsigned int biggestPrecedence{10};
	const unsigned int lowerPrecedence{8};

	const token::TokenType first{token::Type::Number, biggestPrecedence,
								 token::Association::Left};
	const token::TokenType second{token::Type::Number, lowerPrecedence,
								  token::Association::Left};
	ASSERT_FALSE(first == second);
}

TEST(TokenTypeCreationTest, NotEqualAssociation)
{
	const unsigned int biggestPrecedence{10};

	const token::TokenType first{token::Type::Number, biggestPrecedence,
								 token::Association::Left};
	const token::TokenType second{token::Type::Number, biggestPrecedence,
								  token::Association::Right};
	ASSERT_FALSE(first == second);
}

/* --------------------- Тестирование сравнения Токенов --------------------- */
TEST(TokenCreationTest, EqualTokens)
{
	const token::Token first{
		"17", {token::Type::Number, 0, token::Association::None}
	};
	const token::Token second{
		"17", {token::Type::Number, 0, token::Association::None}
	};
	ASSERT_TRUE(first == second);
}

TEST(TokenCreationTest, NotEqualTokens)
{
	const token::Token first{
		"17", {token::Type::Number, 0, token::Association::None}
	};
	const token::Token second{
		"42", {token::Type::Number, 0, token::Association::None}
	};
	ASSERT_FALSE(first == second);
}

/* --------------------- Тестирование Токенизации строки -------------------- */
/* ---- Токенизация только числа */
TEST(TestTokenParse, TokenizerEmptyString)
{
	using namespace token;

	std::stringstream input{""};
	std::vector<Token> output;
	Error result{Error::None};

	result = token::tokenize(input, output);

	ASSERT_EQ(output.size(), 0);
	ASSERT_EQ(result, token::Error::EmptyString);
}

TEST(TestTokenParse, TokenizerNumbers)
{
	using namespace token;

	const std::string dataForTokenize = {"123 1 1000 3 17"};

	const int expectedSize = 5;
	std::stringstream input{dataForTokenize};
	std::vector<Token> output;
	Error result{Error::None};

	std::vector<Token> expected;
	for (const auto &item : utils::split(dataForTokenize, ' '))
	{
		expected.push_back({
			item, {Type::Number, 0, Association::None}
		  });
	}

	result = token::tokenize(input, output);

	ASSERT_EQ(result, token::Error::None);
	ASSERT_EQ(output.size(), expectedSize);
	ASSERT_EQ(output, expected);
}

/*
TODO: Create tokenization and for negative numbers
TEST(TestTokenParse, TokenizerNegativeNumbers)
{
	using namespace token;

	std::string dataForTokenize = {"-1 -88 1000 500 -42 666"};

	const int expectedSize = 6;
	std::stringstream input{dataForTokenize};
	std::vector<Token> output;
	Error result{Error::None};

	std::vector<Token> expected;
	for (const auto &item : utils::split(dataForTokenize, ' '))
	{
		expected.push_back({item, {Type::Number, 0, Association::None}});
	}

	result = token::tokenize(input, output);

	ASSERT_EQ(result, token::Error::None);
	ASSERT_EQ(output.size(), expectedSize);
	ASSERT_EQ(output, expected);
}
*/

/* ---- Токенизация только переменной */
TEST(TestTokenParse, TokenizerVariables)
{
	using namespace token;

	const std::string dataForTokenize = {"A Z c a"};

	const int expectedSize = 4;
	std::stringstream input{dataForTokenize};
	std::vector<Token> output;
	Error result{Error::None};

	std::vector<Token> expected;
	for (const auto &item : utils::split(dataForTokenize, ' '))
	{
		expected.push_back({
			item, {Type::Variable, 0, Association::None}
		});
	}

	result = token::tokenize(input, output);

	ASSERT_EQ(result, token::Error::None);
	ASSERT_EQ(output.size(), expectedSize);
	ASSERT_EQ(output, expected);
}

TEST(TestTokenParse, TokenizerVarAndNum)
{
	using namespace token;

	const std::string dataForTokenize = {"A 10 z"};

	const int expectedSize = 3;
	std::stringstream input{dataForTokenize};
	std::vector<Token> output;
	Error result{Error::None};

	const std::vector<Token> expected{
		{"A",  {Type::Variable, 0, Association::None}},
		{"10", {Type::Number, 0, Association::None}  },
		{"z",  {Type::Variable, 0, Association::None}},
	};

	result = token::tokenize(input, output);

	ASSERT_EQ(result, token::Error::None);
	ASSERT_EQ(output.size(), expectedSize);
	ASSERT_EQ(output, expected);
}

/* ------------------------------- RUN ALL TESTS ---------------------------- */
int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}