#include <iostream>
#include <string>
#include <limits>
#include <regex>
#include "Estudiante.h"
#include "TipoSangre.h"

using namespace std;

void limpiarBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void pausa() {
    cout << endl;
    cout << "Presione Enter para continuar...";
    cin.get();
}

bool soloNumeros(string texto) {
    if (texto.empty()) {
        return false;
    }

    for (char c : texto) {
        if (!isdigit((unsigned char)c)) {
            return false;
        }
    }

    return true;
}

bool validarTipoSangreTexto(string sangre) {
    regex patron("^(AB|A|B|O)[+-]$");
    return regex_match(sangre, patron);
}

int pedirId(string mensaje) {
    string entrada;

    cout << mensaje;
    getline(cin, entrada);

    if (!soloNumeros(entrada)) {
        cout << "ALERTA: El ID debe contener solo numeros." << endl;
        return -1;
    }

    int id = stoi(entrada);

    if (id <= 0) {
        cout << "ALERTA: El ID debe ser mayor que cero." << endl;
        return -1;
    }

    return id;
}

Estudiante pedirDatosEstudiante() {
    string codigo, nombres, apellidos, direccion, fecha_nacimiento;
    int telefono, id_tipo_sangre;

    cout << "Ingrese codigo: ";
    cin >> codigo;
    limpiarBuffer();

    cout << "Ingrese nombres: ";
    getline(cin, nombres);

    cout << "Ingrese apellidos: ";
    getline(cin, apellidos);

    cout << "Ingrese direccion: ";
    getline(cin, direccion);

    cout << "Ingrese telefono: ";
    cin >> telefono;
    limpiarBuffer();

    cout << "Ingrese fecha de nacimiento YYYY-MM-DD: ";
    getline(cin, fecha_nacimiento);

    cout << "Ingrese ID tipo de sangre: ";
    cin >> id_tipo_sangre;
    limpiarBuffer();

    Estudiante estudiante(codigo, nombres, apellidos, direccion, telefono, fecha_nacimiento, id_tipo_sangre, 0);
    return estudiante;
}

void registrarEstudiante() {
    Estudiante estudiante = pedirDatosEstudiante();
    estudiante.crear();
}

void mostrarEstudiantes() {
    Estudiante estudiante;
    estudiante.leer();
}

void buscarEstudiante() {
    int id = pedirId("Ingrese ID del estudiante: ");

    if (id == -1) {
        return;
    }

    Estudiante estudiante;
    estudiante.buscarPorId(id);
}

void modificarEstudiante() {
    int id = pedirId("Ingrese ID del estudiante a modificar: ");

    if (id == -1) {
        return;
    }

    Estudiante estudiante = pedirDatosEstudiante();
    estudiante.setIdEstudiante(id);
    estudiante.actualizar();
}

void eliminarEstudiante() {
    int id = pedirId("Ingrese ID del estudiante a eliminar: ");

    if (id == -1) {
        return;
    }

    Estudiante estudiante;
    estudiante.setIdEstudiante(id);
    estudiante.borrar();
}

void registrarTipoSangre() {
    string sangre;
    TipoSangre tipo;

    cout << endl;
    cout << "Ingrese tipo de sangre." << endl;
    cout << "Ejemplos validos: O+, O-, A+, A-, B+, B-, AB+, AB-" << endl;
    cout << "Tipo de sangre: ";
    getline(cin, sangre);

    if (sangre.empty()) {
        cout << "ALERTA: El tipo de sangre es obligatorio." << endl;
        return;
    }

    if (sangre.length() > 5) {
        cout << "ALERTA: El tipo de sangre debe tener maximo 5 caracteres." << endl;
        return;
    }

    if (!validarTipoSangreTexto(sangre)) {
        cout << "ALERTA: Formato no valido. Use ejemplos como O+, A-, AB+." << endl;
        return;
    }

    if (tipo.existeSangre(sangre)) {
        cout << "ALERTA: Ese tipo de sangre ya existe." << endl;
        return;
    }

    tipo.setSangre(sangre);
    tipo.crear();
}

void mostrarTiposSangre() {
    TipoSangre tipo;
    tipo.leer();
}

