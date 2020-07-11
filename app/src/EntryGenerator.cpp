#include "Employee.h"
#include "EmployeeDAO.h"
#include "EntryGenerator.h"
#include "ID_Pool.h"
#include "TerminalScreen.h"

void EntryGenerator::fillDatabaseThroughDAO(TerminalScreen& screen, EmployeeDAO& employeeDAO) {
    EmployeePrinter employeePrinter;
    ID_Pool& idPool = ID_Pool::getInstance();
    screen.displayOnTerminal(idPool.getEntirePoolAsText());
    screen.printNewLine();

    auto e1 = std::make_unique<Employee>();
    screen.displayOnTerminal(employeePrinter.printEmployeeDetailReportXML(*e1));
    screen.displayOnTerminal(employeePrinter.printEmployeeDetailReportCSV(*e1));

    screen.displayOnTerminal(idPool.getEntirePoolAsText());
    screen.printNewLine();

    auto e2 = std::make_unique<Employee>("Jack Smith", "common good", true);
    screen.displayOnTerminal(employeePrinter.printEmployeeDetailReportXML(*e2));
    screen.displayOnTerminal(employeePrinter.printEmployeeDetailReportCSV(*e2));

    screen.displayOnTerminal(idPool.getEntirePoolAsText());
    screen.printNewLine();

    employeeDAO.saveEmployeeToDatabase(std::move(e1));
    employeeDAO.saveEmployeeToDatabase(std::move(e2));
}

void EntryGenerator::fillDatabaseThroughDAO(EmployeeDAO& employeeDAO) {
    auto e1 = std::make_unique<Employee>();
    auto e2 = std::make_unique<Employee>("Jack Smith", "common good", true);

    // static_cast<void>(employeeDAO);

    employeeDAO.saveEmployeeToDatabase(std::move(e1));
    employeeDAO.saveEmployeeToDatabase(std::move(e2));
}
