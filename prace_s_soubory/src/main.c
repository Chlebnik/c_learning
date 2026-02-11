#include <stdio.h>

#define CTI1 "cti1.txt"
#define CTI2 "cti2.txt"
#define ZAPIS "zapis.txt"

#define CHYBNA_PROMENNA 1
#define CHYBA_IO 2

void porovnej_soubory(FILE *prvni, FILE *druhy, FILE *vypis, int *pocet_radku, int *pocet_rozdilu, int *pocet_znaku) {
  char znak_1, znak_2;

  while ((znak_1 = getc(prvni)) != EOF && (znak_2 = getc(druhy)) != EOF) {
    if (znak_1 != znak_2)
      (*pocet_rozdilu)++;

    if (znak_1 == '\n')
      (*pocet_radku)++;

    (*pocet_znaku)++;
  }
  
  fprintf(vypis, "Pocet nalezenych rozdilu je %d.", *pocet_rozdilu);
  
}

int main(void) {
  
  char volba_vystupu, volba_statistiky;
  printf("Chcete vypsat vysledek do (S)ouboru nebo na (O)brazovku?");
  volba_vystupu = getc(stdin);
  
  /* Vyprazdneni bufferu pro nacteni druhe promene */
  if (volba_vystupu != '\n')
    while (getc(stdin) != '\n')
      ;

  if (volba_vystupu != 'O' && volba_vystupu != 'S') {
    printf("Neznama volba '%c', ocekavane jsou (S) nebo (O).", volba_vystupu);
    return CHYBNA_PROMENNA;
  }

  int pocet_radku = 0, pocet_znaku = 0, pocet_rozdilu = 0, vysledek = 0;
  
  FILE *fr_1,*fr_2,*fw;

  if ((fr_1 = fopen(CTI1, "r")) == NULL) {
    printf("Chyba pri otvirani %s souboru pro cteni.", CTI1);
    return CHYBA_IO;
  }

  if ((fr_2 = fopen(CTI2, "r")) == NULL) {
    printf("Chyba pri otvirani cteni %s souboru pro cteni.", CTI2);
    fclose(fr_1);
    return CHYBA_IO;
  }

  if (volba_vystupu == 'S' && (fw = fopen(ZAPIS, "w")) == NULL) {
    printf("Chyba pri otvirani %s souboru pro zapis.", ZAPIS);
    fclose(fr_1);
    fclose(fr_2);
    return CHYBA_IO;
  } else if (volba_vystupu == 'O') {
    /* Pokud nezapisujeme do souboru, vypisujeme na obrazovku */
    fw = stdout;
  }

  porovnej_soubory(fr_1, fr_2, fw, &pocet_radku, &pocet_rozdilu, &pocet_znaku);

  printf("Chcete na konci vypsat dodatecne statistiky? (A)no / (N)e");
  volba_statistiky = getc(stdin);

  if (volba_statistiky != 'A' && volba_statistiky != 'N') {
    printf("Neznama volba '%c', ocekavane jsou (A) nebo (N).", volba_statistiky);
    return CHYBNA_PROMENNA;
  }

  if (volba_statistiky == 'A')
    fprintf(fw, "Pocet pocet_radku %d, pocet_znaku %d pro soubor %s.", pocet_radku, pocet_znaku, CTI1);

  if (fclose(fr_1) == EOF) {
    printf("Chyba pri zavirani souboru %s.", CTI1);
    vysledek = CHYBA_IO;
  }

  if (fclose(fr_2) == EOF) {
    printf("Chyba pri zavirani souboru %s.", CTI2);
    vysledek = CHYBA_IO;
  }

  if (volba_vystupu == 'S' && fclose(fw) == EOF) {
    printf("Chyba pri zavirani souboru %s.", ZAPIS);
    vysledek = CHYBA_IO;
  }

  return vysledek;
}
