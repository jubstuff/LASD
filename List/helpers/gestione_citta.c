#include "gestione_citta.h"
#include <string.h>


int ConfrontaCitta( void *Pers1, void *Pers2 )
{
	PERSONA P1 = *( (PERSONA *)Pers1 );
	PERSONA P2 = *( (PERSONA *)Pers2 );

	return strcasecmp( P1->Citta, P2->Citta );
}

int ConfrontaPersona( void *Pers1, void *Pers2 )
{
	int ReturnStatus;
	PERSONA P1 = *( (PERSONA *)Pers1 );
	PERSONA P2 = *( (PERSONA *)Pers2 );

	ReturnStatus = strcasecmp( P1->Cognome, P2->Cognome );
	if( ReturnStatus == 0 )
	{
		ReturnStatus = strcasecmp( P1->Nome, P2->Nome );
	}

	return ReturnStatus;
}
