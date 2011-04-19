/**
 * gestione_citta.c
 *
 * Definizioni dei tipi di dato per la gestione di un elenco di persone,
 * con le relative città.
 * 
 * */

typedef struct persona_t 
{
	char *Nome;
	char *Cognome;
	char *Citta;
} PERSONA; 

/**
 * Confronta la citta di residenza di due persone,
 * confrontandole in ordine lessicografico
 *
 * @return -1, 0, 1 se Pers1->Citta [>,==,<] Pers2->Citta rispettivamente
 * */
int ConfrontaCitta( void *Pers1, void *Pers2 );

int ConfrontaPersona( void *Pers1, void *Pers2 );
