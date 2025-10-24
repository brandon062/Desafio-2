#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <random>
#include <chrono>

using namespace std;

// ===== ENUMERACIONES GLOBALES =====
enum TipoMembresia { ESTANDAR, PREMIUM };

enum Genero {
    POP, ROCK, JAZZ, MUSICA_CLASICA, ELECTRONICA,
    HIP_HOP, REGGAE, BLUES, LATINA
};

enum CategoriaPublicidad { CATEGORIA_C, CATEGORIA_B, CATEGORIA_AAA };

// ======== NODO GENÉRICO ========
template <typename T>
struct Nodo {
    T dato;
    Nodo<T>* siguiente;

    Nodo(const T& d) : dato(d), siguiente(nullptr) {}
};

// ======== LISTA ENLAZADA GENÉRICA ========
template <typename T>
class ListaEnlazada {
private:
    Nodo<T>* cabeza;
    int tamano;

public:
    ListaEnlazada() : cabeza(nullptr), tamano(0) {}
    ~ListaEnlazada() { limpiar(); }

    void agregar(const T& elemento) {
        Nodo<T>* nuevo = new Nodo<T>(elemento);
        if (!cabeza) {
            cabeza = nuevo;
        } else {
            Nodo<T>* actual = cabeza;
            while (actual->siguiente) actual = actual->siguiente;
            actual->siguiente = nuevo;
        }
        tamano++;
    }

    bool eliminar(const T& elemento) {
        if (!cabeza) return false;
        if (cabeza->dato == elemento) {
            Nodo<T>* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
            tamano--;
            return true;
        }
        Nodo<T>* actual = cabeza;
        while (actual->siguiente && !(actual->siguiente->dato == elemento)) {
            actual = actual->siguiente;
        }
        if (actual->siguiente) {
            Nodo<T>* temp = actual->siguiente;
            actual->siguiente = temp->siguiente;
            delete temp;
            tamano--;
            return true;
        }
        return false;
    }

    bool buscar(const T& elemento) const {
        Nodo<T>* actual = cabeza;
        while (actual) {
            if (actual->dato == elemento) return true;
            actual = actual->siguiente;
        }
        return false;
    }

    T* obtener(int indice) const {
        if (indice < 0 || indice >= tamano) return nullptr;
        Nodo<T>* actual = cabeza;
        for (int i = 0; i < indice; ++i) actual = actual->siguiente;
        return &(actual->dato);
    }

    bool estaVacia() const { return cabeza == nullptr; }
    int obtenerTamano() const { return tamano; }

    void limpiar() {
        Nodo<T>* actual = cabeza;
        while (actual) {
            Nodo<T>* temp = actual;
            actual = actual->siguiente;
            delete temp;
        }
        cabeza = nullptr;
        tamano = 0;
    }
};

// ======== COLA (FIFO) ========
template <typename T>
class Cola {
private:
    Nodo<T>* frente;
    Nodo<T>* final;
    int tamano;

public:
    Cola() : frente(nullptr), final(nullptr), tamano(0) {}
    ~Cola() { limpiar(); }

    void encolar(const T& elemento) {
        Nodo<T>* nuevo = new Nodo<T>(elemento);
        if (!final) {
            frente = final = nuevo;
        } else {
            final->siguiente = nuevo;
            final = nuevo;
        }
        tamano++;
    }

    bool desencolar() {
        if (!frente) return false;
        Nodo<T>* temp = frente;
        frente = frente->siguiente;
        if (!frente) final = nullptr;
        delete temp;
        tamano--;
        return true;
    }

    T* obtenerFrente() const {
        if (!frente) return nullptr;
        return &(frente->dato);
    }

    bool estaVacia() const { return frente == nullptr; }
    int obtenerTamano() const { return tamano; }

    void limpiar() {
        while (frente) desencolar();
    }
};

// ======== PILA (LIFO) ========
template <typename T>
class Pila {
private:
    Nodo<T>* tope;
    int tamano;

public:
    Pila() : tope(nullptr), tamano(0) {}
    ~Pila() { limpiar(); }

    void apilar(const T& elemento) {
        Nodo<T>* nuevo = new Nodo<T>(elemento);
        nuevo->siguiente = tope;
        tope = nuevo;
        tamano++;
    }

    bool desapilar() {
        if (!tope) return false;
        Nodo<T>* temp = tope;
        tope = tope->siguiente;
        delete temp;
        tamano--;
        return true;
    }

    T* obtenerTope() const {
        if (!tope) return nullptr;
        return &(tope->dato);
    }

    bool estaVacia() const { return tope == nullptr; }
    int obtenerTamano() const { return tamano; }

    void limpiar() {
        while (tope) desapilar();
    }
};

#endif

