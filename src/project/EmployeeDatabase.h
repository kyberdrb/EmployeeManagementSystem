#pragma once

#include <memory>
#include <vector>

class Employee;
class ID;

class EmployeeDatabase {
public:
    std::string selectAll() const;
    Employee& select(std::unique_ptr<ID> employeeID) const;
    void insert(std::unique_ptr<Employee> employee);
    void deleteEntry(std::unique_ptr<ID> employeeID);

    // Singleton
    EmployeeDatabase(const EmployeeDatabase& other) = delete;
    EmployeeDatabase& operator=(const EmployeeDatabase& other) = delete;
    static EmployeeDatabase& getInstance();
private:
    EmployeeDatabase();

    std::vector<std::unique_ptr<Employee>> employees;
};
