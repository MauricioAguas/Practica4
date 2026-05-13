#include <iostream> // Inclusión de la biblioteca estándar de entrada y salida
#include "red.h"    // Inclusión del archivo de encabezado "red.h" que contiene la definición de la clase Red

// agregar librerias faltantes...

using namespace std; // Uso del espacio de nombres estándar para evitar prefijos "std::"

// Menú de usuario
int main()
{
    Red red;    // Creación de una instancia de la clase Red
    int opcion; // Variable para almacenar la opción del usuario
    do          // Bucle para mostrar el menú hasta que el usuario decida salir
    {
        // Mostrar las opciones del menú
        cout << "\n--- MENU RED DE ENRUTADORES ---\n";
        cout << "1. Agregar enrutador\n";
        cout << "2. Remover enrutador\n";
        cout << "3. Agregar enlace\n";
        cout << "4. Eliminar enlace\n";
        cout << "5. Actualizar costo de enlace\n";
        cout << "6. Cargar topologia desde archivo\n";
        cout << "7. Mostrar tabla de enrutamiento\n";
        cout << "8. Obtener costo entre dos enrutadores\n";
        cout << "9. Obtener camino eficiente entre dos enrutadores\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        // Variables para almacenar datos de entrada del usuario
        string nombre, origen, destino, archivo;
        int costo;

        // Procesar la opción seleccionada por el usuario
        switch (opcion)
        {
        case 1: // Agregar enrutador
            // agregar lógica faltante...
            break;
        case 2: // Remover enrutador
            // agregar lógica faltante...
            break;
        case 3: // Agregar enlace
            // agregar lógica faltante...
            break;
        case 4: // Eliminar enlace
            // agregar lógica faltante...
            break;
        case 5: // Actualizar costo de enlace
            // agregar lógica faltante...
            break;
        case 6: // Cargar topología desde archivo
            // agregar lógica faltante...
            break;
        case 7: // Mostrar tabla de enrutamiento
            // agregar lógica faltante...
            break;
        case 8: // Obtener costo entre dos enrutadores
            // agregar lógica faltante...
            break;
        case 9: // Obtener camino eficiente entre dos enrutadores
            // agregar lógica faltante...
            break;
        case 0: // Salir
            cout << "Saliendo...\n";
            break;
        default: // Opción inválida
            cout << "Opcion inválida.\n";
            clearScreen();
        }
    } while (opcion != 0);

    return 0;
}
