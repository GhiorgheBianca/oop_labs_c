#include <assert.h>
#include <string.h>
#include "obiect_electronic.h"
#include "repository.h"
#include "service.h"
#include "validator.h"
#include "teste.h"

void testElectronic() {
	Electronic* p = creeazaElectronic(1, "laptop", "Asus", "1268B2A", 6099.99, 120);

	assert(getId(p) == 1);
	assert(strcmp(getTip(p), "laptop") == 0);
	assert(strcmp(getProducator(p), "Asus") == 0);
	assert(strcmp(getModel(p), "1268B2A") == 0);
	assert(getPret(p) == 6099.99);
	assert(getCantitate(p) == 120);

	destroyElectronic(p);
}

void testAdaugaRepo() {
	Repository* repo = createRepository();

	Electronic* p = creeazaElectronic(1, "laptop", "Asus", "1268B2A", 6099.99, 120);
	assert(adaugaElectronic(repo, p) == 0);

	DynamicArray* vector_dinamic = repo->electronice;

	assert(vector_dinamic->length == 1);
	assert(getId(vector_dinamic->elems[0]) == getId(p));
	assert(strcmp(getTip(vector_dinamic->elems[0]), getTip(p)) == 0);
	assert(strcmp(getProducator(vector_dinamic->elems[0]), getProducator(p)) == 0);
	assert(strcmp(getModel(vector_dinamic->elems[0]), getModel(p)) == 0);
	assert(getPret(vector_dinamic->elems[0]) == getPret(p));
	assert(getCantitate(vector_dinamic->elems[0]) == getCantitate(p));

	assert(adaugaElectronic(repo, p) == -1);

	destroyRepository(repo);
}

void testAdaugaService() {
	Repository* repo = createRepository();
	Service* service = createService(repo);

	assert(adaugaElectronicService(service, 1, "laptop", "Asus", "1268B2A", 6099.99, 120) == 0);
	assert(adaugaElectronicService(service, 0, "", "", "", -1, -3) == 123456);
	assert(adaugaElectronicService(service, 1, "laptop", "Asus", "1268B2A", 6099.99, 120) == -1);

	destroyService(service);

	service = NULL;
	destroyService(service);
	repo = NULL;
	destroyRepository(repo);
}

void testModificaRepo() {
	Repository* repo = createRepository();

	Electronic* p = creeazaElectronic(1, "laptop", "Asus", "1268B2A", 6099.99, 120);

	assert(modificaElectronic(repo, p) == -2);

	adaugaElectronic(repo, p);
	p = creeazaElectronic(1, "laptop", "Asus", "1268B2A", 7599.99, 200);
	modificaElectronic(repo, p);

	DynamicArray* vector_dinamic = repo->electronice;

	assert(getId(vector_dinamic->elems[0]) == 1);
	assert(strcmp(getTip(vector_dinamic->elems[0]), "laptop") == 0);
	assert(strcmp(getProducator(vector_dinamic->elems[0]), "Asus") == 0);
	assert(strcmp(getModel(vector_dinamic->elems[0]), "1268B2A") == 0);
	assert(getPret(vector_dinamic->elems[0]) == getPret(p));
	assert(getCantitate(vector_dinamic->elems[0]) == getCantitate(p));

	destroyElectronic(p);
	destroyRepository(repo);
}

void testModificaService() {
	Repository* repo = createRepository();
	Service* service = createService(repo);

	assert(adaugaElectronicService(service, 1, "laptop", "Asus", "1268B2A", 6099.99, 120) == 0);
	assert(modificaElectronicService(service, 1, 5899.99, 95) == 0);
	assert(modificaElectronicService(service, 1, -1, -3) == 56);

	destroyService(service);
}

