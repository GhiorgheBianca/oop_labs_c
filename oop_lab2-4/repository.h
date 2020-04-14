#pragma once

#include "obiect_electronic.h"
#include "dynamic_array.h"
#include <stdlib.h>

typedef struct 
{
	DynamicArray* electronice;
} Repository;

/*
	Creeaza obiectul de tip Repository
*/
Repository* createRepository();

/*
	Copiaza un obiectul de tip Repository si returneaza un pointer catre copie
*/
Repository* copyRepo(Repository* repository);

/*
	Descriere: verifica daca un repository contine un obiect electronic specificat.
	Returneaza:
		- 1 daca repo contine obiectul electronic,
		- 0 altfel.
*/
int areElectronic(Repository* repository, int id);

/*
	Descriere: adauga un obiect electronic in repository.
	Returneaza:
		- -1 daca repo are deja obiectul electronic respectiv,
		- 0 daca obiectul a fost adaugat cu succes.
*/
int adaugaElectronic(Repository* repository, Electronic* electr);

/*
	Modifica obiectul specificat dupa id daca acesta exista
*/
int modificaElectronic(Repository* repository, Electronic* electr);

/*
	Stergem obiectul specificat dupa id daca acesta exista
*/
int stergeElectronic(Repository* repository, int id);

/*
	Returneaza lista de elemente
*/
TElement* getAll(Repository* repository);

/*
	Elibereaza memoria alocata in Heap de catre Repository
*/
void destroyRepository(Repository* repository);