#include "repository.h"

/*
	Creeaza obiectul de tip Repository in memoria Heap; seteaza lungimea listei la 0
	Returneaza obiectul de tip Repository
*/
Repository* createRepository() 
{
	Repository* repo = (Repository*)malloc(sizeof(Repository));
	if (repo == NULL) {
		return NULL;
	}
	repo->electronice = createDynamicArray(CAPACITY);

	return repo;
}

/*
	Copiaza un obiectul de tip Repository
		repository - pointer al unui obiect de tip Repository
	Returneaza un pointer catre copie
*/
Repository* copyRepo(Repository* repository)
{
	Repository* copie_repo = createRepository();
	DynamicArray* ex_da_address;
	ex_da_address = copie_repo->electronice;
	DynamicArray* copie_vector_dinamic = copyDynamicArray(repository->electronice);

	copie_repo->electronice = copie_vector_dinamic;
	destroyDynamicArray(ex_da_address);
	return copie_repo;
}

/*
	Descriere: Cauta obiectul specificat dupa id in memorie

		repository - pointer al unui obiect de tip Repository => efectul se produce direct in memorie
		p - obiect de tip TElement

	Returneaza -1 in cazul in care obiectul nu exista in memorie
				pozitia elementului din lista daca acesta a fost gasit
*/
int areElectronic(Repository* repository, int id) 
{
	return getPosition(repository->electronice, id);
}

/*
	Descriere: Adauga obiectul de tip Electronic in lista aflata in Containerul din Repository

		repository - pointer al unui obiect de tip Repository => efectul se produce direct in memorie
		p - obiect de tip TElement

	Returneaza -1 in cazul in care obiectul exista deja in memorie
				0 daca adaugarea a fost efectuata cu success
*/
int adaugaElectronic(Repository* repository, Electronic* electr) 
{
	if (areElectronic(repository, getId(electr)) != -1) {
		return -1;
	}
	addElement(repository->electronice, electr);
	return 0;
}

/*
	Descriere: Modifica obiectul specificat dupa id daca acesta exista; schimba doar cantitatea si/sau pretul

		repository - pointer al unui obiect de tip Repository => efectul se produce direct in memorie
		p - obiect de tip TElement

	Returneaza -2 in cazul in care obiectul nu exista in memorie
				0 daca modificarea a fost efectuata cu success
*/
int modificaElectronic(Repository* repository, Electronic* electr)
{
	//verificam existenta obiectului (returnam -2 daca NU exista)
	int poz = areElectronic(repository, getId(electr));
	if (poz == -1) {
		return -2;
	}
	updateElement(repository->electronice, electr);
	return 0;
}

/*
	Descriere: Stergem obiectul specificat dupa id daca acesta exista

		repository - pointer al unui obiect de tip Repository => efectul se produce direct in memorie
		p - obiect de tip TElement

	Returneaza -2 in cazul in care obiectul nu exista in memorie
				0 daca stergerea a fost efectuata cu success
*/
int stergeElectronic(Repository* repository, int id)
{
	//verificam existenta obiectului (returnam -2 daca NU exista)
	int poz = areElectronic(repository, id);
	if (poz == -1) {
		return -2;
	}
	deleteElement(repository->electronice, poz);
	return 0;
}

/*
	Returneaza lista de elemente
*/
TElement* getAll(Repository* repository)
{
	return getAllElems(repository->electronice);
}

/*
	Elibereaza memoria alocata in Heap de catre Repository
		repository - pointer al unui obiect de tip Repository => efectul se produce direct in memorie
*/
void destroyRepository(Repository* repository)
{
	if (repository == NULL)
		return;

	destroyDynamicArray(repository->electronice);
	free(repository);
}