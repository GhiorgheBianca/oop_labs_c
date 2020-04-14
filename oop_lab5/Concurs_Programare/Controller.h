
#pragma once
#include <stdbool.h>
#include"Repo.h"
#include"Participant.h"
#include"Vector.h"

typedef struct {
	VECTOR* totiParticipantii;
	VECTOR* undoList;
} Concurs;

int Srv_Adaugare_Participant(Concurs* Participanti, char* nume, char* prenume, int scor);
/**
pre: Functia primeste ca parametri vectorul de participanti, numele, prenumele si scorul pentru un nou participant.
post: 1- Daca se poate efectua adaugarea; 0 in caz contrar
*/

int Srv_Actualizare_Participant(Concurs* Participanti, char* nume, char* prenume, int scor);
/**
pre: Functia primeste ca parametri vectorul de participanti, numele, prenumele si scorul pentru un participant.
post: 1-Daca s-a reusit actualizarea participantului; 0  in caz contrar.
*/

int Srv_Stergere_Participant(Concurs* Participanti, char* nume, char* prenume);
/**
pre: Functia primeste ca parametri vectorul de participanti, numele si prenumele pentru participantul de sters.
post: 1-Daca s-a reusit stergerea participantului; 0  in cazul in care participantul nu exista
*/


bool este_mai_mare(int first_value, int second_value);
bool este_mai_mic(int first_value, int second_value);

typedef bool (*function) (int, int);

VECTOR* Srv_Filtrare(Concurs* Participanti, int referinta);
/**
pre: Functia primeste ca parametri vectorul de participanti si un scor de referinta
post: se returneaza un vector care contine participantii cu un scor mai mic decat scorul de referinta
*/

void Srv_Sortare(Concurs* Participanti);
/**
Functia primeste un vector de participanti si intoarce vectorul sortat in functie de numele participantilor
*/

int Srv_Undo(Concurs* Participanti);
/**
Restaureaza vectorul ulterior ultimelor operatii
returneaza 0 daca e ok, 1 daca nu se mai poate face undo
*/

Concurs Creeaza_Concurs();
/**
Creeaza un obiect de tipul Concurs
*/

void Distruge_Concurs(Concurs* Participanti);
/**
Distruge un obiect de tipul Concurs
*/