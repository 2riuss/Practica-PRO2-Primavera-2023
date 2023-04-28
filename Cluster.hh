/**
 * @file Cluster.hh
 * @brief Especificacion de la clase Cluster
 */

#ifndef CLUSTER_HH
#define CLUSTER_HH

#include "Procesador.hh"
#include "Proceso.hh"

#ifndef NO_DIAGRAM
#include <string>
#endif

using namespace std;

/**
 * @class Cluster
 * @brief Representa un cluster de procesadores
 *
 * Representa un cluster con un número de procesadores variable, distribuidos en forma de árbol binario, con identificadores únicos.
 * El primer procesador puede ser cualquiera de ellos. Cada procesador puede tener dos, uno o cero procesadores sucesores, también llamados auxiliares.
 *
 * El cluster puede añadir, eliminar y reorganizar los procesos de los procesadores ademas de simular el avance del tiempo
 */
class Cluster {
private:

public:
    // Constructoras

    /**
     * @brief Constructora por defecto
     *
     * Se ejecuta por defecto al declarar un cluster
     * \pre <em>Cierto</em>
     * \post El resultado es un cluster vacio
     */
    Cluster();


    // Modificadoras

    /**
     * @brief Añade un proceso a un procesador
     *
     * \pre <em>Cierto</em>
     * \post El resultado indica si ha sido possible añadir el proceso <em>job</em> a un procesador con identificacion <em>id</em> del P.I.; en caso afirmativo este proceso queda añadido a dicho procesador en el hueco más ajustado con posicion inicial más pequeña
     */
    bool agregar_proceso(const string& id, const Proceso& job);

    /**
     * @brief Elimina un proceso de un procesador
     *
     * \pre <em>Cierto</em>
     * \post El resultado indica si existe i ha sido posible eliminar un proceso de identificacion <em>n</em> en un procesador de identificacion <em>id</em> del P.I.; en caso afirmativo este proceso queda eliminado de dicho procesador
     */
    bool eliminar_proceso(const string& id, int n);

    /**
     * @brief Añade un proceso al cluster
     *
     * \pre <em>Cierto<em>
     * \post El resultado indica si ha sido possible añadir el proceso <em>job</em> al P.I.; en caso afirmativo este poceso queda añadido al procesador mas adequado siguiendo los siguientes criterios por orden:
     *  - hueco más ajustado
     *  - más memoria libre
     *  - más cercania a la raíz del cúster
     *  - más a la izquierda del cluster
     */
    bool agregar_proceso(const Proceso& job);

    /**
     * @brief Sustituye un procesador por un cluster
     *
     * \pre <em>Cierto</em>
     * \post El resultado indica si existe el procesador de identificacion <em>id</em> i ha sido posible substituir-lo por el cluster <em>c</em>; en caso afirmativo el cluster <em>c</em> se coloca en el P.I. ocupando el lugar del procesador
     */
    bool substituir(const string& id, const Cluster& c);

    /**
     * @brief Compacta la memoria de un procesador
     *
     * \pre <em>Cierto</em>
     * \post El resultado indica si existe un procesador de identificacion <em>id</em> en el P.I.; en caso afirmativo se ha compactado la memoria de dicho procesador
     */
    bool compactar_memoria(const string& id);

    /**
     * @brief Compacta la memoria de todos los procesadores del cluster
     *
     * \pre <em>Cierto</em>
     * \post Se ha compactado la memoria de todos los procesadores del P.I.
     */
    void compactar_memoria();

    /**
     * @brief Simula el avance del tiempo en el cluster
     *
     * Se eliminan todos los procesos activos que hayan acabado en ese intervalo de tiempo, i la ejecucion de todos los procesos de todos los procesadores han progresado t unidades de tiempo
     * \pre <em>Cierto</em>
     * \post El P.I. se ha actualizado como si hubieran pasado <em>t</em> unidades de tiempo
     */
    void avanzar_tiempo(int t);


    // Consultoras

    /**
     * @brief Indica si existe el procesador en el cluster
     *
     * \pre <em>Cierto</em>
     * \post El resultado indica si hay algun procesador de identificacion <em>id</em> en el P.I.
     */
    bool existe_procesador(const string& id) const;

    /**
     * @brief Indica si el procesador del cluster contiene el proceso
     *
     * \pre Existe un prodesador con identificacion <em>id</em> en el P.I.
     * \post El resultado indica si el procesador con identificacion <em>id</em> del P.I. contiene algun proceso con identificacion <em>n</em>
     */
    bool existe_proceso(const string& id, int n) const;

    /**
     * @brief Indica si el procesador del cluster contiene procesos en ejecucion
     *
     * \pre Existe un prodesador con identificacion <em>id</em> en el P.I.
     * \post El resultado indica si el procesador con identificacion <em>id</em> del P.I. contiene procesos
     */
    bool procesador_vacio(const string& id) const;


    // Lectura i escritura

    /**
     * @brief Lee un cluster
     *
     * \pre El P.I. esta vacio y estan preparados en el canal estandar de entrada los datos de un cluster
     * \post El P.I. pasa a estar inicializado con el cluster leido del canal estandar de entrada
     */
    void leer_cluster();

    /**
     * @brief Escribe un procesador
     *
     * \pre <em>Cierto</em>
     * \post El resultado indica si existe un procesador con identificacion <em>id</em> en el P.I., en caso afirmativo se ha escrito en el canal estandar de salida la posicion y datos de los procesos de dicho procesador
     */
    bool escribir_procesador(const string& id) const;

    /**
     * @brief Escribe la informacion pertinente a los procesadores del cluster
     *
     * \pre <em>Cierto</em>
     * \post Se ha escrito en el canal estandar de salida todos los procesadores del P.I. con la misma informacion que el metodo <em>escribir_procesador</em>
     */
    void escribir_procesadores() const;

    /**
     * @brief Escribe la estructura de los procesadores del cluster
     *
     * \pre <em>Cierto</em>
     * \post Se ha escrito en el canal estandar de salida la estructura de los procesadores del P.I.
     */
    void escribir_estructura() const;
};

#endif
