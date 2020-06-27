#pragma once
#include <string>
#include <math.h>

struct expData {
    int start;           // Start index of expression
    int end;             // End index of expression
    long double lHalf;   // Left operand
    long double rHalf;   // Right Operand
};

// Gets the expression from equation (equ) with operator at index opP to later on calculate the expression.
// e.g. (equ = "1 + 234 / 567"), (opP = 2) -> (start = 0, end = 6, lHalf = 1, rHalf = 234).
expData getExp(const std::string &equ, int opP) {
    int lastOp = equ.substr(0, opP).find_last_not_of(".-0123456789");
    int nextOp = std::min(equ.substr(opP + 1).find_first_not_of(".-0123456789"), equ.length());
    long double lHalf = std::stold(equ.substr(lastOp + 1, opP - lastOp - 1));
    long double rHalf = std::stold(equ.substr(opP + 1, nextOp));
    return {lastOp + 1, opP + nextOp, lHalf, rHalf};
}

// Calculates 2 operands based on it's operator.
long double calcExp(long double lHalf, long double rHalf, char op) {
    switch(op) {
        case 'v': return lHalf==2 ? sqrt(rHalf) : cbrt(rHalf);
        case '^': return pow(lHalf, rHalf);
        case '*': return lHalf * rHalf;
        case '/': return lHalf / rHalf;
        case '%': return fmod(lHalf, rHalf);
        case '_': return lHalf - rHalf;
        case '+': return lHalf + rHalf;
    }
}

// Calculates the first 2 operands based on it's operator,
// while any operator of ops exists.
void calcAllExpOfOps(std::string &equ, const std::string &ops) {
    while(equ.find_first_of(ops) != std::string::npos) {
        int opP = equ.find_first_of(ops);
        expData exp = getExp(equ, opP);
        std::string res = std::to_string(calcExp(exp.lHalf, exp.rHalf, equ[opP]));
        equ.replace(equ.begin() + exp.start, equ.begin() + exp.end + 1, res);
    }
}
