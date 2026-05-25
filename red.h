#ifndef RED_H
#define RED_H

#include "enrutador.h"
#include <map>
#include <list>
#include <string>

using namespace std;

// Clase para modelar la Red
class Red
{
private:
    // map<nombre, Enrutador> para guardar todos los enrutadores de la red
    map<string, Enrutador> enrutadores;
    // map<origen, map<destino, costo>> para guardar las tablas de enrutamiento de cada enrutador
    map<string, map<string, int>> tablasEnrutamiento;

public:
    // Constructores y destructor
    Red() {}  // Constructor por defecto
    ~Red() {} // Destructor

    // Agregar un enrutador a la red
    void agregarEnrutador(const string &nombre);

    // Remover un enrutador de la red
    void removerEnrutador(const string &nombre);

    // Agregar un enlace entre dos enrutadores
    void agregarEnlace(const string &origen, const string &destino, int costo);

    // Eliminar un enlace entre dos enrutadores
    void eliminarEnlace(const string &origen, const string &destino);

    // Actualizar el costo de un enlace
    void actualizarCosto(const string &origen, const string &destino, int nuevoCosto);

    // Cargar la topología desde un archivo
    void cargarDesdeArchivo(const string &nombreArchivo);

    // Algoritmo de Dijkstra para calcular rutas y costos
    void dijkstra(const string &origen);

    // Actualizar todas las tablas de enrutamiento
    void actualizarTablas();

    // Obtener el costo entre dos enrutadores
    int obtenerCosto(const string &origen, const string &destino);

    // Obtener el camino eficiente entre dos enrutadores como lista de nodos
    list<string> obtenerCamino(const string &origen, const string &destino);

    // Mostrar la tabla de enrutamiento para un enrutador específico
    void mostrarTablaEnrutamiento(const string &nombre);
};

#endif // RED_H
