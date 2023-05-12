/** @file Cluster.cc
    @brief Código de la clase Cluster
*/

#include "Cluster.hh"

Cluster::Cluster() {}

void Cluster::agregar_proceso(const string& id, const Proceso& job) {
    procesadores.find(id) -> second.agregar_proceso(job);
}

void Cluster::eliminar_proceso(const string& id, int n) {
    procesadores.find(id) -> second.eliminar_proceso(n);
}

// esta malament pq proximitat a la arrel i en cas empat esquerra
void Cluster::agregar_proceso_aux(const Proceso& job, const map<string, Procesador>& proc, const BinTree<string>& e, bool& succes, string& candidat, int& min_hueco, int& free_mem) {
    map<string, Procesador>::const_iterator it = proc.find(e.value());
    if (it -> second.cabe_proceso(job)) {
        int aux = it -> second.hueco_proceso(job);
        if (min_hueco == -1 or aux <= min_hueco) {
            int aux2 = it -> second.free_mem();
            if (min_hueco == -1 or aux < min_hueco or free_mem < aux2) {
                min_hueco = aux;
                candidat = it -> first;
                succes = true;
                free_mem = aux2;
            }
        }
    }
    if (min_hueco != job.consultar_mem() and not e.left().empty()) agregar_proceso_aux(job, proc, e.left(), succes, candidat, min_hueco, free_mem);
    if (min_hueco != job.consultar_mem() and not e.right().empty()) agregar_proceso_aux(job, proc, e.right(), succes, candidat, min_hueco, free_mem);
}

bool Cluster::agregar_proceso(const Proceso& job) {
    bool b = false;
    string pro;
    int a1, a2;
    a1 = a2 = -1;
    agregar_proceso_aux(job, procesadores, estr, b, pro, a1, a2);
    if (b) procesadores.find(pro) -> second.agregar_proceso(job);
    return b;
}

BinTree<string> Cluster::substituir_aux(const string& id, BinTree<string>& e1, const BinTree<string>& e2) {
    if (e1.empty()) return e1;
    if (e1.value() == id) return e2;
    BinTree<string> l = e1.left();
    BinTree<string> r = e1.right();
    return BinTree<string>(e1.value(), substituir_aux(id, l, e2), substituir_aux(id, r, e2));
}

void Cluster::substituir(const string& id, const Cluster& c) {
    procesadores.erase(id);
    for (map<string, Procesador>::const_iterator it = c.procesadores.begin(); it != c.procesadores.end(); ++it) {
        procesadores.insert(*it);
    }
    estr = substituir_aux(id, estr, c.estr);
}

void Cluster::compactar_memoria_procesador(const string& id) {
    procesadores.find(id) -> second.compactar_memoria();
}

void Cluster::compactar_memoria() {
    for (map<string, Procesador>::iterator it = procesadores.begin(); it != procesadores.end(); ++it) {
        it -> second.compactar_memoria();
    }
}

void Cluster::avanzar_tiempo(int t) {
    for (map<string, Procesador>::iterator it = procesadores.begin(); it != procesadores.end(); ++it) {
        it -> second.avanzar_tiempo(t);
    }
}

void Cluster::clear() {
    procesadores.clear();
    estr = BinTree<string>();
}

bool Cluster::existe_procesador(const string& id) const {
    return procesadores.find(id) != procesadores.end();
}

bool Cluster::existe_proceso(const string& id, int n) const {
    return procesadores.find(id) -> second.existe_proceso(n);
}

bool Cluster::procesador_vacio(const string& id) const {
    return procesadores.find(id) -> second.vacio();
}

// si implemento un found a l'arbre aquesta canvia
// si fas un bool s'elimina
bool Cluster::procesadores_auxiliares_aux(const BinTree<string>& e, const string& id) {
    if (e.empty()) return false;
    if (e.value() == id) return not e.right().empty() or not e.left().empty();
    return procesadores_auxiliares_aux(e.right(), id) or procesadores_auxiliares_aux(e.left(), id);
}

bool Cluster::procesadores_auxiliares(const string& id) const {
    return procesadores_auxiliares_aux(estr, id);
}

bool Cluster::cabe_proceso(const string& p, const Proceso& job) const {
    return procesadores.find(p) -> second.cabe_proceso(job);
}

void Cluster::leer_cluster_aux(map<string, Procesador>& procesadores, BinTree<string>& e) {
    string id;
    cin >> id;

    if (id != "*") {
        int mem;
        cin >> mem;
        procesadores.insert(make_pair(id, Procesador(mem)));

        BinTree<string> izq, der;
        leer_cluster_aux(procesadores, izq);
        leer_cluster_aux(procesadores, der);
        e = BinTree<string>(id, izq, der);
    }
}

void Cluster::leer_cluster() {
    leer_cluster_aux(procesadores, estr);
}

void Cluster::escribir_procesador(const string& id) const {
    procesadores.find(id) -> second.escribir_procesador();
}

void Cluster::escribir_procesadores() const {
    for (map<string, Procesador>::const_iterator it = procesadores.begin(); it != procesadores.end(); ++it) {
        cout << it -> first << endl;
        it -> second.escribir_procesador();
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
    escribir_estructura_aux(estr);
    cout << endl;
}
