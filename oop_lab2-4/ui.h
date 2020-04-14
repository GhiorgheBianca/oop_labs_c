#pragma once
#include "service.h"

typedef struct {
	Service* service;
} UI;

/*
	Creeaza obiectul de tip UI
*/
UI* createUI(Service* service);

/*
	Porneste interfata pentru utilizator
*/
void run(UI* ui);

/*
	Elibereaza memoria alocata in Heap de catre UI
*/
void destroyUI(UI* ui);