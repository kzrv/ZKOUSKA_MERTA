#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "restaurace.h"


int main(void) {
	int pocet;
	tStul* st = nactiStoly("data.txt", &pocet);
	vypisStoly(st, pocet);
	tStul t = stulMaxPolozka(st, pocet);
	printf("%d", t.cislo);
	return 0;
}