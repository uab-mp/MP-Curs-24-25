#include "Llista.h"
#include "Llista_dinamica.h"
#include <time.h>


Llista llista;
//LlistaDinamica llista;

int main()
{
	clock_t timeAfegeix;
	timeAfegeix = clock();
	for (int i = 0; i < 10000; i++)
	{
		Estudiant e("NOM_1", "NIU_1");
		llista.insereix(e, 0);
	}
	timeAfegeix = clock() - timeAfegeix;
	float tempsAfegeix = (float)timeAfegeix / CLOCKS_PER_SEC;


 	return 0;
}