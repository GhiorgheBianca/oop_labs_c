#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "obiect_electronic.h"

/*
	Descriere: Creeaza produsul cu urmatoarele atribute: 

		id - intreg, identificator unic
		tip - sir de caractere, tipul produsului
		producator - sir de caractere, numele producatorului
		model - sir de caractere, modelul produsului
		pret - numar real (large float), pretul produsului
		cantitate - intreg, cantitatea in care este disponibil produsul

	Returneaza un pointer creat obiectul de tip Electronic
*/
Electronic* creeazaElectronic(int id, char* tip, char* producator, char* model, double pret, int cantitate)
{
	Electronic* electr = (Electronic*)malloc(sizeof(Electronic));

	electr->id = id;

	electr->tip = (char*)malloc(sizeof(char) * (strlen(tip) + 1));
	strcpy(electr->tip, tip);

	electr->producator = (char*)malloc(sizeof(char) * (strlen(producator) + 1));
	strcpy(electr->producator, producator);

	electr->model = (char*)malloc(sizeof(char) * (strlen(model) + 1));
	strcpy(electr->model, model);

	electr->pret = pret;
	electr->cantitate = cantitate;

	return electr;
}

/*
	Elibereaza memoria alocata in Heap de catre obiectul Electronic
		electr - pointer al unui obiect de tip Electronic => efectul se produce direct in memorie
*/
void destroyElectronic(Electronic* electr)
{
	if (electr == NULL)
		return;

	// elibereaza memoria alocata componentelor obiectului de tip Electronic
	free(electr->tip);
	free(electr->producator);
	free(electr->model);

	// elibereaza memoria alocata pentru structura Electronic
	free(electr);
}

/*
	Copiaza un obiectul de tip Electronic
		electr - pointer al unui obiect de tip Electronic
	Returneaza un pointer catre copie
*/
Electronic* copyElectronic(Electronic* electr)
{
	if (electr == NULL)
		return NULL;

	Electronic* copie_electr = creeazaElectronic(getId(electr), getTip(electr), getProducator(electr), getModel(electr), getPret(electr), getCantitate(electr));
	return copie_electr;
}

/*
	Returneaza id-ul produsului
*/
int getId(Electronic* electr)
{
	if (electr == NULL)
		return -1;

	return electr->id;
}

/*
	Returneaza tipul produsului
*/
char* getTip(Electronic* electr)
{
	if (electr == NULL)
		return NULL;

	return electr->tip;
}

/*
	Returneaza producatorul produsului
*/
char* getProducator(Electronic* electr)
{
	if (electr == NULL)
		return NULL;

	return electr->producator;
}

/*
	Returneaza modelul produsului
*/
char* getModel(Electronic* electr)
{
	if (electr == NULL)
		return NULL;

	return electr->model;
}

/*
	Returneaza pretul produsului
*/
double getPret(Electronic* electr)
{
	if (electr == NULL)
		return -1;

	return electr->pret;
}

/*
	Returneaza cantitatea in care este disponibil produsul
*/
int getCantitate(Electronic* electr)
{
	if (electr == NULL)
		return -1;

	return electr->cantitate;
}