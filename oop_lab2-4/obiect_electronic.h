#pragma once

typedef struct
{
	int id;
	char* tip;
	char* producator;
	char* model;
	double pret;
	int cantitate;
} Electronic;

/*
	Creeaza obiectul de tip Electronic
*/
Electronic* creeazaElectronic(int id, char* tip, char* producator, char* model, double pret, int cantitate);

/*
	Elibereaza memoria alocata in Heap de catre obiectul de tip Electronic
*/
void destroyElectronic(Electronic* electr);

/*
	Copiaza un obiectul de tip Electronic si returneaza un pointer catre copie
*/
Electronic* copyElectronic(Electronic* electr);

/*
	Returneaza id-ul produsului
*/
int getId(Electronic* electr);

/*
	Returneaza tipul produsului
*/
char* getTip(Electronic* electr);

/*
	Returneaza producatorul produsului
*/
char* getProducator(Electronic* electr);

/*
	Returneaza modelul produsului
*/
char* getModel(Electronic* electr);

/*
	Returneaza pretul produsului
*/
double getPret(Electronic* electr);

/*
	Returneaza cantitatea in care este disponibil produsul
*/
int getCantitate(Electronic* electr);

/*
	Returneaza un sir de caractere cu toate detaliile unui obiect electronic
*/
void toString(Electronic* electr, char str[]);