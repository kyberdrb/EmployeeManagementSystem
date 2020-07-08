#include "../../app/src/EmployeeDatabase.h"

#include "gtest/gtest.h"

class SomeUnitTest : public ::testing::Test {};

TEST_F(SomeUnitTest, test_foo_differs_from_bar) {
    // EXPECT_EQ("bar", "bar");

    auto& db = EmployeeDatabase::getInstance();
    ASSERT_NE(&db, nullptr);
}
