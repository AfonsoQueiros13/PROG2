/*****************************************************************/
/*           TOOLS | FUNCOES AUXILIARES | PROG2 | MIEEC | 2018/19                */
/*****************************************************************/
/*Jorge Afonso Barandas Queirós up201808903 ------------- Nuno Guterres Nogueira up201808905*/

int maior(int array[10]){
    int greatest = 0;
    int maior = 0;
    for (int i = 0; i < 9; i++) {
        if (array[i] > greatest){
            greatest = array[i];
            maior = i;
        }
    }  
    return maior;
}

char* CategoriaASugerir(int* valores,int *categoria_a_sugerir){
    int max =valores[0]; 
    char *cat =(char*)malloc(sizeof(char));
    for (int i = 1; i < 10; i++){ //vamos ver qual é a categoria predominante
        if (valores[i] > max && i != *categoria_a_sugerir){
            max = valores[i];
            *categoria_a_sugerir = i; 
        }
    }
    if(*categoria_a_sugerir ==0){
        strcpy(cat,"Documentary");
        valores[*categoria_a_sugerir]=0;
    }
    if(*categoria_a_sugerir ==1){
        strcpy(cat,"Short");
        valores[*categoria_a_sugerir]=0;
    }
    if(*categoria_a_sugerir ==2){
        strcpy(cat,"Horror");
        valores[*categoria_a_sugerir]=0;
    }
    if(*categoria_a_sugerir ==3){
        strcpy(cat,"Drama");
        valores[*categoria_a_sugerir]=0;
    }
    if(*categoria_a_sugerir ==4){
        strcpy(cat,"Comedy");
        valores[*categoria_a_sugerir]=0;
    }
    if(*categoria_a_sugerir ==5){
        strcpy(cat,"News");
        valores[*categoria_a_sugerir]=0;
    }
    if(*categoria_a_sugerir ==6){
        strcpy(cat,"Action");
        valores[*categoria_a_sugerir]=0;
    }
    if(*categoria_a_sugerir ==7){
        strcpy(cat,"Animation");
        valores[*categoria_a_sugerir]=0;
    }
    if(*categoria_a_sugerir ==8){
        strcpy(cat,"Fantasy");
        valores[*categoria_a_sugerir]=0;
    }
    if(*categoria_a_sugerir ==9){
        strcpy(cat,"Romance");
        valores[*categoria_a_sugerir]=0;
    }
    return cat;
}


void insert_sorted (float *sorted,int *ids, int count,int id, float value,int anterior,int atual,int po)
{
    int i = 0;
 
    if(anterior == atual){
        printf("id = %d",ids[count]);
        sorted[count] = value;
        ids[count] = id;
        if (count == 0) return;
        for (i = count;i > 0; i--) {
            if (value < sorted[i-1]) 
            {
            sorted[i] = sorted[i-1];
            ids[i] = ids[i-1];
            }
            else break;
        }

        sorted[i] = value;
        ids[i] = id;
    }
    else{
        sorted[count] = value;
        ids[count] = id;
    }
}

unsigned long hash_filme (int filmId, int size) {
    return filmId % size;
}

int * categoriasMaisVista(colecaoFilmes* colecFilmes, colecaoClientes *td,char* username){
    int filmID;
    unsigned long position;
    long index;
    int *contador = (int*)malloc(2*sizeof(int));
    char *cat =(char*)malloc(sizeof(char));
    for(int i=0;i< 10 ;i++)
        contador[i] = 0;
    elementoCliente* elem_client;
    elementoFilme* elem_film;
    //primeira coisa a sugerir -> filmes com a categoria mais vista pelo utilizador
    /* calcula hash para a string a adicionar */
    index = hash_cliente(username, td->tamanho);
    //procura o cliente na colecao clientes
    elem_client = td->elementos[index];
    while (elem_client != NULL && strcmp(elem_client->clien->username, username) != 0){
        elem_client = elem_client->proximo;
    }
    /*encontrou o cliente neste ponto, vamos procurar os filmes por ele vistos
    e perceber quais sao as categorias mais predominantes */
    for(int i = 0;i < elem_client->clien->vistos->tamanho;i++){
        //ver quantos documentarios
        filmID = td->elementos[index]->clien->vistos->elementos[i];
        position = hash_filme(filmID, colecFilmes->tamanho);
        elem_film = colecFilmes->elementos[position];
        //ja descobrimos a localizacao do filme na colecao, agr vamos ver qual a sua categoria
        if(strcmp("Documentary",elem_film->film->categoria)==0) //filme  documentario
            contador[0] ++;
        if(strcmp("Short",elem_film->film->categoria)==0) //filme short
            contador[1] ++;
        if(strcmp("Horror",elem_film->film->categoria)==0) //filme horror
            contador[2] ++;
        if(strcmp("Drama",elem_film->film->categoria)==0) //filme drama
            contador[3] ++;
        if(strcmp("Comedy",elem_film->film->categoria)==0) //filme comedia
            contador[4] ++;
        if(strcmp("News",elem_film->film->categoria)==0) //filme news
            contador[5] ++;
        if(strcmp("Action",elem_film->film->categoria)==0) //filme action
            contador[6] ++;
        if(strcmp("Animation",elem_film->film->categoria)==0) //filme animation
            contador[7] ++;
        if(strcmp("Fantasy",elem_film->film->categoria)==0) //filme fantasy
            contador[8] ++;
        if(strcmp("Romance",elem_film->film->categoria)==0) //filme fantasy
            contador[9] ++;
    }
    return contador;
}
