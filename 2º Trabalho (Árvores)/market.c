/*****************************************************************/
/*           Market | PROG2 | MIEEC | 2018/19                */
/*****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "market.h"

#define RAIZ 		(1)
#define PAI(x) 		(x/2)
#define FILHO_ESQ(x) 	(x*2)
#define FILHO_DIR(x) 	(x*2+1)

//Declaracao funcoes auxiliares//
int maior_que(elemento_t * e1, elemento_t * e2);
int avl_altura(no_avl *no);
int calc_balanceamento(no_avl *N);
no_avl* roda_direita(no_avl *y);
no_avl* roda_esquerda(no_avl *x);
no_avl* avl_no_valormin(no_avl* no);
no_avl* avl_no_valormax(no_avl* no);
int max(int a, int b);
int min(int a, int b);
void avlNoApaga(no_avl* node);
void avlNoCopia(no_avl* nodeDest, no_avl* nodeSource);
void avlNoValorCopia(no_avl* nodeDest, no_avl* nodeSrc);

//*****************EXERCICIO 5.1****************************************************//

elemento_t* elemento_novo(const char* nameItem, const char* expDate, int qty, int sellRate)
{
    elemento_t* elemento = (elemento_t*)malloc(sizeof(elemento_t*));
	if(elemento == NULL)
	    return NULL;
    strcpy(elemento->nameItem,nameItem);
    strcpy(elemento->expirationDate,expDate);
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
    tm.tm_isdst=0;
    time_t t,t1;
    int diff;
    strptime(elem->expirationDate, "%F", &tm);
    strptime(CURDATE, "%F", &tm1);
    diff=difftime(tm.tm_mday,tm1.tm_mday)+((tm.tm_mon-tm1.tm_mon)*30)+((tm.tm_year-tm1.tm_year)*365);
    double metrica=1/(diff+(1000.0/elem->sellRate));
    return metrica;
} 

//***************************PILHAS (5.2)********************************//

heap* heap_nova(int capacidade)
{
	heap *monte = (heap*) malloc(sizeof(heap*));
	if(monte == NULL)
		return NULL;
	monte->capacidade = capacidade;
    monte->tamanho=0;
    monte->elementos = (elemento_t**) malloc(sizeof(elemento_t**));
    return monte;
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
    /*elemento_t *maximo = h->elementos[1]; //posicao 1 tem o elemento mais prioritário!!
    elemento_t *aux= maximo;
    h->tamanho--;
    if(!aux)
        return NULL;
    return aux;*/
    if(!h || !h->tamanho)
    {
        return 0;
    }

    elemento_t *maximo = h->elementos[1];
    elemento_t *ultimo = h->elementos[h->tamanho];
    h->elementos[h->tamanho] = 0;
    --h->tamanho;

    if(h->tamanho)
    {
        int pos, filho;
        for(pos = 1; pos*2 <= h->tamanho; pos = filho)
        {
            filho = pos*2;
            if(filho < h->tamanho && maior_que(h->elementos[filho+1], h->elementos[filho]))
            {
                ++filho;
            }

            if(maior_que(h->elementos[filho], ultimo))
            {
                h->elementos[pos] = h->elementos[filho];
            }
            else
            {
                break;
            }
        }
        h->elementos[pos] = ultimo;
    }

  
    elemento_t * aux = malloc (sizeof (elemento_t*));
    aux = h->elementos[1];
    free(maximo);
    return aux;
}


void mostraHeap(heap *h)
{
    if(!h)
        return;

    for(int indice =1; indice<=(h->tamanho); indice++)
    {
        printf("%s %s %d %d %f\n",h->elementos[indice]->nameItem, h->elementos[indice]->expirationDate,
                        h->elementos[indice]->qty,h->elementos[indice]->sellRate,
                        h->elementos[indice]->priorityVal);
    }
}

//********************Implementacao criacao categoria nova****************************************//

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
    if(categ==NULL)
        return;
    
    heap_apaga(categ->itemTree);
    free(categ->categName);
    categ->categName = NULL;
    free(categ);
    categ = NULL;
}

//*************************AVL (5.3)**************************************//

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
    if (no == NULL)
        return avl_novo_no(categ);
    if (strcmp(categ->categName, no->categ->categName) < 0)
        no->esquerda  = avl_insere(no, categ);
    else if(strcmp(categ->categName, no->categ->categName) > 0)
        no->direita = avl_insere(no, categ);
    else {
        return no;
         }
    
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
}
no_avl* avl_remove(no_avl* no, const char *categStr)
{
   if (no == NULL)
        return no;

    /* se a str a ser removida é menor do que a str da raiz,
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
                no->esquerda = temp->esquerda;
                no->direita = temp->direita;
                no->altura = temp->altura;
            }

            free(temp->categ->categName);
            free(temp);
        }
        else
        {
            /* no' com dois filhos: obtem sucessor em-ordem (menor da arvore direita) */
            no_avl* temp = avl_no_valormin(no->direita);

            /* copia o valor em.ordem do sucessor para este no' */
            no->categ->categName = realloc(no->categ->categName, (strlen(temp->categ->categName)+1)*sizeof(char));
            strcpy(no->categ->categName, temp->categ->categName);

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
}

