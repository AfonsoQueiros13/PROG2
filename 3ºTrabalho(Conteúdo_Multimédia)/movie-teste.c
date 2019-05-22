/*****************************************************************/
/*         Trabalho pratico 3 | PROG2 | MIEEC | 2018/19          */
/*****************************************************************/
/*                  NAO ALTERAR ESTE FICHEIRO                    */
/*****************************************************************/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "movies.h"


/* DEFINES E VARIAVEIS GLOBAIS UTEIS PARA OS TESTES */
#define MAX_LINHA 1024
#define TAB_CLIENTES 401
#define FICH_CLIENTES "clientesShort.csv"
#define FICH_FILMES "filmesShort.txt"



// Mostrar o vetor de Sugestoes
void mostrar_vetorsugestoes(vetor *vec)
{
    int l;
    printf("[");
    for ( l=0;l<vec->tamanho-1;l++)
      printf("%d - ",vec->elementos[l]);
    printf("%d]\n",vec->elementos[vec->tamanho-1]);
}

// Verificar se o vetor de Sugestoes e´ o correto
// 1 se for igual 0 se não for
int comparar_vetorsugestoes(vetor *vec1,vetor *vec2)
{
    if (vec1== NULL || vec2 == NULL)
    return 0;
    if (vec1->tamanho != vec2->tamanho)
    return 0;
    for  (int l=0;l<vec1->tamanho;l++)
    {
        if (vec1->elementos[l] != vec2->elementos[l] )
        return 0;
    }
    return 1;
}

void clientesCarrega(colecaoClientes* td,const char *nomeFicheiro)
{
    FILE *f = fopen(nomeFicheiro, "r");
    char username[15];
    int filmIdvisto, rel=0;;
    if(!f)
    {
        printf("ERRO: ficheiro %s nao encontrado\n", nomeFicheiro);
        return;
    }
    char *token;
    char str[MAX_LINHA];
    while( fgets(str, MAX_LINHA, f) != NULL )
    {
      token = strtok(str, ",");
      strcpy(username,token);
      while( (token = strtok(NULL, ",")) != NULL )
      {
        filmIdvisto=atoi(token);
        //printf("Inserindo username=%s, filmIdvisto=%d\n",username, filmIdvisto);
        rel=clienteAdiciona(td, username, filmIdvisto);
      }
    }
}


int main(int argc, char** argv)
{

  //Carrega a estrutura de clientes
  colecaoClientes* clientes=colecaoClientesNova(TAB_CLIENTES);
  printf("\nCARREGAR CLIENTES e FILMES\n");
  clock_t start_t, end_t;
  start_t = clock();
  clientesCarrega(clientes,FICH_CLIENTES);
  end_t = clock();
  printf("\tTempo carregar clientes: %.6f\n", (double)(end_t - start_t) / CLOCKS_PER_SEC);
  //Carrega a estrutura de filmes
  start_t = clock();
  colecaoFilmes* filmes=filmesCarrega(FICH_FILMES);
  end_t = clock();
  printf("\tTempo carregar filmes: %.6f\n", (double)(end_t - start_t) / CLOCKS_PER_SEC);
  int n_cli=colecaoNumClientes(clientes);
  if (n_cli==10) {
    printf("\tcolecaoNumClientes: numero de clientes correto (10)\n");
  } else {
    printf("\tERRO: colecaoNumClientes: numero de clientes incorreto (retornado %d, esperado %d)\n",n_cli,10);
  }
  if (clienteExiste(clientes,"KB6OC0HI")==1) {
    printf("\tclienteExiste: retorno ok para cliente 'KB6OC0HI' (1)\n");
  } else {
    printf("\tERRO: clienteExiste: retorno incorreto para cliente 'KB6OC0HI' (!=1)\n");
  }


  // Testar a sugestão
  printf("\nSITUACAO INICIAL\n");
  vetor *vec,*vref;
  vref=vetor_novo();
  vetor_insere(vref,14,-1); vetor_insere(vref,57,-1); vetor_insere(vref,39,-1); vetor_insere(vref,20,-1); vetor_insere(vref,13,-1);
  start_t = clock();
  vec=sugestoes(filmes, clientes, "J9IFuAEe", 5, 9.5);
  end_t = clock();
  printf("\tTempo de um pedido de sugestoes: %.6f\n", (double)(end_t - start_t) / CLOCKS_PER_SEC);
  printf("\tSugerido: ");
  mostrar_vetorsugestoes(vec);
  printf("\tEsperado: ");
  mostrar_vetorsugestoes(vref);
  if (comparar_vetorsugestoes(vref,vec)==1) {
    printf("\tSugestoes corretas para situacao inicial\n");
  } else {
    printf("\tERRO: Sugestoes incorretas para situacao inicial\n");
  }
  vetor_apaga(vec);

  // Testar a remoção
  printf("\nREMOVER UM FILME\n");
  removerFilme(filmes, clientes, 14);
  vetor_remove(vref,0); vetor_insere(vref,0,-1);
  start_t = clock();
  vec=sugestoes(filmes, clientes, "J9IFuAEe", 5, 9.5);
  end_t = clock();
  printf("\tTempo de um pedido de sugestoes: %.6f\n", (double)(end_t - start_t) / CLOCKS_PER_SEC);
  printf("\tSugerido: ");
  mostrar_vetorsugestoes(vec);
  printf("\tEsperado: ");
  mostrar_vetorsugestoes(vref);
  if (comparar_vetorsugestoes(vref,vec)==1) {
    printf("\tSugestoes corretas apos remocao de um filme\n");
  } else {
    printf("\tERRO: Sugestoes incorretas apos remocao de um filme\n");
  }
  vetor_apaga(vec);

  // Testar a inserção
  printf("\nINSERIR UM FILME\n");
  inserirNovoFilme(filmes, "O Rei Leao 13", "Comedy", 101, 9.8);
  vetor_remove(vref,4); vetor_insere(vref,101,0);
  start_t = clock();
  vec=sugestoes(filmes, clientes, "J9IFuAEe", 5, 9.5);
  end_t = clock();
  printf("\tTempo de um pedido de sugestoes: %.6f\n", (double)(end_t - start_t) / CLOCKS_PER_SEC);
  printf("\tSugerido: ");
  mostrar_vetorsugestoes(vec);
  printf("\tEsperado: ");
  mostrar_vetorsugestoes(vref);
  if (comparar_vetorsugestoes(vref,vec)==1) {
    printf("\tSugestoes corretas apos insercao de um filme\n");
  } else {
    printf("\tERRO: Sugestoes incorretas apos insercao de um filme\n");
  }
  vetor_apaga(vec);

  vetor_apaga(vref);
  printf("ok");
  colecaoFilmesApaga(filmes,clientes);
  printf("ok");
  colecaoClientesApaga(clientes);
  printf("ok");
  return 0;
}
