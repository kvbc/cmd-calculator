#pragma once
#include <algorithm>
#include <string>
#include "log.h"

long double calcEqu(const std::string &equ, bool legalCheck);

// Finds matching closing bracket in equation.
int findClBracket(const std::string &equ, int start) {
    int opBracket = 0;
    for(int i=start; i<equ.length(); i++)
        if(equ[i] == '(') opBracket++;
        else if(equ[i] == ')') {
            if(!opBracket) return i;
            else           opBracket--;
        }
    return -1;
}

// Checks if parasyntheses is legal
// (closing bracket is found).
bool legalParasyntheses(std::size_t clBracket) {
    if(clBracket < 0) {
        log::error("Unmatched parasyntheses");
        return false;
    }
    return true;
}

// Calculates all the parasyntheses in an equation.
// If parasyntheses are unmatched returns false, otherwise returns true.
bool calcAllParasyntheses(std::string &equ) {
    while(equ.find('(') != std::string::npos) {
        int opBracket = equ.find('(');
        std::size_t clBracket = findClBracket(equ, opBracket + 1);
        if(!legalParasyntheses(clBracket)) return false;
        std::string res = std::to_string(calcEqu(equ.substr(opBracket + 1, clBracket - opBracket - 1), false));
        equ.replace(equ.begin() + opBracket, equ.begin() + clBracket + 1, res);
    }
    int opBracket = std::count(equ.begin(), equ.end(), ')');
    int clBracket = std::count(equ.begin(), equ.end(), '(');
    if(opBracket != clBracket) log::error("Unmatched parasyntheses");
    return opBracket == clBracket;
}
