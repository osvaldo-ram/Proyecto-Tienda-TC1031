# Proyecto-Tienda-TC1031
## Inventario de productos de una tienda

Este proyecto consiste en un sistema sencillo que administra el inventario de productos de una tienda.  
La idea es poder registrar productos con sus datos principales (sku, nombre, categoría, precio, stock y fecha de caducidad)  
y realizar operaciones de ordenamiento para apoyar decisiones como reabastecer, comparar precios o detectar productos próximos a caducar.

Ejemplo de funcionamiento:

 Producto: Leche entera 1L 
 
 Precio: 24.90 pesos  
 
 Stock: 12 piezas  
 
 Caducidad: 30/11/2025  

El sistema puede ordenar los productos por **nombre, precio, stock y fecha de caducidad**, de forma que se puedan tomar mejores decisiones como:  

- Listar primero los productos con menor stock.
  
- Ver cuáles están más baratos o más caros.
  
- Detectar cuáles están por vencer. 

## SICT0301: Evalúa los componentes

### Hace un análisis de complejidad correcto y completo para los algoritmos de ordenamiento usados en el programa

Para los algoritmos de ordenamiento, usé:

Quick Sort para ordenar por nombre. Este algoritmo tiene una complejidad promedio de O(n log n). Entonces, cuando aumenta el número de productos, el tiempo de ejecución crece de manera proporcional al logaritmo del tamaño. En el peor caso puede ser O(n²), pero para datos como nombres de productos que suelen estar desordenados, me parece que funciona bien.

Merge Sort para ordenar por precio. Este algoritmo garantiza O(n log n) en todos los casos, desde el peor hasta en el mejor escenario. Por lo que mantiene un buen rendimiento sin importar cómo estén distribuidos los precios inicialmente.

std::sort para stock y caducidad. Para estos criterios usé el algoritmos de la biblioteca estándar que también tiene complejidad O(n log n), y como ya está optimizado y probado me pareció buena opción.

### Hace un análisis de complejidad correcto y completo todas las estructuras de datos y cada uno de sus usos en el programa

std::vector para productos. Usé vector como estructura principal porque permite acceso rápido a cualquier elemento en O(1) y es compatible con los algoritmos de ordenamiento. La desventaja es que buscar un elemento específico requiere O(n).

std::map para índices. Implementé mapas para organizar productos por categoría y por rangos de precio. Para categorías, localizar la clave de la categoría en el mapa toma O(log C), donde C es el número de categorías distintas, y luego se recorre solo la lista de productos de esa categoría (O(k), donde k es la cantidad de productos en esa categoría).

std::set para categorías. Usé un set para almacenar las categorías únicas. Insertar una categoría es O(log C) y recorrer todas las categorías para mostrarlas es O(C), garantizando que no haya duplicados.

### Hace un análisis de complejidad correcto y completo para todos los demás componentes del programa y determina la complejidad final del programa

#### Operaciones Crear, Leer, Actualizar y Eliminar.

Agregar producto. Primero revisa que el SKU no esté repetido recorriendo la lista completa de productos (O(n)). Después añade el producto al final del vector (O(1) amortizado) y reconstruye los índices (mapas y set) para mantener las búsquedas rápidas (O(n log n)). En conjunto, la operación de agregar es O(n log n).

Buscar por SKU. Tiene que revisar producto por producto hasta encontrar el que coincide con el SKU buscado (O(n)). Entre más productos haya más tiempo tomará.

Actualizar producto. Primero busca el producto (O(n)) y luego reorganiza los índices (O(n log n)).

Eliminar producto. Es similar al de actualizar, busca el producto (O(n)) y reorganiza índices (O(n log n)).

#### Consultar y búsquedas

Mostrar por categoría. Utiliza un mapa que relaciona cada categoría con sus productos. Buscar la categoría en el mapa toma O(log C) (C = número de categorías) y luego se recorren solo los productos de esa categoría (O(k)), por lo que la complejidad total es O(log C + k).

Búsqueda por precio. Actualmente recorre todos los productos uno por uno y filtra los que caen en el rango de precio indicado, con complejidad O(n). Aunque existe un índice por precio, todavía no se usa directamente en esta consulta, lo que deja abierta una posible optimización futura.

Mostrar categorías. Recorre el std::set de categorías únicas para imprimirlas, lo que toma O(C), donde C es el número de categorías distintas.


#### Manejo de archivos

Cargar desde csv. Lee el archivo inventario.csv línea por línea (O(n)), convierte los datos de texto a los tipos correspondientes y al final reconstruye los índices (mapas y set) para que las búsquedas sean rápidas (O(n log n)). La complejidad total de la carga es O(n log n).

Guardar en csv. Recorre todos los productos en memoria y los escribe de nuevo en el mismo archivo inventario.csv, manteniendo el formato original. Esta operación es O(n).

### Complejidad final del programa

El programa funciona muy bien para inventario de tamaño normal tipo cientos o miles de productos. Las partes más lentas son cuando se agregan, actualizan o eliminan productos porque, además de recorrer la lista, se reconstruyen los índices (mapas y set), lo que lleva a una complejidad O(n log n). Esto es necesario para mantener las búsquedas por categoría rápidas.

