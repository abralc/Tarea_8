#include "Persona.h"

Persona::Persona() {
    nombres = "";
    apellidos = "";
    direccion = "";
    fecha_nacimiento = "";
    telefono = 0;
    id_tipo_sangre = 0;
}

Persona::Persona(string nom, string ape, string dir, int tel, string fecha, int tipo_sangre) {
    nombres = nom;
    apellidos = ape;
    direccion = dir;
    telefono = tel;
    fecha_nacimiento = fecha;
    id_tipo_sangre = tipo_sangre;
}

void Persona::setNombres(string nom) {
    nombres = nom;
}

void Persona::setApellidos(string ape) {
    apellidos = ape;
}

void Persona::setDireccion(string dir) {
    direccion = dir;
}

void Persona::setTelefono(int tel) {
    telefono = tel;
}

void Persona::setFechaNacimiento(string fecha) {
    fecha_nacimiento = fecha;
}

void Persona::setIdTipoSangre(int tipo_sangre) {
    id_tipo_sangre = tipo_sangre;
}

string Persona::getNombres() {
    return nombres;
}

string Persona::getApellidos() {
    return apellidos;
}

string Persona::getDireccion() {
    return direccion;
}

int Persona::getTelefono() {
    return telefono;
}

string Persona::getFechaNacimiento() {
    return fecha_nacimiento;
}

int Persona::getIdTipoSangre() {
    return id_tipo_sangre;
}