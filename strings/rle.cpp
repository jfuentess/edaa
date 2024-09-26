#ifndef RLE
#define RLE

#include <cstdint>
#include <string>
#include <vector>

std::vector<std::pair<char, std::uint8_t> > rle(const std::string& text)
{
    std::vector<std::pair<char, std::uint8_t> > enc;

    if (text.empty())
        return enc;

    enc.push_back({text[0], 1});

    for (std::int64_t i = 1; i < text.length(); i++) {
        if (enc.back().first == text[i]) {
            if (enc.back().second == 255)
                enc.push_back({text[i], 1});
            else
                enc.back().second++;
        } else {
            enc.push_back({text[i], 1});
        }
    }

    return enc;
}

#endif
