#include <iostream>
#include <string>
#include <limits>
#include "Estudiante.h"

using namespace std;

void limpiarBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void pausa() {
    cout << endl;
    cout << "Presione Enter para continuar...";
    cin.get();
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
    int id;
    cout << "Ingrese ID del estudiante: ";
    cin >> id;
    limpiarBuffer();

    Estudiante estudiante;
    estudiante.buscarPorId(id);
}

void modificarEstudiante() {
    int id;
    cout << "Ingrese ID del estudiante a modificar: ";
    cin >> id;
    limpiarBuffer();

    Estudiante estudiante = pedirDatosEstudiante();
    estudiante.setIdEstudiante(id);
    estudiante.actualizar();
}

void eliminarEstudiante() {
    int id;
    cout << "Ingrese ID del estudiante a eliminar: ";
    cin >> id;
    limpiarBuffer();

    Estudiante estudiante;
    estudiante.setIdEstudiante(id);
    estudiante.borrar();
}

int main() {
    int opcion;

    do {
        cout << endl;
        cout << "========== CRUD ESTUDIANTES ==========" << endl;
        cout << "1. Registrar estudiante" << endl;
        cout << "2. Mostrar estudiantes" << endl;
        cout << "3. Buscar estudiante por ID" << endl;
        cout << "4. Modificar estudiante" << endl;
        cout << "5. Eliminar estudiante" << endl;
        cout << "0. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        limpiarBuffer();

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