/**
 * @file Procesador.hh
 * @brief Especificacion de la clase Procesador
 */

#ifndef PROCESADOR_HH
#define PROCESADOR_HH

#include "Proceso.hh"

#ifndef NO_DIAGRAM
#include <iostream>
#include <string>
#include <vector>
#include <map>
#endif

using namespace std;

/**
 * @class Procesador
 * @brief Representa un procesador
 *
 * Representa un procesador el qual dispone de una memoria en la que guardará y ejecutará los procesos.
 *
 * El procesador puede añadir, eliminar y reorganizar sus procesos
 */
class Procesador {
private:
    map<int, Proceso> procesos;
    vector<map<int, Proceso>::iterator> mem;

    /* Invariante de la representacion
     *
     */

    int posicion_proceso(int n) const;
    int posicion_hueco(int pmem) const;


public:
    // Constructoras

    /**
     * @brief Constructora por defecto
     *
     * Se ejecuta por defecto al declarar un procesador
     * \pre <em>Cierto</em>
     * \post El resultado es un procesador por defecto
     */
    Procesador();


    /**
     * @brief Constructora por defecto
     *
     * \pre <em>Cierto</em>
     * \post El resultado es un procesador con <em>mem</em> unidades de memoria vacio
     */
    Procesador(int mem);


    // Modificadoras

    /**
     * @brief Añade un proceso al procesador
     *
     * \pre No hay ningun proceso con el mismo identificador que el proceso <em>job</em> en el P.I. y el proceso <em>job</em> cabe en el P.I.
     * \post El proceso <em>job</em> queda añadido al P.I. en el hueco más ajustado con posicion inicial más pequeña
     */
    void agregar_proceso(const Proceso& job);

    /**
     * @brief Elimina un proceso del procesador
     *
     * \pre Existe un proceso con identificacion <em>n</em> en el P.I.
     * \post Se ha eliminado el proceso con identificacion <em>n</em> del P.I.
     */
    void eliminar_proceso(int n);

    /**
     * @brief Compacta la memoria del procesador
     *
     * \pre <em>Cierto</em>
     * \post Se ha compactado la memoria del P.I.; es decir, se han movido todos los procesos hacia el principio de la memoria del P.I. respetando el orden inicial y sin huecos ni solapamientos
     */
    void compactar_memoria();

    /**
     * @brief Simula el avance del tiempo en el procesador
     *
     * Se eliminan todos los procesos activos que hayan acabado en ese intervalo de tiempo, i la ejecucion de todos los procesos han progresado t unidades de tiempo
     * \pre <em>Cierto</em>
     * \post El P.I. se ha actualizado como si hubieran pasado <em>t</em> unidades de tiempo
     */
    void avanzar_tiempo(int t);


    // Consultoras

    /**
     * @brief Indica si el procesador contiene el proceso
     *
     * \pre <em>Cierto</em>
     * \post El resultado indica si el P.I. contiene algun proceso con identificacion <em>n</em>
     */
    bool existe_proceso(int n) const;

    /**
     * @brief Indica si el procesador contiene procesos en ejecucion
     *
     * \pre <em>Cierto</em>
     * \post El resultado indica si el P.I. contiene procesos
     */
    bool vacio() const;

    /**
     * @brief Indica si el proceso cabe en el procesador
     *
     * \pre No existe ningun proceso con la misma identificacion que el proceso <em>job</em> en el P.I.
     * \post El resultado indica si el proceso <em>job</em> cabe en el P.I.
     */
    bool cabe_proceso(const Proceso& job) const;


    // Lectura y escritura

    /**
     * @brief Escribe un procesador
     *
     * \pre <em>Cierto</em>
     * \post Se ha escrito en el canal estandar de salida los procesos del P.I. por orden de posicion de memoriala, escriviendo la posicion y el resto de datos de cada proceso
     */
    void escribir_procesador() const;
};

#endif
