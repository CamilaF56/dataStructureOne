// Camila Fontes Santos
// Laila Esterfane dos Santos Valenca
// Miguel Ferreira Franca

#include <iostream>
#include <time.h>
#include <cstdlib>
#include <locale.h>

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
        cout<<"lista vazia"<<endl;
    return; // lista vazia

    while (atual->next != listaEnc->fim) // vai deletando até o atual for igual a listaEnc->fim
    {
        prox = atual->next;
        free(atual);
        atual = prox;
    }
    free(atual);
    listaEnc->fim = NULL;
    listaEnc->quant = 0;
    cout<<"lista vazia"<<endl;
}

void exibeLista(tipoLista *listaEnc) // OK
{
    if(listaEnc->fim == NULL || listaEnc->quant==0)
    {
        cout<<"lista vazia"<<endl;
    }
    else
    {
        tipoNo *atual;
        atual = listaEnc->fim->next;
        cout<< atual->nome<<endl;
        while(atual != listaEnc->fim)
        {
            atual = atual->next;
            cout<< atual->nome<<endl;
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------//

int insereListaVazia(tipoLista *listaEnc, string name) // OK
{
    tipoNo *novoNo; /*Declaração do ponteiro para o nó a ser criado*/
    novoNo = new tipoNo;
    if(novoNo == NULL) /*Caso a memória não tenha sido alocada*/
        return 0;
    novoNo->nome = name; /*Coloca o dado dentro do nó criado*/
    novoNo->next = novoNo; /*Faz o próximo do nó criado ser ele próprio*/
    listaEnc->fim = novoNo;
    listaEnc->quant++;
}

int insereNaFrente(tipoLista *listaEnc, string name) // OK
{
    tipoNo *novoNo;
    if(listaEnc->fim == NULL)
        insereListaVazia(listaEnc, name);
    else
    {
        novoNo = new tipoNo;
        if(novoNo == NULL)
            return 0;
        novoNo->nome = name;
        novoNo->next = listaEnc->fim->next;
        listaEnc->fim->next = novoNo;
        listaEnc->quant++;
    }
    return 1;
}

//-------------------------------------------------------------------------------------------------------------------//

void sortear(tipoLista *listaEnc)
{
    srand(time(NULL));
    //string nomes[listaEnc->quant];
    int ale = (rand() % listaEnc->quant) + 1;

    // Criação da lista circular
    tipoNo *cabeca = NULL;
    tipoNo *novoParticipante, *atual;

    // Insere cada participante na lista circular
    for (int i = 0; i < listaEnc->quant; i++)
    {
        novoParticipante = new tipoNo;
        novoParticipante->nome = "Participante " + to_string(i+1);

        if (cabeca == NULL)
        {
            cabeca = novoParticipante;
            cabeca->next = cabeca;
            atual = cabeca;
        }
        else
        {
            novoParticipante->next = cabeca;
            atual->next = novoParticipante;
            atual = novoParticipante;
        }
    }

    // Começa a contar a partir do primeiro participante
    atual = cabeca;

    // Enquanto houver mais de um participante na lista circular
    while (atual->next != atual)
    {
        for (int i = 1; i < ale-1; i++)
        {
            atual = atual->next; // Percorre m participantes
        }

        tipoNo *participanteRemovido = atual->next;
        atual->next = participanteRemovido->next; // Remove o participante atual da lista
        if (participanteRemovido == cabeca)   // Se o primeiro participante foi removido, atualiza o início da lista
        {
            cabeca = atual->next;
        }
        cout << "Eliminado: " << participanteRemovido->nome << endl;
        delete participanteRemovido; // Libera a memória alocada para o nó removido
        listaEnc->quant--;

        atual = atual->next; // Passa para o próximo participante na lista
    }

    // O último participante é o vencedor
    cout << "Vencedor: " << atual->nome << endl;
    delete atual, novoParticipante, cabeca;
    listaEnc->quant=0;

    esvaziar(listaEnc);
}

//-------------------------------------------------------------------------------------------------------------------//

int main()
{
    setlocale(LC_ALL, "Portuguese");
    tipoLista listaEnc;
    int op = 0;
    char aux[30];
    inicializar(&listaEnc);
    do
    {
        cout << " MENU\n\n1 - Insere pessoa na lista vazia" << endl;
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
            esvaziar(&listaEnc);
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
