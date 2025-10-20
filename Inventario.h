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

class Producto {
public:
    std::string sku;
    std::string nombre;
    std::string categoria;
    double precio;      
    int cantidad;       
    std::string fechaCaducidad;

    Producto(std::string _sku, std::string _nombre, std::string _categoria,
             double _precio, int _cantidad, std::string _fechaCaducidad)
        : sku(_sku), nombre(_nombre), categoria(_categoria),
          precio(_precio), cantidad(_cantidad), fechaCaducidad(_fechaCaducidad) {} 
};

class Inventario {
private:
    std::vector<Producto> productos;
    std::map<std::string, std::vector<Producto*>> productosPorCategoria;
    std::map<double, std::vector<Producto*>> productosPorPrecio;
    std::set<std::string> categoriasUnicas;

public:
    bool cargarDesdeCSV(const std::string& archivo) {
        std::ifstream file(archivo);
        if (!file.is_open()) {
            std::cout << "Error al abrir el archivo: " << archivo << std::endl;
            return false;
        }

        std::string linea;
        // Saltar encabezado
        if (!std::getline(file, linea)) return false;

        std::vector<Producto> tmp;

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
            std::cout << "No se pudieron cargar productos del archivo." << std::endl;
            return false;
        }

        productos = std::move(tmp);
        construirEstructuras();
        std::cout << "Se cargaron " << productos.size() << " productos correctamente." << std::endl;
        return true;
    }

    void construirEstructuras() {
        productosPorCategoria.clear();
        productosPorPrecio.clear();
        categoriasUnicas.clear();

        for (auto& producto : productos) {
            // Estructura por categoría
            productosPorCategoria[producto.categoria].push_back(&producto);
            
            double precioRedondeado = round(producto.precio / 10.0) * 10.0;
            productosPorPrecio[precioRedondeado].push_back(&producto);
            
            // Conjunto de categorías únicas
            categoriasUnicas.insert(producto.categoria);
        }
    }

    void mostrarProductos() {
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

    void mostrarCategorias() {
        std::cout << "\nCategorias disponibles:" << std::endl;
        for (const auto& categoria : categoriasUnicas) {
            std::cout << "- " << categoria << std::endl;
        }
    }

    void buscarProductosPorRangoPrecio(double min, double max) {
        std::cout << "\nProductos en rango de precio $" << min << " - $" << max << ":" << std::endl;
        std::cout << std::left << std::setw(8)  << "SKU"
                  << std::setw(25) << "Nombre"
                  << std::setw(15) << "Categoria"
                  << std::setw(8)  << "Precio" << std::endl;
        std::cout << std::string(60, '-') << std::endl;

        for (const auto& producto : productos) {
            if (producto.precio >= min && producto.precio <= max) {
                std::cout << std::left << std::setw(8)  << producto.sku
                          << std::setw(25) << producto.nombre
                          << std::setw(15) << producto.categoria
                          << std::setw(8)  << producto.precio << std::endl;
            }
        }
    }

    // Algoritmos de ordenamiento
    void ordenarPorNombre() {
        const size_t n = productos.size();
        for (size_t i = 0; i + 1 < n; ++i) {
            size_t minIdx = i;
            for (size_t j = i + 1; j < n; ++j) {
                if (productos[j].nombre < productos[minIdx].nombre) {
                    minIdx = j;
                }
            }
            if (minIdx != i) std::swap(productos[i], productos[minIdx]);
        }
        construirEstructuras();
    }

    void ordenarPorPrecio() {
        std::sort(productos.begin(), productos.end(),
                  [](const Producto& a, const Producto& b) {
                      return a.precio < b.precio;
                  });
        construirEstructuras();
    }

    void ordenarPorStock() {
        std::sort(productos.begin(), productos.end(),
                  [](const Producto& a, const Producto& b) {
                      return a.cantidad < b.cantidad;
                  });
        construirEstructuras();
    }

    void ordenarPorCaducidad() {
        std::sort(productos.begin(), productos.end(),
                  [](const Producto& a, const Producto& b) {
                      return a.fechaCaducidad < b.fechaCaducidad;
                  });
        construirEstructuras();
    }

    bool guardarEnCSV(const std::string& archivo) {
        std::ofstream file(archivo);
        if (!file.is_open()) {
            std::cout << "Error al crear el archivo: " << archivo << std::endl;
            return false;
        }

        // Escribir encabezado
        file << "sku,nombre,categoria,precio,stock,caducidad\n";
        
        // Escribir productos
        for (const auto& p : productos) {
            file << p.sku << ","
                 << p.nombre << ","
                 << p.categoria << ","
                 << std::fixed << std::setprecision(2) << p.precio << ","
                 << p.cantidad << ","
                 << p.fechaCaducidad << "\n";
        }

        file.close();
        std::cout << "Inventario guardado en " << archivo << " correctamente." << std::endl;
        return true;
    }
};

#endif