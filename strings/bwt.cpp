#ifndef BWT
#define BWT

#include <cstdint>
#include <string>

std::string bwt(const std::string& text)
{
    suffix_array sa(text);
    std::string t(text.length() + 1, ' ');
    const char ETX = 3;

    for (std::int64_t i = 0; i < t.length(); i++) {
        if (sa[i] == 0)
            t[i] = ETX;
        else
            t[i] = text[sa[i] - 1];
    }

    return t;
}

#endif
