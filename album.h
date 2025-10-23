#ifndef ALBUM_H
#define ALBUM_H
#include <string>
#include <iostream>
#include "estructuras.h"

class Album {
private:
    int codigo;
    string nombre;
    string fechaLanzamiento;
    int duracion;
    Genero generos[4];
    int cantidadGeneros;
    string portada;
    ListaEnlazada<int> canciones;

public:
    Album();
    Album(int c, const string& n, const string& f, int d, const string& p);
    Album(const Album& otro);

    // getters
    int getCodigo() const;
    string getNombre() const;
    string getFechaLanzamiento() const;
    int getDuracion() const;
    string getPortada() const;
    int getCantidadGeneros() const;
    Genero getGenero(int indice) const;

    // setters
    void setCodigo(int c);
    void setNombre(const string& n);
    void setFechaLanzamiento(const string& f);
    void setDuracion(int d);
    void setPortada(const string& p);

    // géneros / canciones
    bool agregarGenero(Genero g);
    void agregarCancion(int idCancion);
    bool eliminarCancion(int idCancion);
    bool tieneCancion(int idCancion) const;
    int  getCantidadCanciones() const;
    int  getCancion(int indice) const;

    // operadores
    bool operator==(const Album& otro) const;
    bool operator!=(const Album& otro) const;
    friend ostream& operator<<(ostream& os, const Album& album);
};

#endif





