#include "red.h"
#include <iostream>

using namespace std;

// Constructor por defecto
Red::Red() {}

// Agrega un nuevo enrutador a la red con el nombre dado
// Si ya existe, no hace nada
void Red::agregarEnrutador(const string &nombre) {
    if (enrutadores.find(nombre) == enrutadores.end()) {
        enrutadores[nombre] = Enrutador(nombre);
    }
}

// Remueve un enrutador de la red y todos sus enlaces asociados
void Red::removerEnrutador(const string &nombre) {
    // Eliminar el enrutador del mapa
    enrutadores.erase(nombre);
    // Eliminar su tabla de enrutamiento
    tablasEnrutamiento.erase(nombre);
    // Eliminar enlaces que apunten hacia él desde otros enrutadores
    for (auto &par : enrutadores) {
        par.second.eliminarEnlace(nombre);
    }
}

// Agrega un enlace bidireccional entre origen y destino con el costo dado
// Si alguno de los enrutadores no existe, muestra un error
void Red::agregarEnlace(const string &origen, const string &destino, int costo) {
    if (enrutadores.find(origen) == enrutadores.end()) {
        cout << "Error: enrutador '" << origen << "' no existe." << endl;
        return;
    }
    if (enrutadores.find(destino) == enrutadores.end()) {
        cout << "Error: enrutador '" << destino << "' no existe." << endl;
        return;
    }
    enrutadores[origen].agregarEnlace(destino, costo);
    enrutadores[destino].agregarEnlace(origen, costo);
}

// Elimina el enlace bidireccional entre origen y destino
void Red::eliminarEnlace(const string &origen, const string &destino) {
    if (enrutadores.find(origen) != enrutadores.end()) {
        enrutadores[origen].eliminarEnlace(destino);
    }
    if (enrutadores.find(destino) != enrutadores.end()) {
        enrutadores[destino].eliminarEnlace(origen);
    }
}

// Actualiza el costo del enlace bidireccional entre origen y destino
void Red::actualizarCosto(const string &origen, const string &destino, int nuevoCosto) {
    if (enrutadores.find(origen) != enrutadores.end()) {
        enrutadores[origen].actualizarCosto(destino, nuevoCosto);
    }
    if (enrutadores.find(destino) != enrutadores.end()) {
        enrutadores[destino].actualizarCosto(origen, nuevoCosto);
    }
}

// Retorna el costo mínimo almacenado en la tabla de enrutamiento de origen hacia destino
// Retorna -1 si no existe camino o si algún enrutador no existe
int Red::obtenerCosto(const string &origen, const string &destino) {
    if (tablasEnrutamiento.find(origen) == tablasEnrutamiento.end()) {
        return -1;
    }
    auto &tabla = tablasEnrutamiento[origen];
    if (tabla.find(destino) == tabla.end()) {
        return -1;
    }
    return tabla[destino];
}
