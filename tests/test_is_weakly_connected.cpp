#include "/home/mmaghous/software/Cpp/libs/googletest/googletest/include/gtest/gtest.h"

int main(int argc, char **args)
{
    ::testing::InitGoogleTest(&argc, args);
    return RUN_ALL_TESTS();
}

TEST(someTest,testOne)
{
    ASSERT_EQ(5,5);
}