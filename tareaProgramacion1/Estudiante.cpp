#include "Estudiante.h"
#include <iostream>
#include <mysql.h>

Estudiante::Estudiante() : Persona() {
    id_estudiante = 0;
    codigo = "";
}

Estudiante::Estudiante(string cod, string nom, string ape, string dir, int tel, string fecha, int tipo_sangre, int id)
    : Persona(nom, ape, dir, tel, fecha, tipo_sangre) {
    codigo = cod;
    id_estudiante = id;
}

void Estudiante::setIdEstudiante(int id) {
    id_estudiante = id;
}

void Estudiante::setCodigo(string cod) {
    codigo = cod;
}

int Estudiante::getIdEstudiante() {
    return id_estudiante;
}

string Estudiante::getCodigo() {
    return codigo;
}

void Estudiante::crear() {
    ConexionBD cn;

    if (!cn.abrir_conexion()) {
        cout << "No se pudo conectar a la base de datos." << endl;
        return;
    }

    string consulta = "INSERT INTO estudiantes(codigo, nombres, apellidos, direccion, telefono, fecha_nacimiento, id_tipo_sangre) VALUES('"
        + cn.escapar(codigo) + "','"
        + cn.escapar(nombres) + "','"
        + cn.escapar(apellidos) + "','"
        + cn.escapar(direccion) + "',"
        + to_string(telefono) + ",'"
        + cn.escapar(fecha_nacimiento) + "',"
        + to_string(id_tipo_sangre) + ")";

    int estado = mysql_query(cn.getConector(), consulta.c_str());

    if (estado == 0) {
        cout << "Estudiante registrado correctamente." << endl;
    }
    else {
        cout << "Error al registrar: " << mysql_error(cn.getConector()) << endl;
    }

    cn.cerrar_conexion();
}

void Estudiante::leer() {
    ConexionBD cn;
    MYSQL_ROW fila;
    MYSQL_RES* resultado;

    if (!cn.abrir_conexion()) {
        cout << "No se pudo conectar a la base de datos." << endl;
        return;
    }

    string consulta =
        "SELECT e.id_estudiante, e.codigo, e.nombres, e.apellidos, e.direccion, "
        "e.telefono, e.fecha_nacimiento, ts.sangre "
        "FROM estudiantes e "
        "LEFT JOIN tipos_sangre ts ON e.id_tipo_sangre = ts.id_tipo_sangre "
        "ORDER BY e.id_estudiante ASC";

    int estado = mysql_query(cn.getConector(), consulta.c_str());

    if (estado == 0) {
        resultado = mysql_store_result(cn.getConector());

        cout << endl;
        cout << "========== LISTADO DE ESTUDIANTES ==========" << endl;

        while ((fila = mysql_fetch_row(resultado))) {
            cout << "ID: " << fila[0] << endl;
            cout << "Codigo: " << fila[1] << endl;
            cout << "Nombres: " << fila[2] << endl;
            cout << "Apellidos: " << fila[3] << endl;
            cout << "Direccion: " << fila[4] << endl;
            cout << "Telefono: " << fila[5] << endl;
            cout << "Fecha nacimiento: " << fila[6] << endl;
            cout << "Tipo sangre: " << (fila[7] ? fila[7] : "Sin asignar") << endl;
            cout << "--------------------------------------------" << endl;
        }

        mysql_free_result(resultado);
    }
    else {
        cout << "Error al consultar: " << mysql_error(cn.getConector()) << endl;
    }

    cn.cerrar_conexion();
}

void Estudiante::actualizar() {
    ConexionBD cn;

    if (!cn.abrir_conexion()) {
        cout << "No se pudo conectar a la base de datos." << endl;
        return;
    }

    string consulta = "UPDATE estudiantes SET codigo='"
        + cn.escapar(codigo) + "', nombres='"
        + cn.escapar(nombres) + "', apellidos='"
        + cn.escapar(apellidos) + "', direccion='"
        + cn.escapar(direccion) + "', telefono="
        + to_string(telefono) + ", fecha_nacimiento='"
        + cn.escapar(fecha_nacimiento) + "', id_tipo_sangre="
        + to_string(id_tipo_sangre)
        + " WHERE id_estudiante="
        + to_string(id_estudiante);

    int estado = mysql_query(cn.getConector(), consulta.c_str());

    if (estado == 0) {
        cout << "Estudiante actualizado correctamente." << endl;
    }
    else {
        cout << "Error al actualizar: " << mysql_error(cn.getConector()) << endl;
    }

    cn.cerrar_conexion();
}

