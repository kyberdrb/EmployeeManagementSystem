#include "EmployeeDatabase.h"
#include "EmployeeMissingInDatabase.h"
#include "Employee.h"
#include "ID.h"

#include <sstream>
#include <algorithm>

Employee& EmployeeDatabase::select(std::unique_ptr<ID> employeeID) const {
    Employee employeeToSearch(std::move(employeeID));

    for (auto& employee : employees) {
        if (employeeToSearch == *employee) {
            return *employee;
        }
    }
    
    throw EmployeeMissingInDatabase(std::move(employeeToSearch.moveOwnershipOfID()));
}

std::string EmployeeDatabase::selectAll() const {
    std::stringstream employeeStream;

    if (employees.empty()) {
        employeeStream << "No employees present.";
        return employeeStream.str();
    }

    for (const auto& employee : employees) {
        employeeStream <<
            employee->getEmployeeID() << ";" <<
            employee->getName() << ";" <<
            employee->getDepartment() << ";" <<
            employee->getWorking() << ";";
        employeeStream << '\n';
    }

    std::string&& newstr{employeeStream.str()};
    newstr.pop_back();
    return std::move(newstr);
}

void EmployeeDatabase::insert(std::unique_ptr<Employee> employee) {
    employees.emplace_back(std::move(employee));
}

void EmployeeDatabase::deleteEntry(std::unique_ptr<ID> employeeID) {
    auto numberOfEmployeesBeforeErasure = this->employees.size();

    employees.erase(    // Even if the employeeID is not in the database,
        std::remove_if( // the application will still run stablily...
            employees.begin(),
            employees.end(),
            [&employeeID] (const auto& employee) {
                return employee->getEmployeeID() == *employeeID;
            }
            ),
        employees.end());

        auto numberOfEmployeesAfterErasure = this->employees.size();
        auto noEmployeesWereDeleted = numberOfEmployeesBeforeErasure == numberOfEmployeesAfterErasure;
        if (noEmployeesWereDeleted) {
            throw EmployeeMissingInDatabase(std::move(employeeID));
        }
}

// Singleton
EmployeeDatabase::EmployeeDatabase() : employees() {}

EmployeeDatabase& EmployeeDatabase::getInstance() {
    static std::shared_ptr<EmployeeDatabase> instance(new EmployeeDatabase());
    return *instance.get();
}
