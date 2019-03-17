/*****************************************************************/
/*         Trabalho pratico 1 | PROG2 | MIEEC | 2018/19          */
/*****************************************************************/
/*                    FUNCOES A IMPLEMENTAR                      */
/*****************************************************************/

#include "jogos.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


vetor* jogos_load(const char *nomef){
    vetor*jogos_epl =  vetor_novo();
    int c;
    FILE *fp= fopen(nomef,"r");
    if (fp == NULL){
        printf("Error opening file\n");
        return NULL;
    }
    while ((c = fgetc(fp)) != EOF)
{
    //jogos_epl->elementos->epoca[i]=
    fscanf(fp, "%s", jogos_epl);
    //jogos_epl->elementos->epoca[i]=(char)jogos_epl;
    printf("%s\n",jogos_epl);
    //printf("%c\n",jogos_epl->elementos->epoca[i]);

}
    //printf("%c",jogos_epl->elementos->epoca[i]);

    fclose(fp);
    return jogos_epl;
}


int jogos_save(vetor *vec, const char *nomef){
  FILE *fp= fopen(nomef,"wb");
  if (fp == NULL){
      printf("Error opening file\n");
      return -1;
  }
  fwrite(vec, sizeof(char), sizeof(vec), fp);
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
