#include "tokenlist.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

/* -------------------Тестирование Класса TokenList ------------------------- */
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