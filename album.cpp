#include "Album.h"

Album::Album() : codigo(0), duracion(0), cantidadGeneros(0) {}
Album::Album(int c, const string& n, const string& f, int d, const string& p)
    : codigo(c), nombre(n), fechaLanzamiento(f), duracion(d), portada(p), cantidadGeneros(0) {}
Album::Album(const Album& o) : codigo(o.codigo), nombre(o.nombre), fechaLanzamiento(o.fechaLanzamiento),
    duracion(o.duracion), cantidadGeneros(o.cantidadGeneros), portada(o.portada) {
    for (int i = 0; i < cantidadGeneros; ++i) generos[i] = o.generos[i];
    for (int i = 0; i < o.canciones.obtenerTamano(); ++i) canciones.agregar(*o.canciones.obtener(i));
}

int Album::getCodigo() const { return codigo; }
string Album::getNombre() const { return nombre; }
string Album::getFechaLanzamiento() const { return fechaLanzamiento; }
int Album::getDuracion() const { return duracion; }
string Album::getPortada() const { return portada; }
int Album::getCantidadGeneros() const { return cantidadGeneros; }
Genero Album::getGenero(int i) const { return (i >= 0 && i < cantidadGeneros) ? generos[i] : POP; }

void Album::setCodigo(int c){ codigo=c; }
void Album::setNombre(const string& n){ nombre=n; }
void Album::setFechaLanzamiento(const string& f){ fechaLanzamiento=f; }
void Album::setDuracion(int d){ duracion=d; }
void Album::setPortada(const string& p){ portada=p; }

bool Album::agregarGenero(Genero g) {
    if (cantidadGeneros < 4) { generos[cantidadGeneros++] = g; return true; }
    return false;
}

void Album::agregarCancion(int id) { canciones.agregar(id); }
bool Album::eliminarCancion(int id) { return canciones.eliminar(id); }
bool Album::tieneCancion(int id) const { return canciones.buscar(id); }
int  Album::getCantidadCanciones() const { return canciones.obtenerTamano(); }
int  Album::getCancion(int idx) const { int* p = canciones.obtener(idx); return p ? *p : -1; }

bool Album::operator==(const Album& o) const { return codigo == o.codigo; }
bool Album::operator!=(const Album& o) const { return !(*this == o); }

ostream& operator<<(ostream& os, const Album& a) {
    os << "Album - Codigo: " << a.getCodigo() << ", Nombre: " << a.getNombre()
    << ", Fecha: " << a.getFechaLanzamiento() << ", Duracion: " << a.getDuracion()
    << " min, Canciones: " << a.getCantidadCanciones();
    return os;
}



