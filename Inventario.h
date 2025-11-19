#ifndef INVENTARIO_H
#define INVENTARIO_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <map>
#include <set>
#include <cmath>  
#include <math.h> 

//clase para los productos en el inventario
class Producto {
public:
    std::string sku;            //Identificador unico del producto
    std::string nombre;         //Nombre del producto
    std::string categoria;      //Categoria del producto
    double precio;              //Precio del producto
    int cantidad;               //Cantidad en el inventario
    std::string fechaCaducidad; //Fecha de caducidad YYYY-MM-DD

    //Constructor para un producto con todos sus atributos
    Producto(std::string _sku = "", std::string _nombre = "", std::string _categoria = "",
             double _precio = 0.0, int _cantidad = 0, std::string _fechaCaducidad = "")
        : sku(_sku), nombre(_nombre), categoria(_categoria),
          precio(_precio), cantidad(_cantidad), fechaCaducidad(_fechaCaducidad) {} 
};

//Clase principal para gestionar el inventario
class Inventario {
private:
    std::vector<Producto> productos; //Almacenamiento de todos los productos
    std::map<std::string, std::vector<Producto*>> productosPorCategoria; //Indice para buscar por categoria
    std::map<double, std::vector<Producto*>> productosPorPrecio; //Indice para buscar por rango de precio
    std::set<std::string> categoriasUnicas; //Conjunto de todas las categorias

    //Algoritmo QuickSort para ordenar los productos por su nombre
    void quickSortPorNombre(int left, int right) {
        if (left < right) {
            int pivotIndex = partitionPorNombre(left, right);
            quickSortPorNombre(left, pivotIndex - 1);
            quickSortPorNombre(pivotIndex + 1, right);
        }
    }

    //Funcion auxiliar para particionar en QuickSort
    int partitionPorNombre(int left, int right) {
        std::string pivot = productos[right].nombre;
        int i = left - 1;

        for (int j = left; j < right; j++) {
            if (productos[j].nombre <= pivot) {
                i++;
                std::swap(productos[i], productos[j]);
            }
        }
        std::swap(productos[i + 1], productos[right]);
        return i + 1;
    }

    //Algoritmo MergeSort para ordenar los productos por su precio
    void mergeSortPorPrecio(int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSortPorPrecio(left, mid);
            mergeSortPorPrecio(mid + 1, right);
            mergePorPrecio(left, mid, right);
        }
    }

    //Funcion auxiliar para mezclar en MergeSort
    void mergePorPrecio(int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        //Arrays temporales
        std::vector<Producto> leftArr(n1);
        std::vector<Producto> rightArr(n2);

        for (int i = 0; i < n1; i++)
            leftArr[i] = productos[left + i];
        for (int j = 0; j < n2; j++)
            rightArr[j] = productos[mid + 1 + j];

        int i = 0, j = 0, k = left;

        //Mezclar los arrays temporales al array principal
        while (i < n1 && j < n2) {
            if (leftArr[i].precio <= rightArr[j].precio) {
                productos[k] = leftArr[i];
                i++;
            } else {
                productos[k] = rightArr[j];
                j++;
            }
            k++;
        }

        //Copiar los elementos restantes
        while (i < n1) {
            productos[k] = leftArr[i];
            i++;
            k++;
        }

        while (j < n2) {
            productos[k] = rightArr[j];
            j++;
            k++;
        }
    }

