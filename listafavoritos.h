#ifndef LISTAFAVORITOS_H
#define LISTAFAVORITOS_H
#include "estructuras.h"

class ListaFavoritos {
private:
    ListaEnlazada<int> canciones;
    int capacidadMaxima;

public:
    ListaFavoritos();
    ListaFavoritos(const ListaFavoritos& otro);

    bool agregarCancion(int idCancion);
    bool eliminarCancion(int idCancion);
    bool tieneCancion(int idCancion) const;
    int  obtenerTamano() const;
    int  obtenerCancion(int indice) const;
    bool estaVacia() const;

    void agregarLista(const ListaFavoritos& otraLista);

    ListaFavoritos& operator=(const ListaFavoritos& otro);
    friend ostream& operator<<(ostream& os, const ListaFavoritos& lista);
};

#endif

