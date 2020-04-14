#include "Participant.h"
#include <stdio.h>
#include <stdlib.h>


PARTICIPANT* Creeaza_Participant(char* _Nume, char* _Prenume, int _Scor) 
{
	PARTICIPANT* p = malloc(sizeof(PARTICIPANT));
	p->Nume = malloc(26*sizeof(char));
	strcpy(p->Nume, _Nume);
	p->Prenume = malloc(26 * sizeof(char));
	strcpy(p->Prenume, _Prenume);
	p->Scor = _Scor;

	return p;
}

PARTICIPANT* Copie_Participant(PARTICIPANT* p)
{
	PARTICIPANT* p1 = Creeaza_Participant(p->Nume, p->Prenume, p->Scor);
	/*
	p1->Nume = malloc(strlen(p->Nume) + 1);
	strcpy(p1->Nume, p->Nume);
	p1->Prenume = malloc(strlen(p->Prenume) + 1);
	strcpy(p1->Prenume, p->Prenume);
	p1->Scor = p->Scor;
	*/
	return p1;
}





char* Get_Nume(PARTICIPANT* p)
{
	return p->Nume;
}

char* Get_Prenume(PARTICIPANT* p)
{
	return p->Prenume;
}

int Get_Scor(PARTICIPANT* p)
{
	return p->Scor;
	
}

void Set_Nume(PARTICIPANT* p, char* nume)
{
	strcpy(p->Nume, nume);
}

void Set_Prenume(PARTICIPANT* p, char* prenume)
{
	strcpy(p->Prenume, prenume);
}

void Set_Scor(PARTICIPANT* p, int scor)
{
	p->Scor = scor;
}


void Distruge_Participant(PARTICIPANT* p)
{
	free(p->Nume);
	free(p->Prenume);
	free(p);
}
