#include "udeaTunes.h"
#include <fstream>
#include <sstream>

// ================== CTOR / DTOR ==================
UdeATunes::UdeATunes()
    : usuarioActual(nullptr), reproduciendo(false), cancionActual(nullptr),
    modoRepetir(false), cancionesReproducidas(0), limiteReproduccion(5),
    contadorPublicidadEstandar(0), iteracionesTotales(0), gen(rd()) {}

UdeATunes::~UdeATunes() {
    // Las estructuras enlazadas liberan sus nodos en sus destructores
}

// ================== CARGA DE DATOS ==================
bool UdeATunes::cargarUsuarios(const string& archivo) {
    ifstream f(archivo);
    if (!f.is_open()) return false;
    string linea;
    while (getline(f, linea)) {
        istringstream iss(linea);
        string nick, tipo, ciudad, pais, fecha;
        if (iss >> nick >> tipo >> ciudad >> pais >> fecha) {
            TipoMembresia tm = (tipo == "premium" || tipo == "PREMIUM") ? PREMIUM : ESTANDAR;
            usuarios.agregar(Usuario(nick, tm, ciudad, pais, fecha));
            iteracionesTotales++;
        }
    }
    return true;
}

bool UdeATunes::cargarArtistas(const string& archivo) {
    ifstream f(archivo);
    if (!f.is_open()) return false;
    string linea;
    while (getline(f, linea)) {
        istringstream iss(linea);
        int codigo, edad; string pais;
        if (iss >> codigo >> edad >> pais) {
            artistas.agregar(Artista(codigo, edad, pais));
            iteracionesTotales++;
        }
    }
    return true;
}

bool UdeATunes::cargarAlbumes(const string& archivo) {
    ifstream f(archivo);
    if (!f.is_open()) return false;
    string linea;
    while (getline(f, linea)) {
        istringstream iss(linea);
        int codigo, duracion; string nombre, fecha, portada;
        if (iss >> codigo >> nombre >> fecha >> duracion >> portada) {
            albumes.agregar(Album(codigo, nombre, fecha, duracion, portada));
            iteracionesTotales++;
        }
    }
    return true;
}

bool UdeATunes::cargarCanciones(const string& archivo) {
    ifstream f(archivo);
    if (!f.is_open()) return false;
    string linea;
    while (getline(f, linea)) {
        istringstream iss(linea);
        int id, dur; string nombre, r128, r320;
        if (iss >> id >> nombre >> dur >> r128 >> r320) {
            canciones.agregar(Cancion(id, nombre, dur, r128, r320));
            iteracionesTotales++;
        }
    }
    return true;
}

bool UdeATunes::cargarMensajesPublicitarios(const string& archivo) {
    ifstream f(archivo);
    if (!f.is_open()) return false;
    string linea;
    while (getline(f, linea)) {
        if (linea.empty()) continue;
        size_t pos = linea.find(' ');
        if (pos == string::npos) continue;
        string cat = linea.substr(0, pos);
        string contenido = linea.substr(pos + 1);
        CategoriaPublicidad c;
        if      (cat == "C")   c = CATEGORIA_C;
        else if (cat == "B")   c = CATEGORIA_B;
        else if (cat == "AAA") c = CATEGORIA_AAA;
        else continue;
        mensajesPublicitarios.agregar(MensajePublicitario(contenido, c));
        iteracionesTotales++;
    }
    return true;
}

// ================== SESIÓN ==================
bool UdeATunes::iniciarSesion(const string& nickname) {
    for (int i = 0; i < usuarios.obtenerTamano(); ++i) {
        Usuario* u = usuarios.obtener(i);
        if (u && u->getNickname() == nickname) {
            usuarioActual = u;
            iteracionesTotales++;
            return true;
        }
        iteracionesTotales++;
    }
    return false;
}

void UdeATunes::cerrarSesion() {
    usuarioActual = nullptr;
    detenerReproduccion();
}