void testStergeRepo() {
	Repository* repo = createRepository();

	Electronic* e1 = creeazaElectronic(1, "laptop", "Asus", "1268B2A", 6099.99, 120);
	assert(stergeElectronic(repo, e1->id) == -2);
	adaugaElectronic(repo, e1);

	Electronic* e2 = creeazaElectronic(2, "frigider", "Phillips", "1268B2A", 1099.99, 105);
	adaugaElectronic(repo, e2);

	Electronic* e3 = creeazaElectronic(3, "laptop", "Lenovo", "256CF2A", 4599.99, 300);
	adaugaElectronic(repo, e3);

	Electronic* e4 = creeazaElectronic(4, "frigider", "Galleon", "678FR2B", 2000.87, 84);
	adaugaElectronic(repo, e4);

	DynamicArray* vector_dinamic = repo->electronice;
	assert(vector_dinamic->length == 4);

	stergeElectronic(repo, 2);
	assert(areElectronic(repo, 2) == -1);
	assert(vector_dinamic->length == 3);

	stergeElectronic(repo, 1);
	assert(areElectronic(repo, 1) == -1);
	assert(vector_dinamic->length == 2);

	stergeElectronic(repo, 4);
	assert(areElectronic(repo, 4) == -1);
	assert(vector_dinamic->length == 1);

	stergeElectronic(repo, 3);
	assert(areElectronic(repo, 3) == -1);
	assert(vector_dinamic->length == 0);

	destroyRepository(repo);
}

void testStergeService() {
	Repository* repo = createRepository();
	Service* service = createService(repo);

	Electronic* electr = creeazaElectronic(1, "laptop", "Asus", "1268B2A", 6099.99, 120);
	assert(adaugaElectronic(repo, electr) == 0);
	assert(stergeElectronicService(service, 1) == 0);
	assert(stergeElectronicService(service, 2) == -2);
	assert(stergeElectronicService(service, -1) == 1);

	destroyService(service);
}

void testTipareste()
{
	Repository* repo = createRepository();
	Service* service = createService(repo), * service_ordonat;
	Electronic* p;
	p = creeazaElectronic(1, "laptop", "Asus", "1268B2A", 6099.99, 120);
	adaugaElectronic(repo, p);
	p = creeazaElectronic(2, "frigider", "Phillips", "1268B2A", 1099.99, 105);
	adaugaElectronic(repo, p);
	p = creeazaElectronic(3, "laptop", "Lenovo", "256CF2A", 1099.99, 300);
	adaugaElectronic(repo, p);

	service_ordonat = tiparesteElectronicService(service);
	repo = service_ordonat->repository;
	DynamicArray* vector_dinamic = repo->electronice;
	assert(getId(vector_dinamic->elems[0]) == 1);
	assert(getId(vector_dinamic->elems[1]) == 2);
	assert(getId(vector_dinamic->elems[2]) == 3);
	assert(vector_dinamic->length == 3);

	destroyService(service);
}

void testVizualizareService() {
	Repository* repo = createRepository();
	Service* service = createService(repo), *service_ordonat;
	Electronic* p;
	p = creeazaElectronic(1, "laptop", "Asus", "1268B2A", 6099.99, 120);
	adaugaElectronic(repo, p);
	p = creeazaElectronic(2, "frigider", "Phillips", "1268B2A", 1099.99, 105);
	adaugaElectronic(repo, p);
	p = creeazaElectronic(3, "laptop", "Lenovo", "256CF2A", 1099.99, 300);
	adaugaElectronic(repo, p);

	service_ordonat = vizualizeazaService(service, "crescator");
	repo = service_ordonat->repository;
	DynamicArray* vector_dinamic = repo->electronice;
	assert(getId(repo->electronice->elems[0]) == 2);
	assert(getId(vector_dinamic->elems[1]) == 3);
	assert(getId(vector_dinamic->elems[2]) == 1);

	service_ordonat = vizualizeazaService(service, "descrescator");
	repo = service_ordonat->repository;
	vector_dinamic = repo->electronice;
	assert(getId(vector_dinamic->elems[0]) == 1);
	assert(getId(vector_dinamic->elems[1]) == 3);
	assert(getId(vector_dinamic->elems[2]) == 2);

	destroyService(service);
}

