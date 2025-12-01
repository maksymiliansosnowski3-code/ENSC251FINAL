//

#ifndef STRING_MANIP_HPP
#define STRING_MANIP_HPP

#include <iostream>
#include <string>
using namespace std;

class StringManip {
public:
    // converts a string to uppercase
    static string toUpper(const string& str);
    //  converts a string to lowercase
    static void typoCorrector(string& str);
};

#endif
