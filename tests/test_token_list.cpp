#include "tokenlist.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

/* ------------------- Тестирование Класса TokenList ------------------------ */
/* ==== Создание объекта: ==== */
TEST(TokenListCopyTest, CopyConstructorOperatorTokens)
{
	using namespace token;

	const TokenList none;
	TokenList general{none};

	ASSERT_EQ(general, none);

	const TokenList variable;
	general = variable;

	ASSERT_EQ(general, variable);
}

TEST(TokenListMoveTest, CopyConstructorOperatorTokens)
{
	using namespace token;

	TokenList none;

	TokenList general = std::move(none);

	ASSERT_EQ(general, (TokenList{}));

	TokenList variable{{
		Token{"A", {Type::Variable, 2, Association::Right}},
	}};

	general = std::move(variable);

	ASSERT_EQ(general,
			  (TokenList{{
				  Token{"A", {Type::Variable, 2, Association::Right}},
			  }}));
}
/* ==== Сравнение объектов: ==== */
TEST(TokenListComparasionTests, CompareEqual)
{
	using namespace token;

	const TokenList list{{
		Token{"1000", {Type::Number, 0, Association::None}},
		Token{"+", {Type::Plus, 1, Association::Left}},
		Token{"x", {Type::Variable, 0, Association::None}},
	}};
	const TokenList copy{{
		Token{"1000", {Type::Number, 0, Association::None}},
		Token{"+", {Type::Plus, 1, Association::Left}},
		Token{"x", {Type::Variable, 0, Association::None}},
	}};

	ASSERT_EQ(list, copy);
}

TEST(TokenListComparasionTests, CompareNotEqualSize)
{
	using namespace token;

	const TokenList list{{
		Token{"1000", {Type::Number, 0, Association::None}},
		Token{"+", {Type::Plus, 1, Association::Left}},
		Token{"x", {Type::Variable, 0, Association::None}},
	}};
	const TokenList copy{{
		Token{"1000", {Type::Number, 0, Association::None}},
		Token{"x", {Type::Variable, 0, Association::None}},
	}};

	ASSERT_NE(list, copy);
}

TEST(TokenListComparasionTests, CompareNotEqualValue)
{
	using namespace token;

	const TokenList list{{
		Token{"1000", {Type::Number, 0, Association::None}},
		Token{"+", {Type::Plus, 1, Association::Left}},
		Token{"x", {Type::Variable, 0, Association::None}},
	}};
	const TokenList copy{{
		Token{"1000", {Type::Number, 0, Association::None}},
		Token{"+", {Type::Plus, 1, Association::Left}},
		Token{"y", {Type::Variable, 0, Association::None}},
	}};

	ASSERT_NE(list, copy);
}

/* ==== Основные методы: ==== */
TEST(TokenListTests, WhatSize)
{
	using namespace token;

	const TokenList list{{
		Token{"1000", {Type::Number, 0, Association::None}},
		Token{"+", {Type::Plus, 1, Association::Left}},
		Token{"x", {Type::Variable, 0, Association::None}},
	}};

	ASSERT_EQ(list.size(), 3);

	const TokenList defaultTokenList;

	ASSERT_EQ(defaultTokenList.size(), 0);
}

/* ==== Токенизация: ==== */
TEST(TokenizerTests, EmptyString)
{
	using namespace token;

	TokenList lst;
	const TokensList output;

	const TokenList::Error errorCode = lst.tokenize("");

	ASSERT_EQ(errorCode, TokenList::Error::EmptyString);
	ASSERT_EQ(output.size(), 0);
}

TEST(TokenizerTests, BasicTokenization)
{
	using namespace token;

	TokenList list;
	const TokenList expected{{
		Token{"2", {Type::Number, 0, Association::None}},
		Token{"*", {Type::Multiplication, 2, Association::Left}},
		Token{"x", {Type::Variable, 0, Association::None}},
		Token{"^", {Type::Exponentiation, 3, Association::Right}},
		Token{"100", {Type::Number, 0, Association::None}},
		Token{"+", {Type::Plus, 1, Association::Left}},
		Token{"100", {Type::Number, 0, Association::None}},
		Token{"*", {Type::Multiplication, 2, Association::Left}},
		Token{"x", {Type::Variable, 0, Association::None}},
		Token{"^", {Type::Exponentiation, 3, Association::Right}},
		Token{"2", {Type::Number, 0, Association::None}},
	}};

	const TokenList::Error errorCode =
		list.tokenize("  2 * x ^100+ 100*x ^2  ");

	ASSERT_EQ(errorCode, TokenList::Error::None);
	ASSERT_EQ(list.size(), 11);
	ASSERT_EQ(list, expected);
}

TEST(TokenizerTests, TokenizationSentenceOne)
{
	using namespace token;

	TokenList list;
	const TokenList expected{{
		Token{"1700", {Type::Number, 0, Association::None}},
		Token{"+", {Type::Plus, 1, Association::Left}},
		Token{"13000", {Type::Number, 0, Association::None}},
		Token{"*", {Type::Multiplication, 2, Association::Left}},
		Token{"x", {Type::Variable, 0, Association::None}},
		Token{"^", {Type::Exponentiation, 3, Association::Right}},
		Token{"(", {Type::LeftParenthesis, 0, Association::None}},
		Token{"z", {Type::Variable, 0, Association::None}},
		Token{"+", {Type::Plus, 1, Association::Left}},
		Token{"5", {Type::Number, 0, Association::None}},
		Token{")", {Type::RightParenthesis, 0, Association::None}},
	}};

	const TokenList::Error errorCode =
		list.tokenize("1700 + 13000 * x^(z + 5)");

	ASSERT_EQ(errorCode, TokenList::Error::None);
	ASSERT_EQ(list.size(), 11);
	ASSERT_EQ(list, expected);
}

TEST(TokenizerTests, TokenizationSentenceTwo)
{
	using namespace token;

	TokenList list;
	const TokenList expected{{
		Token{"100", {Type::Number, 0, Association::None}},
		Token{"/", {Type::Division, 2, Association::Left}},
		Token{"(", {Type::LeftParenthesis, 0, Association::None}},
		Token{"x", {Type::Variable, 0, Association::None}},
		Token{"+", {Type::Plus, 1, Association::Left}},
		Token{"5", {Type::Number, 0, Association::None}},
		Token{")", {Type::RightParenthesis, 0, Association::None}},
		Token{"+", {Type::Plus, 1, Association::Left}},
		Token{"28", {Type::Number, 0, Association::None}},
		Token{"*", {Type::Multiplication, 2, Association::Left}},
		Token{"x", {Type::Variable, 0, Association::None}},
		Token{"^", {Type::Exponentiation, 3, Association::Right}},
		Token{"(", {Type::LeftParenthesis, 0, Association::None}},
		Token{"z", {Type::Variable, 0, Association::None}},
		Token{"+", {Type::Plus, 1, Association::Left}},
		Token{"5", {Type::Number, 0, Association::None}},
		Token{")", {Type::RightParenthesis, 0, Association::None}},
	}};

	const TokenList::Error errorCode =
		list.tokenize("100 / (x + 5) + 28 * x^(z + 5)");

	ASSERT_EQ(errorCode, TokenList::Error::None);
	ASSERT_EQ(list.size(), 17);
	ASSERT_EQ(list, expected);
}

/* ------------------------------- RUN ALL TESTS ---------------------------- */
int main (int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}