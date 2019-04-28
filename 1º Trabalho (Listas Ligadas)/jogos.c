                                /*****************************************************************/
                                /*         Trabalho pratico 1 | PROG2 | MIEEC | 2018/19          */
                                /*****************************************************************/
                                /*                    FUNCOES A IMPLEMENTAR                      */
                                /*****************************************************************/

#include "jogos.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//****************PROTOTIPO DAS FUNCOES QUE IMPLEMENTAMOS ALÉM DAS PEDIDAS*************************************************//
void quickSort(vetor_equipas *v, equipa *equipa1, char items[][20], int *diferenca, int left, int right);
void quicksort_golos(vetor_equipas *v, equipa *equipa1);

//*******************************FUNÇÕES A IMPLEMENTAR****************************************//
vetor* jogos_load(const char *nomef){

    FILE *file;
    file = fopen(nomef,"r");
    if(!file){
        perror("Error:");
        return NULL;
    }
    vetor * vtr = vetor_novo();
    if(vtr == NULL) 
        return NULL;

    jogo jogo1;

    while (fscanf(file,"%s %s %s %d %d %d %d", jogo1.epoca, jogo1.nome_casa, jogo1.nome_fora, &jogo1.golos_casa, &jogo1.golos_fora, &jogo1.vermelhos_casa, &jogo1.vermelhos_fora) != EOF)
    {   
        vetor_insere(vtr, jogo1, -1);
	}

    fclose(file);
    return vtr;
}

int jogos_save(vetor *vec, const char *nomef){

    FILE *file;
    file = fopen(nomef,"w");
    if (!file) 
    {
        perror("Error: ");
        return -1;
    }

    for (int i = 0; i < vec->tamanho; i++) 
    {
        jogo * jog = vetor_elemento(vec, i);
        fprintf((FILE*) file, "%s ", jog->epoca);
        fprintf((FILE*) file, "%s ", jog->nome_casa);
        fprintf((FILE*) file, "%s ", jog->nome_fora);
        fprintf((FILE*) file, "%d ", jog->golos_casa);
        fprintf((FILE*) file, "%d ", jog->golos_fora);
        fprintf((FILE*) file, "%d ", jog->vermelhos_casa);
        fprintf((FILE*) file, "%d\n", jog->vermelhos_fora);
    }

    fclose(file);
    return vec->tamanho;
}

void get_equipas (vetor *vec, vetor_equipas *vec_equipas, const char* nome_equipa) 
{
    short marcados_casa = 0;
    short marcados_fora = 0;
    short sofridos_casa = 0;
    short sofridos_fora = 0;
    short vermelho_casa_1 = 0;
    short vermelho_casa_2 = 0;
    short vermelho_casa_3 = 0;
    short vermelho_fora_1 = 0;
    short vermelho_fora_2 = 0;
    short vermelho_fora_3 = 0;
    int diff_golos = 0;
    float vermelhos[3];

    equipa equipa;

    for (int i = 0; i < vec->tamanho; i++) 
    {
        jogo * jg = vetor_elemento(vec, i);
        
        if ((!(strncmp(jg->nome_casa, nome_equipa, strlen(nome_equipa)))) || (!(strncmp(jg->nome_fora, nome_equipa, strlen(nome_equipa)))))
        {
            if (!(strncmp(jg->nome_casa, nome_equipa, strlen(nome_equipa)))) {
                if (jg->golos_casa != 0)
                    marcados_casa += jg->golos_casa;
                if (jg->golos_fora != 0)
                    sofridos_casa += jg->golos_fora;

                if (!(strcmp(jg->epoca, "15/16"))) {
                    //19jogos
                    if (jg->vermelhos_casa != 0)
                        vermelho_casa_1 += jg->vermelhos_casa;
                }
                if (!(strcmp(jg->epoca, "16/17"))) {
                    if (jg->vermelhos_casa != 0)
                        vermelho_casa_2 += jg->vermelhos_casa;
                }
                if (!(strcmp(jg->epoca, "17/18"))) {
                    if (jg->vermelhos_casa != 0)
                        vermelho_casa_3 += jg->vermelhos_casa;
                }
            }

            if (!(strncmp(jg->nome_fora, nome_equipa, strlen(nome_equipa)))) {
                if (jg->golos_fora != 0 )
                    marcados_fora += jg->golos_fora;
                if (jg->golos_casa != 0 )
                    sofridos_fora += jg->golos_casa;

               if (!(strcmp(jg->epoca, "15/16"))) {
                    if (jg->vermelhos_fora != 0)
                        vermelho_fora_1 += jg->vermelhos_fora;
                }
                if (!(strcmp(jg->epoca, "16/17"))) {
                    if (jg->vermelhos_fora != 0)
                        vermelho_fora_2 += jg->vermelhos_fora;
                }
                if (!(strcmp(jg->epoca, "17/18"))) {
                    if (jg->vermelhos_fora != 0)
                        vermelho_fora_3 += jg->vermelhos_fora;
                }
            }
        }
    }

    diff_golos = (marcados_casa + marcados_fora) - (sofridos_casa + sofridos_fora);
    vermelhos[0] = (double)(vermelho_casa_1 + vermelho_fora_1)/38;
    vermelhos[1] = (double)(vermelho_casa_2 + vermelho_fora_2)/38;
    vermelhos[2] = (double)(vermelho_casa_3 + vermelho_fora_3)/38;

    strcpy(equipa.nome_equipa,nome_equipa);
    equipa.diff_golos = diff_golos;
    equipa.vermelhos[0] = vermelhos [0];
    equipa.vermelhos[1] = vermelhos [1];
    equipa.vermelhos[2] = vermelhos [2];
    vetor_equipas_insere(vec_equipas, equipa, -1);
}

