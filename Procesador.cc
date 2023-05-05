#include "Procesador.hh"

Procesador::Procesador() {}

Procesador::Procesador(int mem) {
    mem_mida = mem;
    set<int> newset;
    newset.insert(0);
    huecos.insert(huecos.end(), make_pair(mem, newset));
}

void Procesador::agregar_proceso(const Proceso& job) {
    map<int, set<int>>::iterator it = huecos.lower_bound(job.consultar_mem());
    int pos = *(it -> second.begin());
    map<int, set<int>>::iterator aux = huecos.lower_bound(it -> first - job.consultar_mem());
    if (aux -> first == it -> first - job.consultar_mem()) aux -> second.insert(pos + job.consultar_mem());
    else {
        set<int> newset;
        newset.insert(newset.end(), pos + job.consultar_mem());
        huecos.insert(aux, make_pair(it -> first - job.consultar_mem(), newset));
    }
    it -> second.erase(it -> second.begin());
    if (it -> second.empty()) huecos.erase(it);
    procesos.insert(make_pair(job.consultar_id(), pos));
    mem.insert(make_pair(pos, job));
}

void Procesador::eliminar_proceso(int n) {
    map<int, int>::const_iterator it1 = procesos.find(n);
    map<int, Proceso>::const_iterator it2 = mem.find(it1 -> second);
    procesos.erase(it1);
    int new_hueco = it2 -> second.consultar_mem();
    int pos_ant;
    if (it2 != mem.begin()) {
        map<int, Proceso>::const_iterator aux = it2;
        --aux;
        pos_ant = aux -> first + aux -> second.consultar_mem();
    }
    else pos_ant = 0;
    int hueco_ant = it2 -> first - pos_ant;
    if (hueco_ant > 0) {
        map<int, set<int>>::iterator aux = huecos.find(hueco_ant);
        aux -> second.erase(pos_ant);
        if (aux -> second.empty()) huecos.erase(aux);
        new_hueco += hueco_ant;
    }
    int hueco_post;
    map<int, Proceso>::const_iterator aux = it2;
    ++aux;
    if (aux != mem.end()) {
        hueco_post = aux -> first;
    }
    else hueco_post = mem_mida;
    int pos_post = it2 -> first + it2 -> second.consultar_mem();
    hueco_post -= pos_post;
    if (hueco_post > 0) {
        map<int, set<int>>::iterator aux = huecos.find(hueco_post);
        aux -> second.erase(pos_post);
        if (aux -> second.empty()) huecos.erase(aux);
        new_hueco += hueco_post;
    }
    map<int, set<int>>::iterator a = huecos.lower_bound(new_hueco);
    if (a != huecos.end() and a -> first == new_hueco) a -> second.insert(pos_ant);
    else {
        set<int> newset;
        newset.insert(newset.end(), pos_ant);
        huecos.insert(a, make_pair(new_hueco, newset));
    }
    mem.erase(it2);
}

// void Procesador::compactar_memoria() {}

void Procesador::avanzar_tiempo(int t) {
    map<int, Proceso>::iterator it = mem.begin();
    while (it != mem.end()) {
        if (it -> second.consultar_t() <= t) {
            procesos.erase(it -> second.consultar_id());
            int new_hueco = it -> second.consultar_mem();
            int pos_ant;
            if (it != mem.begin()) {
                map<int, Proceso>::iterator aux = it;
                --aux;
                pos_ant = aux -> first + aux -> second.consultar_mem();
            }
            else pos_ant = 0;
            int hueco_ant = it -> first - pos_ant;
            if (hueco_ant > 0) {
                map<int, set<int>>::iterator aux = huecos.find(hueco_ant);
                aux -> second.erase(pos_ant);
                if (aux -> second.empty()) huecos.erase(aux);
                new_hueco += hueco_ant;
            }
            int hueco_post;
            map<int, Proceso>::const_iterator aux = it;
            ++aux;
            if (aux != mem.end()) {
                hueco_post = aux -> first;
            }
            else hueco_post = mem_mida;
            int pos_post = it -> first + it -> second.consultar_mem();
            hueco_post -= pos_post;
            if (hueco_post > 0) {
                map<int, set<int>>::iterator aux = huecos.find(hueco_post);
                aux -> second.erase(pos_post);
                if (aux -> second.empty()) huecos.erase(aux);
                new_hueco += hueco_post;
            }
            map<int, set<int>>::iterator n = huecos.lower_bound(new_hueco);
            if (n != huecos.end() and n -> first == new_hueco) n -> second.insert(pos_ant);
            else {
                set<int> newset;
                newset.insert(newset.end(), pos_ant);
                huecos.insert(n, make_pair(new_hueco, newset));
            }
            it = mem.erase(it);
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

bool Procesador::cabe_proceso(const Proceso& job) const {
    return huecos.lower_bound(job.consultar_mem()) != huecos.end();
}

void Procesador::escribir_procesador() const {
    for (map<int, Proceso>::const_iterator it = mem.begin(); it != mem.end(); ++it) {
        cout << it -> first << ' ';
        it -> second.escribir_proceso();
    }
}
