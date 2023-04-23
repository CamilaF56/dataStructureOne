#include <stdio.h>

/*Implementação de Lista Simplesmente Encadeada - Estrutura de Dados I - 2021.2*/

/*Tipo de dado que representa um nó da lista encadeada*/
typedef struct no
{
    int dado;
    struct no *proxNo;
    struct no *antNo;
} tipoNo;

/*Tipo de dado que representa uma lista encadeada*/
typedef struct listaGerenciada
{
    tipoNo *inicio;
    tipoNo *fim;
    int quant;
} tipoLista;

/*Função de inicialização da lista encadeada - Deve ser chamada antes de usar a lista*/
void inicializa(tipoLista *lista)
{
    lista->fim = NULL;
    lista->inicio = NULL;
    lista->quant = 1;
}

/*Função para inserção de nó em lista vazia*/
int insereListaVazia(tipoLista *listaEnc, int valor)
{
    tipoNo *novoNo;
    novoNo = (tipoNo *)malloc(sizeof(tipoNo));
    if (novoNo == NULL)
        return 0;
    destruirLista(listaEnc);
    novoNo->antNo = NULL;
    novoNo->dado = valor;
    novoNo->proxNo = NULL;
    listaEnc->inicio = novoNo;
    listaEnc->fim = novoNo;
    listaEnc->quant = 1;
    return 1;
}

int insereNaFrente(tipoLista *listaEnc, int valor)
{
    tipoNo *novoNo;
    if (listaEnc->inicio == NULL)
        return insereListaVazia(listaEnc, valor);
    else
    {
        novoNo = (tipoNo *)malloc(sizeof(tipoNo));
        if (novoNo == NULL)
            return 0;
        novoNo->dado = valor;
        novoNo->proxNo = listaEnc->inicio;
        novoNo->antNo = NULL;
        listaEnc->inicio->antNo = novoNo; // antNo do no anterior
        listaEnc->inicio = novoNo;
        listaEnc->quant++;
        return 1;
    }
}

int inserirFim(tipoLista *listaEnc, int valor)
{
    tipoNo *novoNo;
    if (listaEnc->inicio == NULL)
    {
        return insereListaVazia(listaEnc, valor);
    }
    else
    {
        novoNo = (tipoNo *)malloc(sizeof(tipoNo));
        if (novoNo == NULL)
        {
            return 0;
        }
        novoNo->dado = valor;
        novoNo->proxNo = NULL;
        novoNo->antNo = listaEnc->fim;
        listaEnc->fim->proxNo = novoNo;
        listaEnc->fim = novoNo;
        listaEnc->quant++;
        return 1;
    }
}

int removerInicio(tipoLista *listaEnc)
{
    tipoNo *novoNo;
    if (listaEnc->inicio == NULL)
    {
        return 0;
    }
    else
    {
        if (listaEnc->quant == 1)
        {
            free(listaEnc->inicio);
            listaEnc->quant = 0;
            listaEnc->inicio=NULL;
            listaEnc->fim=NULL;
            return 1;
        }
        novoNo = listaEnc->inicio->proxNo;
        free(listaEnc->inicio);
        listaEnc->inicio = novoNo;
        novoNo->antNo = NULL;
        listaEnc->quant--;
        return 1;
    }
}

int removerFim(tipoLista *listaEnc)
{
    tipoNo *novoNo;
    if (listaEnc->inicio == NULL)
    {
        return 0;
    }
    else
    {
        if (listaEnc->quant == 1)
        {
            free(listaEnc->inicio);
            listaEnc->quant = 0;
            listaEnc->inicio=NULL;
            listaEnc->fim=NULL;
            return 1;
        }
        novoNo = listaEnc->fim->antNo;
        free(listaEnc->fim);
        listaEnc->fim = novoNo;
        novoNo->proxNo = NULL;
        listaEnc->quant--;
        return 1;
    }
}

void exibirLista(tipoLista *listaEnc)
{
    tipoNo *aux = listaEnc->inicio;
    while (aux != NULL)
    {
        printf("%d ", aux->dado);
        aux = aux->proxNo;
    }
    printf("\n");

}

void determinadaPosicao(tipoLista *listaEnc, int valor){
    //considerar lista ordenada
    if(listaEnc->inicio==NULL){
        insereListaVazia(listaEnc, valor);
    }else if(listaEnc->inicio->dado >= valor){
        insereNaFrente(listaEnc, valor);
    }else if(listaEnc->fim->dado <= valor){
        inserirFim(listaEnc, valor);
    }else{
        tipoNo *aux = listaEnc->inicio;
        while(valor >= aux->proxNo->dado){
            aux = aux->proxNo;
        }
        tipoNo *novoNo = (tipoNo*)malloc(sizeof (tipoNo));
        novoNo->dado = valor;
        novoNo->proxNo = aux->proxNo;
        aux->proxNo->antNo = novoNo;
        novoNo->antNo = aux;
        aux->proxNo = novoNo;
        listaEnc->quant++;
    }
}

int pesquisa(tipoLista *listaEnc, int valor){
    tipoNo *aux = listaEnc->inicio;
    if(listaEnc->inicio==NULL){
        printf("Não há elementos na lista\n");
        return 0;
    }
    while(aux!=NULL && aux->dado!=valor){
        aux = aux->proxNo;
    }

    if(aux==NULL){
        printf("Não achou o elemento\n");
    }else{
        printf("Achou o elemento: %d\n", valor);
    }
}

int destruirLista(tipoLista *listaEnc){
    tipoNo *aux;
    if(listaEnc->inicio==NULL){
        return 0;
    }
    while(listaEnc->inicio!=NULL){
        aux = listaEnc->inicio;
        listaEnc->inicio = listaEnc->inicio->proxNo;
        free(aux);
        return 1;
    }
    listaEnc->quant=0;
    listaEnc->inicio=NULL;
    listaEnc->fim=NULL;
}

int main()
{
    tipoLista lista;
    int op, aux, aux2;
    inicializa(&lista);
    do
    {
        printf("\n      Menu Lista Duplamente Encadeada");
        printf("\n1 - Insere um elemento na lista vazia");
        printf("\n2 - Insere elemento no inicio da lista");
        printf("\n3 - Insere elemento no fim da lista");
        printf("\n4 - Remover no inicio");
        printf("\n5 - Remover no fim");
        printf("\n6 - Insere em determinada posição");
        printf("\n7 - Exibir lista");
        printf("\n8 - Destruir lista");
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
            printf("\nDigite o elemento que deseja inserir no inicio da lista:");
            scanf("%d", &aux);
            insereNaFrente(&lista, aux);
            break;
        case 3:
            printf("\nDigite o elemento que deseja inserir no fim da lista:");
            scanf("%d", &aux);
            inserirFim(&lista, aux);
            break;
        case 4:
            printf("\nRemover elemento do inicio da lista");
            removerInicio(&lista);
            break;
        case 5:
            printf("\nRemover elemento do fim da lista");
            removerFim(&lista);
            break;
        case 6:
            printf("\nDigite o elemento que deseja inserir em determinada posição:");
            scanf("%d", &aux);
            determinadaPosicao(&lista, aux);
            break;
        case 7:
            printf("\nExibindo lista:");
            exibirLista(&lista);
            break;
        case 8:
            printf("\nDestruindo lista...");
            destruirLista(&lista);
            break;
        case 0:
            printf("\nEncerrando programa.");
            break;
        default:
            printf("\nOpção inválida!");
        }
    } while (op != 0);
}
