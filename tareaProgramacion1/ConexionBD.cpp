#include "ConexionBD.h"
#include <iostream>

ConexionBD::ConexionBD() {
    conector = nullptr;
}

bool ConexionBD::abrir_conexion() {
    const char* servidor = "127.0.0.1";
    const char* usuario = "root";
    const char* password = "";
    const char* base_datos = "db_escuela";
    unsigned int puerto = 3306;

    conector = mysql_init(nullptr);

    if (conector == nullptr) {
        cout << "Error al iniciar la conexion." << endl;
        return false;
    }

    MYSQL* resultadoConexion = mysql_real_connect(
        conector,
        servidor,
        usuario,
        password,
        base_datos,
        puerto,
        nullptr,
        0
    );

    if (resultadoConexion == nullptr) {
        cout << "Error de conexion: " << mysql_error(conector) << endl;
        mysql_close(conector);
        conector = nullptr;
        return false;
    }

    mysql_set_character_set(conector, "utf8mb4");
    return true;
}

MYSQL* ConexionBD::getConector() {
    return conector;
}

void ConexionBD::cerrar_conexion() {
    if (conector != nullptr) {
        mysql_close(conector);
        conector = nullptr;
    }
}

string ConexionBD::escapar(string texto) {
    if (conector == nullptr) {
        return "";
    }

    char* buffer = new char[texto.length() * 2 + 1];

    unsigned long longitud = mysql_real_escape_string(
        conector,
        buffer,
        texto.c_str(),
        (unsigned long)texto.length()
    );

    string resultado(buffer, longitud);

    delete[] buffer;

    return resultado;
}

string ConexionBD::textoSQL(string texto) {
    return "'" + escapar(texto) + "'";
}

string ConexionBD::numeroSQL(int numero) {
    return to_string(numero);
}