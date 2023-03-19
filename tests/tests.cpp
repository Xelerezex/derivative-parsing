#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include "token.hpp"

using namespace std;

TEST(TestTokenCmp, TokenTest) 
{  
    token::Token first  {token::Type::Number, 10, token::Association::Left};
    token::Token second {token::Type::Number, 10, token::Association::Left};
    ASSERT_TRUE(first == second);
}

TEST(TestFalseTypeTokenCmp, TokenTest) 
{  
    token::Token first  {token::Type::Number,   10, token::Association::Left};
    token::Token second {token::Type::Variable, 10, token::Association::Left};
    ASSERT_FALSE(first == second);
}

TEST(TestFalsePrecedenceTokenCmp, TokenTest) 
{  
    token::Token first  {token::Type::Number, 10, token::Association::Left};
    token::Token second {token::Type::Number, 8,  token::Association::Left};
    ASSERT_FALSE(first == second);
}

TEST(TestFalseAssociationTokenCmp, TokenTest) 
{  
    token::Token first  {token::Type::Number, 10, token::Association::Left};
    token::Token second {token::Type::Number, 10, token::Association::Right};
    ASSERT_FALSE(first == second);
}

TEST(TestTokenParse, TokenTest)
{
    std::stringstream input{"1 2 3"};
    std::vector<token::Token> output;
    token::Error result{token::Error::None};

    result = token::tokenize(input, output);
    ASSERT_TRUE(result == token::Error::None);
    ASSERT_FALSE(result == token::Error::DefaultError);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}