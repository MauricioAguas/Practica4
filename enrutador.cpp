#include "enrutador.h"

// Agrega un enlace directo hacia 'destino' con el costo dado
// Si ya existe, actualiza el costo
void Enrutador::agregarEnlace(const string &destino, int costo) {
    enlaces[destino] = costo;
}

// Elimina el enlace directo hacia 'destino'
// Si no existe, no hace nada
void Enrutador::eliminarEnlace(const string &destino) {
    enlaces.erase(destino);
}

// Actualiza el costo del enlace hacia 'destino'
// Solo actualiza si el enlace ya existe
void Enrutador::actualizarCosto(const string &destino, int costo) {
    auto it = enlaces.find(destino);
    if (it != enlaces.end()) {
        it->second = costo;
    }
}
