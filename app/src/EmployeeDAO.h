#pragma once

#include <memory>
#include <string>

class EmployeeDatabase;
class Employee;
class ID;

class EmployeeDAO {
public:
    explicit EmployeeDAO(EmployeeDatabase& database);

    std::string getAllEmployeesAsText() const;
    void saveEmployeeToDatabase(std::unique_ptr<Employee> employee);
    Employee& getEmployeeByID(std::unique_ptr<ID> employeeID) const;
    void terminateEmployee(std::unique_ptr<ID> employeeID);

private:
    EmployeeDatabase& database;
};
