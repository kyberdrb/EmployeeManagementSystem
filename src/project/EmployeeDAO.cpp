#include "EmployeeDAO.h"
#include "EmployeeDatabase.h"
#include "Employee.h"
#include "ID.h"

EmployeeDAO::EmployeeDAO(EmployeeDatabase& database) : database(database) {}

void EmployeeDAO::saveEmployeeToDatabase(std::unique_ptr<Employee> employee) {
    database.insert(std::move(employee));
}

std::string EmployeeDAO::getAllEmployeesAsText() const {
    return database.selectAll();
}

Employee& EmployeeDAO::getEmployeeByID(std::unique_ptr<ID> employeeID) const {
    return database.select(std::move(employeeID));
}

void EmployeeDAO::terminateEmployee(std::unique_ptr<ID> employeeID) {
    database.deleteEntry(std::move(employeeID));
}
