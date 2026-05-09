#include <iostream>
#include <string>
#include <limits>
#include <regex>
#include <cctype>
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

bool soloLetrasYEspacios(string texto) {
    if (texto.empty()) {
        return false;
    }

    string permitidos = "abcdefghijklmnñopqrstuvwxyzABCDEFGHIJKLMNÑOPQRSTUVWXYZ áéíóúÁÉÍÓÚ";

    for (char c : texto) {
        if (permitidos.find(c) == string::npos) {
            return false;
        }
    }

    return true;
}

bool contieneTextoPeligroso(string texto) {
    string peligrosos[] = {
        "'", "\"", ";", "--", "/*", "*/", "\\",
        "DROP", "drop", "DELETE", "delete",
        "INSERT", "insert", "UPDATE", "update",
        "SELECT", "select"
    };

    for (string palabra : peligrosos) {
        if (texto.find(palabra) != string::npos) {
            return true;
        }
    }

    return false;
}

bool validarCodigoFormato(string codigo) {
    regex patron("^E[0-9]{3}$");
    return regex_match(codigo, patron);
}

bool validarCodigoEstudiante(string codigo, int id_actual, bool esActualizacion) {
    Estudiante validador;

    if (codigo.empty()) {
        cout << "ALERTA: El codigo es obligatorio." << endl;
        return false;
    }

    if (codigo.length() > 4) {
        cout << "ALERTA: El codigo debe tener maximo 4 caracteres." << endl;
        return false;
    }

    if (!validarCodigoFormato(codigo)) {
        cout << "ALERTA: El codigo debe tener el formato E001, E002, E003." << endl;
        return false;
    }

    if (esActualizacion) {
        if (validador.codigoExiste(codigo, id_actual)) {
            cout << "ALERTA: El codigo ya esta registrado en otro estudiante." << endl;
            return false;
        }
    }
    else {
        if (validador.codigoExiste(codigo)) {
            cout << "ALERTA: El codigo ya existe. No se permiten codigos duplicados." << endl;
            return false;
        }
    }

    return true;
}

bool validarNombres(string nombres) {
    if (nombres.empty()) {
        cout << "ALERTA: Los nombres son obligatorios." << endl;
        return false;
    }

    if (nombres.length() > 60) {
        cout << "ALERTA: Los nombres no deben superar 60 caracteres." << endl;
        return false;
    }

    if (!soloLetrasYEspacios(nombres)) {
        cout << "ALERTA: Los nombres solo deben contener letras y espacios." << endl;
        return false;
    }

    return true;
}

bool validarApellidos(string apellidos) {
    if (apellidos.empty()) {
        cout << "ALERTA: Los apellidos son obligatorios." << endl;
        return false;
    }

    if (apellidos.length() > 60) {
        cout << "ALERTA: Los apellidos no deben superar 60 caracteres." << endl;
        return false;
    }

    if (!soloLetrasYEspacios(apellidos)) {
        cout << "ALERTA: Los apellidos solo deben contener letras y espacios." << endl;
        return false;
    }

    return true;
}

bool validarDireccion(string direccion) {
    if (direccion.empty()) {
        cout << "ALERTA: La direccion es obligatoria." << endl;
        return false;
    }

    if (direccion.length() > 100) {
        cout << "ALERTA: La direccion no debe superar 100 caracteres." << endl;
        return false;
    }

    if (contieneTextoPeligroso(direccion)) {
        cout << "ALERTA: La direccion contiene caracteres o palabras no permitidas." << endl;
        return false;
    }

    return true;
}

bool validarTelefono(string telefono) {
    if (telefono.empty()) {
        cout << "ALERTA: El telefono es obligatorio." << endl;
        return false;
    }

    if (!soloNumeros(telefono)) {
        cout << "ALERTA: El telefono solo debe aceptar numeros." << endl;
        return false;
    }

    if (telefono.length() != 8) {
        cout << "ALERTA: El telefono debe tener exactamente 8 digitos." << endl;
        return false;
    }

    return true;
}

