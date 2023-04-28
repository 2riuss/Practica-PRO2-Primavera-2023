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

/**
 * @brief Programa principal de la practica <em>Simulacion de una arquitectura multiprocesador</em>
 */
int main() {
    Cluster c;
    Area_Espera ae;
    ae.leer_prioridades();

    string cmd;
    cin >> cmd;
    while (cmd != "fin") {

        if (cmd == "cc" or cmd == "configurar_cluster") {
            c = Cluster();
            c.leer_cluster();
        }

        else if (cmd == "mc" or cmd == "modificar_cluster") {
            string p;
            cin >> p;
            Cluster aux;
            aux.leer_cluster();

            if (not c.substituir(p, aux)) {
                if (not c.existe_procesador(p)) {
                    cout << "Error: No existe el procesador " << p << endl;
                }
                else if (not c.procesador_vacio(p)) {
                    cout << "Error: El procesador " << p;
                    cout << " tiene procesos en ejecucion" << endl;
                }
                else {
                    cout << "Error: El procesador " << p;
                    cout << " tiene procesadores auxiliares" << endl;
                }
            }
        }

        else if (cmd == "ap" or cmd == "alta_prioridad") {
            string id;
            cin >> id;

            if (not ae.agregar_prioridad(id)) {
                cout << "Error: Prioridad " << id << " ya existente" << endl;
            }
        }

        else if (cmd == "bp" or cmd == "baja_prioridad") {
            string id;
            cin >> id;

            if (ae.eliminar_prioridad(id)) {
                if (not ae.existe_prioridad(id)) {
                    cout << "Error: No existe la prioridad " << id << endl;
                }
                else {
                    cout << "Error: La prioridad " << id;
                    cout << " tiene procesos pendientes" << endl;
                }
            }
        }

        else if (cmd == "ape" or cmd == "alta_proceso_espera") {
            string id;
            cin >> id;
            Proceso job;
            job.leer_proceso();

            if (not ae.agregar_proceso(id, job)) {
                if (not ae.existe_prioridad(id)) {
                    cout << "Error: No existe la prioridad " << id << endl;
                }
                else {
                    cout << "Error: Ya existe un proceso " << job.id();
                    cout << " en la prioridad " << id << endl;
                }
            }
        }

        else if (cmd == "app" or cmd == "alta_proceso_procesador") {
            string p;
            cin >> p;
            Proceso job;
            job.leer_proceso();

            if (not c.agregar_proceso(p, job)) {
                if (not c.existe_procesador(p)) {
                    cout << "Error: No existe el procesador " << p << endl;
                }
                else if (c.existe_proceso(p, job.id())) {
                    cout << "Error: Ya existe un proceso " << job.id();
                    cout << " en el procesador " << p << endl;
                }
                else {
                    cout << "Error: El proceso " << job.id();
                    cout << " no se pude colocar en el procesador ";
                    cout << p << endl;
                }
            }
        }

        else if (cmd == "bpp" or cmd == "baja_proceso_procesador") {
            string p;
            int n;
            cin >> p >> n;

            if (not c.eliminar_proceso(p, n)) {
                if (not c.existe_procesador(p)) {
                    cout << "Error: No existe el procesador " << p << endl;
                }
                else {
                    cout << "Error: No existe el proceso " << n;
                    cout << " en el procesador " << p << endl;
                }
            }
        }

        else if (cmd == "epc" or cmd == "enviar_procesos_cluster") {
            int n;
            cin >> n;

            ae.enviar_procesos_cluster(c, n);
        }

        else if (cmd == "at" or cmd == "avanzar_tiempo") {
            int t;
            cin >> t;

            c.avanzar_tiempo(t);
        }

        else if (cmd == "ipri" or cmd == "imprimir_prioridad") {
            string id;
            cin >> id;

            if (not ae.escribir_prioridad(id)) {
                cout << "Error: No existe la prioridad " << id << endl;
            }
        }

        else if (cmd == "iae" or cmd == "imprimir_area_espera") {
            ae.escribir_area_espera();
        }

        else if (cmd == "ipro" or cmd == "imprimir_procesador") {
            string p;
            cin >> p;

            if (not c.escribir_procesador(p)) {
                cout << "Error: No existe el procesador " << p << endl;
            }
        }

        else if (cmd == "ipc" or cmd == "imprimir_procesadores_cluster") {
            c.escribir_procesadores();
        }

        else if (cmd == "iec" or cmd == "imprimir_estructura_cluster") {
            c.escribir_estructura();
        }

        else if (cmd == "cmp" or cmd == "compactar_memoria_procesador") {
            string p;
            cin >> p;

            if (not c.compactar_memoria(p)) {
                cout << "Error: No existe el procesador " << p << endl;
            }
        }

        else if (cmd == "cmc" or cmd == "compactar_memoria_cluster") {
            c.compactar_memoria();
        }


        cin >> cmd;
    }
}
