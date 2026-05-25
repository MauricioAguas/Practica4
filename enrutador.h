#ifndef ENRUTADOR_H
#define ENRUTADOR_H

#include <string>
#include <map>

using namespace std;

// Clase para modelar un Enrutador
class Enrutador
{
private:
    string nombre;
    // map<destino, costo> para guardar enlaces directos a otros enrutadores
    map<string, int> enlaces;

public:
    // Constructores y destructor
    Enrutador()
        : nombre("")
    {}              // Constructor por defecto
    Enrutador(const string &nombre)
        : nombre(nombre)
    {}              // Constructor con nombre
    ~Enrutador() {} // Destructor

    // Getters
    const string &getNombre() const { return nombre; }          // Getter para el nombre
    const map<string, int> &getEnlaces() const { return enlaces; } // Getter para los enlaces

    // Métodos de funcionamiento para gestionar los enlaces
    void agregarEnlace(const string &destino, int costo);
    void eliminarEnlace(const string &destino);
    void actualizarCosto(const string &destino, int costo);
};

#endif // ENRUTADOR_H
