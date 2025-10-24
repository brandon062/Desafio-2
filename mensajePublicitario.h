#ifndef MENSAJEPUBLICITARIO_H
#define MENSAJEPUBLICITARIO_H
#include <string>
#include <iostream>
#include "estructuras.h"

class MensajePublicitario {
private:
    string contenido;
    CategoriaPublicidad categoria;

public:
    MensajePublicitario();
    MensajePublicitario(const string& c, CategoriaPublicidad cat);
    MensajePublicitario(const MensajePublicitario& otro);

    string getContenido() const;
    CategoriaPublicidad getCategoria() const;
    void setContenido(const string& c);
    void setCategoria(CategoriaPublicidad cat);

    int getPrioridad() const;

    bool operator==(const MensajePublicitario& otro) const;
    bool operator!=(const MensajePublicitario& otro) const;
    friend ostream& operator<<(ostream& os, const MensajePublicitario& mensaje);
};

#endif




