// Camila Fontes Santos
// Laila Esterfane dos Santos Valenca
// Miguel Ferreira Franca

#include <iostream>
#include <time.h>
#include <cstdlib>

using namespace std;

//---------------------------------------------------------------------------------------------------------------//
typedef struct no // OK
{
    string nome;
    struct no *next;
} tipoNo;

typedef struct lista // OK
{
    tipoNo *fim;
    int quant;
} tipoLista;

void inicializar(tipoLista *listaEnc) // OK
{
    listaEnc->fim = NULL;
    listaEnc->quant = 0;
}

void esvaziar(tipoLista *listaEnc) // OK
{
    tipoNo *atual = listaEnc->fim;
    tipoNo *prox;

    if (atual == NULL)
        return; // lista vazia

    while (atual->next != listaEnc->fim) // vai deletando até o atual for igual a listaEnc->fim
    {
        prox = atual->next;
        free(atual);
        atual = prox; // declarando o prox
    }
    free(atual);
    listaEnc->fim = NULL;
    listaEnc->quant = 0;
}
void exibeLista(tipoLista *listaEnc) // Ok
{
    if (listaEnc->fim == NULL)
    {
        cout << "A lista esta vazia." << endl;
        return;
    }

    tipoNo *atual;
    atual = listaEnc->fim->next;
    while (atual != listaEnc->fim)
    {
        cout << atual->nome << " ";
        atual = atual->next;
    }
    cout << atual->nome << endl;
}

//-------------------------------------------------------------------------------------------------------------------//

void insereListaVazia(tipoLista *listaEnc, string name) // OK
{
    tipoNo *novoNo; /*Declaração do ponteiro para o nó a ser criado*/
    novoNo = new tipoNo;
    if (novoNo == NULL) /*Caso a memória não tenha sido alocada*/
        return;
    novoNo->nome = name;   /*Coloca o dado dentro do nó criado*/
    novoNo->next = novoNo; /*Faz o próximo do nó criado ser ele próprio*/
    listaEnc->fim = novoNo;
    listaEnc->quant++;
}

int insereNaFrente(tipoLista *listaEnc, string name) // OK
{
    tipoNo *novoNo;
    novoNo = new tipoNo;
    novoNo->nome = name.c_str();
    if (listaEnc->fim == NULL && listaEnc->quant == 0)   // lista vazia
    {
        novoNo->next = novoNo; // Caso esteja vazia, o novo nó apontará para ele
        // mesmo, e a lista apontará para o novo nó
        listaEnc->fim = novoNo;
        return 0;
    }
    else
    {
        novoNo->next =
            listaEnc->fim
            ->next; // o próximo nó do novo nó será o primeiro nó da lista
        listaEnc->fim->next =
            novoNo; // o próximo nó do último nó da lista será o novo nó

        return 1;
    }
    listaEnc->quant++; // quant++ de elemntos da lista
}

//-------------------------------------------------------------------------------------------------------------------//

void sortear(tipoLista *listaEnc)
{

    int ale = rand() % (listaEnc->quant + 1);

    // Verificar se a lista está vazia
    if (listaEnc->fim == NULL)
    {
        cout << "Lista está vazia" << endl;
        return;
    }

    // Definir posição inicial
    tipoNo *anterior = listaEnc->fim;
    tipoNo *atual = anterior->next;
    for (int i = 1; i < listaEnc->quant; i++)
    {
        anterior = atual;
        atual = atual->next;
    }

    // Eliminar pessoas a cada intervalo
    while (listaEnc->quant > 1)
    {
        for (int i = 0; i < listaEnc->quant; i++)
        {
            anterior = atual;
            atual = atual->next;
        }
        anterior->next = atual->next;
        tipoNo *aux = atual;
        atual = atual->next;
        delete aux;
        listaEnc->quant--;
    }

    // Imprimir vencedor
    cout << "\nVencedor: " << atual->nome << endl;
}



//-------------------------------------------------------------------------------------------------------------------//

int main()
{
    tipoLista listaEnc;
    int op = 0;
    char aux[30];
    inicializar(&listaEnc);
    do
    {
        cout << " MENU\n\n1 - Insere pessoa na lista vazia:" << endl;
        cout << "2 - Inserir pessoa na frente" << endl;
        cout << "3 - Sortear pessoa" << endl;
        cout << "4 - Exibe lista" << endl;
        cout << "5 - Esvaziar lista" << endl;
        cout << "0 - Encerra programa" << endl;
        cout << "Escolha sua opcao: " << endl;
        cin >> op;
        switch (op)
        {
        case 1:
            cout << "\nDigite a pessoa que deseja inserir em lista vazia: " << endl;
            cin >> aux;
            insereListaVazia(&listaEnc, aux);
            cout << "\n";
            break;
        case 2:
            cout << "\nDigite a pessoa que deseja inserir na frente: " << endl;
            cin >> aux;
            insereNaFrente(&listaEnc, aux);
            cout << "\n";
            break;
        case 3:
            sortear(&listaEnc);
            cout << "\n";
            break;

        case 4:
            cout << " Exibir lista: " << endl;
            exibeLista(&listaEnc);
            cout << "\n";
            break;

        case 5:
            esvaziar(&listaEnc);
            cout << "\nLista esvaziada" << endl;
            cout << "\n";
            break;

        case 0:
            cout << "\nEncerrando programa." << endl;
            cout << "\n";
            break;
        }
    }
    while (op != 0);
}
