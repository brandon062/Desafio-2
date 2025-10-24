#include "mensajePublicitario.h"

MensajePublicitario::MensajePublicitario() : categoria(CATEGORIA_C) {}
MensajePublicitario::MensajePublicitario(const string& c, CategoriaPublicidad cat) : contenido(c), categoria(cat) {}
MensajePublicitario::MensajePublicitario(const MensajePublicitario& o) : contenido(o.contenido), categoria(o.categoria) {}

string MensajePublicitario::getContenido() const { return contenido; }
CategoriaPublicidad MensajePublicitario::getCategoria() const { return categoria; }
void MensajePublicitario::setContenido(const string& c){ contenido=c; }
void MensajePublicitario::setCategoria(CategoriaPublicidad cat){ categoria=cat; }

int MensajePublicitario::getPrioridad() const {
    switch (categoria) { case CATEGORIA_C: return 1; case CATEGORIA_B: return 2; case CATEGORIA_AAA: return 3; }
    return 1;
}

bool MensajePublicitario::operator==(const MensajePublicitario& o) const {
    return contenido == o.contenido && categoria == o.categoria;
}
bool MensajePublicitario::operator!=(const MensajePublicitario& o) const { return !(*this == o); }

ostream& operator<<(ostream& os, const MensajePublicitario& m) {
    os << "Publicidad [" << m.getPrioridad() << "] - " << m.getContenido();
    return os;
}

