#include "Cancion.h"

Cancion::Cancion() : identificador(0), duracion(0), reproducciones(0) {}
Cancion::Cancion(int id, const string& n, int d, const string& r128, const string& r320)
    : identificador(id), nombre(n), duracion(d), rutaAudio128(r128), rutaAudio320(r320), reproducciones(0) {}
Cancion::Cancion(const Cancion& o)
    : identificador(o.identificador), nombre(o.nombre), duracion(o.duracion),
    rutaAudio128(o.rutaAudio128), rutaAudio320(o.rutaAudio320), reproducciones(o.reproducciones) {}

int Cancion::getIdentificador() const { return identificador; }
string Cancion::getNombre() const { return nombre; }
int Cancion::getDuracion() const { return duracion; }
string Cancion::getRutaAudio128() const { return rutaAudio128; }
string Cancion::getRutaAudio320() const { return rutaAudio320; }
int Cancion::getReproducciones() const { return reproducciones; }

void Cancion::setIdentificador(int id){ identificador=id; }
void Cancion::setNombre(const string& n){ nombre=n; }
void Cancion::setDuracion(int d){ duracion=d; }
void Cancion::setRutaAudio128(const string& r){ rutaAudio128=r; }
void Cancion::setRutaAudio320(const string& r){ rutaAudio320=r; }

void Cancion::incrementarReproducciones(){ ++reproducciones; }

int Cancion::getCodigoArtista() const { return identificador / 10000; }
int Cancion::getCodigoAlbum() const   { return (identificador % 10000) / 100; }
int Cancion::getCodigoCancion() const { return identificador % 100; }

bool Cancion::operator==(const Cancion& o) const { return identificador == o.identificador; }
bool Cancion::operator!=(const Cancion& o) const { return !(*this == o); }

ostream& operator<<(ostream& os, const Cancion& c) {
    os << "Cancion - ID: " << c.getIdentificador() << ", Nombre: " << c.getNombre()
    << ", Duracion: " << c.getDuracion() << " seg, Reproducciones: " << c.getReproducciones();
    return os;
}





