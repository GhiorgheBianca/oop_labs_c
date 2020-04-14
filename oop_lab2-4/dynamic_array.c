#include "dynamic_array.h"
#include <stdlib.h>

/*
	Creeaza obiectul de tip DynamicArray in memoria Heap; seteaza obiectul de tip DynamicArray
	Returneaza un pointer al unui obiect de tip DynamicArray
*/
DynamicArray* createDynamicArray(int capacity)
{
	DynamicArray* vector_dinamic = (DynamicArray*)malloc(sizeof(DynamicArray));

	// verificam daca spatiul a fost alocat
	if (vector_dinamic == NULL)
		return NULL;

	vector_dinamic->capacity = capacity;
	vector_dinamic->length = 0;

	// alocam spatiu pentru elemente
	vector_dinamic->elems = (TElement*)malloc(capacity * sizeof(TElement));
	if (vector_dinamic->elems == NULL)
		return NULL;

	return vector_dinamic;
}

/*
	Copiaza un obiectul de tip DynamicArray
		vector_dinamic - pointer al unui obiect de tip DynamicArray
	Returneaza un pointer catre copie
*/
DynamicArray* copyDynamicArray(DynamicArray* vector_dinamic)
{
	DynamicArray* copie_vector_dinamic = createDynamicArray(vector_dinamic->capacity);

	for (int i = 0; i < vector_dinamic->length; i++)
		copie_vector_dinamic->elems[i] = copyElectronic(vector_dinamic->elems[i]);

	copie_vector_dinamic->capacity = vector_dinamic->capacity;
	copie_vector_dinamic->length = vector_dinamic->length;
	return copie_vector_dinamic;
}

/*
	Elibereaza memoria alocata in Heap de vectorul dinamic
		vector_dinamic - pointer al unui obiect de tip DynamicArray => efectul se produce direct in memorie
*/
void destroyDynamicArray(DynamicArray* vector_dinamic)
{
	if (vector_dinamic == NULL)
		return;

	// dealocam memoria fiecarui element din vectorul dinamic
	for (int i = 0; i < vector_dinamic->length; i++)
		destroyElectronic(vector_dinamic->elems[i]);
	// vectorul contine pointeri: *Electronic

	// elibereaza spatiul alocat pentru elemente
	free(vector_dinamic->elems);
	vector_dinamic->elems = NULL;

	// elibereaza spatiul alocat pentru vectorul dinamic
	free(vector_dinamic);
}

/*
	Redimensioneaza vectorul, alocand mai multa memorie
	Daca nu poate fi alocat mai mult spatiu returneaza -1, altfel returneaza 0
*/
int ensureCapacity(DynamicArray* vector_dinamic)
{
	if (vector_dinamic == NULL)
		return -1;

	vector_dinamic->capacity *= 2;

	// version 1 - folosind realloc
	//TElement* aux = (TElement*)realloc(vector_dinamic->elems, arr->capacity * sizeof(TElement));
	//if (aux == NULL)
	//	return -1;
	//vector_dinamic->elems = aux;

	// version 2 - alocand memorie noua, copiaza tot si dealoca memoria veche
	TElement* aux = (TElement*)malloc(vector_dinamic->capacity * sizeof(TElement));
	if (aux == NULL)
		return -1;
	for (int i = 0; i < vector_dinamic->length; i++)
		aux[i] = vector_dinamic->elems[i];
	free(vector_dinamic->elems);
	vector_dinamic->elems = aux;

	return 0;
}

/*
	Descriere: Adauga un element nou in vectorul dinamic

		vector_dinamic - pointer al unui obiect de tip DynamicArray => efectul se produce direct in memorie
		elem - obiect de tip TElement
*/
void addElement(DynamicArray* vector_dinamic, TElement elem)
{
	if (vector_dinamic == NULL)
		return;
	if (vector_dinamic->elems == NULL)
		return;

	// redimensioneaza vectorul daca este nevoie
	if (vector_dinamic->length == vector_dinamic->capacity)
		ensureCapacity(vector_dinamic);
	vector_dinamic->elems[vector_dinamic->length++] = elem;
}

/*
	Descriere: Cauta obiectul specificat dupa id in memorie

		vector_dinamic - pointer al unui obiect de tip DynamicArray => efectul se produce direct in memorie
		id - intreg, identificator unic

	Returneaza -1 in cazul in care obiectul nu exista in memorie
				pozitia elementului din lista daca acesta a fost gasit
*/
int getPosition(DynamicArray* vector_dinamic, int id)
{
	for (int i = 0; i < vector_dinamic->length; ++i) {
		if (getId(vector_dinamic->elems[i]) == id) {
			return i;
		}
	}
	return -1;
}

