#include <stdio.h>

/*Implementação de Lista Simplesmente Encadeada - Estrutura de Dados I -
 * 2021.2*/

/*Tipo de dado que representa um nó da lista encadeada*/
typedef struct no
{
    int dado;
    struct no *proxNo;
    struct no *anterior;
} tipoNo;

/*Tipo de dado que representa uma lista encadeada*/
typedef struct listaGerenciada
{
    tipoNo *inicio;
    tipoNo *fim;
    int quant;
} tipoLista;

/*Função de inicialização da lista encadeada - Deve ser chamada antes de usar a
 * lista*/
void inicializa(tipoLista *lista)
{
    lista->fim = NULL;
    lista->inicio = NULL;
    lista->quant = 0;
}

/*Função para inserção de nó em lista vazia*/
int insereListaVazia(tipoLista *listaEnc, int valor)
{
    tipoNo *novoNo;
    novoNo = (tipoNo *)malloc(sizeof(tipoNo));
    if (novoNo == NULL)
        return 0;
    novoNo->dado = valor;
    novoNo->proxNo = NULL;
    listaEnc->inicio = novoNo;
    listaEnc->fim = novoNo;
    listaEnc->quant++;
    return 1;
}

/*Função que faz a inserção de um nó na frente de uma lista simplesmente
 * encadeada*/
int insereNaFrente(tipoLista *listaEnc, int valor)
{
    tipoNo *novoNo;
    if (listaEnc->inicio == NULL)
        insereListaVazia(listaEnc, valor);
    else
    {
        novoNo = (tipoNo *)malloc(sizeof(tipoNo));
        if (novoNo == NULL)
            return 0;
        novoNo->dado = valor;
        novoNo->proxNo = listaEnc->inicio;
        listaEnc->inicio = novoNo;
        listaEnc->quant++;
        return 1;
    }
}

/*Função de exibição da lista simplesmente encadeada*/
int exibeLista(tipoLista *listaEnc)
{
    tipoNo *atual; // Variável que será usada para percorrer a lista*/
    if (listaEnc->inicio == NULL)
        return 0;
    atual = listaEnc->inicio;
    printf("\nLista encadeada: ");
    while (atual != NULL)
    {
        printf("%8d", atual->dado);
        atual = atual->proxNo;
    }
}

int insereNoFim(tipoLista *listaEnc, int valor)
{
    tipoNo *novoNo;
    if (listaEnc->inicio == NULL)
        insereListaVazia(listaEnc, valor);
    else
    {
        novoNo = (tipoNo *)malloc(sizeof(tipoNo));
        if (novoNo == NULL)
            return 0;
        novoNo->dado = valor;
        novoNo->proxNo = NULL;
        listaEnc->fim->proxNo = novoNo;
        listaEnc->fim = novoNo;
        listaEnc->quant++;
        return 1;
    }
}

void removerFim(tipoLista *listaEnc)
{
    tipoNo *penultimo, *ultimo;
    if (listaEnc->quant == 0)
    {
        return; // lista vazia, não há nada para remover
    }
    else if (listaEnc->quant == 1)
    {
        // há somente um nó na lista, então remove
        ultimo = listaEnc->inicio;
        listaEnc->inicio = NULL;
        listaEnc->fim = NULL;
    }
    else
    {
        // há mais de um nó na lista, encontrando o penultimo nó(ultimo que tem
        // valor)
        penultimo = NULL;
        ultimo = listaEnc->inicio;
        while (ultimo->proxNo != NULL)
        {
            penultimo = ultimo;
            ultimo = ultimo->proxNo;
        }
        penultimo->proxNo = NULL;
        listaEnc->fim = penultimo;
    }
    free(ultimo);
    listaEnc->quant--;
}

void destruirLista(tipoLista *listaEnc)
{
    tipoNo *aux;
    while (listaEnc->inicio != NULL)
    {
        aux = listaEnc->inicio;
        listaEnc->inicio = aux->proxNo;
        free(aux);
    }
    listaEnc->fim = NULL;
    listaEnc->quant = 0;
}

void removeDoInicio(tipoLista *listaEnc)
{
    tipoNo *aux;
    aux = listaEnc->inicio;
    if (aux == NULL)
        return;
    listaEnc->inicio = listaEnc->inicio->proxNo;
    if (listaEnc->inicio == NULL)
        listaEnc->fim = NULL;
    listaEnc->quant--;
    free(aux);
}

void main()
{
    tipoLista lista;
    int op, aux, aux2;
    inicializa(&lista);
    do
    {
        printf("\n      Menu Lista Encadeada");
        printf("\n1 - Insere um elemento na lista vazia");
        printf("\n2 - Insere elemento no inicio da lista");
        printf("\n4 - Insere elemento no fim da lista");
        printf("\n5 - Remove do inicio da lista");
        printf("\n6 - Remove nó do final da lista");
        printf("\n7 - Destruir lista");
        printf("\n9 - Exibe a lista");
        printf("\n0 - Encerra o programa");
        printf("\nDigite sua opção:");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            printf("\nDigite o elemento que deseja inserir:");
            scanf("%d", &aux);
            insereListaVazia(&lista, aux);
            break;
        case 2:
            printf("\nDigite o elemento que deseja inserir:");
            scanf("%d", &aux);
            insereNaFrente(&lista, aux);
            break;
        case 4:
            printf("\nDigite o elemento que deseja inserir: ");
            scanf("%d", &aux);
            if (insereNoFim(&lista, aux))
                printf("\nElemento inserido com sucesso");
            break;
        case 5:
            removeDoInicio(&lista);
            break;
        case 6:
            removerFim(&lista);
            break;
        case 7:
            destruirLista(&lista);
            break;
        case 9:
            if (!exibeLista(&lista))
                printf("\nLista vazia!");
            break;
        case 0:
            printf("\nEncerrando programa.");
            break;
        default:
            printf("\nOpção inválida!");
        }
    } while (op != 0);
}