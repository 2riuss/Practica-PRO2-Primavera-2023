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
#include <queue>
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

    /** @brief Estructura interna del cluster */
    BinTree<string> estructura;

    /** @brief Procesadores pertenecientes al cluster y un bool que indica si tienen procesadores auxiliares
     *
     * Ordenados por un identificador */
    map<string, pair<bool, Procesador>> cjt_procesadores;

    /* Invariante de la representacion
     * - Los strings del map cjt_procesadores y los del BinTree estructura representan los identificadores de los procesadores
     * - Todo string de cjt_procesadores también esta en estructura y viceversa
     * - cjt_procesadores no contiene procesadores con un mismo identificador
     * - estructura no contiene dos identificadores iguales
     */

    /** @brief Inmersion de <em>substituir</em>
     *
     * \pre <em>Cierto<em>
     * \post El resultado es:
     * - <em>e1</em>, Si <em>id_procesador</em> no se encuentra en <em>e1</em>
     * - <em>e1</em> con el sub-arbol con valor <em>id_procesador</em> substituido por <em>e2</em>, Si <em>id_procesador</em> se encuentra en <em>e1</em>
     * \coste O(n)
     */
    static BinTree<string> substituir_aux(const string& id_procesador, const BinTree<string>& e1, const BinTree<string>& e2);

    /** @brief Inmersion de <em>leer_cluster</em>
     *
     * \pre Estan preparados en el canal estandar de entrada los datos de un cluster y <em>e</em> es vacio
     * \post <em>e</em> contiene la estructura del cluster del canal estandar de entrada y sus procesadores se han añadido a <em>proc</em>
     * \coste O(n*log(n))
     */
    static void leer_cluster_aux(map<string, pair<bool, Procesador>>& cjt_pro, BinTree<string>& e);

    /** @brief Inmersion de <em>escribir_estructura</em>
     *
     * \pre <em>Cierto</em>
     * \post Se ha escrito en el canal estandar de salida la estructura de procesadores representada por <em>e</em>
     * \coste O(n)
     */
    static void escribir_estructura_aux(const BinTree<string>& e);

    static pair<int, int> eliminar_subarbol(map<string, pair<bool, Procesador>>& proc, BinTree<string>& e);
    static pair<int, int> podar_aux(const string& id_procesador, map<string, pair<bool, Procesador>>& proc, BinTree<string>& e);
