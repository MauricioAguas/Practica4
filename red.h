#ifndef RED_H
#define RED_

#include "enrutador.h"

// agregar librerias faltantes...

// Clase para modelar la Red
class Red
{
private:
    // elegir contenedor adecuado para guardar los enrutadores de la red
    ... enrutadores;
    // elegir contenedor adecuado para guardar las tablas de enrutamiento de cada enrutador
    ... tablasEnrutamiento;

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

    // Obtener el camino eficiente entre dos enrutadores
    // debe aoperar con el mismo tipo de dato que se usó para guardar las rutas en las tablas de enrutamiento
    ... obtenerCamino(const string &origen, const string &destino);

    // Mostrar la tabla de enrutamiento para un enrutador específico
    void mostrarTablaEnrutamiento(const string &nombre);
};

#endif // RED_H
