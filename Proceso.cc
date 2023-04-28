´Proceso::Proceso() {
    int id;
    int t;
    int mem;
}

int Proceso::id() const {
    return id;
}

int Proceso::t() const {
    return t;
}

int Proceso::mem() const {
    return mem;
}

void Proceso::avanzar_tiempo(int t) {
    this -> t -= t;
}

void Proceso::leer_proceso() {
    cin >> id >> mem >> t;
}

void Proceso::escribir_proceso() const {
    cout << id << mem << t << endl;;
}
