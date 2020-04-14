#pragma once
#include "repository.h"

typedef struct
{
	Repository* repository;
} Service;

/*
	Creeaza obiectul de tip Service
*/
Service* createService(Repository* repo);

/*
	Elibereaza memoria alocata in Heap de catre Service
*/
void destroyService(Service* service);

/*
	Adauga obiectul de tip Electronic apeland functia din Repository
*/
int adaugaElectronicService(Service* service, int id, char* tip, char* producator, char* model, double pret, int cantitate);

/*
	Modifica obiectul de tip Electronic apeland functia din Repository
*/
int modificaElectronicService(Service* service, int id, double pret, int cantitate);

/*
	Sterge obiectul de tip Electronic apeland functia din Repository
*/
int stergeElectronicService(Service* service, int id);

/*
	Sorteaza lista de produse din Service in functie de modul dat
*/
Service* vizualizeazaService(Service* service, char* mod);

/*
	Filtreaza lista de produse din Service in functie de modul dat (producator, pret sau cantitate) si de valoarea corespunzatoare (char, double sau int)
*/
Service* filtreazaService(Service* service, char* mod, char* str_val, int num_dec, double num_float);

/*
	Returneaza un pointer al unui obiect de tip Service care contine lista cu toate obiectele de tip Electronic
*/
Service* tiparesteElectronicService(Service* service);