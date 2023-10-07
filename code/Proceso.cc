/** @file Proceso.cc
    @brief Código de la clase Proceso
*/

#include "Proceso.hh"

Proceso::Proceso() {}

void Proceso::avanzar_tiempo(int t) {
    this -> t -= t;
}

int Proceso::consultar_id() const {
    return id;
}

int Proceso::consultar_t() const {
    return t;
}

int Proceso::consultar_mem() const {
    return mem;
}

void Proceso::leer_proceso() {
    cin >> id >> mem >> t;
}

void Proceso::escribir_proceso() const {
    cout << id << ' ' << mem << ' ' << t << endl;;
}
