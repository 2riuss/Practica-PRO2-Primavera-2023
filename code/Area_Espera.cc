/** @file Area_Espera.cc
    @brief Código de la clase Area_Espera
*/

#include "Area_Espera.hh"

Area_Espera::Area_Espera() {}

void Area_Espera::agregar_proceso(const string& id_prioridad, const Proceso& job) {
    cjt_prioridades.find(id_prioridad) -> second.agregar_proceso(job);
}

void Area_Espera::agregar_prioridad(const string& id_prioridad) {
    cjt_prioridades.insert(make_pair(id_prioridad, Prioridad()));
}

void Area_Espera::eliminar_prioridad(const string& id_prioridad) {
    cjt_prioridades.erase(id_prioridad);
}

bool Area_Espera::existe_prioridad(const string& id_prioridad) const {
    return cjt_prioridades.find(id_prioridad) != cjt_prioridades.end();
}

bool Area_Espera::existe_proceso(const string& id_prioridad, int id_proceso) const {
    return cjt_prioridades.find(id_prioridad) -> second.existe_proceso(id_proceso);
}

bool Area_Espera::prioridad_vacia(const string& id_prioridad) const {
    return cjt_prioridades.find(id_prioridad) -> second.vacia();
}

void Area_Espera::leer_prioridades() {
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        string id;
        cin >> id;
        cjt_prioridades.insert(make_pair(id, Prioridad()));
    }
}

void Area_Espera::escribir_prioridad(const string& id_prioridad) const {
    cjt_prioridades.find(id_prioridad) -> second.escribir_prioridad();
}

void Area_Espera::escribir_area_espera() const {
    for (map<string, Prioridad>::const_iterator it = cjt_prioridades.begin(); it != cjt_prioridades.end(); ++it) {
        cout << it -> first << endl;
        it -> second.escribir_prioridad();
    }
}

void Area_Espera::enviar_procesos_cluster(Cluster& c, int n) {
    map<string, Prioridad>::iterator it = cjt_prioridades.begin();
    int procesos_prioridad_no_tratados = it -> second.num_procesos();

    while (n > 0 and it != cjt_prioridades.end()) {

        if (procesos_prioridad_no_tratados > 0) {
            Proceso job = it -> second.primer();
            if (c.agregar_proceso(job)) {
                it -> second.incrementar_aceptados();
                it -> second.eliminar_proceso();
                --n;
            }
            else {
                it -> second.incrementar_rechazados();
                it -> second.eliminar_proceso();
                it -> second.agregar_proceso(job);
            }

            --procesos_prioridad_no_tratados;
        }

        else {
            ++it;
            if (it != cjt_prioridades.end()) {
                procesos_prioridad_no_tratados = it -> second.num_procesos();
            }
        }
    }
}
