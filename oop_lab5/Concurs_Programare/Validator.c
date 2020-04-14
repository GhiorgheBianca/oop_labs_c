#include"Validator.h"
#include"Participant.h"


int Validare_Participant(PARTICIPANT* p)
{

	int erori = 1;
	if (strcmp(Get_Nume(p), "") == 0)
		erori *= 2;
	if (strcmp(Get_Prenume(p), "") == 0)
		erori *= 3;
	if(Get_Scor(p)<0 || Get_Scor(p)>10)
		erori *= 5;
	return erori;

}
