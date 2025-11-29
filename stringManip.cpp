#include <iostream>
#include <string>
#include "stringManip.hpp"
using namespace std;

string StringManip::toUpper(const string& str) {
    string result;
    result.reserve(str.size());

    for (unsigned char c : str) {
        result += static_cast<char>(toupper(c));
    }
    return result;
}

void StringManip::typoCorrector(string& str) {
    size_t strPos = str.find("Bata");

    if (strPos != string::npos) {
        cout << "Known typo 'Bata' found. Typo has been corrected to 'Beta'.\n";
        str.replace(strPos, 4, "Beta");
    }
}
