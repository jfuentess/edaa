# Heaps

Aquí se encuentran wrappers de implementaciones de heaps binarios y binomiales.
Los heaps binarios son derivados de la STL y los binomiales fueron sacados de
[GeeksForGeeks](https://www.geeksforgeeks.org/binomial-heap-2/). Se agregaron
comentarios para describir exactamente qué ocurre.

Las funciones relevantes de la STL son:

- [`std::make_heap`](https://en.cppreference.com/w/cpp/algorithm/make_heap),
- [`std::push_heap`](https://en.cppreference.com/w/cpp/algorithm/push_heap),
- [`std::pop_heap`](https://en.cppreference.com/w/cpp/algorithm/pop_heap).

## Complejidades

Sea $n$ la cantidad de elementos en el heap y $m$ la cantidad de elementos en
el otro heap con el cual se quiere hacer meld.

| Operación | Binario | Binomial |
| --------- | ------- | -------- |
| top | $O(1)$ | $O(1)$ |
| push | $O(\log n)$ | $O(1)$ amortizado |
| pop | $O(\log n)$ | $O(\log n)$ |
| meld | $O(n + m)$ | $O(\log \max(n, m))$ |
| heapify | $O(n)$ | $O(n)$ |

## Referencias interesantes

- Floyd, Robert (1964). _Algorithm 245 – Treesort 3_. Communications of the ACM. *7* (12): 701.
- GeeksForGeeks (2023). _Implementation of Binomial Heap_. Disponible en línea [aquí](https://www.geeksforgeeks.org/implementation-binomial-heap/)
- Knuth, Donald (1998). _Sorting and Searching_. The Art of Computer Programming. Vol. 3 (2nd ed.). Addison-Wesley Professional.
- Vuillemin, Jean (1978). _A data structure for manipulating priority queues_. Communications of the ACM. *21* (4): 309–315.
- Williams, J. W. J. (1964). _Algorithm 232 - Heapsort_. Communications of the ACM. *7* (6): 347–348

A Williams le es atribuida la invención de los heaps, aunque su algoritmo de
construcción no era lineal, fue Floyd quien dio la primera descripción de un
heapify lineal. Finalmente, Vuillemin inventa los heaps binomiales en 1978.

También hay manejo de heaps binarios en Python, ver el módulo [`heapq`](https://docs.python.org/3/library/heapq.html).

Hay muchos más tipos de heaps, uno de los más importantes y con mejores
garantías teóricas son los de [Fibonacci](https://en.wikipedia.org/wiki/Fibonacci_heap).
