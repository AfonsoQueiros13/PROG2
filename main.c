//------------------------------------------------INCLUDES----------------------------------------------------------//
#include "jogos.c"
#include "vetor.c"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//------------------------------------------------MAIN--------------------------------------------------------------//

int main(void){
  vetor* vec_jogos= vetor_novo();
  vec_jogos= jogos_load("stats.txt");
  printf("Vec_jogos: \n ");
  fputs (vec_jogos, stdout);
  return 0;
}
