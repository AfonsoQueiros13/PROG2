/*****************************************************************/
/*         Trabalho pratico 1 | PROG2 | MIEEC | 2018/19          */
/*****************************************************************/
/*                    FUNCOES A IMPLEMENTAR                      */
/*****************************************************************/

#include "jogos.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//--------------------------FUNCAO JOGOS_LOAD---------------------------------------------------------//
vetor* jogos_load(const char *nomef){
    vetor *jogos_epl[3000];
    char line[3000];
    int i=0;
    FILE *fp= fopen(nomef,"r");
    if (fp == NULL){
        printf("Error opening file\n");
        return NULL;
    }
    while(fgets(line, sizeof line, fp)!=NULL)
    {
        jogos_epl[i]= (vetor*) line;
        printf("%s", jogos_epl[i]);
        i++;
    }
    fclose(fp);
    return jogos_epl;
}
//--------------------------FUNCAO JOGOS_SAVE---------------------------------------------------------//
int jogos_save(vetor *vec, const char *nomef){
  FILE *fp= fopen(nomef,"w");
  if (fp == NULL){
      printf("Error opening file\n");
      return -1;
  }
  
  fprintf(fp,"%s",vec);
  fclose(fp);
  return sizeof(vec->tamanho);
}


vetor_equipas *stats_equipa(vetor *vec){

    return NULL;
}


int equipas_ordena(vetor_equipas *v, int criterio){

    return -1;
}


int corrige_jogo(vetor *vec, const char *nomef){

    return -1;
}


int pontos_de_equipa(vetor *vec, char *nome_equipa, char *epoca){

    return -1;
}
