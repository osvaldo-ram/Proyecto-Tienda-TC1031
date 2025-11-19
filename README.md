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

El algoritmo Selection Sort tiene complejidad de O(n²) en el mejor, promedio y peor caso. Esto significa que el tiempo de ejecución crece de forma cuadrática conforme aumenta el número de productos en el inventario, por lo que únicamente resulta práctico para volúmenes pequeños de datos como los que manejo en este avance.  

El algoritmo std::sort tiene una complejidad promedio y en el peor caso de O(n log n), lo que lo hace mucho más eficiente para listas más grandes. Al apoyarse en introsort, ayuda a que en el peor escenario se mantenga un rendimiento decente.  

### Hace un análisis de complejidad correcto y completo todas las estructuras de datos y cada uno de sus usos en el programa

Para el almacenamiento principal de productos, seleccioné std::vector porque ofrece acceso aleatorio en O(1) y es compatible con los algoritmos de ordenamiento de la STL, aunque su búsqueda es O(n).

Para optimizar las consultas frecuentes, implementé std::map para el indexado por categoría y rangos de precio, para operaciones de búsqueda en O(log n). También usé std::set para almacenar categorías únicas, garantizando que las operaciones de inserción y consulta sean O(log n).

En cuanto a los algoritmos, mantuve Selection Sort para ordenar por nombre con complejidad O(n²). Para los criterios como precio, stock y caducidad, utilicé std::sort con complejidad O(n log n).

## SICT0302: Toma decisiones

### Selecciona un algoritmo de ordenamiento adecuado al problema y lo usa correctamente

Para este avance decidí implementar dos enfoques. Para ordenar por nombre utilicé Selection Sort, ya que es un algoritmo sencillo de programar y me permite validar que las comparaciones funcionan correctamente. Aunque no es el más eficiente, me sirve como punto de partida para demostrar el ordenamiento dentro del inventario.  

Para los casos de precio, stock y caducidad empleé std::sort de la STL, que utiliza introsort. Esto permite tener un algoritmo mucho más eficiente y práctico cuando se trabaja con listas más grandes, ya que garantiza un rendimiento promedio y en el peor caso de O(n log n).  

De esta manera, mi sistema integra tanto un algoritmo implementado por Selection Sort como un algoritmo optimizado de biblioteca std::sort, lo que me permite justificar el uso de cada uno según la situación.  

## Selecciona una estructura de datos adecuada al problema y lo usa correctamente

Seleccioné std::vector como estructura principal para el acceso rápido a los elementos y para la compatibilidad con los algoritmos de ordenamiento. Para las consultas específicas, implementé std::map, permite acceder rápidamente a productos por categoría en O(log n) en lugar de tener que hacer búsquedas lineales O(n).

El  std::set para las categorías únicas fue una decisión consciente, ya que me asegura que no habrá duplicados y me permite listar todas las categorías disponibles. Estas estructuras las reconstruyo después de cada ordenamiento para mantener la consistencia entre los datos y los índices.

## SICT0303: Implementa acciones científicas

### Implementa mecanismos para consultar información de las estructuras correctos

Implementé tres mecanismos principales de consulta que aprovechan las estructuras de datos. La función mostrarProductosPorCategoria() utiliza el mapa de categorías para recuperar productos específicos en tiempo O(log n), mucho más eficiente que una búsqueda lineal.

La función buscarProductosPorRangoPrecio() realiza un filtrado sobre el vector principal pero con notificación inmediata de resultados, y mostrarCategorias() utiliza el set para listar todas las categorías disponibles sin duplicados.

## Implementa mecanismos de lectura de archivos para cargar datos a las estructuras de manera correcta

La función cargarDesdeCSV() implementa un proceso robusto que incluye validación de archivo, parsing de cada línea con manejo de excepciones, y la construcción automática de las estructuras de datos auxiliares. Además, después de cargar los datos principales, llamo a construirEstructuras() para inicializar los mapas y sets que optimizan las consultas.

También implementé guardarEnCSV() que permite exportar el estado actual del inventario manteniendo el formato original, con precios de 2 decimales y fechas en formato ISO.


De esta forma, Selection Sort me sirve como referencia didáctica y para validar los procesos de ordenamiento iniciales, mientras que std::sort representa la opción para manejar el inventario completo de manera fácil.
