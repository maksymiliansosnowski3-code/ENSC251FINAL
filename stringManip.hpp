#ifndef STRING_MANIP_HPP
#define STRING_MANIP_HPP

#include <iostream>
#include <string>
using namespace std;

class StringManip {
    public:
        static string toUpper(string str);
        static void typoCorrector(string str);
};
#endif