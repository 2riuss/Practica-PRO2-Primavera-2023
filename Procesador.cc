#include "Procesador.hh"

Procesador::Procesador() {}

Procesador::Procesador(int mem) {
    memory_size = mem;
}

pair<int, map<int, Proceso>::const_iterator> Procesador::posicion_hueco(int pmem) const {
    pair<int, map<int, Proceso>::const_iterator> pos;
    int hueco;
    map<int, Proceso>::const_iterator it = mem.begin();
    int hueco_aux;
    if (it != mem.end()) hueco_aux = it -> first;
    else hueco_aux = memory_size;
    if (pmem <= hueco_aux) {
        hueco = hueco_aux;
        pos.first = 0;
        pos.second = it;
    }
    else {
        hueco = memory_size + 1;
        pos.first = -1;
    }
    while (it != mem.end() and hueco > pmem) {
        int pos_aux = it -> first + it -> second.consultar_mem();
        ++it;
        if (it != mem.end()) hueco_aux = it -> first - pos_aux;
        else hueco_aux = memory_size - pos_aux;
        if (pmem <= hueco_aux and hueco_aux < hueco) {
            hueco = hueco_aux;
            pos.first = pos_aux;
            pos.second = it;
        }
    }
    return pos;
}

void Procesador::agregar_proceso(const Proceso& job) {
    pair<int, map<int, Proceso>::const_iterator> pos = posicion_hueco(job.consultar_mem());
    mem.insert(pos.second, make_pair(pos.first, job));
}

map<int, Proceso>::const_iterator Procesador::posicion_proceso(int n) const {
    for (map<int, Proceso>::const_iterator it = mem.begin(); it != mem.end(); ++it) {
        if (it -> second.consultar_id() == n) return it;
    }
    return mem.end();
}

void Procesador::eliminar_proceso(int n) {
    mem.erase(posicion_proceso(n));
}

// void Procesador::compactar_memoria() {}

void Procesador::avanzar_tiempo(int t) {
    map<int, Proceso>::iterator it = mem.begin();
    while (it != mem.end()) {
        if (it -> second.consultar_t() - t <= 0) it = mem.erase(it);
        else {
            it -> second.avanzar_tiempo(t);
            ++it;
        }
    }
}

bool Procesador::existe_proceso(int n) const {
    return posicion_proceso(n) != mem.end();
}

bool Procesador::vacio() const {
    return mem.empty();
}

bool Procesador::cabe_proceso(const Proceso& job) const {
    return posicion_hueco(job.consultar_mem()).first != -1;
}

void Procesador::escribir_procesador() const {
    for (map<int, Proceso>::const_iterator it = mem.begin(); it != mem.end(); ++it) {
        cout << it -> first << ' ';
        it -> second.escribir_proceso();
    }
}
