#pragma once
#include "Persona.h"
#include "ConexionBD.h"
#include <string>
using namespace std;

class Estudiante : public Persona {
private:
    int id_estudiante;
    string codigo;

public:
    Estudiante();
    Estudiante(string cod, string nom, string ape, string dir, int tel, string fecha, int tipo_sangre, int id);

    void setIdEstudiante(int id);
    void setCodigo(string cod);

    int getIdEstudiante();
    string getCodigo();

    void crear();
    void leer();
    void actualizar();
    void borrar();
    void buscarPorId(int id);
};