#include"Controller.h"
#include"Vector.h"
#include<stdio.h>
#include<string.h>


Concurs Creeaza_Concurs()
{
	Concurs rez;
	rez.totiParticipantii = Creeaza_Vector(Distruge_Participant);
	rez.undoList = Creeaza_Vector(Distruge_Vector);
	return rez;
}


int Srv_Adaugare_Participant(Concurs* Participanti, char* nume, char* prenume, int scor)
{
	PARTICIPANT* p = Creeaza_Participant(nume, prenume, scor);
	VECTOR* toUndo = copyList(Participanti->totiParticipantii, Copie_Participant);
	int v = Validare_Participant(p);
	if (v == 1)
	{
		Repo_Adaugare_Participant(Participanti->totiParticipantii, p);
		Repo_Adaugare_Participant(Participanti->undoList, toUndo);
	}
	else
	{
		Distruge_Participant(p);
		Distruge_Vector(toUndo);
		return v;
	}
	return 1;
}


int Srv_Actualizare_Participant(Concurs* Concurenti, char* nume, char* prenume, int scor)
{
	int i;
	char* nume_curent;
	char* prenume_curent;
	VECTOR* Participanti = Concurenti->totiParticipantii;
	VECTOR* toUndo = copyList(Concurenti->totiParticipantii, Copie_Participant);
	for (i = 0; i < Participanti->Lg; i++)
	{
		nume_curent = Get_Nume(Participanti->Elems[i]);
		prenume_curent = Get_Prenume(Participanti->Elems[i]);

		if (strcmp(nume_curent, nume) == 0 && strcmp(prenume_curent, prenume) == 0)
		{
			Repo_Modifica_Participant(Participanti, i, scor);
			Repo_Adaugare_Participant(Concurenti->undoList, toUndo);
			return 1;
		}
	}
	Distruge_Vector(toUndo);
	return 0;
	
}

int Srv_Stergere_Participant(Concurs* Concurenti, char* nume, char* prenume)
{
	int i;
	char* nume_curent;
	char* prenume_curent;
	VECTOR* Participanti = Concurenti->totiParticipantii;
	VECTOR* toUndo = copyList(Concurenti->totiParticipantii, Copie_Participant);
	for (i = 0; i < Participanti->Lg; i++)
	{
		nume_curent = Get_Nume(Participanti->Elems[i]);
		prenume_curent = Get_Prenume(Participanti->Elems[i]);
		if (strcmp(nume_curent, nume) == 0 && strcmp(prenume_curent, prenume) == 0)
		{
			Repo_Sterge_Participant(Participanti, i);
			Repo_Adaugare_Participant(Concurenti->undoList, toUndo);
			return 1;
		}
	}
	Distruge_Vector(toUndo);
	return 0;


}


bool este_mai_mare(int first_value, int second_value)
{
	return first_value > second_value;
}

bool este_mai_mic(int first_value, int second_value)
{
	return first_value < second_value;
}

typedef bool (*function) (int, int);

VECTOR* Srv_Filtrare(Concurs* Concurenti,int referinta,function compare)
{

	VECTOR* v;
	VECTOR* Participanti = Concurenti->totiParticipantii;
	v = Creeaza_Vector(Distruge_Participant);
	int i, j;
	int scor_curent;
	for (i = 0; i < Participanti->Lg; i++)
	{
		scor_curent = Get_Scor(Participanti->Elems[i]);

		if ((*compare)(scor_curent,referinta)) //scor_curent < referinta
		{
			v->Elems[v->Lg] = Copie_Participant(Participanti->Elems[i]);
			v->Lg++;
		}
	}
	return v;
	
}

void Srv_Sortare(Concurs* Concurenti)
{
	int i, j;
	char nume1[26];
	char nume2[26];
	
	PARTICIPANT* aux;
	VECTOR* Participanti = Concurenti->totiParticipantii;
	for (i = 0; i < Participanti->Lg - 1; i++)
	{
		for (j = i + 1; j < Participanti->Lg; j++)
		{
			strcpy(nume1, Get_Nume(Participanti->Elems[i]));
			strcpy(nume2, Get_Nume(Participanti->Elems[j]));
			if (strcmp(nume1, nume2) > 0)
			{
				aux = Participanti->Elems[i];
				Participanti->Elems[i] = Participanti->Elems[j];
				Participanti->Elems[j] = aux;
			}

		}
	}
}

void Distruge_Concurs(Concurs* Participanti)
{
	Distruge_Vector(Participanti->totiParticipantii);
	Distruge_Vector(Participanti->undoList);
}

int Srv_Undo(Concurs* Participanti)
{
	VECTOR* undoList = Participanti->undoList;
	if (undoList->Lg == 0) {
		return 1;
	}
	VECTOR* l = removeLast(Participanti->undoList);
	Distruge_Vector(Participanti->totiParticipantii);
	Participanti->totiParticipantii = l;
	return 0;
}