void testFiltrare()
{
	Repository* repo = createRepository();
	Service* service = createService(repo);
	Electronic* e1 = creeazaElectronic(1, "laptop", "Asus", "1268B2A", 6099.99, 120);
	adaugaElectronic(repo, e1);

	Electronic* e2 = creeazaElectronic(2, "frigider", "Phillips", "1268B2A", 6099.99, 105);
	adaugaElectronic(repo, e2);

	Electronic* e3 = creeazaElectronic(3, "laptop", "Asus", "256CF2A", 1099.99, 300);
	adaugaElectronic(repo, e3);

	Electronic* e4 = creeazaElectronic(4, "laptop", "Asus", "300AB2V", 2099.99, 105);
	adaugaElectronic(repo, e4);
	
	Service* service_filtrat = filtreazaService(service, "producator", "Asus", 0, 0);
	Repository* repo_filtrat = service_filtrat->repository;
	DynamicArray* vector_dinamic = repo_filtrat->electronice;
	assert(getId(vector_dinamic->elems[0]) == 1);
	assert(getId(vector_dinamic->elems[1]) == 3);
	assert(getId(vector_dinamic->elems[2]) == 4);
	assert(vector_dinamic->length == 3);
	destroyService(service_filtrat);
	
	service_filtrat = filtreazaService(service, "pret", "", 0, 6099.99);
	repo_filtrat = service_filtrat->repository;
	vector_dinamic = repo_filtrat->electronice;
	assert(getId(vector_dinamic->elems[0]) == 1);
	assert(getId(vector_dinamic->elems[1]) == 2);
	assert(vector_dinamic->length == 2);
	destroyService(service_filtrat);
	
	service_filtrat = filtreazaService(service, "cantitate", "", 105, 0);
	repo_filtrat = service_filtrat->repository;
	vector_dinamic = repo_filtrat->electronice;
	assert(getId(vector_dinamic->elems[0]) == 2);
	assert(getId(vector_dinamic->elems[1]) == 4);
	assert(vector_dinamic->length == 2);
	destroyService(service_filtrat);
	
	destroyService(service);
}

void testValidator() {
	Electronic* e_corect = creeazaElectronic(1, "laptop", "Asus", "1268B2A", 6099.99, 120);
	assert(validare_Electronic(e_corect) == 0);
	Electronic* e_tot_gresit = creeazaElectronic(0, "", "", "", -1, -3);
	assert(validare_Electronic(e_tot_gresit) == 123456);
	Electronic* e_id_tip_cant_gresit = creeazaElectronic(-2, "", "Asus", "1268B2A", 6099.99, -4);
	assert(validare_Electronic(e_id_tip_cant_gresit) == 126);
	Electronic* e_prod_model_gresit = creeazaElectronic(1, "laptop", "", "", 6099.99, 120);
	assert(validare_Electronic(e_prod_model_gresit) == 34);
	Electronic* e_tip_model_pret_gresit = creeazaElectronic(1, "", "Asus", "", -6, 120);
	assert(validare_Electronic(e_tip_model_pret_gresit) == 245);
	Electronic* e_model_gresit = creeazaElectronic(1, "laptop", "Asus", "", 6099.99, 120);
	assert(validare_Electronic(e_model_gresit) == 4);

	destroyElectronic(e_corect);
	destroyElectronic(e_tot_gresit);
	destroyElectronic(e_id_tip_cant_gresit);
	destroyElectronic(e_prod_model_gresit);
	destroyElectronic(e_tip_model_pret_gresit);
	destroyElectronic(e_model_gresit);
}

