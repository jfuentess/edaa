/*
 Elias Gamma recuperado de GeeksforGeeks https://www.geeksforgeeks.org/python/elias-gamma-encoding-in-python/
 y transformado a C++ 
*/

#include <bits/stdc++.h>


std::string Unary(int x) {
    return std::string(x - 1, '0') + "1";
}

std::string Binary(int x, int l = 1) {
    std::string s;
    for (int i = l - 1; i >= 0; i--) {
        s.push_back((x & (1 << i)) ? '1' : '0');
    }
    return s;
}


std::string eliasGammaEncode(int x) {
    if (x == 0) return "0";

    int l = (int)log2(x);
    int n = l + 1;
    int b = x - (1 << l);

    return Unary(n) + Binary(b, l);
}


int eliasGammaDecode(const std::string &x) {
    int K = 0;


    while (K < (int)x.size() && x[K] == '0') {
        K++;
    }

    int length = K + 1;

    std::string bits = x.substr(K, length);

    int value = stoi(bits, nullptr, 2);

    return value;
}


