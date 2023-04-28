/**
 * @file Area_Espera.hh
 * @brief Especificacion de la clase Area_Espera
 */

#ifndef AREA_ESPERA_HH
#define AREA_ESPERA_HH

#include "Proceso.hh"
#include "Cluster.hh"
#include "Prioridad.hh"

#ifndef NO_DIAGRAM
#include <string>
#include <map>
#endif

using namespace std;

/**
 * @class Area_Espera
 * @brief Representa una area de espera
 *
 * Representa una area de espera que cuenta con una serie de prioridades con identificacion unica el las que se encuentran los proces pendientes.
 *
 * La area de espera puede añadir y eliminar prioridades, añadir procesos y enviar procesos a un cluster
 */
class Area_Espera {
private:
    map<string, Prioridad> ae;

    /* Invariantes de la representación
     *  - los strings del map ae representan las identificaciones de las prioridades
     *  - ae no contiene prioridades con una misma identificacion
     */


public:
    // Constructoras

    /**
     * @brief Constructora por defecto
     *
     * Se ejecuta por defecto al declarar una area de espera
     * \pre <em>Cierto</em>
     * \post El resultado es una area de espera vacia
     */
    Area_Espera();


    // Modificadoras

    /**
     * @brief Añade un proceso a una prioridad
     *
     * \pre Existe una prioridad con identificacion <em>id</em> en el P.I. y no hay ningun proceso con el mismo identificador que el proceso <em>job</em> en la prioridad
     * \post Se ha añadido el proceso <em>job</em> a la prioridad con identificacion <em>id</em> del P.I.
     */
    void agregar_proceso(const string& id, const Proceso& job);

    /**
     * @brief Añade una prioridad al area de espera
     *
     * \pre En el P.I. no existe ninguna prioridad con identificacion <em>id</em>
     * \post Se ha añadido una prioridad con identificacion <em>id</em> vacia al P.I.
     */
    void agregar_prioridad(const string& id);

    /**
     * @brief Elimina una prioridad del area de espera
     *
     * \pre En el P.I. existe una prioridad con identificacion <em>id</em>, sin procesos pendientes
     * \post Se ha eliminado la prioridad con identificacion <em>id</em> del P.I.
     */
    void eliminar_prioridad(const string& id);


    // Consultoras

    /**
     * @brief Indica si existe la prioridad en la area de espera
     *
     * \pre <em>Cierto</em>
     * \post El resultado indica si el P.I. contiene una prioridad con identificacion <em>id</em>
     */
    bool existe_prioridad(const string& id) const;

    /**
     * @brief Indica si la prioridad del area de espera contiene el proceso
     *
     * \pre Existe una prioridad con identificacion <em>id</em> en el P.I.
     * \post El resultado indica si la prioridad con identificacion <em>id</em> del P.I. contiene algun proceso con identificacion <em>n</em>
     */
    bool existe_proceso(const string& id, int n) const;

    /**
     * @brief Indica si la prioridad del area de espera tiene procesos pendientes
     *
     * \pre Existe una prioridad con identificacion <em>id</em> en el P.I.
     * \post El resultado indica si la prioridad con identificacion <em>id</em> del P.I. tiene procesos pendientes
     */
    bool prioridad_vacia(const string& id) const;


    // Lectura y escritura

    /**
     * @brief Lee una serie de prioridades i las incorpora al area de espera
     *
     * \pre Estan preparados en el canal estandar de entrada un natural N > 0 y los id de N prioridades
     * \post Se han añadido las prioridades vacias leidas del canal estandar de entrada al P.I.
     */
    void leer_prioridades();

    /**
     * @brief Escribe una prioridad
     *
     * \pre Existe una prioridad con identificacion <em>id</em> en el P.I.
     * \post Se ha escrito en el canal estandar de salida los procesos pendientes en orden decreciente de antigüedad, el número de procesos colocados en algun cluster y el número de procesos rechazos de la prioridad con identificacion <em>id</em> del P.I.
     */
    void escribir_prioridad(const string& id) const;

    /**
     * @brief Escribe la informacion pertinente al area de espera
     *
     * \pre <em>Cierto</em>
     * \post Se ha escrito en el canal estandar de salida todas las prioridades del P.I. por orden creciente de prioridad con la misma informacion que el metodo <em>escribir_prioridad</em>
     */
    void escribir_area_espera() const;


    // Auxiliars

    /**
     * @brief Envia un numero determinado de procesos pendientes del area de espera a un cluster
     *
     * \pre <em>Cierto</em>
     * \post Se han eliminado del P.I. se han añadido al cluster <em>c</em> los procesos pendientes que se ha podido con un maximo de <em>n</em> procesos, por orden de prioridad priorizando los mas antiguos. Los procesos rechazados vuelven al area de espera como si fueran nuevos y con la misma prioridad
     */
    void enviar_procesos_cluster(Cluster& c, int n);
};

#endif
