/*****************************************************************/
/*           Movies | PROG2 | MIEEC | 2018/19                */
/*****************************************************************/
/*Jorge Afonso Barandas Queirós up201808903 ------------- Nuno Guterres Nogueira up201808905*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "movies.h"
#include "tools.c"
#define MAXCHAR 100


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

/*================================================================================*/
void mostraTabelaFilmes(colecaoFilmes *colecFilmes)
{
    int i;
    
    if (colecFilmes == NULL) {
        printf ("\nColecaoFilmes Vazia!");
        return;
    } 

    elementoFilme * elem;
    printf("TABELA DE FILMES (%d Filmes)\n", colecFilmes->tamanho);
    for (i = 0; i < colecFilmes->tamanho; i++)
    {
        if (colecFilmes->elementos[i])
        {
            printf("\n[%2d] ", i);
            elem = colecFilmes->elementos[i];
            while (elem)
            {
                printf("\nFilmes: %s\n", elem->film->titulo);
                
                elem = elem->proximo;
            }
            printf("\n");
        }
    }
    printf("\n");
}



colecaoFilmes* TabelaDispersao(int size) {

    colecaoFilmes* colecFilmes = malloc (sizeof(colecaoFilmes));
    if (colecFilmes == NULL)
        return NULL;
    
    colecFilmes->tamanho = size; // funciona melhor com numeros primos
    colecFilmes->elementos = malloc (sizeof(colecaoFilmes)*colecFilmes->tamanho);

    if(colecFilmes->elementos == NULL) {
        free(colecFilmes);
        printf ("\nSem memória disponivel");
        return NULL;
    }

    for (int i = 0; i < colecFilmes->tamanho; i++) {
        colecFilmes->elementos[i] = NULL;
    }

    return colecFilmes;

}

/* Procura um elemento na tabela, devolvendo o endereco do no’ da
respetiva lista ligada onde e’ encontrado (ou NULL caso nao seja encontrado) */
elementoFilme* ProcuraTabela (filme* eFilm, colecaoFilmes* TabelaDispersao) 
{
    unsigned int position;
    elementoFilme *filmElem;

    position = hash_filme(eFilm->filmId, TabelaDispersao->tamanho);
    filmElem = TabelaDispersao->elementos[position];

    while (filmElem != NULL && filmElem->film != eFilm)
        filmElem = filmElem->proximo;

    return filmElem;
}

int InsereNaTabela (filme* elemento, colecaoFilmes* TabelaDispersao) 
{
    unsigned int position;
    elementoFilme  *new_node, *present_node;

    /* Retorna endereço na tabela, ou NULL se não tiver inserido */
    present_node = ProcuraTabela(elemento, TabelaDispersao);

    /* Se não consta da tabela.... */
    if (present_node == NULL) 
    {
        position = hash_filme(elemento->filmId, TabelaDispersao->tamanho);
        new_node = (elementoFilme*) malloc (sizeof(elementoFilme));
        if (new_node == NULL)  {
            printf ("\nNao há espaço na memória");
            return -1;
        }

        new_node->film = elemento;
        new_node->proximo = TabelaDispersao->elementos[position];
        TabelaDispersao->elementos[position] = new_node;
            
        return 1;
    } else return 0;

}

///////////////////////////////////////////////////


/* inserir um Novo Filme*/
int inserirNovoFilme(colecaoFilmes* colecFilmes, char* titulo, char* categoria, int filmId, float rating)
{
    int n;

    if (colecFilmes == NULL)
        printf("\nSem espaço em ColecFilmes");

    filme * filmeDi = malloc (sizeof(filme));
    if (filmeDi == NULL) {
        printf ("\nSem espaço filmeDi");
        return -1;
    }
        
    filmeDi->titulo = malloc(strlen(titulo)+1);
    filmeDi->categoria = malloc(strlen(categoria)+1);
    /*if ((filmeDi->titulo || filmeDi->categoria) == NULL)
        return -1;*/

    strcpy(filmeDi->categoria, categoria);
    strcpy(filmeDi->titulo, titulo);
    filmeDi->filmId = filmId;
    filmeDi->rating = rating;

    n = InsereNaTabela(filmeDi, colecFilmes);

    /* elemento ja constava da tabela */
    if (n == 0)
        return 0;

    /* Nao constava e foi adicionado */
    if (n == 1) 
        return 1;
}

