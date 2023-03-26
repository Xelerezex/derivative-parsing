#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include "token.hpp"

using namespace std;

TEST(TokenCreationTest, AllComparation) 
{  
    token::Token first  {token::Type::Number, 10, token::Association::Left};
    token::Token second {token::Type::Number, 10, token::Association::Left};
    ASSERT_TRUE(first == second);
}

TEST(TokenCreationTest, NotEqualType) 
{  
    token::Token first  {token::Type::Number,   10, token::Association::Left};
    token::Token second {token::Type::Variable, 10, token::Association::Left};
    ASSERT_FALSE(first == second);
}

TEST(TokenCreationTest, NotEqualPrecedence) 
{  
    token::Token first  {token::Type::Number, 10, token::Association::Left};
    token::Token second {token::Type::Number, 8,  token::Association::Left};
    ASSERT_FALSE(first == second);
}

TEST(TokenCreationTest, NotEqualAssociation) 
{  
    token::Token first  {token::Type::Number, 10, token::Association::Left};
    token::Token second {token::Type::Number, 10, token::Association::Right};
    ASSERT_FALSE(first == second);
}

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

    std::stringstream input{"123 1 1000 3 17"};
    std::vector<Token> output;
    Error result{Error::None};
    
    Token digit{Type::Number, 0, Association::None};
    std::vector<Token> expected{digit, digit, digit};

    result = token::tokenize(input, output);

    ASSERT_EQ(result, token::Error::None) << "Error code = " << static_cast<int>(result);
    ASSERT_EQ(output.size(), 5);
    ASSERT_EQ(output, expected);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}