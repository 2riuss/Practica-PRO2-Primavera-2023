/**
 * @mainpage Pràctica Bernat Dosrius Lleonart: Simulando una arquitectura multiprocesador
 *
 * En esta pràctica se construye un programa modular que ofrece un menú de opciones para gestionar una arquitectura multiprocesador. Se introducen las clases Cluster, Procesador, Area_Espera, Prioridad y Proceso.
 *
 * Sólo se documentan elementos públicos.
 */

/**
 * @file program.cc
 * @brief Programa principal de la practica <em>Simulacion de una arquitectura multiprocesador</em>
 */

#include "Cluster.hh"
#include "Area_Espera.hh"
#include "Proceso.hh"

#ifndef NO_DIAGRAM
#include <iostream>
#endif

using namespace std;

/**
 * @brief Programa principal de la practica <em>Simulacion de una arquitectura multiprocesador</em>
 */
int main() {
    Cluster c;
    c.leer_cluster();
    Area_Espera ae;
    ae.leer_prioridades();

    string cmd;
    cin >> cmd;
    while (cmd != "fin") {

        if (cmd == "cc" or cmd == "configurar_cluster") {
            c.clear();
            c.leer_cluster();
            cout << '#' << cmd << endl;
        }
/*
        else if (cmd == "mc" or cmd == "modificar_cluster") {
            string p;
            cin >> p;
            Cluster aux;
            aux.leer_cluster();
            cout << '#' << cmd << ' ' << p << endl;

            if (not c.existe_procesador(p)) {
                cout << "error: no existe procesador" << endl;
            }
            else if (not c.procesador_vacio(p)) {
                cout << "error: procesador con procesos en ejecucion" << endl;
            }
            else if (c.procesadores_auxiliares(p)){
                cout << "error: procesador con procesadores auxiliares" << endl;
            }

            else c.substituir(p, aux);
        }
*/
        else if (cmd == "ap" or cmd == "alta_prioridad") {
            string id;
            cin >> id;
            cout << '#' << cmd << ' ' << id << endl;

            if (ae.existe_prioridad(id)) {
                cout << "error: ya existe prioridad" << endl;
            }

            else ae.agregar_prioridad(id);
        }

        else if (cmd == "bp" or cmd == "baja_prioridad") {
            string id;
            cin >> id;
            cout << '#' << cmd << ' ' << id << endl;

            if (not ae.existe_prioridad(id)) {
                cout << "error: no existe prioridad" << endl;
            }
            else if (not ae.prioridad_vacia(id)) {
                cout << "error: prioridad con procesos" << endl;
            }

            else ae.eliminar_prioridad(id);
        }

        else if (cmd == "ape" or cmd == "alta_proceso_espera") {
            string id;
            cin >> id;
            Proceso job;
            job.leer_proceso();
            cout << '#' << cmd << ' ' << id << ' ' << job.consultar_id() << endl;

            if (not ae.existe_prioridad(id)) {
                cout << "error: no existe prioridad" << endl;
            }
            else if (ae.existe_proceso(id, job.consultar_id())) {
                cout << "error: ya existe proceso" << endl;
            }

            else ae.agregar_proceso(id, job);
        }

        else if (cmd == "app" or cmd == "alta_proceso_procesador") {
            string p;
            cin >> p;
            Proceso job;
            job.leer_proceso();
            cout << '#' << cmd << ' ' << p << ' ' << job.consultar_id() << endl;

            if (not c.existe_procesador(p)) {
                cout << "error: no existe procesador" << endl;
            }
            else if (c.existe_proceso(p, job.consultar_id())) {
                cout << "error: ya existe proceso" << endl;
            }
            else if (not c.cabe_proceso(p, job)) {
                cout << "error: no cabe proceso" << endl;
            }

            else c.agregar_proceso(p, job);
        }

        else if (cmd == "bpp" or cmd == "baja_proceso_procesador") {
            string p;
            int n;
            cin >> p >> n;
            cout << '#' << cmd << ' ' << p << ' ' << n << endl;

            if (not c.existe_procesador(p)) {
                cout << "error: no existe procesador" << endl;
            }
            else if (not c.existe_proceso(p, n)) {
                cout << "error: no existe proceso" << endl;
            }


            else c.eliminar_proceso(p, n);
        }
/*
        else if (cmd == "epc" or cmd == "enviar_procesos_cluster") {
            int n;
            cin >> n;
            cout << '#' << cmd << ' ' << n << endl;

            ae.enviar_procesos_cluster(c, n);
        }
*/
        else if (cmd == "at" or cmd == "avanzar_tiempo") {
            int t;
            cin >> t;
            cout << '#' << cmd << ' ' << t << endl;

            c.avanzar_tiempo(t);
        }

        else if (cmd == "ipri" or cmd == "imprimir_prioridad") {
            string id;
            cin >> id;
            cout << '#' << cmd << ' ' << id << endl;

            if (not ae.existe_prioridad(id)) {
                cout << "error: no existe prioridad" << endl;
            }

            else ae.escribir_prioridad(id);
        }

        else if (cmd == "iae" or cmd == "imprimir_area_espera") {
            cout << '#' << cmd << endl;

            ae.escribir_area_espera();
        }

        else if (cmd == "ipro" or cmd == "imprimir_procesador") {
            string p;
            cin >> p;
            cout << '#' << cmd << ' ' << p << endl;

            if (not c.existe_procesador(p)) {
                cout << "error: no existe procesador" << endl;
            }

            else c.escribir_procesador(p);
        }

        else if (cmd == "ipc" or cmd == "imprimir_procesadores_cluster") {
            cout << '#' << cmd << endl;

            c.escribir_procesadores();
        }

        else if (cmd == "iec" or cmd == "imprimir_estructura_cluster") {
            cout << '#' << cmd << endl;

            c.escribir_estructura();
        }
/*
        else if (cmd == "cmp" or cmd == "compactar_memoria_procesador") {
            string p;
            cin >> p;
            cout << '#' << cmd << ' ' << p << endl;

            if (not c.existe_procesador(p)) {
                cout << "error: no existe procesador" << endl;
            }

            else c.compactar_memoria_procesador(p);
        }

        else if (cmd == "cmc" or cmd == "compactar_memoria_cluster") {
            cout << '#' << cmd << endl;

            c.compactar_memoria();
        }
*/

        cin >> cmd;
    }
}
