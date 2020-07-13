#include <iomanip>
#include <iostream>
#include <string>
#include "equ.h"
#include "log.h"

void getEqu() {
    std::string equ;
    std::cout << "Equation: ";
    std::getline(std::cin, equ);
    std::cout << "Result: " << std::setprecision(14) << calcEqu(equ) << "\n\n";
    getEqu();
}

int main() {
    log::info("Cmd calculator");
    log::info("Operators: + - * / ^ %\n");
    getEqu();
}
