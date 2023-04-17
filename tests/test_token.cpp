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

/* ------------------------------- RUN ALL TESTS ---------------------------- */
int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}