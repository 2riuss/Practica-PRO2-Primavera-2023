Prioridad::Prioridad() {
    queue cjt;
    int rechazados = 0;
    int aceptados = 0;
}

void Prioridad::agregar_proceso(const Proceso& job) {
    cjt.push(job);
}

void Prioridad::eliminar_proceso() {
    cjt.pop();
}

void Prioridad::incrementar_aceptados() {
    ++aceptados;
}

void Prioridad::incrementar_rechazados() {
    ++rechazados;
}

bool Prioridad::existe_proceso(int n) const {
    queue<int> aux = cjt;
    bool found = false;

    while (not found and not aux.empty()) {
        found = aux.top().id == n;
        aux.pop();
    }

    return found;
}

bool Prioridad::vacio() const {
    return cjt.empty();
}

Proceso Prioridad::proceso() const {
    return cjt.top();
}

void Prioridad::escribir_prioridad() const {
    queue<int> aux = cjt;
    while (not aux.empty()) {
        aux.top().escribir_proceso();
        aux.pop()
    }
    cout << aceptados << ' ' << rechazados << endl;
}
