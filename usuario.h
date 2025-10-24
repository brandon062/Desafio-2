#ifndef USUARIO_H
#define USUARIO_H
#include <string>
#include <iostream>
#include "estructuras.h"
#include "listafavoritos.h"

class Usuario {
private:
    string nickname;
    TipoMembresia tipoMembresia;
    string ciudad;
    string pais;
    string fechaInscripcion;
    ListaFavoritos listaFavoritos;

public:
    Usuario();
    Usuario(const string& nick, TipoMembresia tipo, const string& ciu,
            const string& pa, const string& fecha);
    Usuario(const Usuario& otro);

    // getters
    string getNickname() const;
    TipoMembresia getTipoMembresia() const;
    string getCiudad() const;
    string getPais() const;
    string getFechaInscripcion() const;
    ListaFavoritos& getListaFavoritos();
    const ListaFavoritos& getListaFavoritos() const;

    // setters
    void setNickname(const string& nick);
    void setTipoMembresia(TipoMembresia tipo);
    void setCiudad(const string& ciu);
    void setPais(const string& pa);
    void setFechaInscripcion(const string& fecha);

    // helpers
    bool esPremium() const;
    bool esEstandar() const;

    bool agregarAFavoritos(int idCancion);
    bool eliminarDeFavoritos(int idCancion);
    bool tieneEnFavoritos(int idCancion) const;
    bool seguirListaFavoritos(const Usuario& otroUsuario);

    // operadores
    bool operator==(const Usuario& otro) const;
    bool operator!=(const Usuario& otro) const;
    Usuario& operator=(const Usuario& otro);
    friend ostream& operator<<(ostream& os, const Usuario& usuario);
};

#endif