/*
	Descriere: Modifica obiectul specificat dupa id daca acesta exista; schimba doar cantitatea si/sau pretul

		vector_dinamic - pointer al unui obiect de tip DynamicArray => efectul se produce direct in memorie
		elem - obiect de tip TElement
*/
void updateElement(DynamicArray* vector_dinamic, TElement elem)
{
	if (vector_dinamic == NULL)
		return;
	if (vector_dinamic->elems == NULL)
		return;

	TElement* vector = vector_dinamic->elems;
	if (elem->pret != 0)
		vector[getPosition(vector_dinamic, elem->id)]->pret = elem->pret;
	vector[getPosition(vector_dinamic, elem->id)]->cantitate = elem->cantitate;
}

/*
	Descriere: Sterge un element din vectorul dinamic

		vector_dinamic - pointer al unui obiect de tip DynamicArray => efectul se produce direct in memorie
		position - pozitia in vector a elementului care va trebui sters
*/
void deleteElement(DynamicArray* vector_dinamic, int position)
{
	if (vector_dinamic == NULL)
		return;
	if (vector_dinamic->elems == NULL)
		return;

	Electronic* address;
	address = vector_dinamic->elems[position];
	for (int i = position; i < vector_dinamic->length - 1; i++)
	{
		vector_dinamic->elems[i] = vector_dinamic->elems[i + 1];
	}
	vector_dinamic->elems[vector_dinamic->length - 1] = copyElectronic(vector_dinamic->elems[vector_dinamic->length - 1]);
	--vector_dinamic->length;
	destroyElectronic(vector_dinamic->elems[vector_dinamic->length]);
	destroyElectronic(address);
}

/*
	Descriere: Obtine lungimea vectorului dinamic
		vector_dinamic - pointer al unui obiect de tip DynamicArray => efectul se produce direct in memorie
	Returneaza lungimea vectorului dinamic, respectiv -1 in cazul in care vectorul nu a fost alocat
*/
int getLength(DynamicArray* vector_dinamic)
{
	if (vector_dinamic == NULL)
		return -1;

	return vector_dinamic->length;
}

/*
	Descriere: Obtine valoarea obiectului de pe pozitia cautata

		vector_dinamic - pointer al unui obiect de tip DynamicArray => efectul se produce direct in memorie
		position - pozitia in vector a elementului cautat

	Returneaza valoarea obiectului de pe pozitia cautata, respectiv NULL in cazul in care pozitia nu se afla in vector
*/
TElement getElement(DynamicArray* vector_dinamic, int position)
{
	if (vector_dinamic == NULL)
		return NULL;
	if (position < 0 || position >= vector_dinamic->length)
		return NULL;
	return vector_dinamic->elems[position];
}

/*
	Returneaza lista de elemente
*/
TElement* getAllElems(DynamicArray* vector_dinamic)
{
	return vector_dinamic->elems;
}

/*
	Compara doua numere intregi
	Returneaza true daca primul numar este mai mare decat al doilea
			   false daca al doilea numar este mai mare decat primul
*/
bool crescator(double first_value, double second_value)
{
	return first_value > second_value;
}

/*
	Compara doua numere intregi
	Returneaza true daca al doilea numar este mai mare decat primul
			   false daca primul numar este mai mare decat al doilea
*/
bool descrescator(double first_value, double second_value)
{
	return first_value < second_value;
}

/*
	Initializeaza un nou tip: function, pentru sortare crescatoare/descrescatoare
*/
typedef bool (*function) (double, double);

/*
	Sorteaza vectorul de produse crescator/descrescator

		electronice[] - lista cu elemente de tip Electronic
		length - lungimea listei de produse
		function - functia de comparare; decide daca sortarea va fi crescatoare sau descrescatoare
*/
void ordoneaza(DynamicArray* vector_dinamic, int length, function compare)
{
	TElement aux;
	TElement* vector_elemente = vector_dinamic->elems;
	int i = 0, j = 0;
	for (i = 0; i < length - 1; i++)
	{
		for (j = i + 1; j < length; j++)
		{
			if ((*compare)(vector_elemente[i]->pret, vector_elemente[j]->pret))   //electronice[i].pret > electronice[j].pret)
			{
				aux = vector_elemente[i];
				vector_elemente[i] = vector_elemente[j];
				vector_elemente[j] = aux;
			}
			else if (vector_elemente[i]->pret == vector_elemente[j]->pret)
			{
				if ((*compare)(vector_elemente[i]->cantitate, vector_elemente[j]->cantitate))   //electronice[i].cantitate > electronice[j].cantitate)
				{
					aux = vector_elemente[i];
					vector_elemente[i] = vector_elemente[j];
					vector_elemente[j] = aux;
				}
			}
		}
	}
}