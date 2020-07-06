#include "Employee.h"
#include "ID_Pool.h"
#include "TerminalScreen.h"

#include <cstdint>

Employee::Employee() :
    Employee(std::move(ID_Pool::getInstance().borrowID()), "John Doe", "free", true)
{}

Employee::Employee(
        std::string name,
        std::string department,
        bool working)
:
    employeeID(std::move(ID_Pool::getInstance().borrowID())),
    name(std::move(name)),
    department(std::move(department)),
    working(working)
{}

Employee::Employee(
        std::unique_ptr<ID> id,
        std::string name,
        std::string department,
        bool working)
:
    employeeID(std::move(id)),
    name(std::move(name)),
    department(std::move(department)),
    working(working)
{}

Employee::Employee(std::unique_ptr<ID> id) :
    employeeID(std::move(id)),
    name(""),
    department(""),
    working(false)
{}

Employee::Employee(Employee&& otherEmployee) :
    employeeID(std::move(otherEmployee.employeeID)),
    name{otherEmployee.name},
    department{otherEmployee.department},
    working{otherEmployee.working}
{}

Employee& Employee::operator=(Employee&& otherEmployee) {
    if (this == &otherEmployee) {
        return *this;
    }

    this->employeeID = std::move(otherEmployee.employeeID);
    this->name = otherEmployee.name;
    this->department = otherEmployee.department;
    this->working = otherEmployee.working;

    otherEmployee.employeeID.reset(nullptr);

    return *this;
}

const ID& Employee::getEmployeeID() const {
    return *employeeID;
}

std::unique_ptr<ID> Employee::moveOwnershipOfID() {
    return std::move(this->employeeID);
}

std::string Employee::getName() const {
    return name;
}

std::string Employee::getDepartment() const {
    return department;
}

bool Employee::getWorking() const {
    return working;
}

bool Employee::operator==(const Employee& otherEmployee) const {
    bool areObjectsEqual = *(this->employeeID) == *(otherEmployee.employeeID);
    return areObjectsEqual;
}

std::ostream& operator<<(std::ostream& out, const Employee& employee) {
    out <<
        "id:" << *(employee.employeeID) << ";" <<
        "working:" << employee.working << ";" <<
        "department:" << employee.department << ";" <<
        "name:" << employee.name;
    return out;
}

Employee::~Employee() {
    this->giveEmployeeID_BackToPool();
}

void Employee::giveEmployeeID_BackToPool() {
    auto isID_ResetFromTemporaryInstance = this->employeeID != nullptr;
    if (isID_ResetFromTemporaryInstance) {
        ID_Pool::getInstance().giveBackID(std::move(this->employeeID));
    }
}
