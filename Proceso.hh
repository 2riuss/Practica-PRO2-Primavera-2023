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
    int id;
    int t;
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
     */
    Proceso();


    // Modificadoras

    /**
     * @brief Simula el avance del tiempo en el proceso
     *
     * La ejecucion ha progresado t unidades de tiempo
     * \pre El tipempo estimado del P.I. es estrictamente mayor que <em>t</em>
     * \post El P.I. se ha actualizado como si hubieran pasado <em>t</em> unidades de tiempo
     */
    void avanzar_tiempo(int t);


    // Consultoras

    /**
     * @brief Consultora de la identificacion
     *
     * \pre <em>Cierto</em>
     * \post El resultado es la identificacion del P.I.
     */
    int consultar_id() const;

    /**
     * @brief Consultora del tiempo estimado
     *
     * \pre <em>Cierto</em>
     * \post El resultado es el tiempo estimado del P.I.
     */
    int consultar_t() const;

    /**
     * @brief Consultora de la memoria estimada
     *
     * \pre <em>Cierto</em>
     * \post El resultado es la memoria estimada del P.I.
     */
    int consultar_mem() const;


    // Lectura y escritura

    /**
     * @brief Lee un proceso
     *
     * \pre El P.I. esta sin inicializar y estan preparados en el canal estandar de entrada los datos de un proceso
     * \post El P.I. pasa a estar inicializado con el proceso leido del canal estandar de entrada
     */
    void leer_proceso();

    /**
     * @brief Escribe un proceso
     *
     * \pre <em>Cierto</em>
     * \post Se ha escrito en el canal estandar de salida los datos del P.I.
     */
    void escribir_proceso() const;
};

#endif
