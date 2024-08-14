# Helpers para realizar experimentos

Cada vez que queremos validar una hipótesis y comparar algoritmos se deben
realizar experimentos. Estos consumen tiempo y como es una tarea
repetitiva les ofrecemos soluciones precisas y estándares para estas.

### Tiempo

En [uhr](./uhr.cpp) (reloj, en alemán) está un cronómetro configurable
que reporta _tiempo promedio y desviación estándar_ para un set de tests.

#### Compilación

```bash
g++ uhr.cpp -std=c++11 -O2 -o uhr
```

Se pueden usar versiones más nuevas de C++ (14, 17, 20), pero NO anteriores
a C++11. También se puede optimizar de otras formas, pero `-O2` funciona
bastante bien.

#### Uso

```bash
./uhr <filename>.csv
```

Donde `<filename>` es el nombre de archivo donde se escribirán los resultados.
El archivo no debe existir previamente y debe tener extensión `.csv`

### Tablas

En [csvltx](https://github.com/leonardlover/csvltx) hay una herramienta que
ayuda al parsing de archivos CSV en formato de tabla para uso en LaTeX.

Para poder ejecutarla, deben tener [Rust](https://www.rust-lang.org) instalado,
en particular `cargo` y simplemente deben clonar el repositorio y hacer
```bash
cargo run <filename>
```

Donde `<filename>` es el archivo CSV que fue escrito por uhr. Esto imprimirá
en la consola el texto que hay que copiar en el archivo LaTeX para mostrar la tabla.

Tambien existe una alternativa en Python usando Pandas, que es
[`to_latex`](https://pandas.pydata.org/docs/reference/api/pandas.DataFrame.to_latex.html),
el uso de este requiere cargar el CSV como DataFrame y usar el paquete `booktabs`
en LaTeX, así que la alternativa en Rust funciona puramente en la terminal y no
requiere adiciones a LaTeX.
