#pragma once
typedef struct polozka {
	char nazev[30];
	float cena;
	struct polozka* dalsi;
}tPolozka;

typedef struct stul {
	int cislo;
	char nazev[30];
	tPolozka* poleStolu;
}tStul;

tStul* nactiStoly(char* jmSoub, int* pocet);
void vypisStoly(tStul* poleStolu, int pocet);
tStul stulMaxPolozka(tStul* poleStolu, int pocet);