bool validarTipoSangreTexto(string sangre) {
    regex patron("^(AB|A|B|O)[+-]$");
    return regex_match(sangre, patron);
}

string pedirCodigoEstudiante(int id_actual, bool esActualizacion) {
    string codigo;

    do {
        cout << "Ingrese codigo: ";
        getline(cin, codigo);

        if (validarCodigoEstudiante(codigo, id_actual, esActualizacion)) {
            return codigo;
        }

        cout << "Vuelva a ingresar el codigo." << endl << endl;

    } while (true);
}

string pedirNombres() {
    string nombres;

    do {
        cout << "Ingrese nombres: ";
        getline(cin, nombres);

        if (validarNombres(nombres)) {
            return nombres;
        }

        cout << "Vuelva a ingresar los nombres." << endl << endl;

    } while (true);
}

string pedirApellidos() {
    string apellidos;

    do {
        cout << "Ingrese apellidos: ";
        getline(cin, apellidos);

        if (validarApellidos(apellidos)) {
            return apellidos;
        }

        cout << "Vuelva a ingresar los apellidos." << endl << endl;

    } while (true);
}

string pedirDireccion() {
    string direccion;

    do {
        cout << "Ingrese direccion: ";
        getline(cin, direccion);

        if (validarDireccion(direccion)) {
            return direccion;
        }

        cout << "Vuelva a ingresar la direccion." << endl << endl;

    } while (true);
}

int pedirTelefono() {
    string telefonoTexto;

    do {
        cout << "Ingrese telefono: ";
        getline(cin, telefonoTexto);

        if (validarTelefono(telefonoTexto)) {
            return stoi(telefonoTexto);
        }

        cout << "Vuelva a ingresar el telefono." << endl << endl;

    } while (true);
}

int pedirEnteroPositivo(string mensaje) {
    string entrada;

    do {
        cout << mensaje;
        getline(cin, entrada);

        if (!soloNumeros(entrada)) {
            cout << "ALERTA: Debe ingresar solo numeros." << endl;
            cout << "Vuelva a intentarlo." << endl << endl;
            continue;
        }

        int numero = stoi(entrada);

        if (numero <= 0) {
            cout << "ALERTA: El valor debe ser mayor que cero." << endl;
            cout << "Vuelva a intentarlo." << endl << endl;
            continue;
        }

        return numero;

    } while (true);
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

Estudiante pedirDatosEstudiante(int id_actual = 0, bool esActualizacion = false) {
    string codigo;
    string nombres;
    string apellidos;
    string direccion;
    string fecha_nacimiento;
    int telefono;
    int id_tipo_sangre;

    cout << endl;
    cout << "Ingrese los datos del estudiante." << endl;
    cout << "Instrucciones:" << endl;
    cout << "- Codigo obligatorio, maximo 4 caracteres, formato E001." << endl;
    cout << "- Nombres y apellidos obligatorios, solo letras y espacios, maximo 60 caracteres." << endl;
    cout << "- Direccion obligatoria, maximo 100 caracteres, sin caracteres peligrosos." << endl;
    cout << "- Telefono obligatorio, solo numeros, exactamente 8 digitos." << endl;
    cout << endl;

    codigo = pedirCodigoEstudiante(id_actual, esActualizacion);
    nombres = pedirNombres();
    apellidos = pedirApellidos();
    direccion = pedirDireccion();
    telefono = pedirTelefono();

    cout << "Ingrese fecha de nacimiento YYYY-MM-DD: ";
    getline(cin, fecha_nacimiento);

    id_tipo_sangre = pedirEnteroPositivo("Ingrese ID tipo de sangre: ");

    Estudiante estudiante(
        codigo,
        nombres,
        apellidos,
        direccion,
        telefono,
        fecha_nacimiento,
        id_tipo_sangre,
        id_actual
    );

    return estudiante;
}

void registrarEstudiante() {
    Estudiante estudiante = pedirDatosEstudiante(0, false);
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

    Estudiante estudiante = pedirDatosEstudiante(id, true);
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
    int opcion = -1;
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