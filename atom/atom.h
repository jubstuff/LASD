/*
 * atom.h
 *
 * */

#ifndef ATOM_INCLUDED
#define ATOM_INCLUDED
void VisitAtoms();

extern int Atom_length(const char *str);
/**
 * Atom_new
 *
 * Accetta un puntatore ad una sequenza di byte ed il numero di byte in quella
 * sequenza.
 * Aggiunge una copia della sequenza alla tavola degli Atomi, se necessario, e
 * restituisce il puntatore alla copia appena creata.
 * Non restituisce mai il puntatore a NULL.
 * */
extern const char *Atom_new(const char *str, int len);
/**
 * Atom_string
 *
 * Accetta una stringa, e ne aggiunge una copia nella tavola degli Atomi, se
 * necessario. 
 * Restituisce il puntatore alla copia appena creata.
 * */
extern const char *Atom_string(const char *str);
/**
 * Atom_int
 *
 * Restituisce l'Atomo per la rappresentazione in forma di stringa del numero
 * passato come parametro.
 * */
extern const char *Atom_int(long n);

extern void Atom_free(const char *str);

extern void Atom_reset(void);

#endif