Las operaciones rápidas son: Mostrar categorías, búsqueda por categoría.
Las operaciones moderadas son: Agregar/actualizar/eliminar productos.
Las operaciones más lentas son: Buscar por SKU, búsquedas por precio.

Para el uso normal de una tienda, el rendimiento del programa creo que es más que suficiente y las operaciones que se usan más frecuentemente como mostrar productos por categoría son las más eficientes.

## SICT0302: Toma decisiones

### Selecciona un algoritmo de ordenamiento adecuado al problema y lo usa correctamente

Para los diferentes tipos de ordenamiento en el inventario, elegí algoritmos específicos según el tipo de datos.

Para ordenar por nombre usé Quick Sort porque los nombres de productos son texto y este algoritmo es muy eficiente con datos que no tienen un patrón específico. Quick Sort funciona bien en la práctica aunque en teoría puede tener un peor caso lento.

Para ordenar por precio implementé Merge Sort porque los precios son números y este algoritmo garantiza un rendimiento consistente sin importar cómo estén organizados inicialmente los precios.

Para stock y caducidad utilicé el algoritmo std::sort porque ya está probado y optimizado, lo que me ahorra tiempo y evita posibles errores.

Esta combinación me permite tener un balance entre eficiencia y confiabilidad, al usar algoritmos más especializados donde se necesitan y aprovechando lo que ya viene incluido en C++ para ahorrar esfuerzo.

## Selecciona una estructura de datos adecuada al problema y lo usa correctamente

Para almacenar los productos elegí std::vector como estructura principal porque es más eficiente, permite un acceso rápido a cualquier posición, es compatible con todos los algoritmos de ordenamiento, es fácil de usar y de mantener.

Para hacer las búsquedas más rápidas creé índices adicionales con:
std::map para organizar productos por categoría y precio.
std::set para guardar la lista de categorías sin duplicados

Estas estructuras permiten encontrar productos de una categoría, mostrar categorías y operaciones rápidamente.

Y así puedo tener un almacenamiento principal simple y eficiente, con índices que aceleran las búsquedas más frecuentes sin complicar demasiado el código.


## SICT0303: Implementa acciones científicas

### Implementa mecanismos para consultar información de las estructuras correctos

Implementé varios sistemas de consulta que aprovechan las estructuras de datos para obtener información de buena manera:

Búsqueda por categoría. Utilizo un mapa que relaciona cada categoría con sus productos correspondientes. Cuando el usuario busca una categoría, el sistema accede directamente a esa categoría y muestra solo los productos que pertenecen a ella, sin tener que revisar todo el inventario.

Búsqueda por SKU. Implementé una función que recorre la lista de productos hasta encontrar el que coincide con el SKU buscado. Aunque revisa producto por producto, para el tamaño de inventario que se maneja funciona de una manera aceptable.

Búsqueda por rango de precios. Esta función filtra todos los productos y muestra solo aquellos cuyo precio está dentro del rango especificado. Es una búsqueda completa pero efectiva para encontrar productos en un precio específico.

Listado de categorías. Muestro todas las categorías disponibles usando un conjunto que automáticamente elimina duplicados, así se asegura que cada categoría aparezca solo una vez.


## Implementa mecanismos de lectura de archivos para cargar datos a las estructuras de manera correcta

El programa carga el inventario desde un .csv de la siguiente manera:

Proceso de carga. Se lee el archivo línea por línea, ignorando la primera línea que contiene los encabezados. Para cada línea, se separan los campos por comas y se convierten los textos a números donde es necesario como en precio y cantidad.

Manejo de errores. Si se encuentra una línea con formato incorrecto o datos no válidos, se muestra un mensaje de error pero el programa continúa procesando el resto del archivo sin detenerse.

Construcción de estructuras. Después de cargar todos los productos, se construyen automáticamente los mapas y conjuntos que hacen posibles las búsquedas rápidas por categoría y precio.

## Implementa mecanismos de escritura de archivos para guardar los datos de las estructuras de manera correcta

Implementé la capacidad al programa de guardar el inventario actualizado.

Formato. Al guardar el nuevo inventario, mantengo exactamente el mismo formato del archivo original, con los mismos encabezados y orden de campos, sobrescribiendo el archivo "inventario.csv".

Formato de los datos. Los precios se guardan con formato numérico y las fechas en el mismo formato que el archivo original, para que el CSV pueda ser leído por otros programas.

Guardado completo. El programa escribe todos los productos actuales, incluyendo cualquier cambio, adición o eliminación que se haya hecho en la sesión. De esta manera, al volver a ejecutar el programa y cargar "inventario.csv", se conservan los cambios realizados.

Estos mecanismos de entrada y salida hacen que el programa sea confiable y fácil de usar, y permite cargar datos existentes y guardar cambios de forma segura.

## Aclaración del problema "archivo no salva producto"

En la versión anterior, el programa guardaba los cambios en un archivo distinto llamado "inventario_actualizado.csv", pero al iniciar el programa siempre se leía desde "inventario.csv". Esto provocaba que, al cerrar y volver a abrir el programa, los productos recién agregados parecían que no se habían guardado. Para corregir este problema, ahora la opción de guardado escribe directamente sobre "inventario.csv", de modo que al reiniciar el programa los cambios sí se reflejan.
