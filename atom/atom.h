/*
 * atom.h
 *
 * */

#ifndef ATOM_INCLUDED
#define ATOM_INCLUDED
void VisitAtoms();

extern int Atom_length(const char *str);
/**
 * Crea un nuovo Atomo e lo aggiunge alla hash table.
 *
 * Accetta un puntatore ad una sequenza di byte ed il numero di byte in quella
 * sequenza.
 * Aggiunge una copia della sequenza alla tavola degli Atomi, se necessario, e
 * restituisce il puntatore alla copia appena creata.
 * Non restituisce mai il puntatore a NULL.
 *
 * @param str Stringa da inserire nella hash table
 * @param len Lunghezza stringa
 * */
extern const char *Atom_new(const char *str, int len);
/**
 * Crea un nuovo Atomo a partire dalla stringa in ingresso
 *
 * Accetta una stringa, e ne aggiunge una copia nella tavola degli Atomi, se
 * necessario. 
 * Restituisce il puntatore alla copia appena creata.
 *
 * @param str Stringa da inserire nella hash table
 * */
extern const char *Atom_string(const char *str);
/**
 * Crea un nuovo Atomo con la rappresentazione testuale del numero in ingresso
 *
 * Restituisce l'Atomo per la rappresentazione in forma di stringa del numero
 * passato come parametro.
 *
 * @param n Numero da inserire nella hash table
 * */
extern const char *Atom_int(long n);
/**
 * Dealloca l'Atomo rappresentato dalla stringa in ingresso
 *
 * @param str Stringa rappresentante l'Atomo da deallocare.
 * */
extern void Atom_free(const char *str);
/**
 * Dealloca tutti gli atomi presenti nella hash table
 *
 * */
extern void Atom_reset(void);

extern void Atom_vload(const char *str, ...);

extern void Atom_aload(const char *strs[]);

#endif