no_avl* avl_pesquisa(no_avl *no, const char* categStr)
{
    if(no == NULL){
        printf("\nno= NULL!!");
        return NULL;
    } 
    if(strcmp(categStr, no->categ->categName) < 0)
        return avl_pesquisa(no->esquerda,categStr);

    else if(strcmp(categStr, no->categ->categName) > 0)
        return avl_pesquisa(no->direita, categStr);

    else
    {
        printf("\ntem a categoria!");
        return no;
    }

}
void avl_apaga_i(no_avl *no)
{
	if (!no)
		return;
	avl_apaga_i(no->esquerda);
	avl_apaga_i(no->direita);
	avlNoApaga(no);
}

void avl_apaga(arvore_avl* avl)
{
	if (!avl) return;
	avl_apaga_i(avl->raiz);
    free(avl);
}
//******************************ARTIGO_ADICIONA (5.4)************************************//
int artigo_adiciona(arvore_avl *avl, elemento_t* elem, char *categName, int capCateg)
{
    //procurar categoria na arvore, se nao tiver é preciso adicionar, por outras palavras 
    //se avl_pesquisa()==NULL então avl_insere(); visto
    //adicionar o artigo se nao existir
    //verificar se a adicao nao passa a capacidade da heap
   
    no_avl* no;
    //category_t * cat;
    no = avl_pesquisa(no,categName);
     printf("\ntou aqui eheh");
    if(no==NULL)
    {
      
        printf("\nentrei aqui 2");
        no_avl* no_novo;
        printf("\ntou aqui");
        no_novo->categ = novaCategoria(no_novo->categ->itemTree,categName);
        no_novo = avl_insere(no_novo,no_novo->categ);
    }
    /*if(cat->itemTree->tamanho < capCateg){
         printf("\nagora tou aqui");
       if(heap_insere(cat->itemTree,elem) == 1){
            printf("\ne agr tou aqui");
            return 1;
       }
     
    }   */
    //default
    return 0;
}


///   Implementacao montagem montra (5.5)   ///
elemento_t** criar_montra(arvore_avl* avl, const char* categName, int numPorItem, int totalItems, int* tamanhoArray)
{
    //Default
    return NULL;
}

//*******************************FUNCOES AUXILIARES*********************************//8

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

int enoughItems(heap* h, int numPorItem, int totalItems)
{
    int qtyCounter = 0;
    for (int i=1; i<=(h->tamanho); i++)
    {
        qtyCounter += min(h->elementos[i]->qty,numPorItem);
        if(qtyCounter>=totalItems)
        {
            return 1;
        }
    }
    return 0;
}

void avlNoApaga(no_avl* node)
{

    if(!node)
        return;

    categoriaApaga(node->categ);
    node->esquerda = NULL;
    node->direita = NULL;
    node->altura = 0;
    free(node);
    node = NULL;
}

void avlNoCopia(no_avl* nodeDest, no_avl* nodeSrc)
{

    if(!nodeSrc || !nodeDest)
        return;

    nodeDest->categ->categName = realloc(nodeDest->categ->categName, (strlen(nodeSrc->categ->categName)+1)*sizeof(char));
    strcpy(nodeDest->categ->categName, nodeSrc->categ->categName);
    heap_apaga(nodeDest->categ->itemTree);
    nodeDest->categ->itemTree = heap_nova(nodeSrc->categ->itemTree->capacidade);

    for(int i=RAIZ; i<=(nodeSrc->categ->itemTree->tamanho); i++)
    {
        nodeDest->categ->itemTree->elementos[i] = elemento_novo(nodeSrc->categ->itemTree->elementos[i]->nameItem,
        nodeSrc->categ->itemTree->elementos[i]->expirationDate,nodeSrc->categ->itemTree->elementos[i]->qty,
        nodeSrc->categ->itemTree->elementos[i]->sellRate);
    }
	nodeDest->categ->itemTree->tamanho = nodeSrc->categ->itemTree->tamanho;
    nodeDest->esquerda = nodeSrc->esquerda;
    nodeDest->direita = nodeSrc->direita;
    nodeDest->altura = nodeSrc->altura;

}

void avlNoValorCopia(no_avl* nodeDest, no_avl* nodeSrc)
{

    if(!nodeSrc || !nodeDest)
        return;

    nodeDest->categ->categName = realloc(nodeDest->categ->categName, (strlen(nodeSrc->categ->categName)+1)*sizeof(char));
    strcpy(nodeDest->categ->categName, nodeSrc->categ->categName);
    heap_apaga(nodeDest->categ->itemTree);
    nodeDest->categ->itemTree = heap_nova(nodeSrc->categ->itemTree->capacidade);

    for(int i=RAIZ; i<=(nodeSrc->categ->itemTree->tamanho); i++)
    {
        nodeDest->categ->itemTree->elementos[i] = elemento_novo(nodeSrc->categ->itemTree->elementos[i]->nameItem,
        nodeSrc->categ->itemTree->elementos[i]->expirationDate,nodeSrc->categ->itemTree->elementos[i]->qty,
        nodeSrc->categ->itemTree->elementos[i]->sellRate);
    }
	nodeDest->categ->itemTree->tamanho = nodeSrc->categ->itemTree->tamanho;
}