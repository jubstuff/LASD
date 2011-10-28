/*============================================================================*
 *                                                                            *
 * Nome File: jvertex.h                                                       *
 *                                                                            *
 * Scopo:                                                                     *
 *                                                                            *
 * Data Creazione: 14-05-2011                                                 *
 *                                                                            *
 * Ultima Modifica: sab 14 mag 2011 13:17:28 CEST                             *
 *                                                                            *
 * Autore:                                                                    *
 *                                                                            *
 *                                                                            *
 =============================================================================*/

#include <stdlib.h>

#ifndef JVERTEX_H
#define JVERTEX_H

typedef struct jvertex_tag J_VERTEX;

J_VERTEX *JVertex_New();
int JVertex_Delete( J_VERTEX * );
char *JVertex_GetLabel( J_VERTEX * );
char *JVertex_SetLabel( char *, J_VERTEX *);
void JVertex_SetData( void *Data, J_VERTEX *V);


#endif
