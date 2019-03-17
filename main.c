//------------------------------------------------INCLUDES----------------------------------------------------------//
#include "jogos.c"
#include "vetor.c"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//------------------------------------------------MAIN--------------------------------------------------------------//

int main(void){
  vetor* vec_jogos= vetor_novo();
  vec_jogos = jogos_load("stats.txt");
  int numero_elementos= jogos_save(vec_jogos,"epl_games.txt");
  printf("Jogos epl\n");
  //printf("%s",vec_jogos);
  printf("num elementos= %d\n",numero_elementos);
  return 0;
}