void buscarTipoSangre() {
    int id = pedirId("Ingrese ID del tipo de sangre: ");

    if (id == -1) {
        return;
    }

    TipoSangre tipo;

    if (!tipo.existeTipoSangre(id)) {
        cout << "ALERTA: No existe un tipo de sangre con ese ID." << endl;
        return;
    }

    tipo.buscarPorId(id);
}

void modificarTipoSangre() {
    int id = pedirId("Ingrese ID del tipo de sangre a modificar: ");

    if (id == -1) {
        return;
    }

    TipoSangre tipo;

    if (!tipo.existeTipoSangre(id)) {
        cout << "ALERTA: No existe un tipo de sangre con ese ID." << endl;
        return;
    }

    string sangre;

    cout << "Ingrese nuevo tipo de sangre: ";
    getline(cin, sangre);

    if (sangre.empty()) {
        cout << "ALERTA: El tipo de sangre es obligatorio." << endl;
        return;
    }

    if (sangre.length() > 5) {
        cout << "ALERTA: El tipo de sangre debe tener maximo 5 caracteres." << endl;
        return;
    }

    if (!validarTipoSangreTexto(sangre)) {
        cout << "ALERTA: Formato no valido. Use ejemplos como O+, A-, AB+." << endl;
        return;
    }

    if (tipo.existeSangre(sangre, id)) {
        cout << "ALERTA: Ese tipo de sangre ya existe en otro registro." << endl;
        return;
    }

    tipo.setIdTipoSangre(id);
    tipo.setSangre(sangre);
    tipo.actualizar();
}

void eliminarTipoSangre() {
    int id = pedirId("Ingrese ID del tipo de sangre a eliminar: ");

    if (id == -1) {
        return;
    }

    TipoSangre tipo;

    if (!tipo.existeTipoSangre(id)) {
        cout << "ALERTA: No existe un tipo de sangre con ese ID." << endl;
        return;
    }

    string confirmar;

    cout << "Escriba SI para confirmar la eliminacion: ";
    getline(cin, confirmar);

    if (confirmar != "SI") {
        cout << "Eliminacion cancelada." << endl;
        return;
    }

    tipo.setIdTipoSangre(id);
    tipo.borrar();
}

int main() {
    int opcion;
    string entrada;

    do {
        cout << endl;
        cout << "========== SISTEMA DB_ESCUELA ==========" << endl;
        cout << "1. Registrar estudiante" << endl;
        cout << "2. Mostrar estudiantes" << endl;
        cout << "3. Buscar estudiante por ID" << endl;
        cout << "4. Modificar estudiante" << endl;
        cout << "5. Eliminar estudiante" << endl;
        cout << "6. Registrar tipo de sangre" << endl;
        cout << "7. Mostrar tipos de sangre" << endl;
        cout << "8. Buscar tipo de sangre por ID" << endl;
        cout << "9. Modificar tipo de sangre" << endl;
        cout << "10. Eliminar tipo de sangre" << endl;
        cout << "0. Salir" << endl;
        cout << "Seleccione una opcion: ";
        getline(cin, entrada);

        if (!soloNumeros(entrada)) {
            cout << "ALERTA: La opcion debe ser numerica." << endl;
            pausa();
            continue;
        }

        opcion = stoi(entrada);

        switch (opcion) {
        case 1:
            registrarEstudiante();
            pausa();
            break;

        case 2:
            mostrarEstudiantes();
            pausa();
            break;

        case 3:
            buscarEstudiante();
            pausa();
            break;

        case 4:
            modificarEstudiante();
            pausa();
            break;

        case 5:
            eliminarEstudiante();
            pausa();
            break;

        case 6:
            registrarTipoSangre();
            pausa();
            break;

        case 7:
            mostrarTiposSangre();
            pausa();
            break;

        case 8:
            buscarTipoSangre();
            pausa();
            break;

        case 9:
            modificarTipoSangre();
            pausa();
            break;

        case 10:
            eliminarTipoSangre();
            pausa();
            break;

        case 0:
            cout << "Programa finalizado." << endl;
            break;

        default:
            cout << "Opcion no valida." << endl;
            pausa();
            break;
        }

    } while (opcion != 0);

    return 0;
}