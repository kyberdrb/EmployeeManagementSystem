#pragma once

class ID_Pool;

#include "ID.h" // even declaration of member variable with unique_ptr type
                // wants to know the size of the generic attribute for unique_ptr member var.
                // Therefore, we need to include the header file with the class,
                // not just forward declare the class (as I first did :P )
                // because the compiler can only determine the size of the class only when it's included.
                // In this respect, forward declaring the class only informs the compiler
                // that the class will exist in the future, but the compiler can't find out
                // the size of the class just from the forward declaration. That's not enough.
                // Including the header file with the definition of the class is enough ;)


#include <iostream>
#include <memory>
#include <string>

class Employee {
public:
    Employee();

    Employee(
        std::string name,
        std::string department,
        bool working);

    explicit Employee(std::unique_ptr<ID> id);

    Employee(const Employee& otherEmployee) = delete;
    Employee& operator=(const Employee& otherEmployee) = delete;

    Employee(Employee&& otherEmployee);
    Employee& operator=(Employee&& otherEmployee);

    const ID& getEmployeeID() const;
    std::unique_ptr<ID> moveOwnershipOfID();

    std::string getName() const;

    std::string getDepartment() const;

    bool getWorking() const;


    bool operator==(const Employee& otherEmployee) const;

    friend std::ostream& operator<<(std::ostream& out, const Employee& employee);

    ~Employee();

    void giveEmployeeID_BackToPool();

private:
    Employee(
        std::unique_ptr<ID> id,
        std::string name,
        std::string department,
        bool working);

    std::unique_ptr<ID> employeeID;
    std::string name;
    std::string department;
    bool working;

};
