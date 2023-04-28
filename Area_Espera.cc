#include "Area_Espera.hh"

Area_Espera::Area_Espera() {
    map<string, Prioridad> ae;
}

bool Area_Espera::agregar_proceso(const string& id, const Proceso& job) {

}

bool Area_Espera::agregar_prioridad(const string& id) {

}

bool Area_Espera::eliminar_prioridad(const string& id) {

}

bool Area_Espera::existe_prioridad(const string& id) const {
    return ae.find(id) != ae.end();
}

void Area_Espera::leer_prioridades() {

}

bool Area_Espera::escribir_prioridad(const string& id) const {

}

void Area_Espera::escribir_area_espera() const {
    for (map<stirng, Prioridad> const_iterator it = ae.begin(); it != ae.end(); ++it) {
        cout << it -> first << endl;
        it -> second.escribir_prioridad();
    }
}

void Area_Espera::enviar_procesos_cluster(Cluster& c, int n) {}
