#include "Inventario.h"
#include <iostream>
#include <limits>

//Limpia el buffer para no tener problemas con getline
void limpiarBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

//Menu principal
void mostrarMenu() {
    std::cout << "\n=== SISTEMA DE INVENTARIO ===" << std::endl;
    std::cout << "1. Mostrar todos los productos" << std::endl;
    std::cout << "2. Ordenar por nombre" << std::endl;
    std::cout << "3. Ordenar por precio" << std::endl;
    std::cout << "4. Ordenar por stock" << std::endl;
    std::cout << "5. Ordenar por fecha de caducidad" << std::endl;
    std::cout << "6. Mostrar productos por categoria" << std::endl;
    std::cout << "7. Buscar por rango de precio" << std::endl;
    std::cout << "8. Mostrar categorias disponibles" << std::endl;
    std::cout << "9. Agregar producto" << std::endl;
    std::cout << "10. Buscar producto por SKU (Stock Keeping Unit)" << std::endl;
    std::cout << "11. Actualizar producto" << std::endl;
    std::cout << "12. Eliminar producto" << std::endl;
    std::cout << "13. Guardar inventario en CSV" << std::endl;
    std::cout << "14. Salir" << std::endl;
    std::cout << "Selecciona una opcion: ";
}

//Lee los datos de los productos desde la consola
Producto leerProductoDesdeConsola() {
    Producto p;
    std::cout << "Ingrese SKU: ";
    std::getline(std::cin, p.sku);
    std::cout << "Ingrese nombre: ";
    std::getline(std::cin, p.nombre);
    std::cout << "Ingrese categoria: ";
    std::getline(std::cin, p.categoria);
    std::cout << "Ingrese precio: ";
    std::cin >> p.precio;
    std::cout << "Ingrese cantidad: ";
    std::cin >> p.cantidad;
    limpiarBuffer();
    std::cout << "Ingrese fecha de caducidad (YYYY-MM-DD): ";
    std::getline(std::cin, p.fechaCaducidad);
    return p;
}

//Funcion principal del programa
int main() {
    Inventario inventario;

    std::cout << "Cargando inventario desde CSV..." << std::endl;
    if (!inventario.cargarDesdeCSV("inventario.csv")) {
        std::cout << "No se pudo cargar el inventario. Verifica que el archivo 'inventario.csv' exista" << std::endl;
        return 1;
    }

    int opcion;
    do {
        mostrarMenu();
        std::cin >> opcion;
        limpiarBuffer();

        switch (opcion) {
            case 1:
                std::cout << "\n=== INVENTARIO COMPLETO ===" << std::endl;
                inventario.mostrarProductos();
                break;
            case 2:
                inventario.ordenarPorNombre();
                inventario.mostrarProductos();
                break;
            case 3:
                inventario.ordenarPorPrecio();
                inventario.mostrarProductos();
                break;
            case 4:
                inventario.ordenarPorStock();
                inventario.mostrarProductos();
                break;
            case 5:
                inventario.ordenarPorCaducidad();
                inventario.mostrarProductos();
                break;
            case 6: {
                std::string categoria;
                std::cout << "Ingresa la categoria: ";
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
                limpiarBuffer();
                inventario.buscarProductosPorRangoPrecio(min, max);
                break;
            }
            case 8:
                inventario.mostrarCategorias();
                break;
            case 9: {
                std::cout << "\n=== AGREGAR NUEVO PRODUCTO ===" << std::endl;
                Producto nuevoProducto = leerProductoDesdeConsola();
                inventario.agregarProducto(nuevoProducto);
                break;
            }
            case 10: {
                std::string sku;
                std::cout << "Ingrese SKU (A001...A100...) del producto a buscar: ";
                std::getline(std::cin, sku);
                Producto* producto = inventario.buscarProductoPorSKU(sku);
                if (producto != nullptr) {
                    std::cout << "\nProducto encontrado:" << std::endl;
                    std::cout << "SKU: " << producto->sku << std::endl;
                    std::cout << "Nombre: " << producto->nombre << std::endl;
                    std::cout << "Categoria: " << producto->categoria << std::endl;
                    std::cout << "Precio: " << producto->precio << std::endl;
                    std::cout << "Stock: " << producto->cantidad << std::endl;
                    std::cout << "Caducidad: " << producto->fechaCaducidad << std::endl;
                } else {
                    std::cout << "Producto con SKU " << sku << " no encontrado" << std::endl;
                }
                break;
            }
            case 11: {
                std::string sku;
                std::cout << "Ingrese SKU del producto a actualizar: ";
                std::getline(std::cin, sku);
                std::cout << "Ingrese los nuevos datos del producto:" << std::endl;
                Producto productoActualizado = leerProductoDesdeConsola();
                inventario.actualizarProducto(sku, productoActualizado);
                break;
            }
            case 12: {
                std::string sku;
                std::cout << "Ingrese SKU del producto a eliminar: ";
                std::getline(std::cin, sku);
                inventario.eliminarProducto(sku);
                break;
            }
            case 13:
                inventario.guardarEnCSV("inventario.csv"); 
                break;
            case 14:
                std::cout << "Saliendo del sistema..." << std::endl;
                break;
            default:
                std::cout << "Opcion no valida. Intenta de nuevo" << std::endl;
        }
    } while (opcion != 14);

    return 0;
}