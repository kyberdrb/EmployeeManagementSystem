#pragma once

#include <exception>

class NoIDs_InID_Pool : public std::exception {
public:
    const char* what() const noexcept override {
        return "ID Pool is empty. No more IDs to borrow.";
    }
};
