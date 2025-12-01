#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>

class Logger {
private:
    std::string filename;

public:
    Logger(const std::string& file = "log.txt");
    void log(const std::string& msg);
    void show() const;
};

#endif