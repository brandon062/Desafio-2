#include "Artista.h"

Artista::Artista() : codigo(0), edad(0) {}
Artista::Artista(int c, int e, const string& p) : codigo(c), edad(e), pais(p) {}
Artista::Artista(const Artista& otro) : codigo(otro.codigo), edad(otro.edad), pais(otro.pais) {}

int Artista::getCodigo() const { return codigo; }
int Artista::getEdad() const { return edad; }
string Artista::getPais() const { return pais; }
void Artista::setCodigo(int c) { codigo = c; }
void Artista::setEdad(int e) { edad = e; }
void Artista::setPais(const string& p) { pais = p; }

bool Artista::operator==(const Artista& otro) const { return codigo == otro.codigo; }
bool Artista::operator!=(const Artista& otro) const { return !(*this == otro); }

ostream& operator<<(ostream& os, const Artista& a) {
    os << "Artista - Codigo: " << a.getCodigo() << ", Edad: " << a.getEdad()
    << ", Pais: " << a.getPais();
    return os;
}