void Estudiante::borrar() {
    ConexionBD cn;

    if (!cn.abrir_conexion()) {
        cout << "No se pudo conectar a la base de datos." << endl;
        return;
    }

    string consulta = "DELETE FROM estudiantes WHERE id_estudiante=" + to_string(id_estudiante);

    int estado = mysql_query(cn.getConector(), consulta.c_str());

    if (estado == 0) {
        cout << "Estudiante eliminado correctamente." << endl;
    }
    else {
        cout << "Error al eliminar: " << mysql_error(cn.getConector()) << endl;
    }

    cn.cerrar_conexion();
}

void Estudiante::buscarPorId(int id) {
    ConexionBD cn;
    MYSQL_ROW fila;
    MYSQL_RES* resultado;

    if (!cn.abrir_conexion()) {
        cout << "No se pudo conectar a la base de datos." << endl;
        return;
    }

    string consulta =
        "SELECT e.id_estudiante, e.codigo, e.nombres, e.apellidos, e.direccion, "
        "e.telefono, e.fecha_nacimiento, ts.sangre "
        "FROM estudiantes e "
        "LEFT JOIN tipos_sangre ts ON e.id_tipo_sangre = ts.id_tipo_sangre "
        "WHERE e.id_estudiante=" + to_string(id);

    int estado = mysql_query(cn.getConector(), consulta.c_str());

    if (estado == 0) {
        resultado = mysql_store_result(cn.getConector());

        if ((fila = mysql_fetch_row(resultado))) {
            cout << endl;
            cout << "ID: " << fila[0] << endl;
            cout << "Codigo: " << fila[1] << endl;
            cout << "Nombres: " << fila[2] << endl;
            cout << "Apellidos: " << fila[3] << endl;
            cout << "Direccion: " << fila[4] << endl;
            cout << "Telefono: " << fila[5] << endl;
            cout << "Fecha nacimiento: " << fila[6] << endl;
            cout << "Tipo sangre: " << (fila[7] ? fila[7] : "Sin asignar") << endl;
        }
        else {
            cout << "No se encontro el estudiante." << endl;
        }

        mysql_free_result(resultado);
    }
    else {
        cout << "Error al buscar: " << mysql_error(cn.getConector()) << endl;
    }

    cn.cerrar_conexion();
}

bool Estudiante::codigoExiste(string cod, int id_excluir) {
    ConexionBD cn;
    MYSQL_RES* resultado;
    bool existe = false;

    if (!cn.abrir_conexion()) {
        return false;
    }

    string consulta = "SELECT id_estudiante FROM estudiantes WHERE codigo='"
        + cn.escapar(cod) + "'";

    if (id_excluir > 0) {
        consulta += " AND id_estudiante <> " + to_string(id_excluir);
    }

    consulta += " LIMIT 1";

    int estado = mysql_query(cn.getConector(), consulta.c_str());

    if (estado == 0) {
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

bool Estudiante::estudianteExiste(int id) {
    ConexionBD cn;
    MYSQL_RES* resultado;
    bool existe = false;

    if (!cn.abrir_conexion()) {
        return false;
    }

    string consulta = "SELECT id_estudiante FROM estudiantes WHERE id_estudiante="
        + to_string(id)
        + " LIMIT 1";

    int estado = mysql_query(cn.getConector(), consulta.c_str());

    if (estado == 0) {
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

bool Estudiante::tipoSangreExiste(int id_tipo_sangre) {
    ConexionBD cn;
    MYSQL_RES* resultado;
    bool existe = false;

    if (!cn.abrir_conexion()) {
        return false;
    }

    string consulta = "SELECT id_tipo_sangre FROM tipos_sangre WHERE id_tipo_sangre="
        + to_string(id_tipo_sangre)
        + " LIMIT 1";

    int estado = mysql_query(cn.getConector(), consulta.c_str());

    if (estado == 0) {
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