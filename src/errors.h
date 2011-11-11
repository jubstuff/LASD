/**
 * errors.h
 *
 * Return status for functions in the library
 *
 * */
#ifndef J_ERRORS
#define J_ERRORS

typedef enum
{
	SUCCESS, /* OK */
	E_NO_MEM, /* Errore in malloc, memoria insufficiente */
	ERROR, /* Errore generico */
	W_LIST_NOTFOUND, /* Nodo non trovato nella lista */
	W_LIST_DUP, /* Trovato un duplicato nella lista */
	W_SET_NOTFOUND /* Vertice non trovato nell'insieme JVset */

} J_STATUS;

#endif
