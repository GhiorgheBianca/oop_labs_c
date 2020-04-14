#include"Repo.h"
#include"Participant.h"
#include"Controller.h"
#include"Validator.h"
#include"Vector.h"
#include<stdlib.h>
#include<assert.h>
#include"Teste.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>


void Test_Creeaza_Get_Distruge()
{

	PARTICIPANT* p1;
	p1 = Creeaza_Participant("Grigoras", "Bianca", 5);
	
	char* nume;
	char* prenume;
	int scor;
	nume = Get_Nume(p1);
	prenume = Get_Prenume(p1);
	scor = Get_Scor(p1);

	assert(strcmp(nume, "Grigoras") == 0);
	assert(strcmp(prenume, "Bianca") == 0);
	assert(scor == 5);
	
	Distruge_Participant(p1);
	

}


void Test_Actualizare()
{
	Concurs v = Creeaza_Concurs();

	int ok = Srv_Adaugare_Participant(&v, "Grigoras", "Bianca", 5);
	ok = Srv_Adaugare_Participant(&v, "Marcu", "Bianca", 5);
	ok = Srv_Adaugare_Participant(&v, "Popescu", "Bianca", 5);

	ok = Srv_Actualizare_Participant(&v, "Marcu", "Bianca", 7);
	assert(ok == 1);

	int scor;
	scor = Get_Scor(v.totiParticipantii->Elems[1]);
	assert(scor == 7);

	ok= Srv_Actualizare_Participant(&v, "Marcu", "Roxana", 7);
	assert(ok == 0);

	Distruge_Concurs(&v);


}

void Test_Validator()
{
	PARTICIPANT* p1;
	PARTICIPANT* p2;
	PARTICIPANT* p3;
	PARTICIPANT* p4;

	p1 = Creeaza_Participant("Grigoras", "Bianca", 5);
	p2 = Creeaza_Participant("", "Bianca", 5);
	p3 = Creeaza_Participant("Grigoras", "", 5);
	p4 = Creeaza_Participant("Grigoras", "Bianca", -1);

	assert(Validare_Participant(p1) == 1);
	assert(Validare_Participant(p2) == 2);
	assert(Validare_Participant(p3) == 3);
	assert(Validare_Participant(p4) == 5);

	Distruge_Participant(p1);
	Distruge_Participant(p2);
	Distruge_Participant(p3);
	Distruge_Participant(p4);


}

void Test_Srv_Adaugare()
{
	Concurs v;
	v = Creeaza_Concurs();
	v.totiParticipantii->Capacitate = 2;

	int ok = Srv_Adaugare_Participant(&v, "Grigoras", "Bianca", 5);
	ok = Srv_Adaugare_Participant(&v, "Marcu", "Bianca", 5);
	ok = Srv_Adaugare_Participant(&v, "Popescu", "Bianca", 5);

	assert(ok == 1);
	assert(Get_Lungime(v.totiParticipantii) == 3);
	assert(strcmp(Get_Nume(v.totiParticipantii->Elems[0]), "Grigoras") == 0);

	ok = Srv_Adaugare_Participant(&v, "Lavinia", "", -1);
	assert(ok != 1);

	Distruge_Concurs(&v);



}

void Test_Srv_Stergere()
{

	int ok;
	Concurs v;
	v = Creeaza_Concurs();

	ok = Srv_Adaugare_Participant(&v, "Marcu", "Lavinia", 3);
	ok = Srv_Adaugare_Participant(&v, "Grigoras", "Bianca", 4);
	ok = Srv_Adaugare_Participant(&v, "Enache", "Ana", 5);
	
	char* nume;
	nume = Get_Nume(v.totiParticipantii->Elems[1]);
	assert(strcmp(nume, "Grigoras") == 0);

	ok = Srv_Stergere_Participant(&v, "Grigoras", "Bianca");
	assert(ok == 1);
	nume = Get_Nume(v.totiParticipantii->Elems[1]);
	assert(strcmp(nume, "Enache") == 0);
	int scor = Get_Scor(v.totiParticipantii->Elems[1]);
	assert(scor == 5);

	ok = Srv_Stergere_Participant(&v, "Gabor", "Bianca");
	assert(ok == 0);

	Distruge_Concurs(&v);
}


void Test_Filtrare()
{
	int scor1;
	int scor2;

	int i, ok;

	Concurs v1;
	VECTOR* v2;
	v1 = Creeaza_Concurs();
	//v2 = Creeaza_Concurs();
	ok = Srv_Adaugare_Participant(&v1, "Marcu", "Lavinia", 4);
	ok = Srv_Adaugare_Participant(&v1, "Grigoras", "Bianca", 10);

	v2 = Srv_Filtrare(&v1, 9, este_mai_mic);
	assert(v2->Lg == 1);
	Distruge_Vector(v2);

	v2 = Srv_Filtrare(&v1, 3, este_mai_mare);
	assert(v2->Lg == 2);
	Distruge_Vector(v2);

	Distruge_Concurs(&v1);
	

}
	

void Test_Sortare()
{
	
	int ok;

	Concurs v;
	v = Creeaza_Concurs();
	ok = Srv_Adaugare_Participant(&v, "Marcu", "Lavinia", 3);
	ok = Srv_Adaugare_Participant(&v, "Grigoras", "Bianca", 4);
	ok = Srv_Adaugare_Participant(&v, "Enache", "Ana", 5);

	Srv_Sortare(&v);
	char* nume = Get_Nume(v.totiParticipantii->Elems[2]);
	assert(strcmp(nume, "Marcu") == 0);

	Distruge_Concurs(&v);

}


void Test_Undo()
{
	Concurs concurs = Creeaza_Concurs();
	Srv_Adaugare_Participant(&concurs, "Marcu", "Lavinia", 3);
	Srv_Adaugare_Participant(&concurs, "Grigoras", "Bianca", 4);
	Srv_Undo(&concurs);
	VECTOR* l = copyList(concurs.totiParticipantii, Copie_Participant);
	assert(Get_Lungime(l) == 1);
	Distruge_Vector(l);

	Srv_Undo(&concurs);
	l = copyList(concurs.totiParticipantii, Copie_Participant);
	assert(Get_Lungime(l) == 0);
	Distruge_Vector(l);

	assert(Srv_Undo(&concurs) != 0);
	assert(Srv_Undo(&concurs) != 0);
	assert(Srv_Undo(&concurs) != 0);

	Distruge_Concurs(&concurs);
}


void Teste()
{
	Test_Creeaza_Get_Distruge();
	Test_Validator();
	Test_Srv_Adaugare();
	Test_Actualizare();
	Test_Srv_Stergere();
	Test_Filtrare();
	Test_Sortare();
	Test_Undo();
	
}