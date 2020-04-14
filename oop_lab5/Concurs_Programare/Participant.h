#pragma once
#include"Participant.h"


typedef struct {
	char* Nume;
	char* Prenume;
	int Scor;
}PARTICIPANT;

PARTICIPANT* Creeaza_Participant(char* _Nume, char* _Prenume, int _Scor);
/**
pre: nume-char, prenume-char, scor - vector de int
post: p-PARTICIPANT
*/

PARTICIPANT* Copie_Participant(PARTICIPANT* p);

char* Get_Nume(PARTICIPANT* p);
//Metoda get pentru numele unui participant

char* Get_Prenume(PARTICIPANT* p);
//Metoda get pentru prenumele unui participant

int Get_Scor(PARTICIPANT* p);
//Metoda get pentru scorul unui participant

void Set_Nume(PARTICIPANT* p, char* nume);
//Metoda set pentru numele unui participant

void Set_Prenume(PARTICIPANT* p, char* prenume);
//Metoda set pentru prenumele unui participant

void Set_Scor(PARTICIPANT* p, int Scor);
//Metoda set pentru prenumele unui participant

void Distruge_Participant(PARTICIPANT* p);
//Metoda distrugere participant