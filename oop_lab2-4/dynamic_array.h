#pragma once
#include "obiect_electronic.h"
#include <stdbool.h>
#define CAPACITY 10

typedef Electronic* TElement;

typedef struct
{
	TElement* elems;
	// dimensiunea actuala a vectorului
	int length;
	// capacitatea maxima a vectorului
	int capacity;
} DynamicArray;

/*
	Creeaza obiectul de tip DynamicArray
*/
DynamicArray* createDynamicArray(int capacity);

/*
	Copiaza un obiectul de tip DynamicArray si returneaza un pointer catre copie
*/
DynamicArray* copyDynamicArray(DynamicArray* vector_dinamic);

/*
	Elibereaza memoria alocata in Heap de vectorul dinamic
*/
void destroyDynamicArray(DynamicArray* vector_dinamic);

/*
	Redimensioneaza vectorul, alocand mai multa memorie
*/
int ensureCapacity(DynamicArray* vector_dinamic);

/*
	Adauga un element nou in vectorul dinamic
*/
void addElement(DynamicArray* vector_dinamic, TElement elem);

/*
	Cauta obiectul specificat dupa id in memorie
*/
int getPosition(DynamicArray* vector_dinamic, int id);

/*
	Actualizeaza pretul si/sau cantitatea unui element din vector
*/
void updateElement(DynamicArray* vector_dinamic, TElement elem);

/*
	Sterge un element din vectorul dinamic
*/
void deleteElement(DynamicArray* vector_dinamic, int position);

/*
	Obtine lungimea vectorului dinamic
*/
int getLength(DynamicArray* vector_dinamic);

/*
	Obtine valoarea obiectului de pe pozitia cautata
*/
TElement getElement(DynamicArray* vector_dinamic, int position);

/*
	Returneaza lista de elemente
*/
TElement* getAllElems(DynamicArray* vector_dinamic);

/*
	Compara doua numere intregi
	Returneaza true daca primul numar este mai mare decat al doilea
			   false daca al doilea numar este mai mare decat primul
*/
bool crescator(double first_value, double second_value);

/*
	Compara doua numere intregi
	Returneaza true daca al doilea numar este mai mare decat primul
			   false daca primul numar este mai mare decat al doilea
*/
bool descrescator(double first_value, double second_value);

/*
	Initializeaza un nou tip: function, pentru sortare crescatoare/descrescatoare
*/
typedef bool (*function) (double, double);

/*
	Sorteaza vectorul de produse crescator/descrescator
*/
void ordoneaza(DynamicArray* vector_dinamic, int length, function compare);