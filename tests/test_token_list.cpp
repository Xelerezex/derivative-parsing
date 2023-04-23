#include "tokenlist.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

/* -------------------Тестирование Класса TokenList ------------------------- */
/* ==== Сравнение объектов: ==== */
TEST(TokenListComparasionTests, CompareEqual)
{
	using namespace token;

	TokenList list{{
		Token{"1000", {Type::Number, 0, Association::None}},
		Token{"+", {Type::Plus, 1, Association::Left}},
		Token{"x", {Type::Variable, 0, Association::None}},
	}};
	TokenList copy{{
		Token{"1000", {Type::Number, 0, Association::None}},
		Token{"+", {Type::Plus, 1, Association::Left}},
		Token{"x", {Type::Variable, 0, Association::None}},
	}};

	ASSERT_EQ(list, copy);
}

TEST(TokenListComparasionTests, CompareNotEqualSize)
{
	using namespace token;

	TokenList list{{
		Token{"1000", {Type::Number, 0, Association::None}},
		Token{"+", {Type::Plus, 1, Association::Left}},
		Token{"x", {Type::Variable, 0, Association::None}},
	}};
	TokenList copy{{
		Token{"1000", {Type::Number, 0, Association::None}},
		Token{"x", {Type::Variable, 0, Association::None}},
	}};

	ASSERT_NE(list, copy);
}

TEST(TokenListComparasionTests, CompareNotEqualValue)
{
	using namespace token;

	TokenList list{{
		Token{"1000", {Type::Number, 0, Association::None}},
		Token{"+", {Type::Plus, 1, Association::Left}},
		Token{"x", {Type::Variable, 0, Association::None}},
	}};
	TokenList copy{{
		Token{"1000", {Type::Number, 0, Association::None}},
		Token{"+", {Type::Plus, 1, Association::Left}},
		Token{"y", {Type::Variable, 0, Association::None}},
	}};

	ASSERT_NE(list, copy);
}
TEST(TokenizerTests, EmptyString)
{
	using namespace token;

	TokenList lst;
	TokensList output;

	const TokenList::Error errorCode = lst.tokenizer("", output);

	ASSERT_EQ(errorCode, TokenList::Error::EmptyString);
	ASSERT_EQ(output.size(), 0);
}

/* ------------------------------- RUN ALL TESTS ---------------------------- */
int main (int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}