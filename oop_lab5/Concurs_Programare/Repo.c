#include"Repo.h"
#include"Participant.h"
#include"Vector.h"
#include<stdlib.h>
#include<string.h>

void Repo_Adaugare_Participant(VECTOR* Participanti, ElemType p)
{
	Participanti->Lg++;
	if (Participanti->Lg >= Participanti->Capacitate)
	{
		Participanti->Capacitate = Participanti->Capacitate *2;
		ElemType* aux = malloc(Participanti->Capacitate * sizeof(ElemType));
		PARTICIPANT* aux2;
		int j;
		for (j = 0; j < Participanti->Lg - 1; j++)
		{
			aux[j] = Participanti->Elems[j];
		}
		aux2 = Participanti->Elems;
		Participanti->Elems = aux;
		free(aux2);
	}
	Participanti->Elems[Participanti->Lg - 1] = p;
}

void Repo_Modifica_Participant(VECTOR* Participanti, int i, int scor)
{
	Set_Scor(Participanti->Elems[i], scor);
}

void Repo_Sterge_Participant(VECTOR* Participanti, int i)
{
	int j;
	char* nume_curent ;
	char* prenume_curent;
	int scor_curent;
	for (j = i; j < Participanti->Lg - 1; j++)
	{
		nume_curent=Get_Nume(Participanti->Elems[j + 1]);
		prenume_curent = Get_Prenume(Participanti->Elems[j + 1]);
		scor_curent = Get_Scor(Participanti->Elems[j + 1]);

		Set_Nume(Participanti->Elems[j], nume_curent);
		Set_Prenume(Participanti->Elems[j], prenume_curent);
		Set_Scor(Participanti->Elems[j], scor_curent);
	}

	Distruge_Participant(Participanti->Elems[Participanti->Lg - 1]);
	Participanti->Lg--;

}
