# Búsqueda

Aquí se implementan algoritmos básicos de búsqueda. La búsqueda secuencial
es la única que funciona en datos arbitrarios, mientras que la búsqueda
binaria y galopante requieren de tener datos _ordenados_.

## Alternativas en STL

En [`<algorithm>`](https://en.cppreference.com/w/cpp/header/algorithm) se
encuentran muchas funciones útiles para búsqueda:

- [`std::find`](https://en.cppreference.com/w/cpp/algorithm/find), retorna
un iterador a la primera ocurrencia de un elemento en un rango;

- [`std::count`](https://en.cppreference.com/w/cpp/algorithm/count),
retorna la cantidad de ocurrencias del elemento buscado;

- [`std::search`](https://en.cppreference.com/w/cpp/algorithm/search),
como `std::find`, pero busca un rango entero en vez de un solo elemento,

- [`std::binary_search`](https://en.cppreference.com/w/cpp/algorithm/binary_search),
determina si un elemento está presente en un rango ordenado;

- [`std::lower_bound`](https://en.cppreference.com/w/cpp/algorithm/lower_bound) y [`std::upper_bound`](https://en.cppreference.com/w/cpp/algorithm/upper_bound),
retornan iteradores apuntando al inicio y final del rango en donde un
elemento se insertaría para mantener el orden.

## Referencias interesantes

- Bentley, Jon; Yao, Andrew (1976). _An almost optimal algorithm for unbounded searching_. Information Processing Letters. *5* (3): 82–87.
- Bottenbruch, Hermann (1 April 1962). _Structure and use of ALGOL 60_. Journal of the ACM. *9* (2): 161–221.
- Knuth, Donald (1998). _Sorting and Searching_. The Art of Computer Programming. Vol. 3 (2nd ed.). Addison-Wesley Professional.

En Bentley-Yao se describe por primera vez la búsqueda galopante, en Bottenbruch está
la descripción de la búsqueda binaria implementada [aquí](./binary_search.cpp) y en
Knuth está todo lo que uno puede querer saber de búsqueda.
