#include <iostream> // Inclusión de la biblioteca estándar de entrada y salida
#include <list>     // Inclusión de la biblioteca list para representar caminos
#include "red.h"    // Inclusión del archivo de encabezado "red.h" que contiene la definición de la clase Red

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
            cout << "Nombre del enrutador: ";
            cin >> nombre;
            red.agregarEnrutador(nombre);
            // Recalcular tablas para incluir el nuevo enrutador
            red.actualizarTablas();
            cout << "Enrutador '" << nombre << "' agregado.\n";
            break;

        case 2: // Remover enrutador
            cout << "Nombre del enrutador a remover: ";
            cin >> nombre;
            red.removerEnrutador(nombre);
            // Recalcular tablas tras eliminar el enrutador
            red.actualizarTablas();
            cout << "Enrutador '" << nombre << "' removido.\n";
            break;

        case 3: // Agregar enlace
            cout << "Enrutador origen: ";
            cin >> origen;
            cout << "Enrutador destino: ";
            cin >> destino;
            cout << "Costo del enlace: ";
            cin >> costo;
            red.agregarEnlace(origen, destino, costo);
            // Recalcular tablas tras agregar el enlace
            red.actualizarTablas();
            break;

        case 4: // Eliminar enlace
            cout << "Enrutador origen: ";
            cin >> origen;
            cout << "Enrutador destino: ";
            cin >> destino;
            red.eliminarEnlace(origen, destino);
            // Recalcular tablas tras eliminar el enlace
            red.actualizarTablas();
            cout << "Enlace entre '" << origen << "' y '" << destino << "' eliminado.\n";
            break;

        case 5: // Actualizar costo de enlace
            cout << "Enrutador origen: ";
            cin >> origen;
            cout << "Enrutador destino: ";
            cin >> destino;
            cout << "Nuevo costo: ";
            cin >> costo;
            red.actualizarCosto(origen, destino, costo);
            // Recalcular tablas tras actualizar el costo del enlace
            red.actualizarTablas();
            cout << "Costo actualizado.\n";
            break;

        case 6: // Cargar topología desde archivo
            // cargarDesdeArchivo ya llama actualizarTablas() internamente
            cout << "Nombre del archivo: ";
            cin >> archivo;
            red.cargarDesdeArchivo(archivo);
            break;

        case 7: // Mostrar tabla de enrutamiento
            cout << "Nombre del enrutador: ";
            cin >> nombre;
            red.mostrarTablaEnrutamiento(nombre);
            break;

        case 8: // Obtener costo entre dos enrutadores
            cout << "Enrutador origen: ";
            cin >> origen;
            cout << "Enrutador destino: ";
            cin >> destino;
            costo = red.obtenerCosto(origen, destino);
            // Si el costo es -1, no hay camino entre los enrutadores
            if (costo == -1)
                cout << "No hay camino entre '" << origen << "' y '" << destino << "'.\n";
            else
                cout << "Costo de '" << origen << "' a '" << destino << "': " << costo << "\n";
            break;

        case 9: // Obtener camino eficiente entre dos enrutadores
            cout << "Enrutador origen: ";
            cin >> origen;
            cout << "Enrutador destino: ";
            cin >> destino;
            {
                // Obtener el camino como lista de nodos y mostrarlo
                list<string> camino = red.obtenerCamino(origen, destino);
                if (camino.empty()) {
                    cout << "No hay camino entre '" << origen << "' y '" << destino << "'.\n";
                } else {
                    cout << "Camino: ";
                    for (const string &nodo : camino)
                        cout << nodo << " ";
                    cout << "\n";
                }
            }
            break;

        case 0: // Salir
            cout << "Saliendo...\n";
            break;

        default: // Opción inválida
            cout << "Opcion invalida.\n";
        }
    } while (opcion != 0);

    return 0;
}
