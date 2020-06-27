#pragma once
#include <iostream>
#include <string>

void _log(const std::string &prefix, const std::string &msg) {
    std::cout << "[" + prefix + "] " + msg << '\n';
}

class log {
public:
    log() = delete;
    static void info (const std::string &msg) {
        _log("INFO", msg);
    }
    static void warn (const std::string &msg) {
        _log("WARNING", msg);
    }
    static void error(const std::string &msg) {
        _log("ERROR", msg);
    }
};
