#include "listafavoritos.h"

ListaFavoritos::ListaFavoritos() : capacidadMaxima(10000) {}
ListaFavoritos::ListaFavoritos(const ListaFavoritos& o) : capacidadMaxima(o.capacidadMaxima) {
    for (int i = 0; i < o.canciones.obtenerTamano(); ++i) canciones.agregar(*o.canciones.obtener(i));
}

bool ListaFavoritos::agregarCancion(int id) {
    if (canciones.obtenerTamano() >= capacidadMaxima) return false;
    if (canciones.buscar(id)) return false;
    canciones.agregar(id); return true;
}
bool ListaFavoritos::eliminarCancion(int id) { return canciones.eliminar(id); }
bool ListaFavoritos::tieneCancion(int id) const { return canciones.buscar(id); }
int  ListaFavoritos::obtenerTamano() const { return canciones.obtenerTamano(); }
int  ListaFavoritos::obtenerCancion(int i) const { int* p = canciones.obtener(i); return p ? *p : -1; }
bool ListaFavoritos::estaVacia() const { return canciones.estaVacia(); }

void ListaFavoritos::agregarLista(const ListaFavoritos& otra) {
    for (int i = 0; i < otra.obtenerTamano(); ++i) {
        int id = otra.obtenerCancion(i);
        if (!canciones.buscar(id) && canciones.obtenerTamano() < capacidadMaxima) canciones.agregar(id);
    }
}

ListaFavoritos& ListaFavoritos::operator=(const ListaFavoritos& o) {
    if (this != &o) {
        // limpiar
        while (!canciones.estaVacia()) canciones.eliminar(*canciones.obtener(0));
        capacidadMaxima = o.capacidadMaxima;
        for (int i = 0; i < o.canciones.obtenerTamano(); ++i) canciones.agregar(*o.canciones.obtener(i));
    }
    return *this;
}

ostream& operator<<(ostream& os, const ListaFavoritos& l) {
    os << "Lista de Favoritos - Canciones: " << l.obtenerTamano() << "/" << 10000;
    return os;
}
