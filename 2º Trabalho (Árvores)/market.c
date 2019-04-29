            /*****************************************************************/
            /*           Market | PROG2 | MIEEC | 2018/19                */
            /*****************************************************************/
//****INCLUDES E DEFINES NECESSÁRIOS**************************************//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "market.h"

#define RAIZ 		(1)
#define PAI(x) 		(x/2)
#define FILHO_ESQ(x) 	(x*2)
#define FILHO_DIR(x) 	(x*2+1)

//**************DECLARACAO DE FUNÇÕES AUXILIARES**********************************//
int maior_que(elemento_t * e1, elemento_t * e2);
int avl_altura(no_avl *no);
int calc_balanceamento(no_avl *N);
no_avl* roda_direita(no_avl *y);
no_avl* roda_esquerda(no_avl *x);
no_avl* avl_no_valormin(no_avl* no);
no_avl* avl_no_valormax(no_avl* no);
int max(int a, int b);
int min(int a, int b);


//*****************EXERCICIO 5.1****************************************************//

elemento_t* elemento_novo(const char* nameItem, const char* expDate, int qty, int sellRate)
{
    elemento_t* elemento = (elemento_t*)malloc(sizeof(elemento_t*));
	if(elemento == NULL)
	    return NULL;
    strncpy(elemento->nameItem,nameItem,sizeof(nameItem));
    strncpy(elemento->expirationDate,expDate,sizeof(expDate));
    elemento->qty = qty;
    elemento->sellRate = sellRate;
    elemento->priorityVal = calcMetrica(elemento);
    return elemento;
}

void elemento_apaga(elemento_t* elem)
{
    free(elem);
    elem = NULL;
}

//****************************CALCULO METRICA PRIORIDADE***********************************//

float calcMetrica(elemento_t* elem)
{
    struct tm tm,tm1;
    time_t t,t1;
    int diff;
    strptime(elem->expirationDate, "%F", &tm);
    strptime(CURDATE, "%F", &tm1);
    diff=difftime(tm.tm_mday,tm1.tm_mday);
    double metrica=1/(diff+(double)(1000.0/elem->sellRate));
    return metrica;
} 

//***************************PILHAS (5.2)********************************//

heap* heap_nova(int capacidade)
{
	heap *pilha = (heap*) malloc(sizeof(heap*));
	if(pilha == NULL)
		return NULL;
	/* pilha esta' vazia */
	pilha->capacidade = capacidade;
    return pilha;
}

void heap_apaga(heap *h)
{
	free(h);
    h = NULL;
}


int heap_insere(heap *h, elemento_t* elem)
{
	elemento_t * aux;
	int i;
	//gilc
	if(!h) return 0;
	/* se heap esta' cheia, nao insere elemento */
	if (h->tamanho >= h->capacidade)
		return 0;

	if (!elem)
		return 0;

	/* coloca elemento no fim da heap */
	h->tamanho++;
	i = h->tamanho;
	h->elementos[i] = elem;

 	/* enquanto elemento for mais prioritario do que o respetivo pai, troca-os */
	while (i != RAIZ && maior_que(h->elementos[i], h->elementos[PAI(i)]))
	{
		aux = h->elementos[PAI(i)];
		h->elementos[PAI(i)] = h->elementos[i];
		h->elementos[i] = aux;
		i = PAI(i);
	}
	return 1;

    //Default
    return 0;
}


elemento_t* heap_remove(heap * h)
{
    elemento_t * aux;
	int i;
    /* enquanto elemento for mais prioritario do que o respetivo pai, troca-os */
	while (i != RAIZ && maior_que(h->elementos[i], h->elementos[PAI(i)]))
	{
		aux = h->elementos[PAI(i)];
		h->elementos[PAI(i)] = h->elementos[i];
		h->elementos[i] = aux;
		i = PAI(i);
	}
    elemento_apaga(aux);
    return NULL;
}



void mostraHeap(heap *h)
{
    if(!h)
        return;

    for(int indice =1; indice<=h->tamanho; indice++)
    {
        printf("%s %s %d %d %f\n",h->elementos[indice]->nameItem, h->elementos[indice]->expirationDate,
                        h->elementos[indice]->qty,h->elementos[indice]->sellRate,
                        h->elementos[indice]->priorityVal);
    }
}


