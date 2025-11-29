#include <iostream>
#include <string>
#include "stringManip.hpp"
using namespace std;

void StringManip::typoCorrector(string str) {
    size_t strPos = str.find('Bata');

    if (strPos != string::npos) {
        cout << "Known typo 'Bata' found. Typo has been corrected to 'Beta'.\n";
        str.replace(strPos, 4, "Beta");
    }
}

string StringManip::toUpper(string str) {
    string result = "";

    for (char c : str) {
        result += toupper(c);
    }
    return result;
}