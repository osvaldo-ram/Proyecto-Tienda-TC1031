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

## SICT0302: Toma decisiones

### Selecciona un algoritmo de ordenamiento adecuado al problema y lo usa correctamente

Para este avance decidí implementar dos enfoques. Para ordenar por nombre utilicé Selection Sort, ya que es un algoritmo sencillo de programar y me permite validar que las comparaciones funcionan correctamente. Aunque no es el más eficiente, me sirve como punto de partida para demostrar el ordenamiento dentro del inventario.  

Para los casos de precio, stock y caducidad empleé std::sort de la STL, que utiliza introsort. Esto permite tener un algoritmo mucho más eficiente y práctico cuando se trabaja con listas más grandes, ya que garantiza un rendimiento promedio y en el peor caso de O(n log n).  

De esta manera, mi sistema integra tanto un algoritmo implementado por Selection Sort como un algoritmo optimizado de biblioteca std::sort, lo que me permite justificar el uso de cada uno según la situación.  

## SICT0301: Evalúa los componentes

### Hace un análisis de complejidad correcto y completo para los algoritmos de ordenamiento usados en el programa

El algoritmo Selection Sort tiene complejidad de O(n²) en el mejor, promedio y peor caso. Esto significa que el tiempo de ejecución crece de forma cuadrática conforme aumenta el número de productos en el inventario, por lo que únicamente resulta práctico para volúmenes pequeños de datos como los que manejo en este avance.  

El algoritmo std::sort tiene una complejidad promedio y en el peor caso de O(n log n), lo que lo hace mucho más eficiente para listas más grandes. Al apoyarse en introsort, ayuda a que en el peor escenario se mantenga un rendimiento decente.  

De esta forma, Selection Sort me sirve como referencia didáctica y para validar los procesos de ordenamiento iniciales, mientras que std::sort representa la opción para manejar el inventario completo de manera fácil. 


## SICT0303: Implementa acciones científicas

### Implementa mecanismos para consultar información de las estructuras correctos y útiles dentro de un programa


### Implementa mecanismos de lectura de archivos correctos y útiles dentro de un programa


### Implementa mecanismos de escritura de archivos correctos y útiles dentro de un programa
