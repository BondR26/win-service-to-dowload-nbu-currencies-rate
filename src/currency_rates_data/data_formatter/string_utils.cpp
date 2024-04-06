//
// Created by 26bon on 2/16/2024.
//

#include <locale>
#include <codecvt>
#include "string_utils.h"

namespace std
{
    string to_utf8(const wstring &str)
    {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        return converter.to_bytes(str);
    }

    wstring from_utf8(const string &str)
    {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        return converter.from_bytes(str);
    }
}
