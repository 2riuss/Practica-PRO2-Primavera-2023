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
#include <map>
#include <set>
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

    /** @brief Conjuntos de huecos libres en el procesador
     *
     * Los huecos estan designados por su posicion inicial y estan agrupados y ordenados por su tamaño */
    map<int, set<int, greater<int>>> huecos;

    /** @brief Procesos pertenecientes al procesador
     *
     * Ordenados por su posicion inicial */
    map<int, Proceso> pos_proceso;

    /** @brief Posicion inicial de los procesos pertenecientes al procesador
     *
     * Ordenadas por el identificador del proceso al que hacen referencia */
    map<int, int> idProceso_pos;

    /** @brief Tamaño de la memoria del procesador */
    int memory_size;

    /** @brief Cantidad de memoria libre del procesador */
    int free_memory;

    /* Invariante de la representacion
     * - memory_size >= 0
     * - free_memory >= 0
     * - No hay dos procesos con un mismo identificador
     * - Entre los huecos y los procesos no hay dos con la misma posicion inicial y no se superponen
     * - Dado un proceso, su representacion en pos_proceso y idProceso_pos tiene la misma posicion inicial
     * - La suma del tamaño de todos los huecos = free_memory
     * - La suma del tamaño de todos los procesos y todos los huecos = memory_size
     */

    /**
     * @brief Añade un hueco al procesador
     *
     * \pre No hay ningun hueco que empieze en <em>pos</em>
     * \post Se ha añadido un hueco de mida <em>mida</em> que empieza en <em>pos</em> en el P.I.
     * \coste O(log(n))
     */
    void agregar_hueco(int mida, int pos);

    /**
     * @brief Elimina un hueco del procesador
     *
     * \pre Existe un hueco de mida <em>mida</em> que empieza en <em>pos</em>
     * \post Se ha eliminado el hueco de mida <em>mida</em> i que empieza en <em>pos</em> del P.I.
     * \coste O(log(n))
     */
    void eliminar_hueco(int mida, int pos);

    /**
     * @brief Elimina un proceso del procesador y actualiza los huecos
     *
     * \pre <em>it1</em> apunta a un proceso en <em>pos_proceso</em> i <em>it2</em> apunta a la entrada del mismo proceso en <em>idProceso_pos</em>
     * \post Se ha eliminado el proceso apuntado por <em>it1</em> i <em>it2</em> del P.I. y se han actualizado los huecos correspondientes
     * \coste O(log(n))
     */
    void eliminar_proceso_aux(const map<int, Proceso>::const_iterator it1, const map<int, int>::const_iterator it2);

public:
    // Constructoras

    /**
     * @brief Constructora por defecto
     *
     * Se ejecuta por defecto al declarar un procesador
     * \pre <em>Cierto</em>
     * \post El resultado es un procesador pos defecto con 0 unidades de memoria
     * \coste O(1)
     */
    Procesador();


    /**
     * @brief Constructora por defecto
     *
     * \pre <em>Cierto</em>
     * \post El resultado es un procesador con <em>mem</em> unidades de memoria vacio
     * \coste O(1)
     */
    Procesador(int mem);


    // Modificadoras

    /**
     * @brief Añade un proceso al procesador
     *
     * \pre No hay ningun proceso con el mismo identificador que el proceso <em>job</em> en el P.I. y el proceso <em>job</em> cabe en el P.I.
     * \post El proceso <em>job</em> queda añadido al P.I. en el hueco más ajustado con posicion inicial más pequeña
     * \coste O(log(n))
     */
    void agregar_proceso(const Proceso& job);

    /**
     * @brief Elimina un proceso del procesador
     *
     * \pre Existe un proceso con identificador <em>id_proceso</em> en el P.I.
     * \post Se ha eliminado el proceso con identificador <em>id_proceso</em> del P.I.
     * \coste O(log(n))
     */
    void eliminar_proceso(int id_proceso);

    /**
     * @brief Compacta la memoria del procesador
     *
     * \pre <em>Cierto</em>
     * \post Se ha compactado la memoria del P.I.; es decir, se han movido todos los procesos hacia el principio de la memoria del P.I. respetando el orden inicial y sin huecos ni solapamientos
     * \coste O(n_1*log(n) + n_2) tq n = n_1 + n_2 , n_1 = nº procesos a compactar, n_2 = nº procesos ya compactados
     */
    void compactar_memoria();

    /**
     * @brief Simula el avance del tiempo en el procesador
     *
     * Se eliminan todos los procesos activos que hayan acabado en ese intervalo de tiempo, i la ejecucion de todos los procesos han progresado t unidades de tiempo
     * \pre <em>Cierto</em>
     * \post El P.I. se ha actualizado como si hubieran pasado <em>t</em> unidades de tiempo
     * \coste O(n_1*log(n) + n_2) tq n = n_1 + n_2 , n_1 = nº procesos con tiempo menor/igual a t, n_2 = nº procesos con tiempo mayor a t
     */
    void avanzar_tiempo(int t);


    // Consultoras

    /**
     * @brief Indica si el procesador contiene el proceso
     *
     * \pre <em>Cierto</em>
     * \post El resultado indica si el P.I. contiene algun proceso con identificador <em>n</em>
     * \coste O(log(n))
     */
    bool existe_proceso(int id_proceso) const;

    /**
     * @brief Indica si el procesador contiene procesos en ejecucion
     *
     * \pre <em>Cierto</em>
     * \post El resultado indica si el P.I. contiene procesos
     * \coste O(1)
     */
    bool vacio() const;

    /**
     * @brief Consultora de la cantidad de memoria libre del procesador
     *
     * \pre <em>Cierto</em>
     * \post El resultado es el tamaño de la memoria libre del P.I.
     * \coste O(1)
     */
    int free_mem() const;

    /**
     * @brief Indica si el proceso cabe en el procesador
     *
     * \pre No existe ningun proceso con el mismo identificador que el proceso <em>job</em> en el P.I.
     * \post El resultado indica si el proceso <em>job</em> cabe en el P.I.
     * \coste O(log(n))
     */
    bool cabe_proceso(const Proceso& job) const;

    /**
     * @brief Consultora del tamaño del hueco mas ajustado a un proceso
     *
     * \pre No existe ningun proceso con el mismo identificador que el proceso <em>job</em> en el P.I. y el proceso <em>job</em> cabe en el P.I.
     * \post El resultado es el tamaño del hueco mas ajustado al proceso <em>job</em>
     * \coste O(log(n))
     */
    int hueco_proceso(const Proceso& job) const;

    int num_procesos() const;


    // Lectura y escritura

    /**
     * @brief Escribe un procesador
     *
     * \pre <em>Cierto</em>
     * \post Se ha escrito en el canal estandar de salida los procesos del P.I. por orden de posicion de memoriala, escriviendo la posicion y el resto de datos de cada proceso
     * \coste O(n)
     */
    void escribir_procesador() const;
};

#endif
