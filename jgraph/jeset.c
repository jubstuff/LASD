#include "jeset.h"


/*============================DEFINIZIONE STRUTTURE==============================*/

struct jedge_tag 
{
    J_VERTEX *DestVertex; /**< Destinazione dell'arco */
    double   Weight;      /**< Peso dell'arco */
};

struct jeset_tag
{
    J_LIST **AdjLists; /**< Vettore delle liste di adiacenza */
};


/*=======================FINE DEFINIZIONE STRUTTURE==============================*/
