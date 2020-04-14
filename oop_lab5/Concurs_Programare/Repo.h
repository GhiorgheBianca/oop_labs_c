#pragma once
#include"Participant.h"
#include"Vector.h"
 
void Repo_Adaugare_Participant(VECTOR* Participanti, ElemType p);
/**
pre: Functia primeste ca parametri vectorul de participanti si un participant p.
post: v'=Participanti U {p}
*/



void Repo_Modifica_Participant(VECTOR* Participanti, int i, int scor);
/**
Functia primeste ca parametri vectorul de participanti, un nr intreg i si un pointer la un sir de scoruri.
Funtia sterge modifica scorul al participantului de pe pozitia i.

*/


void Repo_Sterge_Participant(VECTOR* Participanti, int i);
/**
Functia primeste ca parametri vectorul de participanti si un nr intreg i. Sterge din vector a i-le participant

*/

