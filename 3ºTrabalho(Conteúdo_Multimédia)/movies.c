/*****************************************************************/
/*           Movies | PROG2 | MIEEC | 2018/19                */
/*****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "movies.h"
#define MAXCHAR 100


//Declaracao funcoes auxiliares//




//////   Implementacao Tabela de Dispersão - Clientes  ///////
colecaoClientes* colecaoClientesNova(int tamanho)
{
    /* aloca memoria para a estrutura tabela_dispersao */

    colecaoClientes *t = (colecaoClientes*) malloc(sizeof (colecaoClientes));
    if (t == NULL)
        return NULL;

    /* aloca memoria para os elementos */
    t->elementos = (elementoCliente **) calloc(tamanho, sizeof (elementoCliente*));
    if (t->elementos == NULL) {
        free(t);
        return NULL;
    }

    t->tamanho = tamanho;

    return t;
}

/////   Implementacao Tabela de Dispersão - Clientes  ///////
colecaoFilmes* colecaoFilmesNova(int tamanho)
{
    /* aloca memoria para a estrutura tabela_dispersao */

    colecaoFilmes *t = (colecaoFilmes*) malloc(sizeof (colecaoFilmes));
    if (t == NULL)
        return NULL;

    /* aloca memoria para os elementos */
    t->elementos = (elementoFilme**) calloc(tamanho, sizeof (elementoFilme));
    if (t->elementos == NULL) {
        free(t);
        return NULL;
    }

    t->tamanho = tamanho;

    return t;
}

void colecaoClientesApaga(colecaoClientes *td)
{
    int i;
    elementoCliente *elem, *aux;

    if (td == NULL) return ;

    /* para cada entrada na tabela */
    for (i = 0; i < td->tamanho; i++)
    {
        /* e enquanto existirem elementos nessa entrada */
        elem = td->elementos[i];
        while (elem != NULL)
        {
            /* liberta cada elemento */
            aux = elem->proximo;
            vetor_apaga(elem->clien->vistos);
            free(elem->clien->username);
            elem->clien->username=NULL;
            free(elem->clien);
            free(elem);
            elem = aux;
        }
    }

    /* liberta vector e estrutura */
    free(td->elementos);
    free(td);
}

int clienteAdiciona(colecaoClientes *td, const char *username, unsigned int filmId)
{
   // Resolução do exercicio 4
   return -1;
}

int clienteRemove(colecaoClientes *td, const char *username)
{
    int index;
    elementoCliente * elem, * aux;

    if (!td) return -1;

    /* calcula hash para a string a remover */
    index = hash_cliente(username, td->tamanho);

    elem = td->elementos[index];
    aux = NULL;

    /* para cada elemento na posicao index */
    while(elem != NULL)
    {
        /* se for a string que se procura, e' removida */
        if (strcmp(elem->clien->username, username) == 0)
        {
            /* se nao for a primeira da lista */
            if (aux != NULL)
                aux->proximo = elem->proximo;
            else
                td->elementos[index] = elem->proximo;
            free(elem->clien);
            free(elem);

            return 1;
        }

        aux = elem;
        elem = elem->proximo;
    }
    return 0;
}


int colecaoNumClientes(colecaoClientes *td)
{
	// resolução do exercicio 5
    return -1;
}

int clienteExiste(colecaoClientes *td, const char *username)
{
    // resolução do exercicio 6
	return -1;

}

unsigned long hash_cliente(const char* username, int tamanho)
{
    int c, t = strlen(username);
    unsigned long hash = 7;

    for(c = 0; c < t; c++)
    {
        hash += (int) username[c]*powf(2,c);
    }

    return hash % tamanho;

}

