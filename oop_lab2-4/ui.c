#include "ui.h"
#include <stdio.h>
#include <string.h>

/*
	Creeaza obiectul de tip UI in memoria Heap; seteaza obiectul de tip Service
	Returneaza un pointer al unui obiect de tip UI
*/
UI* createUI(Service* service)
{
	UI* ui = (UI*)malloc(sizeof(UI));
	if (ui == NULL)
	{
		return NULL;
	}
	ui->service = service;
	return ui;
}

/*
	Copiaza un obiectul de tip UI
		ui - pointer al unui obiect de tip UI
	Returneaza un pointer catre copie
*/
UI* copyUI(UI* ui)
{
	Repository* copie_repo = copyRepo(ui->service->repository);
	Service* copie_serv;
	UI* copie_ui;
	
	copie_serv = createService(copie_repo);
	copie_ui = createUI(copie_serv);
	return copie_ui;
}

/*
	Citeste un sir de caractere cu spatii din input.
	Input:	message - sir de caractere, mesaj ce va fi afisat utilizatorului
			maxStrSize - lungimea maxima a sirului de caractere care va fi citit
	Output: sirul de caractere care a fost citit.
*/
void readStringWithSpaces(const char* message, int maxStrSize, char str[])
{
	printf(message);
	fgets(str, maxStrSize, stdin);
	// the newline is also read so we must eliminate it from the string
	size_t size = strlen(str) - 1;
	if (str[size] == '\n')
		str[size] = '\0';
}

/*
	Citeste un numar intreg de la tastatura. Sesizeaza erorile si cere introducerea numarului pana cand datele sunt corecte.
	Input: trimite mesajul care trebuie afisat de fiecare data cand cere introducerea datelor
	Returneaza numarul.
*/
int readIntegerNumber(const char* message)
{
	char s[16];
	int res = 0;
	int flag = 0;
	int r = 0;

	while (flag == 0)
	{
		printf(message);
		scanf("%s", s);
		strcat(s, "\0");

		r = sscanf(s, "%d", &res);	// reads data from s and stores them as integer, if possible; returns 1 if successful
		flag = (r == 1);
		if (flag == 0)
			printf("Error reading number!\n");
	}
	return res;
}

/*
	Descriere: Trimite atributele obiectului de tip Electronic necesare modificarii produsului; apeleaza functia din Service

		ui - pointer al unui obiect de tip UI => efectul se produce direct in memorie
		code - intreg, retine valoarea id-ului sau 0 daca se modifica atat pretul cat si cantitatea

	Returneaza codul de eroare
*/
int ui_modificare(UI* ui, int code)
{
	int id = code, cantitate = 0;
	double pret = 0;
	if (code == 0)
	{
		id = readIntegerNumber("Id: ");
		printf("Pret: ");
		scanf_s("%lf", &pret);
	}
	cantitate = readIntegerNumber("Cantitate: ");

	return modificaElectronicService(ui->service, id, pret, cantitate);
}

/*
	Descriere: Trimite atributele obiectului de tip Electronic necesare adaugarii produsului; apeleaza functia din Service
		ui - pointer al unui obiect de tip UI => efectul se produce direct in memorie
	Returneaza codul de eroare
*/
int ui_adaugare(UI* ui)
{
	int id = 0, cantitate = 0;
	double pret = 0;
	char tip[50], producator[50], model[50];

	id = readIntegerNumber("Id: ");
	fgetc(stdin); // read the newline, to prevent it from going further to fgets
	readStringWithSpaces("Tip: ", 50, tip);
	readStringWithSpaces("Producator: ", 50, producator);
	readStringWithSpaces("Model: ", 50, model);
	printf("Pret: ");
	scanf_s("%lf", &pret);
	cantitate = readIntegerNumber("Cantitate: ");

	int result = adaugaElectronicService(ui->service, id, tip, producator, model, pret, cantitate);
	if (result == -1)
	{
		int code = id;
		printf("Un produs cu acest id exista deja! Actualizati cantitate: \n");
		result = ui_modificare(ui, code);
	}
	return result;
}

/*
	Descriere: Trimite atributele obiectului de tip Electronic necesare stergerii produsului (id)
		ui - pointer al unui obiect de tip UI => efectul se produce direct in memorie
	Returneaza codul de eroare
*/
int ui_stergere(UI* ui)
{
	int id = 0;
	id = readIntegerNumber("Id: ");
	return stergeElectronicService(ui->service, id);
}

/*
	Tipareste elementele listei de produse
		ui - pointer al unui obiect de tip UI => efectul se produce direct in memorie
*/
void ui_tipareste(UI* ui)
{
	Service* serv = tiparesteElectronicService(ui->service);
	Repository* repo = serv->repository;
	DynamicArray* vector_dinamic = repo->electronice;
	Electronic* electr;
	int i = 0;
	for (i = 0; i < vector_dinamic->length; i++)
	{
		electr = vector_dinamic->elems[i];
		printf("%d ", getId(electr));
		printf("%s ", getTip(electr));
		printf("%s ", getProducator(electr));
		printf("%s ", getModel(electr));
		printf("%.2lf ", getPret(electr));
		printf("%d\n", getCantitate(electr));
	}
}

