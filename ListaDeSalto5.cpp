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
        if (Ant == NULL)
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
            if (Ant->prox[nivel] != NULL)novo->prox[nivel]->ant[nivel] = novo;
            Ant->prox[nivel] = novo;
        }
    }
}
template<typename T>
void Insere(Lista<T>& L, int chave, T valor)
{
    No<T>* NovoPtr = new No<T>(chave, valor);
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
int main()
{
    Lista<int> L;
    IniciaLista(L);
    Insere(L, 1,0);
    Insere(L, 5,0);
    Insere(L, 20,1);
    Insere(L, 40,1);
    mostraLista(L);
    return 0;
}