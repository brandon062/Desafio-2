#ifndef UDEATUNES_H
#define UDEATUNES_H

#include "Usuario.h"
#include "Artista.h"
#include "Album.h"
#include "Cancion.h"
#include "mensajePublicitario.h"
#include "estructuras.h"
#include <chrono>
#include <random>

class UdeATunes {
private:
    ListaEnlazada<Usuario> usuarios;
    ListaEnlazada<Artista> artistas;
    ListaEnlazada<Album> albumes;
    ListaEnlazada<Cancion> canciones;
    ListaEnlazada<MensajePublicitario> mensajesPublicitarios;

    Usuario* usuarioActual;
    bool reproduciendo;
    Cancion* cancionActual;
    Cola<int> historialReproduccion;
    Pila<int>  pilaAnterior; // (queda para futuras mejoras)
    bool modoRepetir;
    int  cancionesReproducidas;
    int  limiteReproduccion;
    int  contadorPublicidadEstandar;

    int  iteracionesTotales;

    random_device rd;
    mt19937 gen;

public:
    UdeATunes();
    ~UdeATunes();

    // Carga
    bool cargarUsuarios(const string& archivo);
    bool cargarArtistas(const string& archivo);
    bool cargarAlbumes(const string& archivo);
    bool cargarCanciones(const string& archivo);
    bool cargarMensajesPublicitarios(const string& archivo);

    // Sesión
    bool iniciarSesion(const string& nickname);
    void cerrarSesion();
    Usuario* getUsuarioActual() const;

    // Reproducción
    bool iniciarReproduccionAleatoria();
    bool siguienteCancion();
    bool cancionAnterior();
    void detenerReproduccion();
    void alternarRepetir();

    bool  estaReproduciendo() const;
    Cancion* getCancionActual() const;
    bool  getModoRepetir() const;
    int   getCancionesReproducidas() const;
    void  incrementarCancionesReproducidas();
    int   getLimiteReproduccion() const;
    int   getContadorPublicidadEstandar() const;
    void  incrementarContadorPublicidadEstandar();
    void  resetearContadorPublicidadEstandar();

    // Favoritos
    bool agregarAFavoritos(int idCancion);
    bool eliminarDeFavoritos(int idCancion);
    bool seguirListaFavoritos(const string& nicknameUsuario);

    // Publicidad
    MensajePublicitario* obtenerMensajePublicitario();

    // Búsquedas
    Cancion* buscarCancion(int idCancion);
    Album*   buscarAlbum(int codigoAlbum);
    Artista* buscarArtista(int codigoArtista);

    // Métricas
    int  getIteracionesTotales() const;
    void resetearIteraciones();
    int  calcularMemoria() const;

    // Info sistema
    int getCantidadUsuarios() const;
    int getCantidadArtistas() const;
    int getCantidadAlbumes() const;
    int getCantidadCanciones() const;
    int getCantidadMensajesPublicitarios() const;
};

#endif

