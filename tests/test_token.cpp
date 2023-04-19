#include "token.hpp"
#include "utils.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

/* -------------------- Тестирование структуры TokenType -------------------- */
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

TEST(TokenTypeSwappingTest, NotEqualTokens)
{
	using namespace token;

	TokenType first{Type::Number, 0, Association::None};
	TokenType second{Type::Variable, 0, Association::None};

	swap(first, second);

	ASSERT_EQ(first,
			  (TokenType{token::Type::Variable, 0, token::Association::None}));

	ASSERT_EQ(second, (TokenType{Type::Number, 0, Association::None}));
}

/* ----------------------- Тестирование класса Token ------------------------ */
/* ==== Сравнение двух объектов: ==== */
TEST(TokenCreationTest, EqualTokens)
{
	const token::Token first{
		"17", {token::Type::Number, 0, token::Association::None}};
	const token::Token second{
		"17", {token::Type::Number, 0, token::Association::None}};
	ASSERT_TRUE(first == second);
}

TEST(TokenCreationTest, NotEqualTokens)
{
	const token::Token first{
		"17", {token::Type::Number, 0, token::Association::None}};
	const token::Token second{
		"42", {token::Type::Number, 0, token::Association::None}};
	ASSERT_FALSE(first == second);
}

/* ==== Создание объекта: ==== */
TEST(TokenCopyTest, CopyConstructorOperatorTokens)
{
	using namespace token;
	Token none{"0", {Type::None, 0, Association::None}};

	Token general{none};

	ASSERT_EQ(general, none);

	Token variable{"A", {Type::Variable, 2, Association::Right}};

	general = variable;

	ASSERT_NE(general, none);
	ASSERT_EQ(general, variable);
}

TEST(TokenSwapTest, NoEqualTokens)
{
	using namespace token;

	Token first{"11", {Type::Number, 0, Association::None}};
	Token second{"A", {Type::Variable, 2, Association::Right}};

	swap(first, second);

	Token firstWas{"11", {Type::Number, 0, Association::None}};
	Token secondWas{"A", {Type::Variable, 2, Association::Right}};

	ASSERT_EQ(first, secondWas);
	ASSERT_NE(first, firstWas);

	ASSERT_EQ(second, firstWas);
	ASSERT_NE(second, secondWas);
}

TEST(TokenMoveTest, CopyConstructorOperatorTokens)
{
	using namespace token;

	Token none{"0", {Type::None, 0, Association::None}};

	Token general = std::move(none);

	ASSERT_EQ(general, (Token{"0", {Type::None, 0, Association::None}}));

	Token variable{"A", {Type::Variable, 2, Association::Right}};

	general = std::move(variable);

	ASSERT_EQ(general, (Token{"A", {Type::Variable, 2, Association::Right}}));
}

/* ==== Создание объекта через фабричный метод ==== */
TEST(TokenCreationTest, EmptyInput)
{
	using namespace token;

	EXPECT_THROW(
		{
			try
			{
				Token numOne = Token::createToken("");
			}
			catch (const std::logic_error &except)
			{
				EXPECT_STREQ("Empty token string", except.what());
				throw;
			}
		},
		std::logic_error);
}

TEST(TokenCreationTest, CreateNumber)
{
	using namespace token;

	Token numOne = Token::createToken("10");
	ASSERT_EQ(numOne, (Token{"10", {Type::Number, 0, Association::None}}));

	Token unknown = Token::createToken("-.-10");
	ASSERT_EQ(unknown, (Token{"-.-10", {Type::None, 0, Association::None}}));
}

TEST(TokenCreationTest, CreateVariable)
{
	using namespace token;

	Token variable = Token::createToken("X");
	ASSERT_EQ(variable, (Token{"X", {Type::Variable, 0, Association::None}}));

	variable = Token::createToken("x");
	ASSERT_EQ(variable, (Token{"x", {Type::Variable, 0, Association::None}}));

	Token unknown = Token::createToken("xX");
	ASSERT_EQ(unknown, (Token{"xX", {Type::None, 0, Association::None}}));

	unknown = Token::createToken("-x");
	ASSERT_EQ(unknown, (Token{"-x", {Type::None, 0, Association::None}}));
}

/* ------------------------------- RUN ALL TESTS ---------------------------- */
int main (int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}