#pragma once

class Employee;

#include <sstream>
#include <string>

class EmployeePrinter {
public:
    std::string printEmployeeDetailReportXML(const Employee& employee) const;
    std::string printEmployeeDetailReportCSV(const Employee& employee) const;
};