vetor_equipas *stats_equipa(vetor *vec)
{

    vetor_equipas * vtr_equipas = vetor_equipas_novo();
    equipa equipa;

    get_equipas(vec, vtr_equipas,"Arsenal");
    get_equipas(vec, vtr_equipas,"Stoke");
    get_equipas(vec,vtr_equipas,"Bournemouth");
    get_equipas(vec, vtr_equipas,"Aston_Villa");
    get_equipas(vec, vtr_equipas,"Chelsea");
    get_equipas(vec, vtr_equipas,"Swansea");
    get_equipas(vec, vtr_equipas,"Everton");
    get_equipas(vec, vtr_equipas,"Watford");
    get_equipas(vec, vtr_equipas,"Leicester");
    get_equipas(vec, vtr_equipas,"Sunderland");
    get_equipas(vec, vtr_equipas,"Man_United");
    get_equipas(vec, vtr_equipas,"Tottenham");
    get_equipas(vec, vtr_equipas,"Norwich");
    get_equipas(vec, vtr_equipas,"Crystal_Palace");
    get_equipas(vec, vtr_equipas,"West_Ham");
    get_equipas(vec, vtr_equipas,"Newcastle");
    get_equipas(vec, vtr_equipas,"Southampton");
    get_equipas(vec, vtr_equipas,"Liverpool");
    get_equipas(vec, vtr_equipas,"West_Brom");
    get_equipas(vec, vtr_equipas,"Man_City");
    get_equipas(vec, vtr_equipas,"Middlesbrough");
    get_equipas(vec, vtr_equipas,"Hull");
    get_equipas(vec, vtr_equipas,"Burnley");
    get_equipas(vec, vtr_equipas,"Brighton");
    get_equipas(vec, vtr_equipas,"Huddersfield");

    return vtr_equipas;

}

//************************************QUICKSORT FOR STRINGS*************************************************//

void quickSort(vetor_equipas *v, equipa *equipa1, char items[][20],int *diferenca, int left, int right)
{
  int i, j;
  char *x;
  char temp[20];
  int aux;
  i = left;
  j = right;
  x = items[(left+right)/2];

  do {
    while((strcmp(items[i],x) < 0) && (i < right)) {
       i++;
    }
    while((strcmp(items[j],x) > 0) && (j > left)) {
        j--;
    }
    if(i <= j) {
      aux =  diferenca[i];
      strcpy(temp, items[i]);
      diferenca[i] = diferenca[j];
      strcpy(items[i], items[j]);
      diferenca[j] = aux;
      strcpy(items[j], temp);
      i++;
      j--;
   }
  } while(i <= j);

  if(left < j) {
     quickSort(v,equipa1,items,diferenca, left, j);
  }
  if(i < right) {
     quickSort(v,equipa1,items,diferenca, i, right);
  }
}

