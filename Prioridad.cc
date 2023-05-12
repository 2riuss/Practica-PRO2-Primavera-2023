/** @file Prioridad.cc
    @brief Código de la clase Prioridad
*/

#include "Prioridad.hh"

Prioridad::Prioridad() {
    rechazados = 0;
    aceptados = 0;
}

void Prioridad::agregar_proceso(const Proceso& job) {
    cjt.insert(cjt.end(), job);
}

void Prioridad::eliminar_proceso() {
    cjt.erase(cjt.begin());
}

void Prioridad::incrementar_aceptados() {
    ++aceptados;
}

void Prioridad::incrementar_rechazados() {
    ++rechazados;
}

bool Prioridad::existe_proceso(int n) const {
    for (list<Proceso>::const_iterator it = cjt.begin(); it != cjt.end(); ++it) {
        if (it -> consultar_id() == n) return true;
    }
    return false;
}

bool Prioridad::vacia() const {
    return cjt.empty();
}

Proceso Prioridad::primer() const {
    return *cjt.begin();
}

Proceso Prioridad::ultim() const {
    list<Proceso>::const_iterator it = cjt.end();
    --it;
    return *it;
}

void Prioridad::escribir_prioridad() const {
    for (list<Proceso>::const_iterator it = cjt.begin(); it != cjt.end(); ++it) {
        it -> escribir_proceso();
    }

    cout << aceptados << ' ' << rechazados << endl;
}