//////////////////////////////////////////////

/// Implementacao criacao categoria nova ///

category_t* novaCategoria(heap* itemTree, char* categName)
{
    category_t* retCat = (category_t*)malloc(sizeof(category_t));

    if(retCat == NULL)
    {
        return NULL;
    }

    retCat->itemTree = itemTree;

    retCat->categName = (char*)malloc((strlen(categName)+1)*sizeof(char));

    if(retCat->categName==NULL)
    {
        return NULL;
    }

    strcpy(retCat->categName,categName);

    return retCat;

    //Default
    return NULL;
}

void categoriaApaga(category_t* categ)
{
    heap_apaga(categ->itemTree);
    free(categ->categName);
    categ->categName = NULL;
    free(categ);
    categ = NULL;
}


////////////////////////////////////////////

//////   Implementacao AVLs (5.3)  ///////

arvore_avl* avl_nova()
{
    // Implementacao exercicio 5.4.1
    arvore_avl *avl = (arvore_avl*) malloc(sizeof(arvore_avl));
    if(avl == NULL)
        return NULL;

    avl->raiz = NULL; /* arvore vazia */

    return avl;

    // Default
    return NULL;
}

no_avl* avl_novo_no(category_t* categ)
{
    // Implementacao exercicio 5.4.2
    no_avl *no = (no_avl*) malloc(sizeof(no_avl));

    if(no==NULL)
        return NULL;

    no->categ = categ;
    no->esquerda = NULL;
    no->direita  = NULL;
    no->altura = 0;  /* novo no e' inicialmente uma folha */
    return no;

    // Default
    return NULL;
}

no_avl* avl_insere(no_avl *no, category_t* categ)
{

    // Default
    return NULL;
}

no_avl* avl_remove(no_avl *no, const char* categStr)
{
    // Implementacao exercicio 5.4.4

    /* 1. efetua remocao normal de arvore binaria de pesquisa */

    if (no == NULL)
        return no;

    /* se o nome da categoria a ser removida é menor do que a str da raiz,
       entao esta' na sub-arvore esquerda */
    if ( strcmp(categStr, no->categ->categName) < 0 )
        no->esquerda = avl_remove(no->esquerda, categStr);

    /* se a str a ser removida é maior do que a str da raiz,
       entao esta' na sub-arvore direita */
    else if( strcmp(categStr, no->categ->categName) > 0 )
        no->direita = avl_remove(no->direita, categStr);

    /* se a str a ser removida é igual a str da raiz,
       entao e' este no a remover */
    else
    {
        /* no' com apenas um filho ou sem filhos */
        if( (no->esquerda == NULL) || (no->direita == NULL) )
        {
            no_avl *temp = no->esquerda ? no->esquerda : no->direita;

            /* caso sem filhos */
            if(temp == NULL)
            {
                temp = no;
                no = NULL;
            }
            else /* caso de um filho */
            {
                /* copia os conteudos do filho que não está vazio */
                no->categ->categName = realloc(no->categ->categName, (strlen(temp->categ->categName)+1)*sizeof(char));
                strcpy(no->categ->categName, temp->categ->categName);
                heap_apaga(no->categ->itemTree);
                no->categ->itemTree = temp->categ->itemTree;
                no->esquerda = temp->esquerda;
                no->direita = temp->direita;
                no->altura = temp->altura;
            }

            free(temp->categ->categName);
            free(temp->categ);
            free(temp);
        }
        else
        {
            /* no' com dois filhos: obtem sucessor em-ordem (menor da arvore direita) */
            no_avl* temp = avl_no_valormin(no->direita);

            /* copia o valor em.ordem do sucessor para este no' */
            no->categ->categName = realloc(no->categ->categName, (strlen(temp->categ->categName)+1)*sizeof(char));
            strcpy(no->categ->categName, temp->categ->categName);
            heap_apaga(no->categ->itemTree);
            no->categ->itemTree = temp->categ->itemTree;

            /* apaga o sucessor em-ordem */
            no->direita = avl_remove(no->direita, temp->categ->categName);
        }
    }

    /* se a arvore tinha apenas um no, então retorna */
    if (no == NULL)
      return no;

    /* 2. atualiza a altura do no corrente */
    no->altura = max(avl_altura(no->esquerda), avl_altura(no->direita)) + 1;

    /* 3. calcula o fator de balanceamento deste no ancestral para verificar
       se deixou de estar balanceado */
    int balance = calc_balanceamento(no);

    /* se o no deixou de estar balanceado, existem 4 casos */

    if (balance > 1) {
        /* Arvore e' right-heavy */
        if (calc_balanceamento(no->direita) < 0) {
            /* Sub-arvore direita é left-heavy */
            /* Rotacao RL */
            no->direita = roda_direita(no->direita);
            return roda_esquerda(no);
        } else {
            /* Rotacao L */
            return roda_esquerda(no);
        }
    }
    else if (balance < -1) {
        /* Arvore e' left-heavy */
        if (calc_balanceamento(no->esquerda) > 0) {
            /* Sub-arvore esquerda é right-heavy */
            /* Rotacao LR */
            no->esquerda = roda_esquerda(no->esquerda);
            return roda_direita(no);
        } else {
            /* Rotacao R */
            return roda_direita(no);
        }
    }
    /* caso esteja balanceada retorna o apontador para o no (inalterado) */
    return no;

    // Default
    return NULL;
}

