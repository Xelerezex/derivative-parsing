#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include "utils.hpp"

/* ------------------------- Тестирование функции split ------------------------- */
TEST(BasicSplitTest, EmptyString) 
{  
    std::string input{""};

    std::vector<std::string> output = utils::split(input, ';');
    std::vector<std::string> expected{};
    
    ASSERT_EQ(output, expected);
}

TEST(BasicSplitTest, SeparatorNoInString) 
{  
    std::string input{"asfas 978a3kbfsd )(*^ ()*^)"};

    std::vector<std::string> output = utils::split(input, '~');
    std::vector<std::string> expected{"asfas 978a3kbfsd )(*^ ()*^)"};
    
    ASSERT_EQ(output, expected);
}

TEST(BasicSplitTest, SpaceSeparator) 
{  
    std::string input{"   17 18 19 ab bc z98;as _=~"};

    std::vector<std::string> output = utils::split(input, ' ');
    std::vector<std::string> expected{"", "", "", "17", "18", "19", "ab", "bc", "z98;as", "_=~"};
    
    ASSERT_EQ(output, expected);
}

TEST(BasicSplitTest, DotSeparator) 
{  
    std::string input{"  192     .      158 .      10 =^^@$&(#) . 12"};

    std::vector<std::string> output = utils::split(input, '.');
    std::vector<std::string> expected{"  192     ", "      158 ", "      10 =^^@$&(#) ", " 12"};
    
    ASSERT_EQ(output, expected);
}

/* --------------------------------- RUN ALL TESTS ------------------------------- */
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}