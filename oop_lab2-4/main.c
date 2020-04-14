#define _CRTDBG_MAP_ALLOC
#include "teste.h"
#include "repository.h"
#include "service.h"
#include "ui.h"
#include <crtdbg.h>
#include <stdlib.h>

int main()
{
	{
		ruleaza_teste();
		Repository* repo = createRepository();
		Service* service = createService(repo);
		UI* ui = createUI(service);

		run(ui);
		
		destroyUI(ui);
	}
	_CrtDumpMemoryLeaks();
	return 0;
}