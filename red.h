#ifndef RED_H
#define RED_H

#include "enrutador.h"
#include <map>
#include <list>
#include <string>

// agregar librerias faltantes...

using namespace std;

// Clase para modelar la Red
class Red
{
private:
    // map<nombre, Enrutador> para guardar los enrutadores de la red
    map<string, Enrutador> enrutadores;
    // map<origen, map<destino, costo>> para guardar las tablas de enrutamiento de cada enrutador
    map<string, map<string, int>> tablasEnrutamiento;
    // map<origen, map<destino, list<string>>> para guardar los caminos completos entre enrutadores
    map<string, map<string, list<string>>> tablasCaminos;

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
    // Formato esperado: "enrutador <nombre>" o "enlace <origen> <destino> <costo>"
    void cargarDesdeArchivo(const string &nombreArchivo);

    // Algoritmo de Dijkstra para calcular rutas y costos desde un origen
    void dijkstra(const string &origen);

    // Actualizar todas las tablas de enrutamiento (ejecuta Dijkstra para cada nodo)
    void actualizarTablas();

    // Obtener el costo entre dos enrutadores (-1 si no hay camino)
    int obtenerCosto(const string &origen, const string &destino);

    // Obtener el camino eficiente entre dos enrutadores
    // Retorna una lista de nodos que conforman el camino más corto
    list<string> obtenerCamino(const string &origen, const string &destino);

    // Mostrar la tabla de enrutamiento para un enrutador específico
    void mostrarTablaEnrutamiento(const string &nombre);

    // Mostrar los vecinos directos y costos de un enrutador especifico
    void verEnrutador(const string &nombre);

    // Generar una red aleatoria con n enrutadores y enlaces aleatorios
    // El numero de enrutadores debe estar entre 2 y 25
    void redAleatoria(int n);
};

#endif // RED_H
