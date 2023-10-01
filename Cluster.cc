/** @file Cluster.cc
    @brief Código de la clase Cluster
*/

#include "Cluster.hh"

Cluster::Cluster() {}

void Cluster::agregar_proceso(const string& id_procesador, const Proceso& job) {
    cjt_procesadores.find(id_procesador) -> second.second.agregar_proceso(job);
}

void Cluster::eliminar_proceso(const string& id_procesador, int id_proceso) {
    cjt_procesadores.find(id_procesador) -> second.second.eliminar_proceso(id_proceso);
}

bool Cluster::agregar_proceso(const Proceso& job) {
    string candidat_id;
    int candidat_hueco = -1;
    int candidat_free_mem = -1;
    queue<BinTree<string>> cola;
    if (not estructura.empty()) cola.push(estructura);

    while (candidat_hueco != job.consultar_mem() and not cola.empty()) {
        map<string, pair<bool, Procesador>>::const_iterator it = cjt_procesadores.find(cola.front().value());
        if (not it -> second.second.existe_proceso(job.consultar_id()) and it -> second.second.cabe_proceso(job)) {
            int hueco = it -> second.second.hueco_proceso(job);
            if (candidat_hueco == -1 or hueco <= candidat_hueco) {
                int free_mem = it -> second.second.free_mem();
                if (candidat_hueco == -1 or hueco < candidat_hueco or candidat_free_mem < free_mem) {
                    candidat_id = it -> first;
                    candidat_hueco = hueco;
                    candidat_free_mem = free_mem;
                }
            }
        }

        if (not cola.front().left().empty()) cola.push(cola.front().left());
        if (not cola.front().right().empty()) cola.push(cola.front().right());
        cola.pop();
    }

    if (candidat_hueco != -1) cjt_procesadores.find(candidat_id) -> second.second.agregar_proceso(job);
    return candidat_hueco != -1;
}

BinTree<string> Cluster::substituir_aux(const string& id_procesador, const BinTree<string>& e1, const BinTree<string>& e2) {
    if (e1.empty()) return e1;
    if (e1.value() == id_procesador) return e2;
    BinTree<string> l = e1.left();
    BinTree<string> r = e1.right();
    return BinTree<string>(e1.value(), substituir_aux(id_procesador, l, e2), substituir_aux(id_procesador, r, e2));
}

void Cluster::substituir(const string& id_procesador, const Cluster& c) {
    cjt_procesadores.erase(id_procesador);
    for (map<string, pair<bool, Procesador>>::const_iterator it = c.cjt_procesadores.begin(); it != c.cjt_procesadores.end(); ++it) {
        cjt_procesadores.insert(*it);
    }
    estructura = substituir_aux(id_procesador, estructura, c.estructura);
}

void Cluster::compactar_memoria_procesador(const string& id_procesador) {
    cjt_procesadores.find(id_procesador) -> second.second.compactar_memoria();
}

void Cluster::compactar_memoria() {
    for (map<string, pair<bool, Procesador>>::iterator it = cjt_procesadores.begin(); it != cjt_procesadores.end(); ++it) {
        it -> second.second.compactar_memoria();
    }
}

void Cluster::avanzar_tiempo(int t) {
    for (map<string, pair<bool, Procesador>>::iterator it = cjt_procesadores.begin(); it != cjt_procesadores.end(); ++it) {
        it -> second.second.avanzar_tiempo(t);
    }
}

void Cluster::clear() {
    cjt_procesadores.clear();
    estructura = BinTree<string>();
}

pair<int, int> Cluster::eliminar_subarbol(map<string, pair<bool, Procesador>>& proc, BinTree<string>& e) {
    if (e.empty()) return make_pair(0, 0);
    map<string, pair<bool, Procesador>>::const_iterator it = proc.find(e.value());

    BinTree<string> l = e.left();
    BinTree<string> r = e.right();
    pair<int, int> a = eliminar_subarbol(proc, l);
    pair<int, int> b = eliminar_subarbol(proc, r);
    int n = it -> second.second.num_procesos();

    e = BinTree<string>();
    proc.erase(it);
    return make_pair(1 + a.first + b.first, n + a.second + b.second);
}

pair<int, int> Cluster::podar_aux(const string& id, map<string, pair<bool, Procesador>>& proc, BinTree<string>& e) {
    if (e.empty()) return make_pair(0, 0);
    if (e.value() == id) return eliminar_subarbol(proc, e);
    if ((not e.left().empty() and e.left().value() == id and e.right().empty()) or (e.left().empty() and not e.right().empty() and e.right().value() == id)) {
        proc.find(e.value()) -> second.first = false;
    }
    BinTree<string> l = e.left();
    BinTree<string> r = e.right();
    pair<int, int> a = podar_aux(id, proc, l);
    pair<int, int> b = podar_aux(id, proc, r);
    e = BinTree<string>(e.value(), l, r);
    return make_pair(a.first + b.first, a.second + b.second);
}

pair<int, int> Cluster::podar(const string& id_procesador) {
    return podar_aux(id_procesador, cjt_procesadores, estructura);
}

bool Cluster::existe_procesador(const string& id_procesador) const {
    return cjt_procesadores.find(id_procesador) != cjt_procesadores.end();
}

bool Cluster::existe_proceso(const string& id_procesador, int id_proceso) const {
    return cjt_procesadores.find(id_procesador) -> second.second.existe_proceso(id_proceso);
}

bool Cluster::procesador_vacio(const string& id_procesador) const {
    return cjt_procesadores.find(id_procesador) -> second.second.vacio();
}

bool Cluster::procesadores_auxiliares(const string& id_procesador) const {
    return cjt_procesadores.find(id_procesador) -> second.first;
}

bool Cluster::cabe_proceso(const string& id_procesador, const Proceso& job) const {
    return cjt_procesadores.find(id_procesador) -> second.second.cabe_proceso(job);
}

bool Cluster::primer_procesador(const string& id_procesador) const {
    return estructura.value() == id_procesador;
}

void Cluster::leer_cluster_aux(map<string, pair<bool, Procesador>>& cjt_pro, BinTree<string>& e) {
    string id;
    cin >> id;

    if (id != "*") {
        int mem;
        cin >> mem;

        BinTree<string> izq, der;
        leer_cluster_aux(cjt_pro, izq);
        leer_cluster_aux(cjt_pro, der);

        cjt_pro.insert(make_pair(id, make_pair(not izq.empty() or not der.empty(), Procesador(mem))));
        e = BinTree<string>(id, izq, der);
    }
}

void Cluster::leer_cluster() {
    leer_cluster_aux(cjt_procesadores, estructura);
}

void Cluster::escribir_procesador(const string& id) const {
    cjt_procesadores.find(id) -> second.second.escribir_procesador();
}

void Cluster::escribir_procesadores() const {
    for (map<string, pair<bool, Procesador>>::const_iterator it = cjt_procesadores.begin(); it != cjt_procesadores.end(); ++it) {
        cout << it -> first << endl;
        it -> second.second.escribir_procesador();
    }
}

void Cluster::escribir_estructura_aux(const BinTree<string>& e) {
    if (not e.empty()) {
        cout << '(' << e.value();
        escribir_estructura_aux(e.left());
        escribir_estructura_aux(e.right());
        cout << ')';
    }
    else cout << ' ';
}

void Cluster::escribir_estructura() const {
    escribir_estructura_aux(estructura);
    cout << endl;
}