/*
	Tipareste elementele listei de produse formate dupa sortare
		ui - pointer al unui obiect de tip UI => efectul se produce direct in memorie
*/
void ui_vizualizeaza(UI* ui)
{
	char mod[50] = "";
	fgetc(stdin); // read the newline, to prevent it from going further to fgets
	readStringWithSpaces("Crescator/Descrescator: ", 50, mod);
	strcpy(mod, _strlwr(mod));
	/* prelucram service-ul */
	ui->service = vizualizeazaService(ui->service, mod);
	ui_tipareste(ui);
}

/*
	Tipareste elementele listei de produse formate dupa filtrare
		ui - pointer al unui obiect de tip UI => efectul se produce direct in memorie
*/
void ui_filtreaza(UI* ui)
{
	int num_dec = -1;
	double num_float = -1;
	char mod[50] = "", val_str[50] = "";

	fgetc(stdin); // read the newline, to prevent it from going further to fgets
	readStringWithSpaces("Dupa producator/pret/cantitate: ", 50, mod);
	strcpy(mod, _strlwr(mod));

	if (strcmp(mod, "producator") == 0)
	{
		readStringWithSpaces("Valoare: ", 50, val_str);
	}
	else if (strcmp(mod, "pret") == 0)
	{
		printf("Valoare: ");
		scanf_s("%lf", &num_float);
	}
	else if (strcmp(mod, "cantitate") == 0)
	{
		num_dec = readIntegerNumber("Valoare: ");
	}

	/* prelucram service-ul */
	Service* ex_address;
	ex_address = ui->service;
	ui->service = filtreazaService(ui->service, mod, val_str, num_dec, num_float);
	destroyService(ex_address);

	Service* service = ui->service;
	Repository* repo = service->repository;
	DynamicArray* vector_dinamic = repo->electronice;
	if (getLength(vector_dinamic) == 0)
		printf("Nu s-a gasit niciun obiect!\n");
	else
		ui_tipareste(ui);
}

/*
	Afiseaza meniul aplicatiei si colecteaza datele necesare prelucrarii
		ui - pointer al unui obiect de tip UI => efectul se produce direct in memorie
*/
void run(UI* ui)
{
	int ruleaza = 1;
	while (ruleaza) {
		int cmd = 0;
		cmd = readIntegerNumber("1. Adauga \n2. Tipareste \n3. Modifica \n4. Sterge  \n5. Vizualizeaza \n6. Filtreaza \n0. Iesire \nComanda: ");

		switch (cmd) {
		case 0:
			ruleaza = 0;
			printf("Exit successfully.");
			break;

		case 1:
		{
			/*
			a) Adaugarea de noi produse. Daca produsul este deja in stoc trebuie actualizat cantitatea
			*/
			int result = ui_adaugare(ui);
			if (result == 0)
				printf("Produs electronic adaugat cu succes.\n");
			else if (result != 0 && result != -1)
			{
				printf("Eroare! Codul erorii: %d.\n", result);
			}
			break;
		}

		case 2:
			/*
			Tipareste produsele
			*/
			ui_tipareste(ui);
			break;

		case 3:
		{
			/*
			b) Actualizare produse (modificare pret sau cantitate)
			*/
			int result = ui_modificare(ui, 0);
			if (result == 0)
				printf("Produs electronic modificat cu succes.\n");
			else if (result == -2)
			{
				printf("Nu exista niciun obiect electronic cu acest id!\n");
			}
			else if (result != 0)
			{
				printf("Eroare! Codul erorii: %d.\n", result);
			}
			break;
		}

		case 4:
		{
			/*
			c) Stergere produs
			*/
			int result = ui_stergere(ui);
			if (result == 0)
			{
				printf("Produs electronic sters cu succes.\n");
			}
			else if (result == -2)
			{
				printf("Nu exista niciun obiect electronic cu acest id!\n");
			}
			else if (result != 0)
			{
				printf("Eroare! Codul erorii: %d.\n", result);
			}
			break;
		}

		case 5:
		{
			/*
			d) Vizualizare produse din stoc, ordonat dupa pret, cantitate (crescator/descrescator)
			*/
			UI* copie_ui = copyUI(ui);
			ui_vizualizeaza(copie_ui);
			destroyUI(copie_ui);
			break;
		}

		case 6:
		{
			/*
			e) Vizualizare lista de produse filtrate dupa un criteriu (producator, pret, cantitate)
			*/
			UI* copie_ui = copyUI(ui);
			ui_filtreaza(copie_ui);
			destroyUI(copie_ui);
			break;
		}

		default:
			printf("Comanda invalida!!!\n");
		}
		printf("\n");
	}
}

/*
	Elibereaza memoria alocata in Heap de catre UI
		ui - pointer al unui obiect de tip UI => efectul se produce direct in memorie
*/
void destroyUI(UI* ui)
{
	destroyService(ui->service);
	free(ui);
}