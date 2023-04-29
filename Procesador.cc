#include "Procesador.hh"

Procesador::Procesador() {}

Procesador::Procesador(int mem) {
    this -> mem.insert(this -> mem.end(), make_pair(mem, Proceso()));
    mem_size = mem;
}

list<pair<int, Proceso>>::iterator Procesador::posicion_hueco(int pmem) {
    list<pair<int, Proceso>>::iterator it = mem.end();
    int hueco = mem_size + 1;

    for (list<pair<int, Proceso>>::iterator aux = mem.begin(); aux != mem.end() and hueco > pmem; ++aux) {
        if (not aux -> second.inizializado() and pmem <= aux -> first and aux -> first < hueco) {
            hueco = aux -> first;
            it = aux;
        }
    }
    return it;
}

void Procesador::agregar_proceso(const Proceso& job) {
    list<pair<int, Proceso>>::iterator it = posicion_hueco(job.consultar_mem());
    mem.insert(it, make_pair(job.consultar_mem(), job));
    if (it -> first == job.consultar_mem()) mem.erase(it);
    else it -> first -= job.consultar_mem();
}

list<pair<int, Proceso>>::iterator Procesador::posicion_proceso(int n) {
    for (list<pair<int, Proceso>>::iterator it = mem.begin(); it != mem.end(); ++it) {
        if (it -> second.inizializado() and it -> second.consultar_id() == n) return it;
    }
    return mem.end();
}

void Procesador::eliminar_proceso_aux(list<pair<int, Proceso>>::iterator& it) {
    int aux = it -> first;
    it = mem.erase(it);
    if (it != mem.end() and not it -> second.inizializado()) {
        aux += it -> first;
        it = mem.erase(it);
    }
    if (it != mem.begin()) {
        --it;
        if (not it -> second.inizializado()) {
            aux += it -> first;
            it = mem.erase(it);
        }
        else ++it;
    }
    mem.insert(it, make_pair(aux, Proceso()));
}

void Procesador::eliminar_proceso(int n) {
    list<pair<int, Proceso>>::iterator it = posicion_proceso(n);
    eliminar_proceso_aux(it);
}

// void Procesador::compactar_memoria() {}

void Procesador::avanzar_tiempo(int t) {
    list<pair<int, Proceso>>::iterator it = mem.begin();
    while (it != mem.end()) {
        if (it -> second.inizializado()) {
            if (it -> second.consultar_t() - t <= 0) eliminar_proceso_aux(it);
            else {
                it -> second.avanzar_tiempo(t);
                ++it;
            }
        }
        else ++it;
    }
}

bool Procesador::existe_proceso(int n) {
    return posicion_proceso(n) != mem.end();
}

bool Procesador::vacio() const {
    return mem.size() == 1 and not mem.begin() -> second.inizializado();
}

bool Procesador::cabe_proceso(const Proceso& job) {
    return posicion_hueco(job.consultar_mem()) != mem.end();
}

void Procesador::escribir_procesador() const {
    int pos = 0;
    for (list<pair<int, Proceso>>::const_iterator it = mem.begin(); it != mem.end(); ++it) {
        if (it -> second.inizializado()) {
            cout << pos << ' ';
            it -> second.escribir_proceso();
        }
        pos += it -> first;
    }
}
