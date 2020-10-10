#include<iostream>

/*
############################################################################
IMPLEMENTACAO BASEADA EM CLASSE + HIERARQUIA, NO ESPECIALIZADO
template<typename T>
class no{
    public:
    int chave;
    no* prox;
    no* ant;
    T info;
};

template<typename T>
class no5 : public no<T>{
    public:
    no5* prox5;
    no5* ant5;
};

template<typename T>
class no20 : public no5<T>{
    public:
    no20* prox20;
    no20* ant20;
};

template<typename T>
class Lista
{
    public:
    int tam;
    no<T>* fim[3];
    no<T>* inicio[3];

    Lista<T>()
    {
        for(int i=0;i<3;i++)
        {
            this->inicio[i] = NULL;
            this->fim[i] = NULL;
        }
        tam =0;
    }
};
###############################################################################
*/
/*
############################################################################
IMPLEMENTACAO BASEADA EM ESTRUTURA, COM NO GENERICO
template<typename T>
struct no{
    T info;
    int chave;
    no* prox[3];        //A posicao 0 se refere as conexoes de nivel 1
    no* ant[3];         //a posicao 1 para novel 2...
};

template<typename T>
struct Lista
{
    int tam;
    no<T>* fim[3];
    no<T>* inicio[3];

    Lista<T>()
    {
        for(int i=0;i<3;i++)
        {
            this->inicio[i] = NULL;
            this->fim[i] = NULL;
        }
        tam =0;
    }
};
########################################################################
*/

int main()
{
    //Lista<int> L;
    return 0;
}