no_avl* avl_pesquisa(no_avl *no, const char* categStr)
{

    // Default
    return NULL;
}

void avl_apaga(arvore_avl* avl)
{
	if (!avl) return;
    while(avl->raiz != NULL)
    {
        avl->raiz = avl_remove(avl->raiz, avl->raiz->categ->categName);
    }

    free(avl);
}

///////////////////////////////////////



///   Implementacao adicao artigo (5.4)
int artigo_adiciona(arvore_avl *avl, elemento_t* elem, char *categName, int capCateg)
{

    //Default
    return 0;

}

//////////////////////////////////////////////


///   Implementacao montagem montra (5.5)   ///
elemento_t** criar_montra(arvore_avl* avl, const char* categName, int numPorItem, int totalItems, int* tamanhoArray)
{
    //Default
    return NULL;
}

//////////////////////////////////////////////





// Auxiliary functions

int maior_que(elemento_t* e1, elemento_t* e2)
{
	if (e1 == NULL || e2 == NULL)
	{
		return 0;
	}

	return e1->priorityVal > e2->priorityVal;
}

int avl_altura(no_avl *no)
{
    if (no == NULL)
        return -1;
    return no->altura;
}

int calc_balanceamento(no_avl *N)
{
    if (N == NULL)
        return 0;
    return avl_altura(N->direita) - avl_altura(N->esquerda);
}

no_avl* roda_direita(no_avl *y)
{
    no_avl *x = y->esquerda;
    no_avl *T2 = x->direita;

    /* efetua rotacao */
    x->direita = y;
    y->esquerda = T2;

    /* atualiza alturas */
    y->altura = max(avl_altura(y->esquerda), avl_altura(y->direita))+1;
    x->altura = max(avl_altura(x->esquerda), avl_altura(x->direita))+1;

    /* retorna novo no' */
    return x;
}

no_avl* roda_esquerda(no_avl *x)
{
    no_avl *y = x->direita;
    no_avl *T2 = y->esquerda;

    /* efetua rotacao */
    y->esquerda = x;
    x->direita = T2;

    /*  atualiza alturas */
    x->altura = max(avl_altura(x->esquerda), avl_altura(x->direita))+1;
    y->altura = max(avl_altura(y->esquerda), avl_altura(y->direita))+1;

    /* retorna novo no' */
    return y;
}


no_avl* avl_no_valormin(no_avl* no)
{
    no_avl* curr = no;

    /* percorre a arvore para encontrar o filho mais 'a esquerda */
    while (curr->esquerda != NULL)
        curr = curr->esquerda;

    return curr;
}

no_avl* avl_no_valormax(no_avl* no)
{
    no_avl* curr = no;

    /* percorre a arvore para encontrar o filho mais 'a direita */
    while (curr->direita != NULL)
        curr = curr->direita;

    return curr;
}

int max(int a, int b)
{
    return (a > b)? a : b;
}

int min(int a, int b)
{
    return (a < b)? a : b;
}