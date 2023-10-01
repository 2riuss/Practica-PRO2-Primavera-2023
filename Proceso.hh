/**
 * @file Proceso.hh
 * @brief Especificacion de la clase Proceso
 */

#ifndef PROCESO_HH
#define PROCESO_HH

#ifndef NO_DIAGRAM
#include <iostream>
#endif

using namespace std;

/**
 * @class Proceso
 * @brief Representa un proceso
 *
 * Representa un proceso que consiste en su identificador, la cantidad de memoria estimada que va a necesitar para ejecutarse y el tiempo estimado de ejecución
 */
class Proceso {
private:

    /** @brief Identificador del proceso */
    int id;

    /** @brief Tiempo estimado de ejecucion del proceso */
    int t;

    /** @brief Memoria necesaria estimada para ejecutar el proceso */
    int mem;

    /* invariantes de la representación:
     * - id és un entero >= 0 si el proceso esta inicializado
     * - t és un entero > 0 si el proceso esta inicializado
     * - mem és un entero > 0 si el proceso esta inicializado
     */

public:
    // Constructoras

    /**
     * @brief Constructora por defecto
     *
     * Se ejecuta por defecto al declarar un proceso
     * \pre <em>Cierto</em>
     * \post El resultado es un proceso sin inicializar
     * \coste O(1)
     */
    Proceso();


    // Modificadoras

    /**
     * @brief Simula el avance del tiempo en el proceso
     *
     * La ejecucion ha progresado t unidades de tiempo
     * \pre El P.I. esta inicializado y el tipempo estimado del P.I. es estrictamente mayor que <em>t</em>
     * \post El P.I. se ha actualizado como si hubieran pasado <em>t</em> unidades de tiempo
     * \coste O(1)
     */
    void avanzar_tiempo(int t);


    // Consultoras

    /**
     * @brief Consultora del identificador
     *
     * \pre El P.I. esta inicializado
     * \post El resultado es el identificador del P.I.
     * \coste O(1)
     */
    int consultar_id() const;

    /**
     * @brief Consultora del tiempo estimado
     *
     * \pre El P.I. esta inicializado
     * \post El resultado es el tiempo estimado del P.I.
     * \coste O(1)
     */
    int consultar_t() const;

    /**
     * @brief Consultora de la memoria estimada
     *
     * \pre El P.I. esta inicializado
     * \post El resultado es la memoria estimada del P.I.
     * \coste O(1)
     */
    int consultar_mem() const;


    // Lectura y escritura

    /**
     * @brief Lee un proceso
     *
     * \pre El P.I. esta sin inicializar y estan preparados en el canal estandar de entrada los datos de un proceso
     * \post El P.I. pasa a estar inicializado con el proceso leido del canal estandar de entrada
     * \coste O(1)
     */
    void leer_proceso();

    /**
     * @brief Escribe un proceso
     *
     * \pre El P.I. esta inicializado
     * \post Se ha escrito en el canal estandar de salida los datos del P.I.
     * \coste O(1)
     */
    void escribir_proceso() const;
};

#endif
