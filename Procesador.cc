/** @file Procesador.cc
    @brief Código de la clase Procesador
*/

#include "Procesador.hh"

Procesador::Procesador() {}

Procesador::Procesador(int mem) {
    mem_mida = mem;

    set<int> newset;
    newset.insert(newset.end(), 0);
    huecos.insert(huecos.end(), make_pair(mem, newset));
}

void Procesador::agregar_hueco(int mida, int pos) {
    map<int, set<int>>::iterator it = huecos.lower_bound(mida);
    if (it != huecos.end() and it -> first == mida) it -> second.insert(pos);
    else {
        set<int> auxset;
        auxset.insert(auxset.end(), pos);
        huecos.insert(it, make_pair(mida, auxset));
    }
}

void Procesador::agregar_proceso(const Proceso& job) {
    map<int, set<int>>::iterator it = huecos.lower_bound(job.consultar_mem());
    int job_pos = *(it -> second.begin());
    int hueco_mida = it -> first - job.consultar_mem();
    int hueco_pos = job_pos + job.consultar_mem();

    it -> second.erase(it -> second.begin());
    if (it -> second.empty()) huecos.erase(it);

    agregar_hueco(hueco_mida, hueco_pos);
    procesos.insert(make_pair(job.consultar_id(), job_pos));
    mem.insert(make_pair(job_pos, job));
}

void Procesador::eliminar_hueco(int mida, int pos) {
    map<int, set<int>>::iterator it = huecos.find(mida);
    it -> second.erase(pos);
    if (it -> second.empty()) huecos.erase(it);
}

void Procesador::eliminar_proceso_aux(const map<int, Proceso>::const_iterator it1, const map<int, int>::const_iterator it2) {
    int pos_ant;
    if (it1 != mem.begin()) {
        map<int, Proceso>::const_iterator it_ant = it1;
        --it_ant;
        pos_ant = it_ant -> first + it_ant -> second.consultar_mem();
    }
    else pos_ant = 0;
    int hueco_ant = it1 -> first - pos_ant;

    if (hueco_ant > 0) eliminar_hueco(hueco_ant, pos_ant);


    int pos_post = it1 -> first + it1 -> second.consultar_mem();
    int hueco_post;
    map<int, Proceso>::const_iterator it_post = it1;
    ++it_post;
    if (it_post != mem.end()) hueco_post = it_post -> first - pos_post;
    else hueco_post = mem_mida - pos_post;

    if (hueco_post > 0) eliminar_hueco(hueco_post, pos_post);


    int hueco_nou = it1 -> second.consultar_mem() + hueco_ant + hueco_post;
    agregar_hueco(hueco_nou, pos_ant);

    mem.erase(it1);
    procesos.erase(it2);
}

void Procesador::eliminar_proceso(int n) {
    map<int, int>::const_iterator it2 = procesos.find(n);
    map<int, Proceso>::const_iterator it1 = mem.find(it2 -> second);
    eliminar_proceso_aux(it1, it2);
}

void Procesador::compactar_memoria() {
    int pos = 0;
    map<int, Proceso>::iterator it = mem.begin();
    while (it != mem.end()) {
        if (it -> first != pos) {
            procesos.find(it -> second.consultar_id()) -> second = pos;
            mem.insert(it, make_pair(pos, it -> second));
            pos += it -> second.consultar_mem();
            it = mem.erase(it);
        }
        else {
            pos += it -> second.consultar_mem();
            ++it;
        }
    }
    huecos.clear();
    set<int> newset;
    newset.insert(newset.end(), pos);
    huecos.insert(huecos.end(), make_pair(mem_mida - pos, newset));
}

void Procesador::avanzar_tiempo(int t) {
    map<int, Proceso>::iterator it = mem.begin();
    while (it != mem.end()) {
        if (it -> second.consultar_t() <= t) {
            map<int, Proceso>::const_iterator it1 = it;
            map<int, int>::const_iterator it2 = procesos.find(it1 -> second.consultar_id());
            ++it;
            eliminar_proceso_aux(it1, it2);
        }
        else {
            it -> second.avanzar_tiempo(t);
            ++it;
        }
    }
}

bool Procesador::existe_proceso(int n) const {
    return procesos.find(n) != procesos.end();
}

bool Procesador::vacio() const {
    return procesos.empty();
}

int Procesador::free_mem() const {
    int aux = 0;
    for (map<int, set<int>>::const_iterator it = huecos.begin(); it != huecos.end(); ++it) {
        aux += it -> first*it -> second.size();
    }
    return aux;
}

bool Procesador::cabe_proceso(const Proceso& job) const {
    return huecos.lower_bound(job.consultar_mem()) != huecos.end();
}

int Procesador::hueco_proceso(const Proceso& job) const {
    return huecos.lower_bound(job.consultar_mem()) -> first;
}

void Procesador::escribir_procesador() const {
    for (map<int, Proceso>::const_iterator it = mem.begin(); it != mem.end(); ++it) {
        cout << it -> first << ' ';
        it -> second.escribir_proceso();
    }
}
