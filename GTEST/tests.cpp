#include <gtest/gtest.h>
#include "add.cpp"

TEST(ADDTest, PositiveNos) {
	ASSERT_EQ(6, add(2, 4));
	ASSERT_EQ(5, add(2, 4));
}

TEST(ADDTest, NegativeNos) {
	ASSERT_EQ(6, add(2, 4));
	ASSERT_EQ(5, add(2, 4));
}

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
