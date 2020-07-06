#pragma once

#include "EmployeePrinter.h"
class TerminalScreen;
class EmployeeDAO;

#include <memory>

class EntryGenerator {
public:
    void fillDatabaseThroughDAO(TerminalScreen& screen, EmployeeDAO& employeeDAO);
};
