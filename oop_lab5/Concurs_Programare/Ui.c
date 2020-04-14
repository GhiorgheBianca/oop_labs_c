#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Participant.h"
#include"Controller.h"
#include"Vector.h"
#include"Ui.h"


void Ui_Adaugare_Participant(Concurs* Participanti)
{
	char nume[26];
	char prenume[26];

	printf("Introduceti numele participantului: ");
	scanf("%s", nume);

	printf("Introduceti prenumele participantului: ");
	scanf("%s", prenume);

	printf("Introduceti scorul: ");
	char nr[26];
	

	int j,ok,scor;
	while(1)
	{
		scanf("%s", nr);
		ok = 1;
		for(j=0;j<=strlen(nr)-1 && ok==1 ;j++)
			if (strchr("0123456789",nr[j]) == 0)
			{
				ok=0;
			}
		if (ok == 1)
		{
			scor = atoi(nr);
			break;
		}
		else
		{
			printf("Valoare numerica invalida! Reintroduceti!\n");
		}

		
	}

	ok = Srv_Adaugare_Participant(Participanti, nume, prenume, scor);

	if (ok %2==0)
		printf("Nume invalid!\n");
	if(ok%3==0)
		printf("Prenume invalid!\n");
	if (ok % 5 == 0)
		printf("Scor invalid!\n");




}

void Ui_Tipareste_Participanti(Concurs* Concurenti)
{
	printf("Participanti: \n");
	int i;
	VECTOR* Participanti = Concurenti->totiParticipantii;
	for (i = 0; i < Participanti->Lg; i++)
	{
		printf("Participant %d : ", i);
		printf("nume: %s, prenume: %s, scoruri: %d\n", Get_Nume(Participanti->Elems[i]), Get_Prenume(Participanti->Elems[i]),Get_Scor(Participanti->Elems[i]));
		
	}
}

void Ui_Actualizare_Participant(Concurs* Participanti)
{
	char nume[26];
	char prenume[26];

	printf("Adaugati numele participantului de modificat: ");
	scanf("%s", nume);

	printf("Adaugati prenumele participantului de modificat: ");
	scanf("%s", prenume);

	printf("Introduceti noul scor: ");
	char nr[26];

	int j, ok, scor;
	while (1)
	{
		scanf("%s", nr);
		ok = 1;
		for (j = 0; j <= strlen(nr) - 1 && ok == 1; j++)
			if (strchr("0123456789", nr[j]) == 0)
			{
				ok = 0;
			}
		if (ok == 1)
		{
			scor = atoi(nr);
			break;
		}
		else
		{
			printf("Valoare numerica invalida! Reintroduceti!\n");
		}


	}

	ok = Srv_Actualizare_Participant(Participanti, nume, prenume, scor);

	if (ok == 0)
		printf("Participant inexistent!\n");

}

void Ui_Stergere_Participant(Concurs* Participanti)
{
	char nume[26];
	char prenume[26];

	printf("Adaugati numele participantului de sters: ");
	scanf("%s", nume);

	printf("Adaugati numele participantului de sters: ");
	scanf("%s", prenume);

	int ok = Srv_Stergere_Participant(Participanti, nume, prenume);

	if (ok == 0)
		printf("Participant inexistent!\n");

}

void Ui_Filtrare_Participanti(Concurs* Participanti)
{
	int referinta, command;

	printf("Filtreaza dupa cei care au:\n1. un scor mai mic decat o valoare\n2. un scor mai mare decat o valoare data\n");
	printf("Introduceti numarul sub-comenzii: ");
	scanf("%d", &command);

	printf("Introduceti media de referinta: ");
	scanf("%d", &referinta);

	VECTOR* v;
	
	if (command == 1)
		v = Srv_Filtrare(Participanti, referinta, este_mai_mic);
	else if (command == 2)
		v = Srv_Filtrare(Participanti, referinta, este_mai_mare);

	Ui_Tipareste_Participanti(&v);
	Distruge_Vector(v);

}

void Ui_Sortare(Concurs* Participanti)
{
	Srv_Sortare(Participanti);
	Ui_Tipareste_Participanti(Participanti);
}

int Ui_Undo(Concurs* Participanti)
{
	int result = Srv_Undo(Participanti);
	Ui_Tipareste_Participanti(&(Participanti->totiParticipantii));
	return result;
}