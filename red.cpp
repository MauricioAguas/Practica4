#include "red.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <climits>

using namespace std;

// Nota: los nombres de enrutadores son sensibles a mayusculas y minusculas.
// 'A' y 'a' se tratan como enrutadores distintos.

// Agrega un nuevo enrutador a la red con el nombre dado
// Si ya existe, no hace nada
void Red::agregarEnrutador(const string &nombre) {
    if (enrutadores.find(nombre) == enrutadores.end()) {
        enrutadores[nombre] = Enrutador(nombre);
    }
}

// Remueve un enrutador de la red y todos sus enlaces asociados
// Si no existe, muestra un mensaje de error indicando sensibilidad a mayusculas
void Red::removerEnrutador(const string &nombre) {
    // Verificar que el enrutador existe antes de intentar eliminarlo
    if (enrutadores.find(nombre) == enrutadores.end()) {
        cout << "Error: enrutador '" << nombre << "' no existe. ";
        cout << "Recuerde que los nombres son sensibles a mayusculas ('A' != 'a')." << endl;
        return;
    }
    // Eliminar el enrutador del mapa
    enrutadores.erase(nombre);
    // Eliminar su tabla de enrutamiento y sus caminos
    tablasEnrutamiento.erase(nombre);
    tablasCaminos.erase(nombre);
    // Eliminar enlaces que apunten hacia el desde otros enrutadores
    for (auto &par : enrutadores) {
        par.second.eliminarEnlace(nombre);
    }
}

// Agrega un enlace bidireccional entre origen y destino con el costo dado
// Si alguno de los enrutadores no existe, muestra un error indicando sensibilidad a mayusculas
void Red::agregarEnlace(const string &origen, const string &destino, int costo) {
    if (enrutadores.find(origen) == enrutadores.end()) {
        cout << "Error: enrutador '" << origen << "' no existe. ";
        cout << "Recuerde que los nombres son sensibles a mayusculas ('A' != 'a')." << endl;
        return;
    }
    if (enrutadores.find(destino) == enrutadores.end()) {
        cout << "Error: enrutador '" << destino << "' no existe. ";
        cout << "Recuerde que los nombres son sensibles a mayusculas ('A' != 'a')." << endl;
        return;
    }
    enrutadores[origen].agregarEnlace(destino, costo);
    enrutadores[destino].agregarEnlace(origen, costo);
}

// Elimina el enlace bidireccional entre origen y destino
// Si alguno de los enrutadores no existe, muestra un error indicando sensibilidad a mayusculas
void Red::eliminarEnlace(const string &origen, const string &destino) {
    if (enrutadores.find(origen) == enrutadores.end()) {
        cout << "Error: enrutador '" << origen << "' no existe. ";
        cout << "Recuerde que los nombres son sensibles a mayusculas ('A' != 'a')." << endl;
        return;
    }
    if (enrutadores.find(destino) == enrutadores.end()) {
        cout << "Error: enrutador '" << destino << "' no existe. ";
        cout << "Recuerde que los nombres son sensibles a mayusculas ('A' != 'a')." << endl;
        return;
    }
    enrutadores[origen].eliminarEnlace(destino);
    enrutadores[destino].eliminarEnlace(origen);
}

// Actualiza el costo del enlace bidireccional entre origen y destino
// Si alguno de los enrutadores no existe, muestra un error indicando sensibilidad a mayusculas
void Red::actualizarCosto(const string &origen, const string &destino, int nuevoCosto) {
    if (enrutadores.find(origen) == enrutadores.end()) {
        cout << "Error: enrutador '" << origen << "' no existe. ";
        cout << "Recuerde que los nombres son sensibles a mayusculas ('A' != 'a')." << endl;
        return;
    }
    if (enrutadores.find(destino) == enrutadores.end()) {
        cout << "Error: enrutador '" << destino << "' no existe. ";
        cout << "Recuerde que los nombres son sensibles a mayusculas ('A' != 'a')." << endl;
        return;
    }
    enrutadores[origen].actualizarCosto(destino, nuevoCosto);
    enrutadores[destino].actualizarCosto(origen, nuevoCosto);
}

// Carga la topologia desde un archivo de texto
// Formato esperado:
//   enrutador <nombre>
//   enlace <origen> <destino> <costo>
// Las lineas que empiezan con '#' son comentarios y se ignoran
void Red::cargarDesdeArchivo(const string &nombreArchivo) {
    ifstream archivo(nombreArchivo);
    // Verificar que el archivo se pudo abrir
    if (!archivo.is_open()) {
        cout << "Error: no se pudo abrir el archivo '" << nombreArchivo << "'." << endl;
        return;
    }

    string linea;
    int numLinea = 0;
    while (getline(archivo, linea)) {
        numLinea++;
        // Ignorar lineas vacias y comentarios
        if (linea.empty() || linea[0] == '#') continue;

        istringstream ss(linea);
        string tipo;
        ss >> tipo;

        if (tipo == "enrutador") {
            // Leer y agregar el enrutador
            string nombre;
            if (ss >> nombre) {
                agregarEnrutador(nombre);
            } else {
                cout << "Advertencia: linea " << numLinea << " mal formada: '" << linea << "'" << endl;
            }
        } else if (tipo == "enlace") {
            // Leer y agregar el enlace entre dos enrutadores
            string origen, destino;
            int costo;
            if (ss >> origen >> destino >> costo) {
                agregarEnlace(origen, destino, costo);
            } else {
                cout << "Advertencia: linea " << numLinea << " mal formada: '" << linea << "'" << endl;
            }
        } else {
            cout << "Advertencia: linea " << numLinea << " desconocida: '" << linea << "'" << endl;
        }
    }

    archivo.close();
    // Recalcular todas las tablas luego de cargar la topologia
    actualizarTablas();
    cout << "Topologia cargada desde '" << nombreArchivo << "'. Tablas actualizadas." << endl;
}

