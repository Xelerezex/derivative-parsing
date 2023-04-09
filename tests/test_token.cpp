#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include "token.hpp"
#include "utils.hpp"
    
using namespace std;

/* -------------------- Тестирование сравнения типов токена -------------------- */
TEST(TokenTypeCreationTest, AllComparation) 
{  
    token::TokenType first  {token::Type::Number, 10, token::Association::Left};
    token::TokenType second {token::Type::Number, 10, token::Association::Left};
    ASSERT_TRUE(first == second);
}

TEST(TokenTypeCreationTest, NotEqualType) 
{  
    token::TokenType first  {token::Type::Number,   10, token::Association::Left};
    token::TokenType second {token::Type::Variable, 10, token::Association::Left};
    ASSERT_FALSE(first == second);
}

TEST(TokenTypeCreationTest, NotEqualPrecedence) 
{  
    token::TokenType first  {token::Type::Number, 10, token::Association::Left};
    token::TokenType second {token::Type::Number, 8,  token::Association::Left};
    ASSERT_FALSE(first == second);
}

TEST(TokenTypeCreationTest, NotEqualAssociation) 
{  
    token::TokenType first  {token::Type::Number, 10, token::Association::Left};
    token::TokenType second {token::Type::Number, 10, token::Association::Right};
    ASSERT_FALSE(first == second);
}

/* ---------------------- Тестирование сравнения Токенов ---------------------- */
TEST(TokenCreationTest, EqualTokens) 
{  
    token::Token first  {"17", {token::Type::Number, 0, token::Association::None}};
    token::Token second {"17", {token::Type::Number, 0, token::Association::None}};
    ASSERT_TRUE(first == second);
}

TEST(TokenCreationTest, NotEqualTokens) 
{  
    token::Token first  {"17", {token::Type::Number, 0, token::Association::None}};
    token::Token second {"42", {token::Type::Number, 0, token::Association::None}};
    ASSERT_FALSE(first == second);
}

/* ---------------------- Тестирование Токенизации строки --------------------- */
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

    std::string dataForTokenize = {"123 1 1000 3 17"};

    const int expectedSize = 5;
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

/* --------------------------------- RUN ALL TESTS ------------------------------- */
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}