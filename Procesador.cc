/** @file Procesador.cc
    @brief Código de la clase Procesador
*/

#include "Procesador.hh"

Procesador::Procesador() {
    memory_size = 0;
    free_memory = 0;
}

Procesador::Procesador(int mem) {
    memory_size = mem;
    free_memory = mem;

    set<int, greater<int>> newset;
    newset.insert(newset.end(), 0);
    huecos.insert(huecos.end(), make_pair(mem, newset));
}

void Procesador::agregar_hueco(int mida, int pos) {
    map<int, set<int, greater<int>>>::iterator it = huecos.lower_bound(mida);
    if (it != huecos.end() and it -> first == mida) it -> second.insert(pos);
    else {
        set<int, greater<int>> newset;
        newset.insert(newset.end(), pos);
        huecos.insert(it, make_pair(mida, newset));
    }

    free_memory += mida;
}

void Procesador::agregar_proceso(const Proceso& job) {
    map<int, set<int, greater<int>>>::iterator it = huecos.lower_bound(job.consultar_mem());
    int job_pos = *(it -> second.begin());
    int newhueco_mida = it -> first - job.consultar_mem();
    int newhueco_pos = job_pos + job.consultar_mem();

    free_memory -= it -> first;
    it -> second.erase(it -> second.begin());
    if (it -> second.empty()) huecos.erase(it);

    agregar_hueco(newhueco_mida, newhueco_pos);
    idProceso_pos.insert(make_pair(job.consultar_id(), job_pos));
    pos_proceso.insert(make_pair(job_pos, job));
}

void Procesador::eliminar_hueco(int mida, int pos) {
    map<int, set<int, greater<int>>>::iterator it = huecos.find(mida);
    it -> second.erase(pos);
    if (it -> second.empty()) huecos.erase(it);

    free_memory -= mida;
}

void Procesador::eliminar_proceso_aux(const map<int, Proceso>::const_iterator it1, const map<int, int>::const_iterator it2) {
    int pos_ant;
    if (it1 != pos_proceso.begin()) {
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
    if (it_post != pos_proceso.end()) hueco_post = it_post -> first - pos_post;
    else hueco_post = memory_size - pos_post;

    if (hueco_post > 0) eliminar_hueco(hueco_post, pos_post);


    int hueco_nou = it1 -> second.consultar_mem() + hueco_ant + hueco_post;
    agregar_hueco(hueco_nou, pos_ant);

    pos_proceso.erase(it1);
    idProceso_pos.erase(it2);
}

void Procesador::eliminar_proceso(int id_proceso) {
    map<int, int>::const_iterator it2 = idProceso_pos.find(id_proceso);
    map<int, Proceso>::const_iterator it1 = pos_proceso.find(it2 -> second);
    eliminar_proceso_aux(it1, it2);
}

void Procesador::compactar_memoria() {
    if (free_memory == 0) return;

    int pos = 0;
    map<int, Proceso>::iterator it = pos_proceso.begin();
    while (it != pos_proceso.end()) {
        if (pos != it -> first) {
            idProceso_pos.find(it -> second.consultar_id()) -> second = pos;
            pos_proceso.insert(it, make_pair(pos, it -> second));
            pos += it -> second.consultar_mem();
            it = pos_proceso.erase(it);
        }
        else {
            pos += it -> second.consultar_mem();
            ++it;
        }
    }

    huecos.clear();
    set<int, greater<int>> newset;
    newset.insert(newset.end(), pos);
    huecos.insert(huecos.end(), make_pair(free_memory, newset));
}

void Procesador::avanzar_tiempo(int t) {
    map<int, Proceso>::iterator it = pos_proceso.begin();
    while (it != pos_proceso.end()) {
        if (it -> second.consultar_t() <= t) {
            map<int, Proceso>::const_iterator it1 = it;
            map<int, int>::const_iterator it2 = idProceso_pos.find(it1 -> second.consultar_id());
            ++it;
            eliminar_proceso_aux(it1, it2);
        }
        else {
            it -> second.avanzar_tiempo(t);
            ++it;
        }
    }
}

bool Procesador::existe_proceso(int id_proceso) const {
    return idProceso_pos.find(id_proceso) != idProceso_pos.end();
}

bool Procesador::vacio() const {
    return idProceso_pos.empty();
}

int Procesador::free_mem() const {
    return free_memory;
}

bool Procesador::cabe_proceso(const Proceso& job) const {
    return huecos.lower_bound(job.consultar_mem()) != huecos.end();
}

int Procesador::hueco_proceso(const Proceso& job) const {
    return huecos.lower_bound(job.consultar_mem()) -> first;
}

int Procesador::num_procesos() const {
    return idProceso_pos.size();
}

void Procesador::escribir_procesador() const {
    for (map<int, Proceso>::const_iterator it = pos_proceso.begin(); it != pos_proceso.end(); ++it) {
        cout << it -> first << ' ';
        it -> second.escribir_proceso();
    }
}
