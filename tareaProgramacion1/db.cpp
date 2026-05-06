#include "db.h"
#include <mysql.h>
#include <iostream>
#include <sstream>
#include <stdexcept>

static MYSQL* conn = nullptr;

static std::string escape_string(const std::string& s) {
    if (!conn) return "";
    std::string buf;
    buf.resize(2 * s.size() + 1);
    unsigned long out_len = mysql_real_escape_string(conn, &buf[0], s.c_str(), (unsigned long)s.size());
    return std::string(buf.c_str(), out_len);
}

bool DB::connect(const char* host, const char* user, const char* passwd, const char* db, unsigned int port) {
    conn = mysql_init(nullptr);
    if (!conn) {
        std::cerr << "mysql_init failed\n";
        return false;
    }
    if (!mysql_real_connect(conn, host, user, passwd, db, port, nullptr, 0)) {
        std::cerr << "Connection error: " << mysql_error(conn) << "\n";
        mysql_close(conn);
        conn = nullptr;
        return false;
    }
    // Optional: set utf8mb4
    if (mysql_set_character_set(conn, "utf8mb4") != 0) {
        std::cerr << "Warning: could not set charset: " << mysql_error(conn) << "\n";
    }
    return true;
}

void DB::close() {
    if (conn) {
        mysql_close(conn);
        conn = nullptr;
    }
}

std::vector<std::pair<int, std::string>> DB::get_tipos_sangre() {
    std::vector<std::pair<int, std::string>> out;
    if (!conn) return out;
    if (mysql_query(conn, "SELECT id_tipo_sangre, sangre FROM tipos_sangre")) {
        std::cerr << "Query error: " << mysql_error(conn) << "\n";
        return out;
    }
    MYSQL_RES* res = mysql_store_result(conn);
    if (!res) return out;
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(res))) {
        int id = row[0] ? std::atoi(row[0]) : 0;
        std::string s = row[1] ? row[1] : "";
        out.emplace_back(id, s);
    }
    mysql_free_result(res);
    return out;
}

std::vector<Student> DB::get_all_students() {
    std::vector<Student> list;
    if (!conn) return list;
    const char* q = "SELECT e.id_estudiante, e.codigo, e.nombres, e.apellidos, e.direccion, e.telefono, e.fecha_nacimiento, e.id_tipo_sangre, t.sangre "
        "FROM estudiantes e LEFT JOIN tipos_sangre t ON e.id_tipo_sangre = t.id_tipo_sangre";
    if (mysql_query(conn, q)) {
        std::cerr << "Query error: " << mysql_error(conn) << "\n";
        return list;
    }
    MYSQL_RES* res = mysql_store_result(conn);
    if (!res) return list;
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(res))) {
        Student s;
        s.id = row[0] ? std::atoi(row[0]) : 0;
        s.codigo = row[1] ? row[1] : "";
        s.nombres = row[2] ? row[2] : "";
        s.apellidos = row[3] ? row[3] : "";
        s.direccion = row[4] ? row[4] : "";
        s.telefono = row[5] ? std::atoi(row[5]) : 0;
        s.fecha_nacimiento = row[6] ? row[6] : "";
        s.id_tipo_sangre = row[7] ? std::atoi(row[7]) : 0;
        s.sangre = row[8] ? row[8] : "";
        list.push_back(s);
    }
    mysql_free_result(res);
    return list;
}

bool DB::insert_student(const Student& s) {
    if (!conn) return false;
    std::ostringstream q;
    q << "INSERT INTO estudiantes (codigo, nombres, apellidos, direccion, telefono, fecha_nacimiento, id_tipo_sangre) VALUES (";
    q << "'" << escape_string(s.codigo) << "', ";
    q << "'" << escape_string(s.nombres) << "', ";
    q << "'" << escape_string(s.apellidos) << "', ";
    q << "'" << escape_string(s.direccion) << "', ";
    q << (s.telefono) << ", ";
    q << "'" << escape_string(s.fecha_nacimiento) << "', ";
    if (s.id_tipo_sangre > 0) q << s.id_tipo_sangre;
    else q << "NULL";
    q << ")";
    if (mysql_query(conn, q.str().c_str())) {
        std::cerr << "Insert error: " << mysql_error(conn) << "\n";
        return false;
    }
    return true;
}

bool DB::update_student(const Student& s) {
    if (!conn) return false;
    std::ostringstream q;
    q << "UPDATE estudiantes SET ";
    q << "codigo = '" << escape_string(s.codigo) << "', ";
    q << "nombres = '" << escape_string(s.nombres) << "', ";
    q << "apellidos = '" << escape_string(s.apellidos) << "', ";
    q << "direccion = '" << escape_string(s.direccion) << "', ";
    q << "telefono = " << s.telefono << ", ";
    q << "fecha_nacimiento = '" << escape_string(s.fecha_nacimiento) << "', ";
    if (s.id_tipo_sangre > 0) q << "id_tipo_sangre = " << s.id_tipo_sangre;
    else q << "id_tipo_sangre = NULL";
    q << " WHERE id_estudiante = " << s.id;
    if (mysql_query(conn, q.str().c_str())) {
        std::cerr << "Update error: " << mysql_error(conn) << "\n";
        return false;
    }
    return true;
}

bool DB::delete_student(int id) {
    if (!conn) return false;
    std::ostringstream q;
    q << "DELETE FROM estudiantes WHERE id_estudiante = " << id;
    if (mysql_query(conn, q.str().c_str())) {
        std::cerr << "Delete error: " << mysql_error(conn) << "\n";
        return false;
    }
    return true;
}