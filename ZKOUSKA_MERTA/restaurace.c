
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "restaurace.h"

tPolozka* vytvorPolozku(char* jmPol, float cena);

tStul* nactiStoly(char* jmSoub, int* pocet) {
	FILE* f = fopen(jmSoub, "r");
	if (f == NULL) {
		printf("CHYBA CTENI");
		return -1;
	}
	int n = 0;
	char buffer[100];
	while (fgets(buffer,100,f)) {
		if (isdigit(buffer[0])) {
			n++;
		}
	}
	tStul* stl = malloc(sizeof(tStul) * n);
	if (stl == NULL) {
		printf("CBYBA");
		fclose(f);
		return NULL;
	}
	rewind(f);
	char buf[100];
	fgets(buf, 100, f);
	for (int i = 0; i < n; i++) {
		char* s = strchr(buf, ';');
		*s = '\0';
		stl[i].cislo = atoi(buf);
		char *nazev = s + 1;
		strcpy(stl[i].nazev, nazev);

		int j = 0;
		tPolozka* polozky = NULL;
		tPolozka* posledni = NULL;
		while (fgets(buf,100,f) && !isdigit(buf[0])) {
			char* stringa = strchr(buf, ';');
			*stringa = '\0';
			char* name = buf;
			float cena = atof(stringa + 1);
			if (j == 0) {
				polozky = vytvorPolozku(name, cena);
				posledni = polozky;
			}
			if (j > 0) {
				tPolozka* pol = vytvorPolozku(name, cena);
				posledni->dalsi = pol;
				posledni = posledni->dalsi;
			}
			j++;
		}
		stl[i].poleStolu = polozky;
	}
	*pocet = n;
	fclose(f);
	return stl;
}
void vypisStoly(tStul* poleStolu, int pocet) {
	for (int i = 0; i < pocet; i++) {
		printf("%s\n", poleStolu[i].nazev);
		tPolozka* p = poleStolu[i].poleStolu;
		while (p != NULL) {
			printf("--%s %f\n", p->nazev, p->cena);
			p = p->dalsi;
		}
	}
}
tStul stulMaxPolozka(tStul* poleStolu, int pocet) {
	tStul pol = poleStolu[0];
	float cena=0;
	for (int i = 0; i < pocet; i++) {
		tPolozka* p = poleStolu[i].poleStolu;
		while (p != NULL) {
			if (p->cena > cena) {
				cena = p->cena;
				pol = poleStolu[i];
			}
			p = p->dalsi;
		}
	}
	return pol;
}

static tPolozka* vytvorPolozku(char *jmPol, float cena) {
	tPolozka* pol = (tPolozka*)malloc(sizeof(tPolozka));
	if (pol == NULL) {
		printf("CHYBA ALLOKOVANI");
		return NULL;
	}
	strcpy(pol->nazev, jmPol);
	pol->cena = cena;
	pol->dalsi = NULL;
	return pol;
}



