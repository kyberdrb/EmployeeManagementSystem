#include "EmployeePrinter.h"
#include "Employee.h"

std::string EmployeePrinter::printEmployeeDetailReportXML(const Employee& employee) const {
    std::stringstream employeeInfo;
    employeeInfo <<
        "<" << "id" << ">" << employee.getEmployeeID() << "<" << "/" << "id" << ">" << '\n' <<
        "<" << "name" << ">" << employee.getName() << "<" << "/" << "name" << ">" << '\n' <<
        "<" << "department" << ">" << employee.getDepartment() << "<" << "/" << "department" << ">" << '\n' <<
        "<" << "working" << ">" << employee.getWorking() << "<" << "/" << "working" << ">";
    employeeInfo << '\n';
    return employeeInfo.str();
}

std::string EmployeePrinter::printEmployeeDetailReportCSV(const Employee& employee) const {
    std::stringstream employeeInfo;
    employeeInfo <<
        employee.getEmployeeID() << ";" <<
        "\"" << employee.getName() << "\"" << ";" <<
        "\"" << employee.getDepartment() << "\"" << ";" <<
        employee.getWorking();
    employeeInfo << std::endl;
    return employeeInfo.str();
}
