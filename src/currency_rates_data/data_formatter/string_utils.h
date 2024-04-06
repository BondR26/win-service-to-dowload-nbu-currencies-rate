//
// Created by 26bon on 2/16/2024.
//

#ifndef COOL_PROJECT_STRING_UTILS_H
#define COOL_PROJECT_STRING_UTILS_H
#include <string>

namespace std
{
    string to_utf8(const wstring &str);

    wstring from_utf8(const string &str);
}

#endif //COOL_PROJECT_STRING_UTILS_H
