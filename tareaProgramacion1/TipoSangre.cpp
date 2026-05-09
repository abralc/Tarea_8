#include "TipoSangre.h"
#include "ConexionBD.h"
#include <iostream>
#include <mysql.h>

using namespace std;

TipoSangre::TipoSangre() {
    id_tipo_sangre = 0;
    sangre = "";
}

TipoSangre::TipoSangre(int id, string tipo) {
    id_tipo_sangre = id;
    sangre = tipo;
}

void TipoSangre::setIdTipoSangre(int id) {
    id_tipo_sangre = id;
}

void TipoSangre::setSangre(string tipo) {
    sangre = tipo;
}

int TipoSangre::getIdTipoSangre() {
    return id_tipo_sangre;
}

string TipoSangre::getSangre() {
    return sangre;
}

void TipoSangre::crear() {
    ConexionBD cn;

    if (!cn.abrir_conexion()) {
        cout << "No se pudo conectar a la base de datos." << endl;
        return;
    }

    string consulta = "INSERT INTO tipos_sangre(sangre) VALUES('"
        + cn.escapar(sangre) + "')";

    int estado = mysql_query(cn.getConector(), consulta.c_str());

    if (estado == 0) {
        cout << "Tipo de sangre registrado correctamente." << endl;
    }
    else {
        cout << "Error al registrar tipo de sangre: " << mysql_error(cn.getConector()) << endl;
    }

    cn.cerrar_conexion();
}

void TipoSangre::leer() {
    ConexionBD cn;
    MYSQL_ROW fila;
    MYSQL_RES* resultado;

    if (!cn.abrir_conexion()) {
        cout << "No se pudo conectar a la base de datos." << endl;
        return;
    }

    string consulta = "SELECT id_tipo_sangre, sangre FROM tipos_sangre ORDER BY id_tipo_sangre ASC";

    int estado = mysql_query(cn.getConector(), consulta.c_str());

    if (estado == 0) {
        resultado = mysql_store_result(cn.getConector());

        cout << endl;
        cout << "========== LISTADO DE TIPOS DE SANGRE ==========" << endl;

        while ((fila = mysql_fetch_row(resultado))) {
            cout << "ID: " << fila[0] << " | Tipo: " << fila[1] << endl;
        }

        mysql_free_result(resultado);
    }
    else {
        cout << "Error al consultar tipos de sangre: " << mysql_error(cn.getConector()) << endl;
    }

    cn.cerrar_conexion();
}

void TipoSangre::actualizar() {
    ConexionBD cn;

    if (!cn.abrir_conexion()) {
        cout << "No se pudo conectar a la base de datos." << endl;
        return;
    }

    string consulta = "UPDATE tipos_sangre SET sangre='"
        + cn.escapar(sangre)
        + "' WHERE id_tipo_sangre="
        + to_string(id_tipo_sangre);

    int estado = mysql_query(cn.getConector(), consulta.c_str());

    if (estado == 0) {
        cout << "Tipo de sangre actualizado correctamente." << endl;
    }
    else {
        cout << "Error al actualizar tipo de sangre: " << mysql_error(cn.getConector()) << endl;
    }

    cn.cerrar_conexion();
}

void TipoSangre::borrar() {
    ConexionBD cn;

    if (!cn.abrir_conexion()) {
        cout << "No se pudo conectar a la base de datos." << endl;
        return;
    }

    string consulta = "DELETE FROM tipos_sangre WHERE id_tipo_sangre="
        + to_string(id_tipo_sangre);

    int estado = mysql_query(cn.getConector(), consulta.c_str());

    if (estado == 0) {
        cout << "Tipo de sangre eliminado correctamente." << endl;
    }
    else {
        cout << "Error al eliminar tipo de sangre: " << mysql_error(cn.getConector()) << endl;
        cout << "Verifique que no este asignado a algun estudiante." << endl;
    }

    cn.cerrar_conexion();
}

void TipoSangre::buscarPorId(int id) {
    ConexionBD cn;
    MYSQL_ROW fila;
    MYSQL_RES* resultado;

    if (!cn.abrir_conexion()) {
        cout << "No se pudo conectar a la base de datos." << endl;
        return;
    }

    string consulta = "SELECT id_tipo_sangre, sangre FROM tipos_sangre WHERE id_tipo_sangre="
        + to_string(id);

    int estado = mysql_query(cn.getConector(), consulta.c_str());

    if (estado == 0) {
        resultado = mysql_store_result(cn.getConector());

        if ((fila = mysql_fetch_row(resultado))) {
            cout << endl;
            cout << "========== TIPO DE SANGRE ENCONTRADO ==========" << endl;
            cout << "ID: " << fila[0] << endl;
            cout << "Tipo: " << fila[1] << endl;
        }
        else {
            cout << "No se encontro el tipo de sangre." << endl;
        }

        mysql_free_result(resultado);
    }
    else {
        cout << "Error al buscar tipo de sangre: " << mysql_error(cn.getConector()) << endl;
    }

    cn.cerrar_conexion();
}

bool TipoSangre::existeTipoSangre(int id) {
    ConexionBD cn;
    MYSQL_RES* resultado;
    bool existe = false;

    if (!cn.abrir_conexion()) {
        return false;
    }

    string consulta = "SELECT id_tipo_sangre FROM tipos_sangre WHERE id_tipo_sangre="
        + to_string(id)
        + " LIMIT 1";

    if (mysql_query(cn.getConector(), consulta.c_str()) == 0) {
        resultado = mysql_store_result(cn.getConector());

        if (resultado != nullptr && mysql_num_rows(resultado) > 0) {
            existe = true;
        }

        if (resultado != nullptr) {
            mysql_free_result(resultado);
        }
    }

    cn.cerrar_conexion();
    return existe;
}

bool TipoSangre::existeSangre(string tipo, int id_excluir) {
    ConexionBD cn;
    MYSQL_RES* resultado;
    bool existe = false;

    if (!cn.abrir_conexion()) {
        return false;
    }

    string consulta = "SELECT id_tipo_sangre FROM tipos_sangre WHERE sangre='"
        + cn.escapar(tipo)
        + "'";

    if (id_excluir > 0) {
        consulta += " AND id_tipo_sangre <> " + to_string(id_excluir);
    }

    consulta += " LIMIT 1";

    if (mysql_query(cn.getConector(), consulta.c_str()) == 0) {
        resultado = mysql_store_result(cn.getConector());

        if (resultado != nullptr && mysql_num_rows(resultado) > 0) {
            existe = true;
        }

        if (resultado != nullptr) {
            mysql_free_result(resultado);
        }
    }

    cn.cerrar_conexion();
    return existe;
}