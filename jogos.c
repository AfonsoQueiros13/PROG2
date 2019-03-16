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
    vetor *jogos_epl;
    FILE *fp= fopen(nomef,"r");
    if (fp == NULL){
        printf("Error opening file");
        return NULL;
    }
         while ( fgets ( jogos_epl, sizeof jogos_epl, fp ) != NULL ) /* read a line */
         {
            fputs ( jogos_epl, stdout ); /* write the line in array */
         }
    fclose(fp);
    return jogos_epl;
}


int jogos_save(vetor *vec, const char *nomef){

    return -1;
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
