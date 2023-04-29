#include "Procesador.hh"

Procesador::Procesador() {}

Procesador::Procesador(int mem) {
    this -> mem = vector<Proceso>(mem);
}

int Procesador::posicion_hueco(int pmem) const {
    int i = 0;
    int hueco = mem.size() + 1;
    int pos = -1;
    int pos_aux = 0;
    while (i <= mem.size() and hueco > pmem) {
        if (i == mem.size() or mem[i].inizializado()) {
            int hueco_aux = i - pos_aux;
            if (pmem <= hueco_aux and hueco_aux < hueco) {
                hueco = hueco_aux;
                pos = pos_aux;
            }
            if (i < mem.size()) {
                i += mem[i].consultar_mem();
                pos_aux = i;
            }
            else ++i;
        }
        else ++i;
    }

    return pos;
}

void Procesador::agregar_proceso(const Proceso& job) {
    mem[posicion_hueco(job.consultar_mem())] = job;
}

int Procesador::posicion_proceso(int n) const {
    int i = 0;
    bool found = false;
    while (not found and i < mem.size()) {
        if (mem[i].inizializado()) {
            if (mem[i].consultar_id() == n) found = true;
            else i += mem[i].consultar_mem();
        }
        else ++i;
    }

    if (i >= mem.size()) return -1;
    return i;
}

void Procesador::eliminar_proceso(int n) {
    mem[posicion_proceso(n)] = Proceso();
}

// void Procesador::compactar_memoria() {}

void Procesador::avanzar_tiempo(int t) {
    int i = 0;
    while (i < mem.size()) {
        if (mem[i].inizializado()) {
            int aux = mem[i].consultar_mem();
            if (mem[i].consultar_t() - t <= 0) mem[i] = Proceso();
            else mem[i].avanzar_tiempo(t);
            i += aux;
        }
        else ++i;
    }
}

bool Procesador::existe_proceso(int n) const {
    if (posicion_proceso(n) == -1) return false;
    return true;
}

bool Procesador::vacio() const {
    for (int i = 0; i < mem.size(); ++i) {
        if (mem[i].inizializado()) return false;
    }
    return true;
}

bool Procesador::cabe_proceso(const Proceso& job) const {
    return posicion_hueco(job.consultar_mem()) != -1;
}

void Procesador::escribir_procesador() const {
    int i = 0;
    while (i < mem.size()) {
        if (mem[i].inizializado()) {
            cout << i << ' ';
            mem[i].escribir_proceso();
            i += mem[i].consultar_mem();
        }
        else ++i;
    }
}
