#include"Controller.h"
#include"Vector.h"
#include<stdio.h>

VECTOR* Creeaza_Vector(DestroyFct f)
{
	VECTOR* v = malloc(sizeof(VECTOR));
	v->Capacitate = 100;
	v->Elems = malloc(sizeof(ElemType)*v->Capacitate);
	v->Lg = 0;
	v->destroy = f;
	return v;
}

int Get_Lungime(VECTOR* v)
{
	return v->Lg;
}

void Distruge_Vector(VECTOR* v)
{
	int i;
	for (i = 0; i < v->Lg; i++)
	{
		v->destroy(v->Elems[i]);
	}
	free(v->Elems);
	free(v);
}

ElemType removeLast(VECTOR* l) {
	ElemType rez = l->Elems[l->Lg - 1];
	l->Lg -= 1;
	return rez;
}

VECTOR* copyList(VECTOR* l, CopyFct cf) {
	VECTOR* rez = Creeaza_Vector(l->destroy);
	for (int i = 0; i < Get_Lungime(l); i++) {
		ElemType p = l->Elems[i];
		Repo_Adaugare_Participant(rez, cf(p));
	}
	return rez;
}