//***************************************QUICKSORT DIFF GOALS**********************************************//
void quicksort_golos(vetor_equipas *v, equipa *equipa1){

    int diferenca[25];
    char nome_equipa[25][30];
    char temp [25][30];

    for (int i = 0; i < v->tamanho; i++) 
    {
            equipa1 = vetor_equipas_elemento(v, i);
            diferenca[i] = equipa1->diff_golos;
            strcpy(nome_equipa[i], equipa1->nome_equipa);
    }

    for (int i = 0; i < v->tamanho; i++)                     //Loop for ascending ordering
	{
		for (int j = 0; j < v->tamanho; j++)             //Loop for comparing other values
		{
			if (diferenca[j] > diferenca[i])                //Comparing other array elements
			{
				int tmp = diferenca[i];         //Using temporary variable for storing last value
                strcpy(temp[i], nome_equipa[i]);
				diferenca[i] = diferenca[j];          //replacing value
                strcpy(nome_equipa[i], nome_equipa[j]);
				diferenca[j] = tmp;             //storing last value
                strcpy(nome_equipa[j], temp[i]);
			} 
		}
	}

    for(int i = 0; i < v->tamanho; i++)
    {
       equipa1->diff_golos = diferenca[i];
       strcpy(equipa1->nome_equipa, nome_equipa[i]);
       vetor_equipas_atribui(v, i, *equipa1); 
    }
    
}

int equipas_ordena(vetor_equipas *v, int criterio){

    equipa * equipa1;
    char buffer[30][20];
    int diferenca[25];

    if (criterio == 0) 
    {
        for (int i = 0; i < v->tamanho; i++) 
        {
            equipa1 = vetor_equipas_elemento(v, i);
            strcpy(buffer[i],equipa1->nome_equipa);
            diferenca[i]= equipa1->diff_golos;
        }

        quickSort(v,equipa1,buffer,diferenca,0,v->tamanho-1);

    for(int i = 0; i < v->tamanho; i++) 
        {
            equipa1 = vetor_equipas_elemento(v, i);
            strcpy(equipa1->nome_equipa,buffer[i]);
            equipa1->diff_golos = diferenca[i];
            vetor_equipas_atribui(v,i,*equipa1);          
        }
    }

    if (criterio == 1) 
    {
        quicksort_golos(v, equipa1);
    }
    return 0;
}


int corrige_jogo(vetor *vec, const char *nomef){

    FILE *filer;
    filer = fopen(nomef,"r");
    if (!filer) 
    {
        perror("Error: ");
        return -1;
    }

    jogo jogo1;

    while (fscanf(filer,"%s %s %s %d %d %d %d", jogo1.epoca, jogo1.nome_casa, jogo1.nome_fora, &jogo1.golos_casa, &jogo1.golos_fora, &jogo1.vermelhos_casa, &jogo1.vermelhos_fora) != EOF)
    {
        for (int i = 0; i < vec->tamanho; i++) 
        {
            jogo * jogo2 = vetor_elemento(vec, i);

            if ((!(strcmp(jogo1.epoca,jogo2->epoca))) 
            && (!(strcmp(jogo1.nome_casa,jogo2->nome_casa)))  
            && (!(strcmp(jogo1.nome_fora,jogo2->nome_fora)))) 
            {
                vetor_atribui(vec, i, jogo1);
            }

        }
    }
    fclose(filer);
    return 0;
}

int pontos_de_equipa(vetor *vec, char *nome_equipa, char *epoca){
    
    int pontos = 0;

    for(int i = 0; i < vec->tamanho; i++)
    {
        jogo * jg = vetor_elemento(vec, i);
        if ((!(strcmp(jg->epoca, epoca)))) 
        {
            if ((!(strcmp(jg->nome_casa, nome_equipa))) || (!(strcmp(jg->nome_fora, nome_equipa)))) 
            {
                // Joga em casa!
                if (!(strcmp(nome_equipa, jg->nome_casa))) 
                {
                    if ((jg->golos_casa) > (jg->golos_fora)) {
                        pontos += 3;
                    }
                    if ((jg->golos_casa) == (jg->golos_fora))
                        pontos += 1;
                }
                // Joga fora!
                if (!(strcmp(nome_equipa, jg->nome_fora))) 
                {
                    if ((jg->golos_casa) < (jg->golos_fora)) {
                        pontos += 3;
                    }
                    if ((jg->golos_casa) == (jg->golos_fora))
                        pontos += 1;
                }
            }
        }
    }
    return pontos;
}





