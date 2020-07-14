#include "../../app/src/Employee.h"
#include "../../app/src/EmployeeDAO.h"
#include "../../app/src/EmployeeDatabase.h"
#include "../../app/src/EntryGenerator.h"
#include "../../app/src/EmployeeMissingInDatabase.h"
#include "../../app/src/ID_Pool.h"
#include "../../app/src/NoIDs_InID_Pool.h"

#include "gtest/gtest.h"

class EmployeeManagementSystemTests : public ::testing::Test {
protected:
    std::unique_ptr<EmployeeDAO> employeeDAO;
    ID_Pool& idPool = ID_Pool::getInstance();

    EmployeeManagementSystemTests() : employeeDAO(nullptr) {}

    void SetUp() override {
        auto& db = EmployeeDatabase::getInstance();
        this->employeeDAO = std::make_unique<EmployeeDAO>(db);
        EntryGenerator entryGenerator;
        entryGenerator.fillDatabaseThroughDAO(*(this->employeeDAO));
    }
};

TEST_F(EmployeeManagementSystemTests, test_client) {
    {
        ASSERT_EQ("2", this->idPool.getEntirePoolAsText());


        auto borrowedID = idPool.borrowID();

        // #ASSERT_EQ()
		idPool.getEntirePoolAsText();


        std::unique_ptr<ID> anotherBorrowedID;
        try {
            anotherBorrowedID = idPool.borrowID();
        } catch (const NoIDs_InID_Pool& exc) {
            // #ASSERT_EQ()
            exc.what();
        }

        // #ASSERT_EQ()
		idPool.getEntirePoolAsText();


        idPool.giveBackID(std::move(borrowedID));

        // #ASSERT_EQ()
		idPool.getEntirePoolAsText();


        // #ASSERT_EQ()
		idPool.getEntirePoolAsText();


        idPool.giveBackID(std::move(anotherBorrowedID));

        // #ASSERT_EQ()
		idPool.getEntirePoolAsText();


        // #ASSERT_EQ()
		idPool.getEntirePoolAsText();

    }


    // #ASSERT_EQ()
	ID_Pool::getInstance().getEntirePoolAsText();


    {
        auto id = std::make_unique<ID>(0);
        // #ASSERT_EQ()
		this->employeeDAO->getEmployeeByID(std::move(id));

    }

    // #ASSERT_EQ()
	ID_Pool::getInstance().getEntirePoolAsText();


    {
        auto id = std::make_unique<ID>(1);
        // #ASSERT_EQ()
		this->employeeDAO->getEmployeeByID(std::move(id));

    }

    // #ASSERT_EQ()
	ID_Pool::getInstance().getEntirePoolAsText();


    {
        try {
            auto id = std::make_unique<ID>(20);
            // #ASSERT_EQ()
            this->employeeDAO->getEmployeeByID(std::move(id));
        } catch (const EmployeeMissingInDatabase& exc) {
            std::stringstream failureMessage;
            failureMessage <<  "Failure at printing the employee with 'id=" << exc.what() << "'" ;
            // #ASSERT_EQ()
            failureMessage.str();
        }

    }

    // #ASSERT_EQ()
	ID_Pool::getInstance().getEntirePoolAsText();


    // #ASSERT_EQ()
	this->employeeDAO->getAllEmployeesAsText();


    {
        auto id = std::make_unique<ID>(1);
        this->employeeDAO->terminateEmployee(std::move(id));
    }

    // #ASSERT_EQ()
	ID_Pool::getInstance().getEntirePoolAsText();


    // #ASSERT_EQ()
	this->employeeDAO->getAllEmployeesAsText();


    {
        auto id = std::make_unique<ID>(0);
        this->employeeDAO->terminateEmployee(std::move(id));
    }

    // #ASSERT_EQ()
	ID_Pool::getInstance().getEntirePoolAsText();


    // #ASSERT_EQ()
	this->employeeDAO->getAllEmployeesAsText();


    {
        try {
            auto id = std::make_unique<ID>(30);
            this->employeeDAO->terminateEmployee(std::move(id));
        } catch (const EmployeeMissingInDatabase& exc) { // if I wouldn't wrap the 'terminateEmployee' function call in a try block and catch the exception and only executed the body of the try block without catching the exception from 'terminateEmployee' function, the program would leak memory - and I don't want that. I want from my programs to clean up all memory they use because I want to write programs that would stabily run for as long as possible.
            std::stringstream failureMessage;
            failureMessage << "Employee with 'id=" << exc.what() << "'" << " is missing in database";
            // #ASSERT_EQ()
            failureMessage.str();
        }
    }

    // #ASSERT_EQ()
	ID_Pool::getInstance().getEntirePoolAsText();


    // #ASSERT_EQ()
	this->employeeDAO->getAllEmployeesAsText();

}

TEST_F(EmployeeManagementSystemTests, test_something_else) {
    ASSERT_EQ(  "0;John Doe;free;1\n"
                "1;Jack Smith;common good;1",
                this->employeeDAO->getAllEmployeesAsText());
}
