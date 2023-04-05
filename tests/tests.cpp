#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include "token.hpp"

using namespace std;

TEST(TokenCreationTest, AllComparation) 
{  
    token::TokenType first  {token::Type::Number, 10, token::Association::Left};
    token::TokenType second {token::Type::Number, 10, token::Association::Left};
    ASSERT_TRUE(first == second);
}

TEST(TokenCreationTest, NotEqualType) 
{  
    token::TokenType first  {token::Type::Number,   10, token::Association::Left};
    token::TokenType second {token::Type::Variable, 10, token::Association::Left};
    ASSERT_FALSE(first == second);
}

TEST(TokenCreationTest, NotEqualPrecedence) 
{  
    token::TokenType first  {token::Type::Number, 10, token::Association::Left};
    token::TokenType second {token::Type::Number, 8,  token::Association::Left};
    ASSERT_FALSE(first == second);
}

TEST(TokenCreationTest, NotEqualAssociation) 
{  
    token::TokenType first  {token::Type::Number, 10, token::Association::Left};
    token::TokenType second {token::Type::Number, 10, token::Association::Right};
    ASSERT_FALSE(first == second);
}

TEST(TestTokenParse, TokenizerEmptyString)
{   
    using namespace token;

    std::stringstream input{""};
    std::vector<TokenType> output;
    Error result{Error::None};

    result = token::tokenize(input, output);

    ASSERT_EQ(output.size(), 0);
    ASSERT_EQ(result, token::Error::EmptyString);
}

// TODO:  Сделать проверку именно с токенами {value, tokenType}, а не просто {tokenType}
TEST(TestTokenParse, TokenizerNumbers)
{   
    using namespace token;

    const int expectedSize = 5;
    std::stringstream input{"123 1 1000 3 17"};
    std::vector<TokenType> output; // TODO: Move TokenType to Token
    Error result{Error::None};
    
    std::vector<TokenType> expected;
    for (int index = 0; index < expectedSize; ++index)
    {
        expected.push_back({Type::Number, 0, Association::None});
    }

    result = token::tokenize(input, output);

    ASSERT_EQ(result, token::Error::None);
    ASSERT_EQ(output.size(), expectedSize);
    ASSERT_EQ(output, expected);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}