// Algoritmo de Dijkstra: calcula el camino mas corto desde 'origen'
// hacia todos los demas enrutadores y actualiza tablasEnrutamiento y tablasCaminos
void Red::dijkstra(const string &origen) {
    // distancias: costo minimo desde origen hasta cada nodo (inicialmente infinito)
    map<string, int> distancias;
    // previo: nodo anterior en el camino mas corto para reconstruir rutas
    map<string, string> previo;
    // Cola de prioridad: (costo, nodo) ordenada de menor a mayor costo
    priority_queue<pair<int,string>, vector<pair<int,string>>, greater<pair<int,string>>> pq;

    // Inicializar todas las distancias en infinito
    for (auto &par : enrutadores) {
        distancias[par.first] = INT_MAX;
        previo[par.first] = "";
    }
    distancias[origen] = 0;
    pq.push({0, origen});

    while (!pq.empty()) {
        auto [costoActual, nodoActual] = pq.top();
        pq.pop();

        // Ignorar si ya encontramos un camino mejor para este nodo
        if (costoActual > distancias[nodoActual]) continue;

        // Revisar todos los vecinos del nodo actual
        for (auto &enlace : enrutadores[nodoActual].getEnlaces()) {
            string vecino = enlace.first;
            int peso = enlace.second;
            int nuevoCosto = distancias[nodoActual] + peso;

            // Actualizar si encontramos un camino mas corto
            if (nuevoCosto < distancias[vecino]) {
                distancias[vecino] = nuevoCosto;
                previo[vecino] = nodoActual;
                pq.push({nuevoCosto, vecino});
            }
        }
    }

    // Guardar las distancias calculadas en la tabla de enrutamiento del origen
    tablasEnrutamiento[origen] = distancias;

    // Reconstruir y guardar los caminos completos usando el mapa 'previo'
    for (auto &par : enrutadores) {
        string destino = par.first;
        if (destino == origen) continue;
        list<string> camino;
        string actual = destino;
        // Recorrer hacia atras desde el destino hasta el origen
        while (actual != "") {
            camino.push_front(actual);
            actual = previo[actual];
        }
        // Solo guardar si el camino es valido (empieza desde el origen)
        if (!camino.empty() && camino.front() == origen) {
            tablasCaminos[origen][destino] = camino;
        }
    }
}

// Ejecuta Dijkstra para todos los enrutadores de la red
void Red::actualizarTablas() {
    for (auto &par : enrutadores) {
        dijkstra(par.first);
    }
}

// Retorna el costo minimo de origen a destino
// Retorna -1 si no existe camino o si algun enrutador no existe
int Red::obtenerCosto(const string &origen, const string &destino) {
    if (tablasEnrutamiento.find(origen) == tablasEnrutamiento.end()) {
        return -1;
    }
    auto &tabla = tablasEnrutamiento[origen];
    if (tabla.find(destino) == tabla.end()) {
        return -1;
    }
    // Si el costo es INT_MAX, el nodo es inalcanzable
    int costo = tabla[destino];
    return (costo == INT_MAX) ? -1 : costo;
}

// Retorna el camino mas corto entre origen y destino como lista de nodos
// Retorna lista vacia si no hay camino
list<string> Red::obtenerCamino(const string &origen, const string &destino) {
    if (tablasCaminos.find(origen) == tablasCaminos.end()) return {};
    if (tablasCaminos[origen].find(destino) == tablasCaminos[origen].end()) return {};
    return tablasCaminos[origen][destino];
}

// Muestra la tabla de enrutamiento de un enrutador especifico
// Imprime destino, costo y camino completo para cada nodo alcanzable
void Red::mostrarTablaEnrutamiento(const string &nombre) {
    if (enrutadores.find(nombre) == enrutadores.end()) {
        cout << "Error: enrutador '" << nombre << "' no existe. ";
        cout << "Recuerde que los nombres son sensibles a mayusculas ('A' != 'a')." << endl;
        return;
    }
    if (tablasEnrutamiento.find(nombre) == tablasEnrutamiento.end()) {
        cout << "La tabla de '" << nombre << "' esta vacia. Ejecute actualizar tablas primero." << endl;
        return;
    }
    cout << "\nTabla de enrutamiento de '" << nombre << "':\n";
    cout << "Destino\t\tCosto\t\tCamino\n";
    cout << "-------\t\t-----\t\t------\n";
    for (auto &par : tablasEnrutamiento[nombre]) {
        string destino = par.first;
        int costo = par.second;
        if (destino == nombre) continue;
        cout << destino << "\t\t";
        // Si el costo es INT_MAX, el nodo es inalcanzable
        if (costo == INT_MAX)
            cout << "INF\t\tSin camino\n";
        else {
            cout << costo << "\t\t";
            // Imprimir el camino completo nodo por nodo
            list<string> camino = obtenerCamino(nombre, destino);
            for (const string &nodo : camino)
                cout << nodo << " ";
            cout << "\n";
        }
    }
}
