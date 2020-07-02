#pragma once

#include "ID.h"

#include <exception>
#include <string>

class EmployeeMissingInDatabase : public std::exception {
public:
    explicit EmployeeMissingInDatabase(std::unique_ptr<ID> id) :
        id(std::move(id)),
        idAsText(this->id->getID_AsText())
    {}

    const char* what() const noexcept override {
        return this->idAsText.c_str();
    }

private:
    std::unique_ptr<ID> id;
    std::string idAsText;
};
