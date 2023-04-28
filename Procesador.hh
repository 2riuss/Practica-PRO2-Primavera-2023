/**
 * @file Procesador.hh
 * @brief Especificacion de la clase Procesador
 */

#ifndef PROCESADOR_HH
#define PROCESADOR_HH

#include "Proceso.hh"

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
     * \pre <em>Cierto</em>
     * \post El resultado indica si ha sido possible añadir el proceso <em>job</em> al P.I.; en caso afirmativo proceso queda añadido al P.I. en el hueco más ajustado con posicion inicial más pequeña
     */
    bool agregar_proceso(const Proceso& job);

    /**
     * @brief Elimina un proceso del procesador
     *
     * \pre <em>Cierto</em>
     * \post El resultado indica si existe i ha sido posible eliminar un proceso de identificacion <em>n</em> en el P.I.; en caso afirmativo este queda eliminado del P.I.
     */
    bool eliminar_proceso(int n);

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


    // Lectura y escritura

    /**
     * @brief Escribe un procesador
     *
     * \pre <em>Cierto</em>
     * \post Se ha escrito en el canal estandar de salida la posicion y datos de los procesos del P.I.
     */
    void escribir_procesador() const;
};

#endif
