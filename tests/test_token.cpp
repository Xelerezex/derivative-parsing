#include "token.hpp"
#include "utils.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

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
TEST(TokenCreationTest, DefaultTokenCreation)
{
	using namespace token;
	const Token none;

	ASSERT_EQ(none, (Token{"Empty", {Type::None, 0, Association::None}}));
}

TEST(TokenCopyTest, CopyConstructorOperatorTokens)
{
	using namespace token;
	const Token none;

	Token general{none};

	ASSERT_EQ(general, none);

	const Token variable{"A", {Type::Variable, 2, Association::Right}};

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

	const Token firstWas{"11", {Type::Number, 0, Association::None}};
	const Token secondWas{"A", {Type::Variable, 2, Association::Right}};

	ASSERT_EQ(first, secondWas);
	ASSERT_NE(first, firstWas);

	ASSERT_EQ(second, firstWas);
	ASSERT_NE(second, secondWas);
}

TEST(TokenMoveTest, CopyConstructorOperatorTokens)
{
	using namespace token;

	Token none;

	Token general = std::move(none);

	ASSERT_EQ(general, (Token{"Empty", {Type::None, 0, Association::None}}));

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
				const Token numOne = Token::createToken("");
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

	const Token numOne = Token::createToken("10");
	ASSERT_EQ(numOne, (Token{"10", {Type::Number, 0, Association::None}}));

	const Token unknown = Token::createToken("-.-10");
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

TEST(TokenCreationTest, CreateLeftParentesis)
{
	using namespace token;

	const Token variable = Token::createToken("(");
	ASSERT_EQ(variable,
			  (Token{"(", {Type::LeftParenthesis, 0, Association::None}}));

	Token unknown = Token::createToken("(x");
	ASSERT_EQ(unknown, (Token{"(x", {Type::None, 0, Association::None}}));

	unknown = Token::createToken("-(");
	ASSERT_EQ(unknown, (Token{"-(", {Type::None, 0, Association::None}}));
}

TEST(TokenCreationTest, CreateRightParentesis)
{
	using namespace token;

	const Token variable = Token::createToken(")");
	ASSERT_EQ(variable,
			  (Token{")", {Type::RightParenthesis, 0, Association::None}}));

	Token unknown = Token::createToken("x)");
	ASSERT_EQ(unknown, (Token{"x)", {Type::None, 0, Association::None}}));

	unknown = Token::createToken(")^");
	ASSERT_EQ(unknown, (Token{")^", {Type::None, 0, Association::None}}));
}

TEST(TokenCreationTest, CreatePlus)
{
	using namespace token;

	const Token plus = Token::createToken("+");
	ASSERT_EQ(plus, (Token{"+", {Type::Plus, 1, Association::Left}}));

	const Token unknown = Token::createToken("+x");
	ASSERT_EQ(unknown, (Token{"+x", {Type::None, 0, Association::None}}));
}

TEST(TokenCreationTest, CreateMinus)
{
	using namespace token;

	const Token minus = Token::createToken("-");
	ASSERT_EQ(minus, (Token{"-", {Type::Minus, 1, Association::Left}}));

	const Token unknown = Token::createToken("-x");
	ASSERT_EQ(unknown, (Token{"-x", {Type::None, 0, Association::None}}));
}

TEST(TokenCreationTest, CreateMultiplication)
{
	using namespace token;

	const Token multiplication = Token::createToken("*");
	ASSERT_EQ(multiplication,
			  (Token{"*", {Type::Multiplication, 2, Association::Left}}));

	const Token unknown = Token::createToken("*x");
	ASSERT_EQ(unknown, (Token{"*x", {Type::None, 0, Association::None}}));
}

TEST(TokenCreationTest, CreateDivision)
{
	using namespace token;

	const Token division = Token::createToken("/");
	ASSERT_EQ(division, (Token{"/", {Type::Division, 2, Association::Left}}));

	const Token unknown = Token::createToken("x/");
	ASSERT_EQ(unknown, (Token{"x/", {Type::None, 0, Association::None}}));
}

TEST(TokenCreationTest, CreateExponentiation)
{
	using namespace token;

	const Token exponentiation = Token::createToken("^");
	ASSERT_EQ(exponentiation,
			  (Token{"^", {Type::Exponentiation, 3, Association::Right}}));

	const Token unknown = Token::createToken("x^");
	ASSERT_EQ(unknown, (Token{"x^", {Type::None, 0, Association::None}}));
}

/* ---------------- Тестирование основных методов класса Token -------------- */
TEST(TokenGeneralMethods, IsNone)
{
	using namespace token;

	const Token exponentiation = Token::createToken("^");
	ASSERT_FALSE(exponentiation.isNone());

	const Token space = Token::createToken(" ");
	ASSERT_TRUE(space.isNone());

	const Token defaultToken;
	ASSERT_TRUE(defaultToken.isNone());
}

/* ------------------------------- RUN ALL TESTS ---------------------------- */
int main (int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}