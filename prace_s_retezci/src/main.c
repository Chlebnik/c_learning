#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_VSTUP 1000
#define MAX_DELKA_POLE 80
#define DELKA_POLE 10

int vyskyt_znaku() {
  
  int vyskyt = 0;
  char znak;
  char *vstup;
  char *vysledek;
  
  if ((vstup = malloc(sizeof(char) * MAX_DELKA_POLE)) == NULL) {
    printf("Chyba pri alokaci pameti.");
    return 1;
  }

  printf("Prosim zadejte vstupni text ukonceny ENTER.\n");

  *vstup = 0;
  
  /* nacti vstup, aktualni delka pole se uchovava na prvnim pozici */
  while (++(*vstup) != MAX_DELKA_POLE - 2 && (*(vstup + *vstup) = getc(stdin)) != '\n')
    ;
  
  *(vstup + *vstup) = '\0';

  /* vyprazdni zasobnik pokud text byl delsi nez nase pole */
  while (*(vstup + *vstup - 1) != '\n' && getc(stdin) != '\n')
    ;

  printf("Zadejte znak jehoz vyskyt chcete najit.\n");
    
  znak = getc(stdin);

  vysledek = vstup + 1;

  while ((vysledek = strchr(vysledek, znak)) != NULL) {
    printf("%d vyskyt znaku %c nalezen ve slove '%s' na poizci %d.\n", ++vyskyt, *vysledek, vysledek, vysledek-vstup-1);
    vysledek++;
  }
  
  printf("Zadali jste text:\n%s", (vstup+1)); 

  return 0;

}

int zapis_retezec_na_konec_souboru(){
  FILE *fw;
  char *nazev_souboru;
  char *radka;
  int index_nove_radky;

  nazev_souboru = malloc(MAX_DELKA_POLE * sizeof(char));
  printf("Zadejte jmeno souboru do ktereho se bude zapisovat:\n");
  if (fgets(nazev_souboru, MAX_DELKA_POLE, stdin) == NULL) {
    printf("Chyba pri nacitani jmena souboru.");
    free(nazev_souboru);
    return 1;
  }

  index_nove_radky = strcspn(nazev_souboru, "\r\n\0");
  if (index_nove_radky < MAX_DELKA_POLE)
    nazev_souboru[index_nove_radky] = '\0';
    
  if ((fw = fopen(nazev_souboru, "a")) == NULL) {
    printf("Chyba pri otevirani souboru '%s'.", nazev_souboru);
    free(nazev_souboru);
    return 2;
  
}

  printf("Nyni zadavejte retezce do maximalni delky 80. Pro ukonceni zadejte prazdny retezec.\n");

  radka = malloc(MAX_DELKA_POLE * sizeof(char));
  while(*(fgets(radka, MAX_DELKA_POLE, stdin)) != '\n') {
    if (fputs(radka, fw) == EOF) {
      printf("Chyba pri zapisi radky '%s' do souboru '%s'.", radka, nazev_souboru);
      break;
    }
  }

  if (fclose(fw) == EOF)
    printf("Chyba pri zavirani souboru '%s'.", nazev_souboru);

  free(nazev_souboru);
  free(radka);
  return 0;
}


int vyhledej_retezec_v_souboru(void) {
  FILE *fw;
  char *nazev_souboru;
  char *hledany_retezec;
  char *radka;
  int *nalezene_radky;
  int index_konce_radky = MAX_DELKA_POLE;
  int delka_pole = 0;
  int cislo_radky = 0;

  nazev_souboru = malloc(MAX_DELKA_POLE * sizeof(char));

  printf("Zadejte nazev souboru, ktery chcete prohledat:\n");
  if (fgets(nazev_souboru, MAX_DELKA_POLE, stdin) == NULL) {
    printf("Chyba pri nacitani nazvu souboru.");
    free(nazev_souboru);
    return 1;
  }

  index_konce_radky = strcspn(nazev_souboru, "\r\n\0");
  if (index_konce_radky < MAX_DELKA_POLE)
    nazev_souboru[index_konce_radky] = '\0';
 
  hledany_retezec = malloc(MAX_DELKA_POLE * sizeof(char)); 
  printf("Zadejte hledany retezec:\n");
  if (fgets(hledany_retezec, MAX_DELKA_POLE, stdin) == NULL) {
    printf("Chyba pri nacitani hledaneho retezce.");
    free(nazev_souboru);
    free(hledany_retezec);
    return 1;
  }

  index_konce_radky = strcspn(hledany_retezec, "\r\n\0");
  if (index_konce_radky < MAX_DELKA_POLE)
    hledany_retezec[index_konce_radky] = '\0';

  if ((fw = fopen(nazev_souboru, "r")) == NULL) {
    printf("Chyba pri otvirani souboru '%s'.", nazev_souboru);
    free(nazev_souboru);
    free(hledany_retezec);
    return 1;
  }
  
  nalezene_radky = calloc(DELKA_POLE, sizeof(int));
  radka = malloc(MAX_VSTUP * sizeof(char));
  while(fgets(radka, MAX_VSTUP, fw) != NULL) {
    if (feof(fw)) {
      printf("Konec souboru.\n");
      break;
    }
    cislo_radky++;
    if (strstr(radka, hledany_retezec) == NULL)
      continue;
    if (++delka_pole % DELKA_POLE == 0) {
      if ((nalezene_radky = realloc(nalezene_radky, (delka_pole + DELKA_POLE) * sizeof(int))) == NULL) {
        printf("Problem pri alokaci nove pameti.\n");
        break;
      }
      for(int i=0; i < DELKA_POLE; i++) {
        *(nalezene_radky + delka_pole + i) = 0;
      }
    }
    *(nalezene_radky + delka_pole - 1) = cislo_radky;
  }
   
  if (fclose(fw) == EOF)
    printf("Chyba pri zavirani souboru.\n");
  
  printf("Zadany retezec '%s' byl nalezen %d krat v souboru '%s'.\n", hledany_retezec, delka_pole, nazev_souboru);
  if (delka_pole > 0) {
    printf("Byl nalezen na radkach: ");
    for (int i=0; i < delka_pole; i++) {
      printf("%d, ", *(nalezene_radky + i));
    }
  }
  free(nazev_souboru);
  free(hledany_retezec);
  free(radka);
  free(nalezene_radky);
  return 0;
}

int main(void) {
  /* return vyskyt_znaku(); */
  /* return zapis_retezec_na_konec_souboru(); */
  return vyhledej_retezec_v_souboru();
}