colecaoFilmes* filmesCarrega(const char *nomeFicheiro)
{
   FILE *fp;
    char *filename = "filmesShort.txt";
    char titulo[100];
    char categoria[20];
    int filmId;
    float rating;

    fp = fopen(filename , "r");
    if (fp == NULL){
        printf("Could not open file %s",filename);
        return NULL; 
    }
   
    /* Cria Tabela de dispersao */
    colecaoFilmes * colecao = TabelaDispersao(200);

    printf ("\nTamanho da tabela: %d", colecao->tamanho);
    while(!feof(fp)){
        fscanf(fp,"%100[^|\t]|%20[^|\t]|%d|%f",titulo,categoria,&filmId,&rating);
        inserirNovoFilme(colecao, titulo, categoria, filmId, rating);
    }
    
    fclose(fp);
    return colecao;
}

// Remover um filme///
int removerFilme(colecaoFilmes* colecFilmes, colecaoClientes *td, int filmId)
{
    unsigned int position;

    position = hash_filme(filmId, colecFilmes->tamanho);

    if (colecFilmes == NULL) {
        printf ("\nSem memória !");
        return -1;
    }
    elementoFilme* filmElem = ProcuraTabela(colecFilmes->elementos[position]->film, colecFilmes);
    elementoFilme* aux;
    elementoCliente * elem;

    /* Nao consta da tabela */
    if (filmElem == NULL)
    {
        printf ("\nNao consta da tabela !");
        return 0;
    } 
    else 
    {
        aux = NULL;

        /* Enquanto existir valores na tabela */
        while(filmElem != NULL)
        {
            /* Se coincidir o mesmo film ID */
            if (filmElem->film->filmId == filmId)
            {
                if (aux != NULL)
                    aux->proximo = filmElem->proximo;
                else
                    colecFilmes->elementos[position] = filmElem->proximo;

                free(filmElem->film);
                free(filmElem);

                /* A remover todos os vistos **deste filme** de todos os clientes */
                for (int i = 0; i < td->tamanho; i++) 
                {
                    elem = td->elementos[i];

                    /* Consta da tabela - há cliente registado */
                    if (elem != NULL) 
                    {
                        /*Verificar se viu o filme ou não */
                        for (int j = 0; j < elem->clien->vistos->tamanho; j++)
                        {
                            if (elem->clien->vistos->elementos[j] == filmId)
                            {
                                vetor_remove(elem->clien->vistos, j);
                            }
                        }
                    }
                }

                return 1;
            }

            aux = filmElem;
            filmElem = filmElem->proximo;
        }
    }
}

// Remover a estrutura colecaoFilmes
void colecaoFilmesApaga(colecaoFilmes* colecFilmes, colecaoClientes *td)
{
    if (!(colecFilmes)) {
        printf ("\nSem espaço alocado");
        return;
    }

    elementoCliente *elemCliente;
    elementoFilme *elemFilme;

    for (int i = 0; i < td->tamanho; i++) 
    {
        elemCliente = td->elementos[i];

        /* Se existe cliente */
        if (elemCliente != NULL) 
        {
            for (int j = 0; j < colecFilmes->tamanho; j++)
            {
                elemFilme = colecFilmes->elementos[j];

                /* Se existir filme, remove dos vistos do cliente */
                if (elemFilme != NULL) 
                {
                    vetor_remove(elemCliente->clien->vistos, j);
                }
            }
        }
    }

    /* to every malloc I need 1 free() */
    for (int i = 0; i < colecFilmes->tamanho; i++) {
        
        elemFilme = colecFilmes->elementos[i];

        if (elemFilme != NULL)
        {
            free(elemFilme->film->titulo);
            free(elemFilme->film->categoria);
            free(elemFilme->film);
        }
    }

    free(colecFilmes->elementos);
    free(colecFilmes);
    /* Não muito certo em relaçao as memorias */
}

//Sugestões //////////////////////////////

