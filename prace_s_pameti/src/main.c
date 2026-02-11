#include <stdio.h>
#include <stdlib.h>

#define SOUBOR "cti.txt"
#define POCATECNI_VELIKOST_POLE 10

int main(void) {

  /* 
     Precti soubor a uloz si velikost radek. 
     Pri startu bude mit dynamicky alokovane pole
     velikost 10 a pri jeho naplneni se alokuje
     nova velikost, 2x vetsi. Na konci se uvolni 
     pamet a vypise se delka radek.
     -- malloc - alokuj pamet
     -- calloc - alokuj pamet pro x prvku a vypln nulama
     -- realloc - prealokuj pamet
     -- free - uvolni pamet
  */
  
  int cislo_radku = -1;
  int velikost_pole = POCATECNI_VELIKOST_POLE;
  char znak;
  FILE *fr;
  int *p_velikost_radku;

  if ((fr = fopen(SOUBOR, "r")) == NULL) {
    printf("Chyba pri nacitani souboru '%s'.", SOUBOR);
    return 1;
  }

  if ((p_velikost_radku = (int *) malloc(velikost_pole * sizeof(int))) == NULL) {
    printf("Chyba pri alokaci pameti.");
    return 2;
  }

  while((znak = getc(fr)) != EOF) {
    if (cislo_radku == -1) {
      cislo_radku = 0;
      /* prvotni vynulovani */
      *(p_velikost_radku + cislo_radku) = 0;
    }
    if (znak == '\n') {
      cislo_radku++;
      if (cislo_radku >= velikost_pole) {
        velikost_pole *= 2;
        if ((p_velikost_radku = (int *) realloc(p_velikost_radku, velikost_pole * sizeof(int))) == NULL) {
          printf("Chyba pri alokaci pameti.\n");
          fclose(fr);
          return 2;
        }
      }
      /* prvotni vynulovani */
      *(p_velikost_radku + cislo_radku) = 0;
    }
    else {
      *(p_velikost_radku + cislo_radku) += 1;
    }
  }

  if (fclose(fr) == EOF)
    printf("Chyba pri zavirani souboru '%s'.\n", SOUBOR);
  
  for(int i = 0; i <= cislo_radku; i++) {
    printf("[%d] velikost %d.\n", i, *(p_velikost_radku + i));
  }

  free(p_velikost_radku);

  return 0;
}