Usuario* UdeATunes::getUsuarioActual() const { return usuarioActual; }

// ================== REPRODUCCIÓN ==================
bool UdeATunes::iniciarReproduccionAleatoria() {
    if (!usuarioActual || canciones.estaVacia()) return false;
    uniform_int_distribution<> dis(0, canciones.obtenerTamano() - 1);
    int i = dis(gen);
    cancionActual = canciones.obtener(i);
    if (cancionActual) {
        reproduciendo = true;
        cancionActual->incrementarReproducciones();
        if (usuarioActual->esPremium())
            historialReproduccion.encolar(cancionActual->getIdentificador());
        iteracionesTotales++;
        return true;
    }
    return false;
}

bool UdeATunes::siguienteCancion() {
    if (!usuarioActual || !reproduciendo || cancionesReproducidas > getLimiteReproduccion())
        return false;

    if (modoRepetir && cancionActual) {
        cancionActual->incrementarReproducciones();
        iteracionesTotales++;
        return true;
    }

    uniform_int_distribution<> dis(0, canciones.obtenerTamano() - 1);
    cancionActual = canciones.obtener(dis(gen));
    if (cancionActual) {
        cancionActual->incrementarReproducciones();
        if (usuarioActual->esPremium())
            historialReproduccion.encolar(cancionActual->getIdentificador());
        iteracionesTotales++;
        return true;
    }
    return false;
}

bool UdeATunes::cancionAnterior() {
    if (!usuarioActual || !usuarioActual->esPremium() || historialReproduccion.estaVacia())
        return false;

    int* id = historialReproduccion.obtenerFrente();
    if (!id) return false;

    for (int i = 0; i < canciones.obtenerTamano(); ++i) {
        Cancion* c = canciones.obtener(i);
        if (c && c->getIdentificador() == *id) {
            cancionActual = c;
            historialReproduccion.desencolar();
            iteracionesTotales++;
            return true;
        }
        iteracionesTotales++;
    }
    return false;
}

void UdeATunes::detenerReproduccion() {
    reproduciendo = false;
    cancionActual = nullptr;
    modoRepetir = false;
    cancionesReproducidas = 0;
    contadorPublicidadEstandar = 0;
    while (!historialReproduccion.estaVacia()) historialReproduccion.desencolar();
}

void UdeATunes::alternarRepetir() {
    if (usuarioActual && usuarioActual->esPremium())
        modoRepetir = !modoRepetir;
}

bool UdeATunes::estaReproduciendo() const { return reproduciendo; }
Cancion* UdeATunes::getCancionActual() const { return cancionActual; }
bool UdeATunes::getModoRepetir() const { return modoRepetir; }
int  UdeATunes::getCancionesReproducidas() const { return cancionesReproducidas; }
void UdeATunes::incrementarCancionesReproducidas() { ++cancionesReproducidas; }
int  UdeATunes::getLimiteReproduccion() const {
    return (usuarioActual && usuarioActual->esEstandar()) ? 5 : limiteReproduccion;
}
int  UdeATunes::getContadorPublicidadEstandar() const { return contadorPublicidadEstandar; }
void UdeATunes::incrementarContadorPublicidadEstandar() { ++contadorPublicidadEstandar; }
void UdeATunes::resetearContadorPublicidadEstandar() { contadorPublicidadEstandar = 0; }

// ================== FAVORITOS ==================
bool UdeATunes::agregarAFavoritos(int idCancion) {
    if (!usuarioActual || !usuarioActual->esPremium()) return false;

    bool existe = false;
    for (int i = 0; i < canciones.obtenerTamano(); ++i) {
        Cancion* c = canciones.obtener(i);
        if (c && c->getIdentificador() == idCancion) { existe = true; break; }
        iteracionesTotales++;
    }
    if (existe) {
        iteracionesTotales++;
        return usuarioActual->agregarAFavoritos(idCancion);
    }
    return false;
}

