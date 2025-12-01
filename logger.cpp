#include "logger.hpp" // fixed case: was "Logger.hpp" causing missing header error
#include <fstream> // for file reading and writing
#include <iostream>
using namespace std;

Logger::Logger(const string& file) {
    filename = file;
}


void Logger::log(const string& msg) {
    std::ofstream out(filename, ios::app); // append msg to filename
    if (!out) return; // if failed to open return nothing
    out << msg << "\n"; // writes msg as a new line in file
}

void Logger::show() const {
    ifstream in(filename); // read file
    if (!in) { // if cant read file
        std::cout << "No log file found.\n";
        return;
    }

    string line;
    cout << "----- LOGS -----\n";
    while (std::getline(in, line)) { // get the line, in for reading the files
        std::cout << line << "\n"; // output each line
    }
    cout << "----------------------\n";
}


