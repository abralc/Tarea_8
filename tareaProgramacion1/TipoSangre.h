#pragma once

#include <string>
using namespace std;

class TipoSangre {
private:
    int id_tipo_sangre;
    string sangre;

public:
    TipoSangre();
    TipoSangre(int id, string tipo);

    void setIdTipoSangre(int id);
    void setSangre(string tipo);

    int getIdTipoSangre();
    string getSangre();

    void crear();
    void leer();
    void actualizar();
    void borrar();
    void buscarPorId(int id);

    bool existeTipoSangre(int id);
    bool existeSangre(string tipo, int id_excluir = 0);
};