#include "service.h"
#include "validator.h"
#include <string.h>

/*
	Creeaza obiectul de tip Service in memoria Heap; seteaza obiectul de tip Repository
	Returneaza un pointer al unui obiect de tip Service
*/
Service* createService(Repository* repo)
{
	Service* service = (Service*)malloc(sizeof(Service));
	if (NULL == service) {
		return NULL;
	}
	service->repository = repo;
	return service;
}

/*
	Elibereaza memoria alocata in Heap de catre Service
		service - pointer al unui obiect de tip Service => efectul se produce direct in memorie
*/
void destroyService(Service* service)
{
	if (service == NULL)
		return;

	destroyRepository(service->repository);
	free(service);
}

/*
	Descriere: Adauga obiectul de tip Electronic apeland functia din Repository; valideaza obiectul Electronic creat

		service - pointer al unui obiect de tip Service => efectul se produce direct in memorie
		id - intreg, identificator unic
		tip - pointer catre un sir de caractere, tipul produsului
		producator - pointer catre un sir de caractere, numele producatorului
		model - pointer catre un sir de caractere, modelul produsului
		pret - numar real (large float), pretul produsului
		cantitate - intreg, cantitatea in care este disponibil produsul

	Returneaza un cod de eroare in cazul in care obiectul nu este valid
				0 daca adaugarea a fost efectuata cu success
*/
int adaugaElectronicService(Service* service, int id, char* tip, char* producator, char* model, double pret, int cantitate)
{
	Electronic* electr = creeazaElectronic(id, tip, producator, model, pret, cantitate);

	int err_code = validare_Electronic(electr);
	if (err_code != 0)
	{
		destroyElectronic(electr);
		return err_code;
	}

	err_code = adaugaElectronic(service->repository, electr);
	if (err_code == -1)
	{
		destroyElectronic(electr);
		return err_code;
	}

	return err_code;
}

/*
	Descriere: Modifica obiectul de tip Electronic apeland functia din Repository; valideaza pretul, respectiv cantitatea pentru obiectului Electronic care urmeaza a fi modificat

		service - pointer al unui obiect de tip Service => efectul se produce direct in memorie
		id - intreg, identificator unic
		pret - numar real (large float), pretul produsului
		cantitate - intreg, cantitatea in care este disponibil produsul

	Returneaza un cod de eroare in cazul in care pretul si/sau cantitatea nu este valida
				0 daca modificarea a fost efectuata cu success
*/
int modificaElectronicService(Service* service, int id, double pret, int cantitate)
{
	Electronic* electr = creeazaElectronic(id, "valid", "valid", "valid", pret, cantitate);

	int err_code = validare_Electronic(electr);
	if (err_code != 0)
	{
		destroyElectronic(electr);
		return err_code;
	}

	err_code = modificaElectronic(service->repository, electr);
	destroyElectronic(electr);
	return err_code;
}

/*
	Descriere: Sterge obiectul de tip Electronic apeland functia din Repository; valideaza id-ul pentru obiectului Electronic care urmeaza a fi sters

		service - pointer al unui obiect de tip Service => efectul se produce direct in memorie
		id - intreg, identificator unic

	Returneaza un cod de eroare in cazul in care id-ul nu este valid
				0 daca stergerea a fost efectuata cu success
*/
int stergeElectronicService(Service* service, int id)
{
	Electronic* electr = creeazaElectronic(id, "valid", "valid", "valid", 1.00, 1);

	int err_code = validare_Electronic(electr);
	if (err_code != 0)
	{
		destroyElectronic(electr);
		return err_code;
	}

	err_code = stergeElectronic(service->repository, electr->id);
	destroyElectronic(electr);
	return err_code;
}

/*
	Sorteaza lista de produse din Service in functie de modul dat
		
		service - pointer al unui obiect de tip Service => efectul se produce direct in memorie
		mod - pointer catre un sir de caractere, retine modul in care va fi sortata lista ("crescator" sau "descrescator")

	Returneaza un pointer al unui obiect de tip Service cu lista sortata
*/
Service* vizualizeazaService(Service* service, char* mod)
{
	Repository* repo = service->repository;
	DynamicArray* vector_dinamic = repo->electronice;
	if (strcmp(mod, "crescator") == 0)
	{
		ordoneaza(vector_dinamic, vector_dinamic->length, crescator);
	}
	else if (strcmp(mod, "descrescator") == 0)
	{
		ordoneaza(vector_dinamic, vector_dinamic->length, descrescator);
	}

	return service;
}

/*
	Filtreaza lista de produse din Service in functie de modul dat (producator, pret sau cantitate) si de valoarea corespunzatoare (char, double sau int)

		service - pointer al unui obiect de tip Service => efectul se produce direct in memorie
		mod - pointer catre un sir de caractere, retine modul in care va fi sortata lista ("producator", "pret" sau "cantitate")
		str_val - pointer catre un sir de caractere, valoarea cu care se va compara in cazul in care modul este "producator"
		num_dec - intreg, valoarea cu care se va compara in cazul in care modul este "cantitate"
		num_float - numar real (large float), valoarea cu care se va compara in cazul in care modul este "pret"

	Returneaza un pointer al unui obiect de tip Service
*/
Service* filtreazaService(Service* service, char* mod, char* str_val, int num_dec, double num_float)
{
	Repository* repo = service->repository; 
	Repository* copie_repo = createRepository();
	Service* filtrat = createService(copie_repo);
	DynamicArray* vector_dinamic = copyDynamicArray(repo->electronice);
	int i = 0;
	for (i = 0; i < vector_dinamic->length; i++)
	{
		if (strcmp(mod, "producator") == 0)
		{
			if (strstr(getProducator(vector_dinamic->elems[i]), str_val) != NULL)
			{
				Electronic* copie_electr = copyElectronic(vector_dinamic->elems[i]);
				adaugaElectronic(copie_repo, copie_electr);
			}
		}
		else if (strcmp(mod, "pret") == 0)
		{
			if (num_float == getPret(vector_dinamic->elems[i]))
			{
				Electronic* copie_electr = copyElectronic(vector_dinamic->elems[i]);
				adaugaElectronic(copie_repo, copie_electr);
			}
		}
		else if (strcmp(mod, "cantitate") == 0)
		{
			if (num_dec == getCantitate(vector_dinamic->elems[i]))
			{
				Electronic* copie_electr = copyElectronic(vector_dinamic->elems[i]);
				adaugaElectronic(copie_repo, copie_electr);
			}
		}
	}
	destroyDynamicArray(vector_dinamic);
	return filtrat;
}

/*
	Returneaza un pointer al unui obiect de tip Service care contine lista cu toate obiectele de tip Electronic
		service - pointer al unui obiect de tip Service => efectul se produce direct in memorie
*/
Service* tiparesteElectronicService(Service* service)
{
	Repository* repo = service->repository;
	DynamicArray* vector_dinamic = repo->electronice;
	vector_dinamic->elems = getAll(service->repository);
	return service;
}