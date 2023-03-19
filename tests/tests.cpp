#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include "token.hpp"

using namespace std;

TEST(TestComparison, TokenTest) 
{  
    token::Token first  {token::Type::Number, 10, token::Association::Left};
    token::Token second {token::Type::Number, 10, token::Association::Left};
    ASSERT_TRUE(first == second);
}

TEST(TestFalseTypeComparison, TokenTest) 
{  
    token::Token first  {token::Type::Number,   10, token::Association::Left};
    token::Token second {token::Type::Variable, 10, token::Association::Left};
    ASSERT_FALSE(first == second);
}

TEST(TestFalsePrecedenceComparison, TokenTest) 
{  
    token::Token first  {token::Type::Number, 10, token::Association::Left};
    token::Token second {token::Type::Number, 8,  token::Association::Left};
    ASSERT_FALSE(first == second);
}

TEST(TestFalseAssociationComparison, TokenTest) 
{  
    token::Token first  {token::Type::Number, 10, token::Association::Left};
    token::Token second {token::Type::Number, 10, token::Association::Right};
    ASSERT_FALSE(first == second);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}