#include"Repo.h"
#include"Participant.h"
#include"Controller.h"
#include"Validator.h"
#include"Teste.h"
#include"Vector.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h> 

int main()
{
	Teste();
	
	Concurs Participanti = Creeaza_Concurs();
	
	while (1) {
		printf("1. Adauga \n2. Tipareste \n3. Actualizare\n4. Stergere\n5. Filtrare\n6. Sortare\n7. Undo\n0. Iesire \nComanda: ");
		int cmd = 0;
		scanf("%d", &cmd);
		if (cmd == 0)
		{
			printf("bye");
			break;
		}
		if (cmd == 1)
			Ui_Adaugare_Participant(&Participanti);
		if (cmd == 2)
			Ui_Tipareste_Participanti(&Participanti);
		if (cmd == 3)
			Ui_Actualizare_Participant(&Participanti);
		if (cmd == 4)
			Ui_Stergere_Participant(&Participanti);
		if (cmd == 5)
			Ui_Filtrare_Participanti(&Participanti);
		if (cmd == 6)
			Ui_Sortare(&Participanti);
		if (cmd == 7)
			if (Ui_Undo(&Participanti) != 0)
			{
				printf("Nu se mai poate executa undo!\n");
			}
		
		printf("\n");

	}
	Distruge_Concurs(&Participanti);
	
	_CrtDumpMemoryLeaks();
	return 0;
}