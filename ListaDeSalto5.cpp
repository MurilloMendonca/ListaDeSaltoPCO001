#include<iostream>

template<typename T>
struct No{
    T info;
    int chave;
    No* prox[3];        //A posicao 0 se refere as conexoes de nivel 1
    No* ant[3];         //a posicao 1 para nivel 2...

    No(){
        for(int i=0;i<3;i++)
        {
            this->prox[i] = NULL;
            this->ant[i] = NULL;
        }
    }
    No(int k, T v)
    {
        for(int i=0;i<3;i++)
        {
            this->prox[i] = NULL;
            this->ant[i] = NULL;
        }
        this->chave=k;
        this->info=v;
    }
    No(int k)
    {
        for(int i=0;i<3;i++)
        {
            this->prox[i] = NULL;
            this->ant[i] = NULL;
        }
        this->chave=k;
    }
};

template<typename T>
struct Lista
{
    int tam;
    No<T>* fim[3];
    No<T>* inicio[3];
};
template<typename T>
void IniciaLista (Lista<T>& L)
{
    for(int i=0;i<3;i++)
    {
        L.inicio[i] = NULL;
        L.fim[i] = NULL;
    }
    L.tam =0;
}

template<typename T>
void Insere(Lista<T>& L, No<T>*& novo, int nivel)
{
    if (L.inicio[nivel] == NULL)
    {
        L.inicio[nivel] = novo;
        L.fim[nivel] = novo;
    }
    else
    {
        No<T>* Aux = L.inicio[nivel];
        No<T>* Ant = NULL;
        while ((Aux != NULL) && (Aux->chave < novo->chave))//Caminha
        {
            Ant = Aux;
            Aux = Aux->prox[nivel];
        }
        if (Ant == NULL)//Se nao andou
        {
            novo->prox[nivel] = L.inicio[nivel];
            novo->ant[nivel] = NULL;
            L.inicio[nivel] = novo;
            L.inicio[nivel] = novo;
        }
        else
        {
            novo->prox[nivel] = Ant->prox[nivel];
            novo->ant[nivel] = Ant;
            if(Ant->prox[nivel] == NULL) L.fim[nivel] = novo;
            if (Ant->prox[nivel] != NULL)novo->prox[nivel]->ant[nivel] = novo;
            Ant->prox[nivel] = novo;
        }
    }
}
template<typename T>
void Insere(Lista<T>& L, int chave, T valor)
{
    No<T>* NovoPtr = new No<T>(chave, valor);
    L.tam++;
    Insere(L, NovoPtr, 0);
    if(chave%5==0)
        Insere(L,NovoPtr, 1);
    if(chave%20==0)
        Insere(L,NovoPtr, 2);
}

template<typename T>
void mostraLista(Lista<T> L)
{
    No<T>* aux;
    for(int i=0; i<3;i++){
        printf("\n Nivel %i: ", i);
        aux = L.inicio[i];
        if(aux==NULL) continue;
        while (aux->prox[i] != NULL)
        {
            printf("%i <-> ", aux->chave);
            aux = aux->prox[i];
        }
        printf("%i -> NULL\n", aux->chave);
    }
}
template<typename T>
void mostraListaReversa(Lista<T> L)
{
    No<T>* aux;
    for(int i=0; i<3;i++){
        printf("\n Nivel %i: ", i);
        aux = L.fim[i];
        if(aux==NULL) continue;
        while (aux->ant[i] != NULL)
        {
            printf("%i <-> ", aux->chave);
            aux = aux->ant[i];
        }
        printf("%i -> NULL\n", aux->chave);
    }
}
template<typename T>
bool busca(Lista<T> L, No<T>*& N)
{
    int nivel=2;
    No<T>* aux, *ant;
    aux = L.inicio[nivel];
    ant=L.inicio[nivel-1];
        while ( nivel>=0)
        {
            if(aux==NULL)//Se chegou no final da lista no nivel atual -> desce o nivel
            {
                nivel--;
                aux = ant;
                continue;
            }
            if(aux->chave==N->chave)//Se achou ->retorna
            {
                delete N;
                N = aux;
                return true;
            }
            if(aux->chave>N->chave)//Se passou -> volta 1 e desce de nivel
            {
                aux = ant;
                if(ant==L.inicio[nivel-1]){//se não andou
                    if(nivel==2) //E se da pra descer
                        ant = L.inicio[nivel-2];
                }
                else ant = ant->ant[nivel];//Se andou, volta 1
                
                nivel--;
                continue;
            }
            ant = aux;
            aux = aux->prox[nivel];
        }
    return false;
}

template<typename T>
bool busca(Lista<T> L, int chave)
{
    No<T>* busc = new No<T>(chave);
    return busca(L,busc);
}
template<typename T>
void remove(Lista<T>&L, No<T>*N, int nivel)
{
    if(N->ant[nivel]==NULL)//primeiro no
    {
        L.inicio[nivel] = N->prox[nivel];
    }
    else
    {
        N->ant[nivel]->prox[nivel] = N->prox[nivel];
        
    }
    if(N->prox[nivel]==NULL)//ultimo no
    {
        L.fim[nivel] = N->ant[nivel];
    }
    else
    {
        N->prox[nivel]->ant[nivel] = N->ant[nivel];
    }

}
template<typename T>
bool remove(Lista<T>&L, No<T>&N)
{
    No<T>* aux = new No<T>(N.chave);
    if(!busca(L,aux))
    {
        delete aux;
        return false;
    }
    L.tam--;
    remove(L, aux, 0);
    if(aux->chave%5==0)
        remove(L,aux,1);
    if(aux->chave%20==0)
        remove(L,aux,2);
    delete aux;
    return true;
    
}

template<typename T>
bool remove(Lista<T>&L, int chave)
{
    No<T> rem(chave);
    return remove(L, rem);
}


int main()
{
    Lista<int> L;
    IniciaLista(L);
    Insere(L, 1,0);
    Insere(L, 5,0);
    Insere(L, 20,1);
    Insere(L, 40,1);
    Insere(L,42,0);
    printf("\nLista de tamnho: %i\n", L.tam);
    printf("Antes");
    mostraLista(L);
    remove(L,40);
    printf("Depois");
    mostraLista(L);
    printf("Reverso:");
    mostraListaReversa(L);//Pra conferir se os ponteiros do fim e ant estao funcionando
    printf("\nLista de tamnho: %i\n", L.tam);
    //if(busca(L,5)) printf("Achou\n"); 
    return 0;
}