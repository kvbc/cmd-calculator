#pragma once
#include <string>
#include <regex>
#include "exp.h"
#include "parasyntheses.h"
#include "log.h"

// Replaces all the functions in the equation with it's operator.
void initFunc(std::string &equ, const std::string &func, const std::string &op) {
    while(equ.find(func + '(') != std::string::npos) {
        int funcP = equ.find(func + '(');
        int clBracket = findClBracket(equ, funcP + (func.length() + 1));
        std::string funcC = equ.substr(funcP + (func.length() + 1), clBracket - funcP - (func.length() + 1));
        std::string res = std::to_string(calcEqu(funcC, false, false));
        equ.replace(equ.begin() + funcP, equ.begin() + clBracket + 1, op + res);
    }
}

// Initializes the equation for easier use of functions.
void initEqu(std::string &equ) {
    equ = std::regex_replace(equ, std::regex(" "), "");
    equ = std::regex_replace(equ, std::regex("-"), "_");
    initFunc(equ, "sqrt", "2v");
    initFunc(equ, "cbrt", "3v");
}

// Returns an beautified equation.
std::string beautifyEqu(const std::string &equ) {
    std::string ops = "^*/%-+";
    std::string beautyEqu;
    for(char c : std::regex_replace(equ, std::regex(" "), "")) {
        bool op = ops.find(c) != std::string::npos;
        if(op) beautyEqu += ' ';
        beautyEqu += c;
        if(op) beautyEqu += ' ';
    }
    return beautyEqu;
}

// Checks if the equation is legal
// (contains nothing other than digits, operators, parasyntheses and '.').
bool legalEqu(const std::string &equ) {
    std::string illegalChars = std::regex_replace(equ, std::regex("[.0-9v^*/%_+()]"), "");
    if(illegalChars.length()) {
        log::error("Illegal character(s) in mathematical equation");
        return false;
    }
    return true;
}

// Calculates the equation.
long double calcEqu(const std::string &equ, bool beautify = true, bool legalCheck = true) {
    std::string equCpy = equ;
    if(beautify)                          std::cout << "Beautified: " << beautifyEqu(equCpy) << std::endl;
    initEqu(equCpy);
    if(!equCpy.length())                  return 0;
    if(legalCheck && !legalEqu(equCpy))   return -1;
    if(!calcAllParasyntheses(equCpy))     return -1;
    calcAllExpOfOps(equCpy, "v");
    calcAllExpOfOps(equCpy, "^");
    calcAllExpOfOps(equCpy, "*/");
    calcAllExpOfOps(equCpy, "%");
    calcAllExpOfOps(equCpy, "_+");
    return std::stold(equCpy);
}
