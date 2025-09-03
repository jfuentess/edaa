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
    const int d = 256; // tamaño del alfabeto (Pensado para ASCII, cambiar el valor si es necesario)
    int64_t count = 0; // número de ocurrencias del patrón "pat"

    int txt_length = txt.length();
    int pat_length = pat.length();

    int p = 0; // hash del patrón
    int t = 0; // hash de la ventana actual del texto
    int h = 1; // valor = pow(d, path_length-1) % q

    // Precalcular h = d^(txt_length-1) % q
    for (int i = 0; i < txt_length - 1; i++) {
        h = (h * d) % q;
    }

    // Hash inicial del patrón y de la primera ventana del texto
    for (int i = 0; i < txt_length; i++) {
        p = (d * p + pat[i]) % q;
        t = (d * t + txt[i]) % q;
    }

    // Deslizar el patrón sobre el texto
    for (int i = 0; i <= pat_length - txt_length; i++) {
        // Si los hashes coinciden, verificar carácter a carácter
        if (p == t) {
            int j = 0;
            while (j < txt_length && txt[i + j] == pat[j]) {
                j++;
            }
            if (j == txt_length) {
                count++; // patrón encontrado
            }
        }

        // Calcular el hash para la siguiente ventana
        if (i < pat_length - txt_length) {
            t = (d * (t - txt[i] * h) + txt[i + txt_length]) % q;

            // Asegurar que el hash sea positivo
            if (t < 0) {
                t += q;
            }
        }
    }

    return count;
}

#endif
