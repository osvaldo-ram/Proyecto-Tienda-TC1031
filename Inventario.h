#ifndef INVENTARIO_H
#define INVENTARIO_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>

class Producto {
public:
    std::string sku;
    std::string nombre;
    std::string categoria;
    int cantidad;
    double precio;
    std::string fechaCaducidad;

    Producto(std::string _sku, std::string _nombre, std::string _categoria,
             double _precio, int _cantidad, std::string _fechaCaducidad)
        : sku(_sku), nombre(_nombre), categoria(_categoria),
          precio(_precio), cantidad(_cantidad), fechaCaducidad(_fechaCaducidad) {}
};

class Inventario {
private:
    std::vector<Producto> productos;

public:
    bool cargarDesdeCSV(const std::string& archivo) {
        std::ifstream file(archivo);
        if (!file.is_open()) {
            std::cout << "Error al abrir el archivo: " << archivo << std::endl;
            return false;
        }

        std::string linea;

        // Saltar encabezado: sku,nombre,categoria,precio,stock,caducidad
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
                double precio = std::stod(precioStr); // columna 4
                int    cantidad = std::stoi(stockStr); // columna 5
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
        std::cout << "Se cargaron " << productos.size() << " productos correctamente." << std::endl;
        return true;
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

    // Selection Sort por nombre (ascendente)
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
    }

    // std::sort por precio (ascendente)
    void ordenarPorPrecio() {
        std::sort(productos.begin(), productos.end(),
                  [](const Producto& a, const Producto& b) {
                      return a.precio < b.precio;
                  });
    }

    // std::sort por stock (ascendente)
    void ordenarPorStock() {
        std::sort(productos.begin(), productos.end(),
                  [](const Producto& a, const Producto& b) {
                      return a.cantidad < b.cantidad;
                  });
    }

    // std::sort por fecha ISO (ascendente: proximas a vencer primero)
    void ordenarPorCaducidad() {
        std::sort(productos.begin(), productos.end(),
                  [](const Producto& a, const Producto& b) {
                      return a.fechaCaducidad < b.fechaCaducidad;
                  });
    }
};

#endif