bool UdeATunes::eliminarDeFavoritos(int idCancion) {
    if (!usuarioActual || !usuarioActual->esPremium()) return false;
    iteracionesTotales++;
    return usuarioActual->eliminarDeFavoritos(idCancion);
}

bool UdeATunes::seguirListaFavoritos(const string& nicknameUsuario) {
    if (!usuarioActual || !usuarioActual->esPremium()) return false;
    for (int i = 0; i < usuarios.obtenerTamano(); ++i) {
        Usuario* u = usuarios.obtener(i);
        if (u && u->getNickname() == nicknameUsuario) {
            iteracionesTotales++;
            return usuarioActual->seguirListaFavoritos(*u);
        }
        iteracionesTotales++;
    }
    return false;
}

// ================== PUBLICIDAD ==================
MensajePublicitario* UdeATunes::obtenerMensajePublicitario() {
    if (mensajesPublicitarios.estaVacia()) return nullptr;

    // “Ruleta” ponderada por prioridad (1,2,3)
    ListaEnlazada<int> indices;
    for (int i = 0; i < mensajesPublicitarios.obtenerTamano(); ++i) {
        MensajePublicitario* m = mensajesPublicitarios.obtener(i);
        if (m) {
            for (int w = 0; w < m->getPrioridad(); ++w) indices.agregar(i);
        }
        iteracionesTotales++;
    }
    if (indices.estaVacia()) return nullptr;

    uniform_int_distribution<> dis(0, indices.obtenerTamano() - 1);
    int* idx = indices.obtener(dis(gen));
    iteracionesTotales++;
    return idx ? mensajesPublicitarios.obtener(*idx) : nullptr;
}

// ================== BÚSQUEDA ==================
Cancion* UdeATunes::buscarCancion(int idCancion) {
    for (int i = 0; i < canciones.obtenerTamano(); ++i) {
        Cancion* c = canciones.obtener(i);
        if (c && c->getIdentificador() == idCancion) {
            iteracionesTotales++;
            return c;
        }
        iteracionesTotales++;
    }
    return nullptr;
}

Album* UdeATunes::buscarAlbum(int codigoAlbum) {
    for (int i = 0; i < albumes.obtenerTamano(); ++i) {
        Album* a = albumes.obtener(i);
        if (a && a->getCodigo() == codigoAlbum) {
            iteracionesTotales++;
            return a;
        }
        iteracionesTotales++;
    }
    return nullptr;
}

Artista* UdeATunes::buscarArtista(int codigoArtista) {
    for (int i = 0; i < artistas.obtenerTamano(); ++i) {
        Artista* a = artistas.obtener(i);
        if (a && a->getCodigo() == codigoArtista) {
            iteracionesTotales++;
            return a;
        }
        iteracionesTotales++;
    }
    return nullptr;
}

// ================== MÉTRICAS / INFO ==================
int UdeATunes::getIteracionesTotales() const { return iteracionesTotales; }
void UdeATunes::resetearIteraciones() { iteracionesTotales = 0; }

int UdeATunes::calcularMemoria() const {
    int m = 0;
    m += usuarios.obtenerTamano() * sizeof(Usuario);
    m += artistas.obtenerTamano() * sizeof(Artista);
    m += albumes .obtenerTamano() * sizeof(Album);
    m += canciones.obtenerTamano() * sizeof(Cancion);
    m += mensajesPublicitarios.obtenerTamano() * sizeof(MensajePublicitario);
    m += sizeof(UdeATunes);
    return m;
}

int UdeATunes::getCantidadUsuarios() const { return usuarios.obtenerTamano(); }
int UdeATunes::getCantidadArtistas() const { return artistas.obtenerTamano(); }
int UdeATunes::getCantidadAlbumes() const { return albumes.obtenerTamano(); }
int UdeATunes::getCantidadCanciones() const { return canciones.obtenerTamano(); }
int UdeATunes::getCantidadMensajesPublicitarios() const { return mensajesPublicitarios.obtenerTamano(); }