void testDynamicArray()
{
	DynamicArray* vector_dinamic = NULL;
	assert(getLength(vector_dinamic) == -1);
	assert(ensureCapacity(vector_dinamic) == -1);
	assert(getElement(vector_dinamic, 0) == NULL);
	vector_dinamic = createDynamicArray(2);
	assert(getLength(vector_dinamic) == 0);
	assert(getElement(vector_dinamic, -1) == NULL);

	if (vector_dinamic == NULL)
		assert(0);

	assert(vector_dinamic->capacity == 2);
	assert(vector_dinamic->length == 0);

	Electronic* e1 = creeazaElectronic(1, "laptop", "Asus", "1268B2A", 6099.99, 120);
	addElement(vector_dinamic, e1);
	assert(vector_dinamic->length == 1);

	Electronic* e2 = creeazaElectronic(2, "frigider", "Phillips", "1268B2A", 6099.99, 105);
	addElement(vector_dinamic, e2);
	assert(vector_dinamic->length == 2);

	// forteaza marirea capacitatii
	Electronic* e3 = creeazaElectronic(3, "laptop", "Asus", "256CF2A", 1099.99, 300);
	addElement(vector_dinamic, e3);
	assert(vector_dinamic->length == 3);
	assert(vector_dinamic->capacity == 4);

	Electronic* e = getElement(vector_dinamic, 0);
	assert(getId(e) == 1);

	// distruge vectorul dinamic si obiectele Electronice asociate
	destroyDynamicArray(vector_dinamic);

	vector_dinamic->elems = NULL;
	addElement(vector_dinamic, e);
	updateElement(vector_dinamic, e);
	deleteElement(vector_dinamic, 0);
	vector_dinamic = NULL;
	addElement(vector_dinamic, e);
	updateElement(vector_dinamic, e);
	deleteElement(vector_dinamic, 0);
	destroyDynamicArray(vector_dinamic);
}

void testObiectElectronic()
{
	Electronic* electr = NULL;
	assert(copyElectronic(electr) == NULL);
	assert(getId(electr) == -1);
	assert(getTip(electr) == NULL);
	assert(getProducator(electr) == NULL);
	assert(getModel(electr) == NULL);
	assert(getPret(electr) == -1);
	assert(getCantitate(electr) == -1);

	Electronic* e = creeazaElectronic(1, "laptop", "Asus", "1268B2A", 6099.99, 120);
	Electronic* copie_e = copyElectronic(e);
	assert(copie_e != e);
	assert(copie_e->id == e->id);
	assert(strcmp(copie_e->tip, e->tip) == 0);
	assert(strcmp(copie_e->producator, e->producator) == 0);
	assert(strcmp(copie_e->model, e->model) == 0);
	assert(copie_e->pret == e->pret);
	assert(copie_e->cantitate == e->cantitate);

	destroyElectronic(copie_e);
	destroyElectronic(electr);
	destroyElectronic(e);
}

void testCopy()
{
	Repository* repo = createRepository();
	DynamicArray* vector_dinamic = repo->electronice;
	Electronic* e1 = creeazaElectronic(1, "laptop", "Asus", "1268B2A", 6099.99, 120);
	addElement(vector_dinamic, e1);
	Electronic* e2 = creeazaElectronic(2, "frigider", "Phillips", "1268B2A", 6099.99, 105);
	addElement(vector_dinamic, e2);
	DynamicArray* copie_vector_dinamic = copyDynamicArray(vector_dinamic);
	assert(vector_dinamic != copie_vector_dinamic);
	assert(vector_dinamic->capacity == copie_vector_dinamic->capacity);
	assert(vector_dinamic->length == copie_vector_dinamic->length);
	for (int i = 0; i < vector_dinamic->length; i++)
		assert(copie_vector_dinamic->elems[i]->id == vector_dinamic->elems[i]->id);
	
	Repository* copie_repo = copyRepo(repo);
	assert(copie_repo != repo);

	destroyDynamicArray(copie_vector_dinamic);
	destroyRepository(copie_repo);
	destroyRepository(repo);
}

void ruleaza_teste() {
	testElectronic(); //corectat
	testAdaugaRepo(); //corectat
	testAdaugaService(); //corectat
	testModificaRepo(); //corectat
	testModificaService(); //corectat
	testStergeRepo(); //corectat
	testStergeService(); //corectat
	testTipareste(); //corectat
	testVizualizareService(); //corectat
	testFiltrare(); //corectat
	testValidator(); //corectat
	testDynamicArray(); //corectat
	testObiectElectronic(); //corectat
	testCopy(); //corectat
}