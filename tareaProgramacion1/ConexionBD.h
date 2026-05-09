#pragma once
#include <mysql.h>
#include <string>
using namespace std;

class ConexionBD {
private:
    MYSQL* conector;

public:
    ConexionBD();
    bool abrir_conexion();
    MYSQL* getConector();
    void cerrar_conexion();

    string escapar(string texto);
    string textoSQL(string texto);
    string numeroSQL(int numero);
};;