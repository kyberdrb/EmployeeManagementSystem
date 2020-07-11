// Lexicographic order of include statements
// - see https://llvm.org/docs/CodingStandards.html#include-style
#include "../src/Employee.h"
#include "../src/EmployeeDAO.h"
#include "../src/EmployeeDatabase.h"
#include "../src/EntryGenerator.h"
#include "../src/EmployeeMissingInDatabase.h"
#include "../src/ID_Pool.h"
#include "../src/NoIDs_InID_Pool.h"
#include "../src/TerminalScreen.h"

#include <sstream>

int main() {
    auto& db = EmployeeDatabase::getInstance();
    EmployeeDAO employeeDAO(db);
    TerminalScreen screen;
    EntryGenerator entryGenerator;
    // entryGenerator.fillDatabaseThroughDAO(screen, employeeDAO);
    entryGenerator.fillDatabaseThroughDAO(employeeDAO);

    screen.displayOnTerminal(employeeDAO.getAllEmployeesAsText());

    screen.printNewLine();
    screen.displayOnTerminal("---");
    screen.printNewLine();

    {
        ID_Pool& idPool = ID_Pool::getInstance(); // we can access to the singleton
                                                  // either directly using the static method 'ID_Pool::getInstance' each time
                                                  // or by reference, calling the 'getInstance' function only once
                                                  //  and then using the reference

        screen.displayOnTerminal(idPool.getEntirePoolAsText());
        screen.printNewLine();

        screen.displayOnTerminal(idPool.getEntirePoolAsText());
        screen.printNewLine();

        auto borrowedID = idPool.borrowID();

        screen.displayOnTerminal(idPool.getEntirePoolAsText());
        screen.printNewLine();

        std::unique_ptr<ID> anotherBorrowedID;
        try {
            anotherBorrowedID = idPool.borrowID();
        } catch (const NoIDs_InID_Pool& exc) {
            screen.displayOnTerminal(exc.what());
            screen.printNewLine();
        }

        screen.displayOnTerminal(idPool.getEntirePoolAsText());
        screen.printNewLine();

        idPool.giveBackID(std::move(borrowedID));

        screen.displayOnTerminal(idPool.getEntirePoolAsText());
        screen.printNewLine();

        screen.displayOnTerminal(idPool.getEntirePoolAsText());
        screen.printNewLine();

        idPool.giveBackID(std::move(anotherBorrowedID));

        screen.displayOnTerminal(idPool.getEntirePoolAsText());
        screen.printNewLine();

        screen.displayOnTerminal(idPool.getEntirePoolAsText());
        screen.printNewLine();
    }

    screen.printNewLine();
    screen.displayOnTerminal("---");
    screen.printNewLine();

    screen.displayOnTerminal(ID_Pool::getInstance().getEntirePoolAsText());
    screen.printNewLine();

    {
        auto id = std::make_unique<ID>(0);
        screen.displayOnTerminal(employeeDAO.getEmployeeByID(std::move(id)));
        screen.printNewLine();
    }

    screen.displayOnTerminal(ID_Pool::getInstance().getEntirePoolAsText());
    screen.printNewLine();

    {
        auto id = std::make_unique<ID>(1);
        screen.displayOnTerminal(employeeDAO.getEmployeeByID(std::move(id)));
        screen.printNewLine();
    }

    screen.displayOnTerminal(ID_Pool::getInstance().getEntirePoolAsText());
    screen.printNewLine();

    {
        try {
            auto id = std::make_unique<ID>(20);
            screen.displayOnTerminal(employeeDAO.getEmployeeByID(std::move(id)));
        } catch (const EmployeeMissingInDatabase& exc) {
            std::stringstream failureMessage;
            failureMessage <<  "Failure at printing the employee with 'id=" << exc.what() << "'" ;
            screen.displayOnTerminal(failureMessage.str());
        }
        screen.printNewLine();
    }

    screen.displayOnTerminal(ID_Pool::getInstance().getEntirePoolAsText());
    screen.printNewLine();

    screen.displayOnTerminal(employeeDAO.getAllEmployeesAsText());
    screen.printNewLine();

    {
        auto id = std::make_unique<ID>(1);
        employeeDAO.terminateEmployee(std::move(id));
    }

    screen.displayOnTerminal(ID_Pool::getInstance().getEntirePoolAsText());
    screen.printNewLine();

    screen.displayOnTerminal(employeeDAO.getAllEmployeesAsText());
    screen.printNewLine();

    {
        auto id = std::make_unique<ID>(0);
        employeeDAO.terminateEmployee(std::move(id));
    }

    screen.displayOnTerminal(ID_Pool::getInstance().getEntirePoolAsText());
    screen.printNewLine();

    screen.displayOnTerminal(employeeDAO.getAllEmployeesAsText());
    screen.printNewLine();

    {
        try {
            auto id = std::make_unique<ID>(30);
            employeeDAO.terminateEmployee(std::move(id));
        } catch (const EmployeeMissingInDatabase& exc) { // if I wouldn't wrap the 'terminateEmployee' function call in a try block and catch the exception and only executed the body of the try block without catching the exception from 'terminateEmployee' function, the program would leak memory - and I don't want that. I want from my programs to clean up all memory they use because I want to write programs that would stabily run for as long as possible.
            std::stringstream failureMessage;
            failureMessage << "Employee with 'id=" << exc.what() << "'" << " is missing in database";
            screen.displayOnTerminal(failureMessage.str());
            screen.printNewLine();
        }
    }

    screen.displayOnTerminal(ID_Pool::getInstance().getEntirePoolAsText());
    screen.printNewLine();

    screen.displayOnTerminal(employeeDAO.getAllEmployeesAsText());
    screen.printNewLine();

    return 0;
}
