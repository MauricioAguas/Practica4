#ifndef ENRUTADOR_H
#define ENRUTADOR_H

#include <string>

// agregar librerias faltantes...

using namespace std;

// Clase para modelar un Enrutador
class Enrutador
{
private:
    string nombre;
    // Elegir contenedor adecuado para guardar
    // enlaces directos a otros enrutadores y su costo
    ... enlaces;

public:
    // Constructores y destructor
    Enrutador()
        : nombre("")
    {}              // Constructor por defecto
    ~Enrutador() {} // Destructor

    // Getters
    const string &getNombre() const { return nombre; } // Getter para el nombre
    const... &getEnlaces() const { return enlaces; }   // Getter para los enlaces

    // Métodos de funcionamiento para gestionar los enlaces
    void agregarEnlace(const string &destino, int costo);
    void eliminarEnlace(const string &destino);
    void actualizarCosto(const string &destino, int costo);
};

#endif // ENRUTADOR_H
