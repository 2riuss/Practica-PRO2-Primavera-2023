/** @file Area_Espera.cc
    @brief Código de la clase Area_Espera
*/

#include "Area_Espera.hh"

Area_Espera::Area_Espera() {}

void Area_Espera::agregar_proceso(const string& id, const Proceso& job) {
    ae.find(id) -> second.agregar_proceso(job);
}

void Area_Espera::agregar_prioridad(const string& id) {
    ae.insert(make_pair(id, Prioridad()));
}

void Area_Espera::eliminar_prioridad(const string& id) {
    ae.erase(id);
}

bool Area_Espera::existe_prioridad(const string& id) const {
    return ae.find(id) != ae.end();
}

bool Area_Espera::existe_proceso(const string& id, int n) const {
    return ae.find(id) -> second.existe_proceso(n);
}

bool Area_Espera::prioridad_vacia(const string& id) const {
    return ae.find(id) -> second.vacia();
}

void Area_Espera::leer_prioridades() {
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        string id;
        cin >> id;
        ae.insert(make_pair(id, Prioridad()));
    }
}

void Area_Espera::escribir_prioridad(const string& id) const {
    ae.find(id) -> second.escribir_prioridad();
}

void Area_Espera::escribir_area_espera() const {
    for (map<string, Prioridad>::const_iterator it = ae.begin(); it != ae.end(); ++it) {
        cout << it -> first << endl;
        it -> second.escribir_prioridad();
    }
}

// void Area_Espera::enviar_procesos_cluster(Cluster& c, int n) {}