public:
    // Constructoras

    /**
     * @brief Constructora por defecto
     *
     * Se ejecuta por defecto al declarar un cluster
     * \pre <em>Cierto</em>
     * \post El resultado es un cluster vacio
     * \coste O(1)
     */
    Cluster();


    // Modificadoras

    /**
     * @brief Añade un proceso a un procesador
     *
     * \pre Existe un procesador con identificador <em>id_procesador</em> en el P.I., no hay ningun proceso con el mismo identificador que el proceso <em>job</em> en el procesador y el proceso <em>job</em> cabe en dicho procesador
     * \post El proceso <em>job</em> queda añadido al procesador con identificador <em>id_procesador</em> del P.I. en el hueco más ajustado con posicion inicial más pequeña
     * \coste O(log(n))
     */
    void agregar_proceso(const string& id_procesador, const Proceso& job);

    /**
     * @brief Elimina un proceso de un procesador
     *
     * \pre Existe un procesador con identificador <em>id_procesador</em> en el P.I. que contiene el proceso con identificador <em>id_proceso</em>
     * \post Se ha eliminado el proceso con identificador <em>id_proceso</em> del procesador con identificador <em>id_procesador</em> del P.I.
     * \coste O(log(n))
     */
    void eliminar_proceso(const string& id_procesador, int id_proceso);

    /**
     * @brief Añade un proceso al cluster
     *
     * \pre <em>Cierto</em>
     * \post El resultado indica si ha sido possible añadir el proceso <em>job</em> al P.I.; en caso afirmativo este poceso queda añadido en el hueco más ajustado con posicion inicial más pequeña de un procesador.
     * Criterios de seleccion del procesador, por orden:
     * - Hueco más ajustado al proceso <em>job</em>
     * - Más memoria libre
     * - Más cercania a la raíz del cúster
     * - Más a la izquierda del cluster
     * \coste O(n*log(n))
     */
    bool agregar_proceso(const Proceso& job);

    /**
     * @brief Sustituye un procesador por un cluster
     *
     * \pre En el P.I. existe un procesador con identificador <em>id_procesador</em>, sin procesos en ejecucion y sin procesadores auxiliares
     * \post El cluster <em>c</em> se ha colocado en el lugar del procesador con identificador <em>id_procesador</em>, substituiendolo en el P.I.
     * \coste O(N*log(n) + n + N) , n = nº procesadores del P.I., N = nº procesadores en el cluster <em>c</em>
     */
    void substituir(const string& id_procesador, const Cluster& c);

    /**
     * @brief Compacta la memoria de un procesador
     *
     * \pre Existe un procesador con identificador <em>id_procesador</em> en el P.I.
     * \post Se ha compactado la memoria del procesador con identificador <em>id_procesador</em> del P.I.; es decir, se han movido todos los procesos hacia el principio de la memoria del procesador respetando el orden inicial y sin huecos ni solapamientos
     * \coste O(n_1*log(n) + n_2) tq n = n_1 + n_2 , n_1 = nº procesos a compactar del procesador, n_2 = nº procesos ya compactados del procesador
     */
    void compactar_memoria_procesador(const string& id_procesador);

    /**
     * @brief Compacta la memoria de todos los procesadores del cluster
     *
     * \pre <em>Cierto</em>
     * \post Se ha compactado la memoria de todos los procesadores del P.I.; de la misma manera que el metodo <em>compactar_memoria_procesador</em>
     * \coste O(n_1*log(n) + n_2) tq n = n_1 + n_2 , n_1 = nº procesos a compactar del cluster, n_2 = nº procesos ya compactados del cluster
     */
    void compactar_memoria();

    /**
     * @brief Simula el avance del tiempo en el cluster
     *
     * Se eliminan todos los procesos activos que hayan acabado en ese intervalo de tiempo, y la ejecucion de todos los procesos de todos los procesadores han progresado t unidades de tiempo
     * \pre <em>Cierto</em>
     * \post El P.I. se ha actualizado como si hubieran pasado <em>t</em> unidades de tiempo
     * \coste O(n_1*log(n) + n_2) tq n = n_1 + n_2 , n_1 = nº procesos con tiempo menor/igual a t del cluster, n_2 = nº procesos con tiempo mayor a t del cluster
     */
    void avanzar_tiempo(int t);

    /**
     * @brief Vacia al cluster
     *
     * Se eliminan todos los procesadores y sus procesos
     * \pre <em>Cierto</em>
     * \post El P.I. queda vacio
     * \coste O(n)
     */
    void clear();

    pair<int, int> podar(const string& id_procesador);


    // Consultoras

    /**
     * @brief Indica si existe el procesador en el cluster
     *
     * \pre <em>Cierto</em>
     * \post El resultado indica si hay algun procesador de identificador <em>id_procesador</em> en el P.I.
     * \coste O(log(n))
     */
    bool existe_procesador(const string& id_procesador) const;

    /**
     * @brief Indica si el procesador del cluster contiene el proceso
     *
     * \pre Existe un procesador con identificador <em>id_procesador</em> en el P.I.
     * \post El resultado indica si el procesador con identificador <em>id_procesador</em> del P.I. contiene algun proceso con identificador <em>id_proceso</em>
     * \coste O(log(n))
     */
    bool existe_proceso(const string& id_procesador, int id_proceso) const;

    /**
     * @brief Indica si el procesador del cluster contiene procesos en ejecucion
     *
     * \pre Existe un procesador con identificador <em>id_procesador</em> en el P.I.
     * \post El resultado indica si el procesador con identificador <em>id_procesador</em> del P.I. contiene procesos
     * \coste O(log(n))
     */
    bool procesador_vacio(const string& id_procesador) const;

    /**
     * @brief Indica si el procesador del cluster tiene procesadores auxiliares
     *
     * \pre Existe un procesador con identificador <em>id_procesador</em> en el P.I.
     * \post El resultado indica si el procesador con identificador <em>id_procesador</em> del P.I. tiene procesadores auxiliares
     * \coste O(log(n))
     */
    bool procesadores_auxiliares(const string& id_procesador) const;

    /**
     * @brief Indica si el proceso cabe en el procesador del cluster
     *
     * \pre Existe un procesador con identificador <em>id_procesador</em> en el P.I. y no existe ningun proceso con el mismo identificador que el proceso <em>job</em> en dicho procesador
     * \post El resultado indica si el proceso <em>job</em> cabe en el procesador con identificador <em>id_procesador</em> del P.I.
     * \coste O(log(n))
     */
    bool cabe_proceso(const string& id_procesador, const Proceso& job) const;

    bool primer_procesador(const string& id_procesador) const;


    // Lectura i escritura

    /**
     * @brief Lee un cluster
     *
     * \pre El P.I. esta vacio y estan preparados en el canal estandar de entrada los datos de un cluster
     * \post El P.I. pasa a estar inicializado con el cluster leido del canal estandar de entrada
     * \coste O(n*log(n))
     */
    void leer_cluster();

    /**
     * @brief Escribe un procesador
     *
     * \pre Existe un procesador con identificador <em>id_procesador</em> en el P.I.
     * \post Se ha escrito en el canal estandar de salida la posicion y datos de los procesos del procesador con identificador <em>id_procesador</em> del P.I.
     * \coste O(log(n) + m) , n = nº procesadores, m = nº procesos en el procesador
     */
    void escribir_procesador(const string& id_procesador) const;

    /**
     * @brief Escribe la informacion pertinente a los procesadores del cluster
     *
     * \pre <em>Cierto</em>
     * \post Se ha escrito en el canal estandar de salida todos los procesadores del P.I. por orden creciente de identificador con la misma informacion que el metodo <em>escribir_procesador</em>
     * \coste O(n + m_t) , n = nº procesadores, m_t = nº procesos en el cluster
     */
    void escribir_procesadores() const;

    /**
     * @brief Escribe la estructura de los procesadores del cluster
     *
     * \pre <em>Cierto</em>
     * \post Se ha escrito en el canal estandar de salida la estructura de los procesadores del P.I.
     * \coste O(n)
     */
    void escribir_estructura() const;
};

#endif
