/**
 * @file Prioridad.hh
 * @brief Especificacion de la clase Prioridad
 */

#ifndef PRIORIDAD_HH
#define PRIORIDAD_HH

#include "Proceso.hh"

#ifndef NO_DIAGRAM
#include <list>
#endif

/**
 * @class Prioridad
 * @brief Representa una prioridad
 *
 * Representa un conjunto de procesos ordenados por antiguedad con dos contadores que indican el numero de procesos rechazados y aceptados por algun cluster
 *
 * La prioridad puede añadir y eliminar procesos, augmentar sus contadores de procesos rechazados y aceptados por algun cluster
 */
class Prioridad {
private:
    list<Proceso> cjt;
    int rechazados;
    int aceptados;

    /* invariantes de la representación:
     * - cjt no contiene procesos con una misma id
     * - cjt esta ordenado por antiguedad
     * - rechazados és un entero >= 0
     * - aceptados és un entero >= 0
     */

public:
    // Constructoras

    /**
     * @brief Constructora por defecto
     *
     * Se ejecuta por defecto al declarar una prioridad
     * \pre <em>Cierto</em>
     * \post El resultado es una prioridad vacia
     */
    Prioridad();


    // Modificadoras

    /**
     * @brief Añade un proceso a la prioridad
     *
     * \pre En el P.I. no hay procesos con la misma identificacion que <em>job</em>
     * \post Se ha añadido el proceso <em>job</em> al P.I.
     */
    void agregar_proceso(const Proceso& job);

    /**
     * @brief Elimina un proceso de la prioridad
     *
     * \pre El P.I. contine algun proceso
     * \post Se ha eliminado el proceso mas antiguo del P.I.
     */
    void eliminar_proceso();

    /**
     * @brief Incrementa el contador de procesos aceptados de la prioridad en uno
     *
     * \pre <em>Cierto</em>
     * \post Se ha incrementado en uno el contador de procesos aceptados del P.I.
     */
    void incrementar_aceptados();

    /**
     * @brief Incrementa el contador de procesos rechazados de la prioridad en uno
     *
     * \pre <em>Cierto</em>
     * \post Se ha incrementado en uno el contador de procesos rechazados del P.I.
     */
    void incrementar_rechazados();


    // Consultoras

    /**
     * @brief Indica si la prioridad contiene el proceso
     *
     * \pre <em>Cierto</em>
     * \post El resultado indica si el P.I. contiene algun proceso con identificacion <em>n</em>
     */
    bool existe_proceso(int n) const;

    /**
     * @brief Indica si la prioridad contiene procesos pendientes
     *
     * \pre <em>Cierto</em>
     * \post El resultado indica si el P.I. contiene procesos
     */
    bool vacia() const;

    /**
     * @brief Consultora del proceso mas antiguo
     *
     * \pre El P.I. contine algun proceso
     * \post El resultado es el proceso mas antiguo del P.I.
     */
    Proceso proceso() const;


    // Lectura y escritura

    /**
     * @brief Escribe una prioridad
     *
     * \pre <em>Cierto</em>
     * \post Se ha escrito en el canal estandar de salida los procesos del P.I. en orden decreciente de antigüedad, el número de procesos colocados en algun cluster y el número de procesos rechazos del P.I.
     */
    void escribir_prioridad() const;
};

#endif