vetor* sugestoes(colecaoFilmes* colecFilmes, colecaoClientes *td,char* username, int nFilmes, float limiar)
{
    vetor *sugestoes = vetor_novo();
    int id;
    int count_filmescatpref =0;
    int count =0;
    int cont=0;
    char *categoria =(char*)malloc(sizeof(char));
    float rating;
    float sorted[100];
    int ids[100];
    int filmID;
    int categoria_a_sugerir;
    char insere =0;
    FILE *filmesnvistos;
    FILE *filmescatpref;
    filmesnvistos = fopen("filmesnaovistos.txt", "w");
    char filmes[2000];
    int *valores = (int*)malloc(10*sizeof(int));
    char *cat =(char*)malloc(sizeof(char));
    elementoFilme *elem_film;
    elementoCliente *elem_clien;
    long index = hash_cliente(username, td->tamanho);
    //procura o cliente na colecao clientes
    elem_clien = td->elementos[index];
    while (elem_clien != NULL && strcmp(elem_clien->clien->username, username) != 0){
        elem_clien = elem_clien->proximo;
    }
    for(int i = 0;i <= colecFilmes->tamanho;i++)
    {
        if (colecFilmes->elementos[i])
        {
            elem_film = colecFilmes->elementos[i];
            while (elem_film)
            {
                for(int j = 0;j <  elem_clien->clien->vistos->tamanho;j++)
                {
                    filmID = td->elementos[index]->clien->vistos->elementos[j]; 
                    if(elem_film->film->filmId == filmID) // utilizador viu este filme
                        insere=1;    
                }
                if(insere==0 && elem_film->film->rating > limiar){
                    sprintf(filmes,"%d_%.2lf_%s\n",
                    elem_film->film->filmId,elem_film->film->rating,elem_film->film->categoria);
                    fputs(filmes,filmesnvistos);
            }     
                insere=0;
                elem_film = elem_film->proximo;
            }
        
        }

    }
    fclose(filmesnvistos);
    //guardado o vetor com os filmes que ele não viu, veremos qual a catergoria mais vista pelo utilizador;
    valores = categoriasMaisVista(colecFilmes,td,username);
    categoria_a_sugerir = maior(valores);
    printf("\n->_>_>_>_>_CATEGORIA A SUGERIR = %d",categoria_a_sugerir);
    for(int i=0;i<10;i++){
        printf("\n%d",valores[i]);
    }
    //agora vamos selecionar os filmes para sugerir conforme as categorias mais vistas
    filmescatpref = fopen("filmescatpreferida.txt","w+");
    while(count_filmescatpref < nFilmes){
        filmesnvistos = fopen("filmesnaovistos.txt","r");
        int categoria_anterior = categoria_a_sugerir;
        cat = CategoriaASugerir(valores,&categoria_a_sugerir); //categoria mais vista pelo user
        int categoria_atual = categoria_a_sugerir;
        while(fscanf(filmesnvistos,"%d_%f_%s\n",&id,&rating,categoria)!=EOF)
        {
            if(strcmp(categoria,cat)==0){
                sprintf(filmes,"%d_%.2lf_%s\n",
                id,rating,categoria);
                fputs(filmes,filmescatpref);
                count_filmescatpref ++;
                insert_sorted(sorted,ids, count,id,rating,&categoria_anterior,&categoria_atual,&count_filmescatpref); 
                count ++;
            }
        printf("\ncount = %d",count);
        }
        //memset(sorted,0,sizeof(sorted));
        count =0;

    }
    fclose(filmesnvistos);
    fclose(filmescatpref);
    filmescatpref = fopen("filmescatpreferida.txt","r");

    printf("\ncount = %d",count);
    for (int i = count-1; i >= 0; i-- ) 
    {
        printf("\n%d",ids[i]);
        if(cont <nFilmes){
            vetor_insere(sugestoes,ids[i],-1);
            cont++;
        }
       
    }
    while(count < nFilmes ){//insere 0's no final
        vetor_insere(sugestoes,0,-1);
        count ++;
    }
    fclose(filmescatpref);

    //free dos mallocs
    //free(cat);
    //free(valores);
    //free(categoria);
    return sugestoes; 
}




////////////////////////////////////!!!!!!!!FIM!!!!!!!!//////////////////////////////////////////////

