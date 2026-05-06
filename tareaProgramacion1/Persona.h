#pragma once
#include <string>
using namespace std;

class Persona {
protected:
    string nombres;
    string apellidos;
    string direccion;
    string fecha_nacimiento;
    int telefono;
    int id_tipo_sangre;

public:
    Persona();
    Persona(string nom, string ape, string dir, int tel, string fecha, int tipo_sangre);

    void setNombres(string nom);
    void setApellidos(string ape);
    void setDireccion(string dir);
    void setTelefono(int tel);
    void setFechaNacimiento(string fecha);
    void setIdTipoSangre(int tipo_sangre);

    string getNombres();
    string getApellidos();
    string getDireccion();
    int getTelefono();
    string getFechaNacimiento();
    int getIdTipoSangre();
};