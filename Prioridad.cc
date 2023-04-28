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
    list<Proceso>::const_iterator it = cjt.begin();
    bool found = false;

    while (not found and it != cjt.end()) {
        found = it -> consultar_id() == n;
        ++it;
    }

    return found;
}

bool Prioridad::vacia() const {
    return cjt.empty();
}

Proceso Prioridad::proceso() const {
    return *cjt.begin();
}

void Prioridad::escribir_prioridad() const {
    for (list<Proceso>::const_iterator it = cjt.begin(); it != cjt.end(); ++it) {
        it -> escribir_proceso();
    }

    cout << aceptados << ' ' << rechazados << endl;
}
