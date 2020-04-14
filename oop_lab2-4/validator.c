#include "obiect_electronic.h"
#include <string.h>

/*
	Valideaza obiectul de tip Electronic
*/
int validare_Electronic(Electronic* electr) {
	int err_code = 0;

	if (getId(electr) < 1)
		err_code = err_code * 10 + 1;
	if (strlen(getTip(electr)) == 0)
		err_code = err_code * 10 + 2;
	if (strlen(getProducator(electr)) == 0)
		err_code = err_code * 10 + 3;
	if (strlen(getModel(electr)) == 0)
		err_code = err_code * 10 + 4;
	if (getPret(electr) < 0)
		err_code = err_code * 10 + 5;
	if (getCantitate(electr) < 0)
		err_code = err_code * 10 + 6;

	return err_code;
}