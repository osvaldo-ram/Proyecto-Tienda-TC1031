#include "inventario.h"
#include <iostream>

int main() {
    Inventario inventario;

    std::cout << "Cargando inventario desde CSV..." << std::endl;
    if (!inventario.cargarDesdeCSV("inventario.csv")) {
        std::cout << "No se pudo cargar el inventario. Verifica que el archivo 'inventario.csv' exista. Tambien puede intentar meter ela rchivo .csv dentro de la carpeta output." << std::endl;
        return 1;
    }

    int opcion;
    do {
        std::cout << "\n SISTEMA DE INVENTARIO " << std::endl;
        std::cout << "1. Mostrar productos originales" << std::endl;
        std::cout << "2. Ordenar por nombre" << std::endl;
        std::cout << "3. Ordenar por precio" << std::endl;
        std::cout << "4. Ordenar por stock" << std::endl;
        std::cout << "5. Ordenar por fecha de caducidad" << std::endl;
        std::cout << "6. Salir" << std::endl;
        std::cout << "Selecciona una opcion: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                std::cout << "\n Inventario Original " << std::endl;
                inventario.mostrarProductos();
                break;
            case 2:
                inventario.ordenarPorNombre();
                std::cout << "\n Ordenado por Nombre " << std::endl;
                inventario.mostrarProductos();
                break;
            case 3:
                inventario.ordenarPorPrecio();
                std::cout << "\n Ordenado por Precio " << std::endl;
                inventario.mostrarProductos();
                break;
            case 4:
                inventario.ordenarPorStock();
                std::cout << "\n Ordenado por Stock " << std::endl;
                inventario.mostrarProductos();
                break;
            case 5:
                inventario.ordenarPorCaducidad();
                std::cout << "\n Ordenado por Caducidad " << std::endl;
                inventario.mostrarProductos();
                break;
            case 6:
                std::cout << "Saliendo del sistema..." << std::endl;
                break;
            default:
                std::cout << "Opcion no valida. Intenta de nuevo." << std::endl;
        }
    } while (opcion != 6);

    return 0;
}