#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include "token.hpp"

using namespace std;

TEST(TestComparision, TokenTest) 
{  
    using namespace token;

    Token first  {Type::Number, 10, Association::Left};
    Token second {Type::Number, 10, Association::Left};
    
    ASSERT_TRUE(first == second);
}
 
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}