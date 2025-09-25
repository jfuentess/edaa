/*
 Elias Omega obtenido de Bitte ein Bit
 y trasnformado a C++
*/

#include <bits/stdc++.h>

std::string eliasOmegaEncode(unsigned int n) {
    assert(n > 0);

    std::string c = "0";
    while (n > 1) {
        std::string bin = std::bitset<64>(n).to_string(); 

        bin.erase(0, bin.find('1'));

        c = bin + c;
        n = (int)bin.size() - 1;
    }
    return c;
}

unsigned int eliasOmegaDecode(const std::string &c) {
    unsigned int n = 1;
    size_t i = 0;

    while (c[i] != '0') {
        std::string m = c.substr(i, n + 1);
        i += n + 1;
        n = stoi(m, nullptr, 2);
    }
    return n;
}
