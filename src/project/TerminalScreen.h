#pragma once

#include <iostream>

class TerminalScreen {
public:
    template <typename Printable>
    void displayOnTerminal(Printable&& message) {
        std::cout << message << '\n';
    }

    void printNewLine();
};
