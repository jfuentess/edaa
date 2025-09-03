#ifndef RK
#define RK

#include <iostream>
#include <string>

// Rabin-Karp pattern searching algorithm
/*
pat = Patrón
txt = Texto
q = Número primo utilizado para la función hash. El valor se podría dejar constante dentro de la función, pero para patrones grandes
es mejor tener un q más grande.
*/
int64_t rk(const std::string &pat, const std::string &txt, int q) {
    const int d = 256; // tamaño del alfabeto (ASCII)
    int64_t count = 0;

    int txt_length = txt.length();
    int pat_length = pat.length();

    if (pat_length > txt_length) return 0;

    int p = 0; // hash del patrón
    int t = 0; // hash de la ventana actual del texto
    int h = 1; // d^(pat_length-1) % q

    // Precalcular h
    for (int i = 0; i < pat_length - 1; i++) {
        h = (h * d) % q;
    }

    // Hash inicial del patrón y de la primera ventana del texto
    for (int i = 0; i < pat_length; i++) {
        p = (d * p + pat[i]) % q;
        t = (d * t + txt[i]) % q;
    }

    // Deslizar el patrón sobre el texto
    for (int i = 0; i <= txt_length - pat_length; i++) {
        if (p == t) {
            int j = 0;
            while (j < pat_length && txt[i + j] == pat[j]) {
                j++;
            }
            if (j == pat_length) {
                count++;
            }
        }

        // Calcular el hash de la siguiente ventana
        if (i < txt_length - pat_length) {
            t = (d * (t - txt[i] * h) + txt[i + pat_length]) % q;
            if (t < 0) {
                t += q;
            }
        }
    }

    return count;
}

#endif
