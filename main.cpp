#include "inventario.h"
#include <iostream>
#include <limits>

void limpiarBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    Inventario inventario;

    std::cout << "Cargando inventario desde CSV..." << std::endl;
    if (!inventario.cargarDesdeCSV("inventario.csv")) {
        std::cout << "No se pudo cargar el inventario. Verifica que el archivo 'inventario.csv' exista." << std::endl;
        return 1;
    }

    int opcion;
    do {
        std::cout << "\n=== SISTEMA DE INVENTARIO ===" << std::endl;
        std::cout << "1. Mostrar productos originales" << std::endl;
        std::cout << "2. Ordenar por nombre" << std::endl;
        std::cout << "3. Ordenar por precio" << std::endl;
        std::cout << "4. Ordenar por stock" << std::endl;
        std::cout << "5. Ordenar por fecha de caducidad" << std::endl;
        std::cout << "6. Mostrar productos por categoria" << std::endl;
        std::cout << "7. Buscar por rango de precio" << std::endl;
        std::cout << "8. Mostrar categorias disponibles" << std::endl;
        std::cout << "9. Guardar inventario en CSV" << std::endl;
        std::cout << "10. Salir" << std::endl;
        std::cout << "Selecciona una opcion: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                std::cout << "\n=== INVENTARIO ORIGINAL ===" << std::endl;
                inventario.mostrarProductos();
                break;
            case 2:
                inventario.ordenarPorNombre();
                std::cout << "\n=== ORDENADO POR NOMBRE ===" << std::endl;
                inventario.mostrarProductos();
                break;
            case 3:
                inventario.ordenarPorPrecio();
                std::cout << "\n=== ORDENADO POR PRECIO ===" << std::endl;
                inventario.mostrarProductos();
                break;
            case 4:
                inventario.ordenarPorStock();
                std::cout << "\n=== ORDENADO POR STOCK ===" << std::endl;
                inventario.mostrarProductos();
                break;
            case 5:
                inventario.ordenarPorCaducidad();
                std::cout << "\n=== ORDENADO POR CADUCIDAD ===" << std::endl;
                inventario.mostrarProductos();
                break;
            case 6: {
                std::string categoria;
                std::cout << "Ingresa la categoria: ";
                limpiarBuffer();
                std::getline(std::cin, categoria);
                inventario.mostrarProductosPorCategoria(categoria);
                break;
            }
            case 7: {
                double min, max;
                std::cout << "Precio minimo: ";
                std::cin >> min;
                std::cout << "Precio maximo: ";
                std::cin >> max;
                inventario.buscarProductosPorRangoPrecio(min, max);
                break;
            }
            case 8:
                inventario.mostrarCategorias();
                break;
            case 9:
                inventario.guardarEnCSV("inventario_actualizado.csv");
                break;
            case 10:
                std::cout << "Saliendo del sistema..." << std::endl;
                break;
            default:
                std::cout << "Opcion no valida. Intenta de nuevo." << std::endl;
                limpiarBuffer();
        }
    } while (opcion != 10);

    return 0;
}