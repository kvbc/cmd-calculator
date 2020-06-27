#include <iostream>
#include <string>
#include "equ.h"
#include "log.h"

void getEqu() {
    std::string equ;
    std::cout << "Equation: ";
    std::getline(std::cin, equ);
    std::cout << "Result: " << calcEqu(equ) << "\n\n";
    getEqu();
}

int main() {
    log::info("Basic cmd calculator");
    log::info("Operators: - + * / % ^");
    log::info("Functions: sqrt, cbrt");
    std::cout << '\n';
    getEqu();
}
