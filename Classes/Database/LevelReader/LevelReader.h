#ifndef __LEVEL_READER_H__
#define __LEVEL_READER_H__

#include "Database/nlohmann/json.hpp"
#include <string>
using json = nlohmann::json;
using namespace std;

string stringToRawString(string s) {
    string res = "";
    for (char c : s) {
        if (c == '\"') {
            res = res + "\\\"";
        }
        else {
            res = res + c;
        }
    }
    return res;
}

#endif // !__LEVEL_READER_H__