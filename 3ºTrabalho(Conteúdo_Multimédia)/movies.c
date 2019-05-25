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

/////   Implementacao ClienteNovo  ///////
elementoCliente* clienteNovo(const char *username,int id){

    elementoCliente * cli = (elementoCliente*)malloc(sizeof (elementoCliente));
    cli->clien = (cliente*)malloc(sizeof(cliente));
    
    cli->clien->username = (char*)malloc(sizeof(char));
    strcpy(cli->clien->username,username);
    
    cli->clien->vistos = vetor_novo();
    cli->clien->vistos->elementos = (int*)malloc(sizeof(int));
    if(id!=0)
        vetor_insere(cli->clien->vistos,id,-1);
    return cli;
    
}


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

/******************************** FUNCAO 1 FEITA!!****************************************************/
int clienteAdiciona(colecaoClientes *td, const char *username, unsigned int filmId)
{
    //por alguma razao adiciona um id =0, falta resolver isto
    char insere = 1;
    long  index;
    elementoCliente * elem;
    if (!td) return -1;

    /* calcula hash para a string a adicionar */
    index = hash_cliente(username, td->tamanho);
    /* verifica se chave ja' existe na lista */
    elem = td->elementos[index];
    while (elem != NULL && strcmp(elem->clien->username, username) != 0){
        elem = elem->proximo;
    }
        
    if (elem == NULL) //vai-se criar novo cliente
    {
        if(strcmp("abcde",username)==0)
            printf("\nnão existe o username %s! irá ser add agora.\n ",username);
        //copia id e nome 
        elem = clienteNovo(username,filmId);
        //insere no inicio da lista 
        elem->proximo = td->elementos[index];
        td->elementos[index] = elem;
        //mostraTabela(td);
        return 1;
        
    } else { //existe o cliente com o ID passado por parametro
        for(int i = 0 ; i < td->elementos[index]->clien->vistos->tamanho;i++){
            if(td->elementos[index]->clien->vistos->elementos[i] == filmId){
                return 0;
            }
        }
        //mostraTabela(td);
        vetor_insere(td->elementos[index]->clien->vistos,filmId,-1);
        return 1;  
    }

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


/******************************** FUNCAO 2 FEITA!!****************************************************/
int colecaoNumClientes(colecaoClientes *td)
{
    //funcao feita!
    int i, count = 0;
    elementoCliente * elem;

    if (!td) return -1;

    /* percorre todos os elementos da tabela */
    for (i = 0; i < td->tamanho; i++)
    {
        elem = td->elementos[i];
        while(elem != NULL)
        {
            elem = elem->proximo;
            count++;
        }
    }
    return count;
}

/********************************FUNCAO 3 FEITA!!****************************************************/
int clienteExiste(colecaoClientes *td, const char *username)
{
    elementoCliente* elem;
    long index = hash_cliente(username, td->tamanho);
    /* verifica se chave ja' existe na lista */
    elem = td->elementos[index];
    if(elem!=NULL)
        printf("\nelem = %s",elem->clien->username);
    while (elem != NULL ){
        if(strcmp(elem->clien->username, username) == 0)
            return 1;
        elem = elem->proximo;
    }  
    return 0;

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
    // resolução do exercicio 5
	return -1;
}

colecaoFilmes* filmesCarrega(const char *nomeFicheiro)
{
   // resolução do exercicio 6
   return NULL;


}


// Remover um filme///
int removerFilme(colecaoFilmes* colecFilmes, colecaoClientes *td, int filmId)
{
    // resolução do exercicio 7
   return -1;
}

// Remover a estrutura colecaoFilmes
void colecaoFilmesApaga(colecaoFilmes* colecFilmes, colecaoClientes *td)
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

