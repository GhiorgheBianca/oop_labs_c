#pragma once

#include"Participant.h"

typedef void* ElemType;
typedef void(*DestroyFct) (ElemType);

typedef struct {
	ElemType* Elems;
	int Lg;
	int Capacitate;
	DestroyFct destroy;

}VECTOR;

VECTOR* Creeaza_Vector(DestroyFct f);
//Initializare vector

int Get_Lungime(VECTOR* v);
//Metoda get pentru un vector

void Distruge_Vector(VECTOR* v);
//Metoda distrugere vector

ElemType removeLast(VECTOR* l);
/**
Sterge ultimul element din lista
returneaza elementul sters
*/

typedef ElemType(*CopyFct) (ElemType);
VECTOR* copyList(VECTOR* l, CopyFct cf);
/**
Creeaza o copie dupa o lista
returneaza un VECTOR care contine aceleasi elemente ca l
*/