/*================================================================================*/
void mostraTabela(colecaoClientes *td)
{
    int i;
    elementoCliente * elem;


    printf("TABELA DE CLIENTES (%d Clientes)\n", colecaoNumClientes(td));
    for (i = 0; i < td->tamanho; i++)
    {
        if (td->elementos[i])
        {
            printf("\t[%2d]", i);
            elem = td->elementos[i];
            while (elem)
            {
                printf(" : [\"%s\" Filmes: ", elem->clien->username);
                if (elem->clien->vistos->tamanho>0)
                {

                    for (int j=0; j<elem->clien->vistos->tamanho; j++)
                    {
                        printf(" (%d)", elem->clien->vistos->elementos[j]);
                    }

                }
                printf("]");
                elem = elem->proximo;
            }
            printf("\n");
        }
    }
    printf("\n");
}



///////////////////////////////////////////////////



/* inserir um Novo Filme*/
int inserirNovoFilme(colecaoFilmes* colecFilmes, char* titulo, char* categoria, int filmId, float rating)
{
    int i;
    if(!colecFilmes)
        return -1;
    elementoFilme* elem;
     if (elem == NULL)
    {
        /* novo elemento, chave nao existe na lista */

        /* aloca memoria para o elemento */
        elem = (elementoFilme*) malloc(sizeof (elementoFilme));
        if (elem == NULL)
            return -1;

        /* aloca memoria para o valoreto */
        elem->film = (filme*) malloc(sizeof (filme));
        if (elem->film == NULL)
            return -1;
    }
        /*copia chave e valor */
        strcpy(elem->film->titulo,titulo);
        //strcpy(elem->obj->valor, valor);

    //strcpy(colecFilmes->elementos[0]->film->titulo,titulo);
   // printf("\nehehe =  %s",colecFilmes->elementos[0]->film->titulo);
   /* for(int i = 0;i < colecFilmes->tamanho;i++){
        
        if(strcmp(colecFilmes->elementos[i]->film->titulo,titulo)==0
        ||colecFilmes->elementos[i]->film->filmId == filmId) //os filmes ñ podem ter mesmo id e nome
            return 0;
    } */
  // strcpy(colecFilmes->elementos[colecFilmes->tamanho]->film->titulo,titulo);
   // strcpy(colecFilmes->elementos[colecFilmes->tamanho]->film->categoria,categoria);
   // colecFilmes->elementos[colecFilmes->tamanho]->film->filmId = filmId;
  // colecFilmes->elementos[colecFilmes->tamanho]->film->rating = rating;
   colecFilmes->tamanho++;
    //return 1;//sucesso*/
    return 1;

}

colecaoFilmes* filmesCarrega(const char *nomeFicheiro)
{
    int resultado;
    FILE *fp;
    char str[MAXCHAR];
    char ch;
    int tamanho_colecao=0;
    char *filename = "filmesShort.txt";
    char titulo[100];
    char categoria[20];
    char filmId[3];
    float rating;

    fp = fopen(filename , "r");
    if (fp == NULL){
        printf("Could not open file %s",filename);
        return NULL; //erro
    }

    //fclose(fp);
    fp = fopen(filename , "r");
    colecaoFilmes * colecao = colecaoFilmesNova(tamanho_colecao);
    printf(" TAM = %d",tamanho_colecao);
    while(!feof(fp)){
        fscanf(fp,"%100[^|\t]|%20[^|\t]|%3[^|]|%f",titulo,categoria,filmId,&rating);
        printf("\n%s|",titulo);printf("%s|",categoria);printf("%d|",atoi(filmId));printf("%f\n",rating);
        inserirNovoFilme(colecao,titulo,categoria,atoi(filmId),rating);
    }
    fclose(fp);
    return colecao;
}


// Remover um filme///
int removerFilme(colecaoFilmes* colecFilmes, colecaoClientes *td, int nFilme)
{
    // resolução do exercicio 7
   return -1;
}

// Remover a estrutura colecaoFilmes
void colecaoFilmesApaga(colecaoFilmes* colecFilmes,colecaoClientes *td)
{
    // resolução do exercicio 8

}

//Sugestões //////////////////////////////


vetor* sugestoes(colecaoFilmes* colecFilmes, colecaoClientes *td,char* username, int nFilmes, float limiar)
{
	// resolução do exercicio 9
   return NULL;
}



///////////////////////////////////////