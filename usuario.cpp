#include "Usuario.h"

Usuario::Usuario() : tipoMembresia(ESTANDAR) {}

Usuario::Usuario(const string& nick, TipoMembresia t, const string& ciu,
                 const string& pa, const string& fecha)
    : nickname(nick), tipoMembresia(t), ciudad(ciu), pais(pa), fechaInscripcion(fecha) {}

Usuario::Usuario(const Usuario& o)
    : nickname(o.nickname), tipoMembresia(o.tipoMembresia), ciudad(o.ciudad),
    pais(o.pais), fechaInscripcion(o.fechaInscripcion), listaFavoritos(o.listaFavoritos) {}

string Usuario::getNickname() const { return nickname; }
TipoMembresia Usuario::getTipoMembresia() const { return tipoMembresia; }
string Usuario::getCiudad() const { return ciudad; }
string Usuario::getPais() const { return pais; }
string Usuario::getFechaInscripcion() const { return fechaInscripcion; }
ListaFavoritos& Usuario::getListaFavoritos() { return listaFavoritos; }
const ListaFavoritos& Usuario::getListaFavoritos() const { return listaFavoritos; }

void Usuario::setNickname(const string& s){ nickname=s; }
void Usuario::setTipoMembresia(TipoMembresia t){ tipoMembresia=t; }
void Usuario::setCiudad(const string& s){ ciudad=s; }
void Usuario::setPais(const string& s){ pais=s; }
void Usuario::setFechaInscripcion(const string& s){ fechaInscripcion=s; }

bool Usuario::esPremium() const { return tipoMembresia == PREMIUM; }
bool Usuario::esEstandar() const { return tipoMembresia == ESTANDAR; }

bool Usuario::agregarAFavoritos(int id){ return esPremium() ? listaFavoritos.agregarCancion(id) : false; }
bool Usuario::eliminarDeFavoritos(int id){ return esPremium() ? listaFavoritos.eliminarCancion(id) : false; }
bool Usuario::tieneEnFavoritos(int id) const { return esPremium() ? listaFavoritos.tieneCancion(id) : false; }

bool Usuario::seguirListaFavoritos(const Usuario& otro){
    if (esPremium() && otro.esPremium()) { listaFavoritos.agregarLista(otro.getListaFavoritos()); return true; }
    return false;
}

bool Usuario::operator==(const Usuario& o) const { return nickname == o.nickname; }
bool Usuario::operator!=(const Usuario& o) const { return !(*this == o); }

Usuario& Usuario::operator=(const Usuario& o) {
    if (this != &o) {
        nickname=o.nickname; tipoMembresia=o.tipoMembresia; ciudad=o.ciudad; pais=o.pais;
        fechaInscripcion=o.fechaInscripcion; listaFavoritos=o.listaFavoritos;
    }
    return *this;
}

ostream& operator<<(ostream& os, const Usuario& u) {
    os << "Usuario - Nickname: " << u.getNickname()
    << ", Tipo: " << (u.getTipoMembresia()==PREMIUM ? "Premium" : "Estandar")
    << ", Ciudad: " << u.getCiudad() << ", Pais: " << u.getPais()
    << ", Fecha: " << u.getFechaInscripcion();
    if (u.esPremium()) os << ", Favoritos: " << u.getListaFavoritos().obtenerTamano();
    return os;
}


