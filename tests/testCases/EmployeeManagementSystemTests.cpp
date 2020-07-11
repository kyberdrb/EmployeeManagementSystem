#include "../../app/src/EmployeeDatabase.h"

#include "gtest/gtest.h"

class EmployeeManagementSystemTests : public ::testing::Test {};

TEST_F(EmployeeManagementSystemTests, test_client) {
    auto& db = EmployeeDatabase::getInstance();
    ASSERT_NE(&db, nullptr);
}
