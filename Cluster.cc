#include "Cluster.hh"

Cluster::Cluster() {}

void Cluster::agregar_proceso(const string& id, const Proceso& job) {
    procesadores.find(id) -> second.agregar_proceso(job);
}

void Cluster::eliminar_proceso(const string& id, int n) {
    procesadores.find(id) -> second.eliminar_proceso(n);
}

// void Cluster::agregar_proceso(const Proceso& job) {}

// void Cluster::substituir(const string& id, const Cluster& c) {}

// void Cluster::compactar_memoria_procesador(const string& id) {}

// void Cluster::compactar_memoria() {}

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
    return procesadores.find(id) == procesadores.end();
}

bool Cluster::existe_proceso(const string& id, int n) const {
    return procesadores.find(id) -> second.existe_proceso(n);
}

bool Cluster::procesador_vacio(const string& id) const {
    return procesadores.find(id) -> second.vacio();
}

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

void Cluster::leer_cluster_aux(map<string, Procesador>& proc, BinTree<string>& e) {
    string id;
    cin >> id;

    if (id != "*") {
        int mem;
        cin >> mem;
        proc.insert(make_pair(id, Procesador(mem)));

        BinTree<string> izq, der;
        leer_cluster_aux(proc, izq);
        leer_cluster_aux(proc, der);
        e = BinTree<string>(id, izq, der);
    }
}

void Cluster::leer_cluster() {
    leer_cluster_aux(procesadores, estr);
}

void Cluster::escribir_procesador(const string& id) const {
    return procesadores.find(id) -> second.escribir_procesador();
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
