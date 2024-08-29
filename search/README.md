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
