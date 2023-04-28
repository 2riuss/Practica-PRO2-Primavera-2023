#include "Procesador.hh"

Procesador::Procesador() {}

Procesador::Procesador(int mem) {
    this -> mem = vector<map<int, Proceso>::iterator> (mem, procesos.end());
}

int Procesador::posicion_hueco(int pmem) const {
    int i = 0;
    int hueco = mem.size();
    int pos = -1;
    int pos_aux = 0;
    while (i < mem.size() and hueco > pmem) {
        if (mem[i] != procesos.end()) {
            int hueco_aux = i - pos_aux;
            if (pmem <= hueco_aux and hueco_aux < hueco) {
                hueco = hueco_aux;
                pos = pos_aux;
            }
            i += mem[i] -> second.consultar_mem();
            pos_aux = i;
        }
        else ++i;
    }

    return pos;
}

void Procesador::agregar_proceso(const Proceso& job) {
    mem[posicion_hueco(job.consultar_mem())] = procesos.insert(make_pair(job.consultar_id(), job)).first;
}

int Procesador::posicion_proceso(int n) const {
    int i = 0;
    bool found = false;
    while (not found and i < mem.size()) {
        if (mem[i] != procesos.end()) {
            if (mem[i] -> first == n) found = true;
            else i += mem[i] -> second.consultar_mem();
        }
        else ++i;
    }

    if (i >= mem.size()) return -1;
    return i;
}

void Procesador::eliminar_proceso(int n) {
    int i = posicion_proceso(n);
    procesos.erase(mem[i]);
    mem[i] = procesos.end();
}

// void Procesador::compactar_memoria() {}

void Procesador::avanzar_tiempo(int t) {
    int i = 0;
    while (i < mem.size()) {
        if (mem[i] != procesos.end()) {
            int aux = mem[i] -> second.consultar_mem();
            if (mem[i] -> second.consultar_t() - t == 0) {
                procesos.erase(mem[i]);
                mem[i] = procesos.end();
            }
            else mem[i] -> second.avanzar_tiempo(t);
            i += aux;
        }
        else ++i;
    }
}

bool Procesador::existe_proceso(int n) const {
    return procesos.find(n) != procesos.end();
}

bool Procesador::vacio() const {
    return procesos.empty();
}

bool Procesador::cabe_proceso(const Proceso& job) const {
    return posicion_hueco(job.consultar_mem()) != -1;
}

void Procesador::escribir_procesador() const {
    int i = 0;
    while (i < mem.size()) {
        if (mem[i] != procesos.end()) {
            cout << i << ' ';
            mem[i] -> second.escribir_proceso();
            i += mem[i] -> second.consultar_mem();
        }
        else ++i;
    }
}
