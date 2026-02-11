#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define DELKA_POLE 10

typedef struct tslovo {
  char *text;
  unsigned int cetnost;
  struct tslovo *p_dalsi;
} TSLOVO;


void nacti_slova(char *jmeno_souboru, TSLOVO *p_slovo) {

}

int main(void){
  // nacti soubor
  // nacti unikatni slova a jejich cetnost
  // vypis 20 nejcetnejsich
  // vypis nejcetnejsi
}
