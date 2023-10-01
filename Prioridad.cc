/** @file Prioridad.cc
    @brief Código de la clase Prioridad
*/

#include "Prioridad.hh"

Prioridad::Prioridad() {
    rechazados = 0;
    aceptados = 0;
}

void Prioridad::agregar_proceso(const Proceso& job) {
    procesos_pendientes.insert(procesos_pendientes.end(), job);
}

void Prioridad::eliminar_proceso() {
    procesos_pendientes.erase(procesos_pendientes.begin());
}

void Prioridad::incrementar_aceptados() {
    ++aceptados;
}

void Prioridad::incrementar_rechazados() {
    ++rechazados;
}

bool Prioridad::existe_proceso(int id_proceso) const {
    for (list<Proceso>::const_iterator it = procesos_pendientes.begin(); it != procesos_pendientes.end(); ++it) {
        if (it -> consultar_id() == id_proceso) return true;
    }
    return false;
}

bool Prioridad::vacia() const {
    return procesos_pendientes.empty();
}

Proceso Prioridad::primer() const {
    return *procesos_pendientes.begin();
}

int Prioridad::num_procesos() const {
    return procesos_pendientes.size();
}

void Prioridad::escribir_prioridad() const {
    for (list<Proceso>::const_iterator it = procesos_pendientes.begin(); it != procesos_pendientes.end(); ++it) {
        it -> escribir_proceso();
    }

    cout << aceptados << ' ' << rechazados << endl;
}
