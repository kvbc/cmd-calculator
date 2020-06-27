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
    log::info("Cmd calculator");
    log::info("Operators: + - * / ^ %\n");
    getEqu();
}
