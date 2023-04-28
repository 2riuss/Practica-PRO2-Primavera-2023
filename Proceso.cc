#include "Proceso.hh"

Proceso::Proceso() {
    id = -1;
}

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

bool Proceso::inizializado() const {
    return id != -1;
}

void Proceso::leer_proceso() {
    cin >> id >> mem >> t;
}

void Proceso::escribir_proceso() const {
    cout << id << ' ' << mem << ' ' << t << endl;;
}
