/**
 * @file Cluster.hh
 * @brief Especificacion de la clase Cluster
 */

#ifndef CLUSTER_HH
#define CLUSTER_HH

#include "Procesador.hh"
#include "Proceso.hh"

#ifndef NO_DIAGRAM
#include <iostream>
#include <string>
#include "BinTree.hh"
#include <map>
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

    BinTree<string> estr;
    map<string, Procesador> procesadores;

    /* Invariante de la representacion
     * estr no buit
     */

    /** @brief Inmersion de <em>leer_cluster</em>, debilitamiento de la postcondicion
     *
     * \pre Estan preparados en el canal estandar de entrada los datos de un cluster y <em>e</em> es vacio
     * \post <em>e</em> contiene la estructura del cluster del canal estandar de entrada y sus procesadores se han añadido a <em>proc</em>
     */
    static void leer_cluster_aux(map<string, Procesador>& proc, BinTree<string>& e);
    static void escribir_estructura_aux(const BinTree<string>& e);

// pre: procesador id pertenece a e
    static bool procesadores_auxiliares_aux(const BinTree<string>& e, const string& id);
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
     * \pre Existe un procesador con identificacion <em>id</em> en el P.I., no hay ningun proceso con el mismo identificador que el proceso <em>job</em> en el procesador y el proceso <em>job</em> cabe en dicho procesador
     * \post El proceso <em>job</em> queda añadido al procesador con identificacion <em>id</em> del P.I. en el hueco más ajustado con posicion inicial más pequeña
     */
    void agregar_proceso(const string& id, const Proceso& job);

    /**
     * @brief Elimina un proceso de un procesador
     *
     * \pre Existe un procesador con identificacion <em>id</em> en el P.I. que contiene el proceso con identificacion <em>n</em>
     * \post Se ha eliminado el proceso con identificacion <em>n</em> del procesador con identificacion <em>id</em> del P.I.
     */
    void eliminar_proceso(const string& id, int n);

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
    void agregar_proceso(const Proceso& job);

    /**
     * @brief Sustituye un procesador por un cluster
     *
     * \pre En el P.I. existe un procesador con identificacion <em>id</em>, sin procesos en ejecucion y sin procesadores auxiliares
     * \post El cluster <em>c</em> se ha colocado en el lugar del procesador con identificacion <em>id</em>, substituiendolo en el P.I.
     */
    void substituir(const string& id, const Cluster& c);

    /**
     * @brief Compacta la memoria de un procesador
     *
     * \pre Existe un procesador con identificacion <em>id</em> en el P.I.
     * \post Se ha compactado la memoria del procesador con identificacion <em>id</em> del P.I.; es decir, se han movido todos los procesos hacia el principio de la memoria del procesador respetando el orden inicial y sin huecos ni solapamientos
     */
    void compactar_memoria_procesador(const string& id);

    /**
     * @brief Compacta la memoria de todos los procesadores del cluster
     *
     * \pre <em>Cierto</em>
     * \post Se ha compactado la memoria de todos los procesadores del P.I.; de la misma manera que el metodo <em>compactar_memoria_procesador</em>
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

    /**
     * @brief Vacia al cluster
     *
     * Se eliminan todos los procesadores y sus procesos
     * \pre <em>Cierto</em>
     * \post El P.I. queda vacio
     */
    void clear();


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
     * \pre Existe un procesador con identificacion <em>id</em> en el P.I.
     * \post El resultado indica si el procesador con identificacion <em>id</em> del P.I. contiene algun proceso con identificacion <em>n</em>
     */
    bool existe_proceso(const string& id, int n);

    /**
     * @brief Indica si el procesador del cluster contiene procesos en ejecucion
     *
     * \pre Existe un procesador con identificacion <em>id</em> en el P.I.
     * \post El resultado indica si el procesador con identificacion <em>id</em> del P.I. contiene procesos
     */
    bool procesador_vacio(const string& id) const;

    /**
     * @brief Indica si el procesador del cluster tiene procesadores auxiliares
     *
     * \pre Existe un procesador con identificacion <em>id</em> en el P.I.
     * \post El resultado indica si el procesador con identificacion <em>id</em> del P.I. tiene procesadores auxiliares
     */
    bool procesadores_auxiliares(const string& id) const;

    /**
     * @brief Indica si el proceso cabe en el procesador del cluster
     *
     * \pre Existe un procesador con identificacion <em>id</em> en el P.I. y no existe ningun proceso con la misma identificacion que el proceso <em>job</em> en dicho procesador
     * \post El resultado indica si el proceso <em>job</em> cabe en el procesador con identificacion <em>id</em> del P.I.
     */
    bool cabe_proceso(const string& p, const Proceso& job);


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
     * \pre Existe un procesador con identificacion <em>id</em> en el P.I.
     * \post Se ha escrito en el canal estandar de salida la posicion y datos de los procesos del procesador con identificacion <em>id</em> del P.I.
     */
    void escribir_procesador(const string& id) const;

    /**
     * @brief Escribe la informacion pertinente a los procesadores del cluster
     *
     * \pre <em>Cierto</em>
     * \post Se ha escrito en el canal estandar de salida todos los procesadores del P.I. por orden creciente de identificador con la misma informacion que el metodo <em>escribir_procesador</em>
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