public:

    //Agrega un nuevo producto al inventario
    bool agregarProducto(const Producto& nuevoProducto) {
        //Verifica que el SKU no este duplicado
        for (const auto& producto : productos) {
            if (producto.sku == nuevoProducto.sku) {
                std::cout << "Error: El SKU " << nuevoProducto.sku << " ya existe" << std::endl;
                return false;
            }
        }
        
        productos.push_back(nuevoProducto);
        construirEstructuras(); //Actualizar indices
        std::cout << "Producto agregado exitosamente" << std::endl;
        return true;
    }

    //Busca un producto por su SKU 
    Producto* buscarProductoPorSKU(const std::string& sku) {
        for (auto& producto : productos) {
            if (producto.sku == sku) {
                return &producto;
            }
        }
        return nullptr; //Devuelve nullptr si no se encuentra el producto
    }

    //Actualiza la informacion de un producto que ya existe
    bool actualizarProducto(const std::string& sku, const Producto& productoActualizado) {
        for (auto& producto : productos) {
            if (producto.sku == sku) {
                producto = productoActualizado;
                construirEstructuras(); //Reconstruye el indice despues de actualizar
                std::cout << "Producto actualizado exitosamente" << std::endl;
                return true;
            }
        }
        std::cout << "Error: Producto con SKU " << sku << " no encontrado" << std::endl;
        return false;
    }

    //Elimina un producto del inventario
    bool eliminarProducto(const std::string& sku) {
        auto it = std::remove_if(productos.begin(), productos.end(),
                               [&](const Producto& p) { return p.sku == sku; });
        
        if (it != productos.end()) {
            productos.erase(it, productos.end());
            construirEstructuras(); //Actualiza el indice despues de eliminar
            std::cout << "Producto eliminado exitosamente" << std::endl;
            return true;
        }
        
        std::cout << "Error: Producto con SKU " << sku << " no encontrado" << std::endl;
        return false;
    }

    //Carga los productos desde el .csv
    bool cargarDesdeCSV(const std::string& archivo) {
        std::ifstream file(archivo);
        if (!file.is_open()) {
            std::cout << "Error al abrir el archivo: " << archivo << std::endl;
            return false;
        }

        std::string linea;
        //Salta la linea de encabezado
        if (!std::getline(file, linea)) return false;

        std::vector<Producto> tmp;

        //Lee cada linea del archivo
        while (std::getline(file, linea)) {
            if (linea.empty()) continue;

            std::stringstream ss(linea);
            std::string sku, nombre, categoria, precioStr, stockStr, fecha;

            if (!std::getline(ss, sku, ',')      ||
                !std::getline(ss, nombre, ',')   ||
                !std::getline(ss, categoria, ',')||
                !std::getline(ss, precioStr, ',')||
                !std::getline(ss, stockStr, ',') ||
                !std::getline(ss, fecha, ',')) {
                continue;
            }

            try {
                double precio = std::stod(precioStr);
                int cantidad = std::stoi(stockStr);
                tmp.emplace_back(sku, nombre, categoria, precio, cantidad, fecha);
            } catch (...) {
                std::cout << "Error procesando linea: " << linea << std::endl;
                continue;
            }
        }

        if (tmp.empty()) {
            std::cout << "No se pudieron cargar productos del archivo" << std::endl;
            return false;
        }

        productos = std::move(tmp);
        construirEstructuras(); //Construye indices despues de cargar
        std::cout << "Se cargaron " << productos.size() << " productos correctamente" << std::endl;
        return true;
    }

    //Construye las estructuras de indice para busquedas
    void construirEstructuras() {
        productosPorCategoria.clear();
        productosPorPrecio.clear();
        categoriasUnicas.clear();

        for (auto& producto : productos) {
            //Indexa por categoria
            productosPorCategoria[producto.categoria].push_back(&producto);
            
            //Indexa por rangos de precio redondeado a decenas
            double precioRedondeado = round(producto.precio / 10.0) * 10.0;
            productosPorPrecio[precioRedondeado].push_back(&producto);
            
            //Almacena categorias unicas
            categoriasUnicas.insert(producto.categoria);
        }
    }

    //Muestra todos los productos
    void mostrarProductos() {
        if (productos.empty()) {
            std::cout << "No hay productos en el inventario" << std::endl;
            return;
        }

        std::cout << std::fixed << std::setprecision(2);
        std::cout << std::left << std::setw(8)  << "SKU"
                  << std::setw(25) << "Nombre"
                  << std::setw(15) << "Categoria"
                  << std::setw(8)  << "Precio"
                  << std::setw(8)  << "Stock"
                  << std::setw(12) << "Caducidad" << std::endl;
        std::cout << std::string(80, '-') << std::endl;

        for (const auto& p : productos) {
            std::cout << std::left << std::setw(8)  << p.sku
                      << std::setw(25) << p.nombre
                      << std::setw(15) << p.categoria
                      << std::setw(8)  << p.precio
                      << std::setw(8)  << p.cantidad
                      << std::setw(12) << p.fechaCaducidad
                      << std::endl;
        }
    }

    //Muestra productos filtrados por su categoria
    void mostrarProductosPorCategoria(const std::string& categoria) {
        auto it = productosPorCategoria.find(categoria);
        if (it == productosPorCategoria.end()) {
            std::cout << "Categoria no encontrada: " << categoria << std::endl;
            return;
        }

        std::cout << "\nProductos en categoria '" << categoria << "':" << std::endl;
        std::cout << std::left << std::setw(8)  << "SKU"
                  << std::setw(25) << "Nombre"
                  << std::setw(8)  << "Precio"
                  << std::setw(8)  << "Stock" << std::endl;
        std::cout << std::string(50, '-') << std::endl;

        for (const auto& p : it->second) {
            std::cout << std::left << std::setw(8)  << p->sku
                      << std::setw(25) << p->nombre
                      << std::setw(8)  << p->precio
                      << std::setw(8)  << p->cantidad << std::endl;
        }
    }

    //Muestra todas las categorias
    void mostrarCategorias() {
        std::cout << "\nCategorias disponibles:" << std::endl;
        for (const auto& categoria : categoriasUnicas) {
            std::cout << "- " << categoria << std::endl;
        }
    }

    //Busca productos por su rango de precio
    void buscarProductosPorRangoPrecio(double min, double max) {
        std::vector<Producto*> resultados;
        
        //Filtra productos por su rango de precio
        for (const auto& producto : productos) {
            if (producto.precio >= min && producto.precio <= max) {
                resultados.push_back(const_cast<Producto*>(&producto));
            }
        }

        if (resultados.empty()) {
            std::cout << "No se encontraron productos en el rango de precio $" << min << " - $" << max << std::endl;
            return;
        }

        std::cout << "\nProductos en rango de precio $" << min << " - $" << max << ":" << std::endl;
        std::cout << std::left << std::setw(8)  << "SKU"
                  << std::setw(25) << "Nombre"
                  << std::setw(15) << "Categoria"
                  << std::setw(8)  << "Precio" << std::endl;
        std::cout << std::string(60, '-') << std::endl;

        for (const auto& producto : resultados) {
            std::cout << std::left << std::setw(8)  << producto->sku
                      << std::setw(25) << producto->nombre
                      << std::setw(15) << producto->categoria
                      << std::setw(8)  << producto->precio << std::endl;
        }
    }

    //Metodos de ordenamiento

    void ordenarPorNombre() {
        if (productos.empty()) return;
        quickSortPorNombre(0, productos.size() - 1);
        std::cout << "Productos ordenados por nombre" << std::endl;
    }

    void ordenarPorPrecio() {
        if (productos.empty()) return;
        mergeSortPorPrecio(0, productos.size() - 1);
        std::cout << "Productos ordenados por precio" << std::endl;
    }

    void ordenarPorStock() {
        std::sort(productos.begin(), productos.end(),
                  [](const Producto& a, const Producto& b) {
                      return a.cantidad < b.cantidad;
                  });
        std::cout << "Productos ordenados por stock" << std::endl;
    }

    void ordenarPorCaducidad() {
        std::sort(productos.begin(), productos.end(),
                  [](const Producto& a, const Producto& b) {
                      return a.fechaCaducidad < b.fechaCaducidad;
                  });
        std::cout << "Productos ordenados por fecha de caducidad" << std::endl;
    }

    //Guarda el inventario actual 
    bool guardarEnCSV(const std::string& archivo) {
        std::ofstream file(archivo);
        if (!file.is_open()) {
            std::cout << "Error al crear el archivo: " << archivo << std::endl;
            return false;
        }

        //Escribe el encabezado
        file << "sku,nombre,categoria,precio,stock,caducidad\n";
        
        //Escribe cada producto
        for (const auto& p : productos) {
            file << p.sku << ","
                 << p.nombre << ","
                 << p.categoria << ","
                 << std::fixed << std::setprecision(2) << p.precio << ","
                 << p.cantidad << ","
                 << p.fechaCaducidad << "\n";
        }

        file.close();
        std::cout << "Inventario guardado en " << archivo << " correctamente" << std::endl;
        return true;
    }

    //Devuelve el numero total de los productos en el inventario
    size_t obtenerNumeroProductos() const {
        return productos.size();
    }
};

#endif