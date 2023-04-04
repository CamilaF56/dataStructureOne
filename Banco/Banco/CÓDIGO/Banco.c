#include <stdio.h>
#include <string.h>
#include "gconio.h"

// Camila Fontes Santos
// Laila Esterfane dos Santos Valença
// Marlysson Silva Dantas
// Miguel Ferreira França
// Vinícius Lima Santos

typedef struct no
{
    int senha, prioridade, tempo;
    char nome[30];
    struct no *proxNo, *antNo;
} tipoNo;

typedef struct listaGerenciada
{
    tipoNo *fim, *inicio;
    int quant;
} tipoLista;

void inicializa(tipoLista *listaEnc)
{
    listaEnc->fim = NULL;
    listaEnc->inicio = NULL;
    listaEnc->quant = 0;
}

int insereListaVazia(tipoLista *listaEnc, int tipocliente, char cliente[30], int prioridade, int horarioMin)
{
    tipoNo *novoNo;
    novoNo = (tipoNo *)malloc(sizeof(tipoNo));
    if (novoNo == NULL)
        return 0;

    strcpy(novoNo->nome, cliente);
    novoNo->senha = tipocliente;
    novoNo->prioridade = prioridade;
    novoNo->tempo = horarioMin;

    novoNo->proxNo = NULL;
    novoNo->antNo = NULL;
    listaEnc->inicio = novoNo;
    listaEnc->fim = novoNo;
    listaEnc->quant++;
    return 1;
}

int insereNaFrente(tipoLista *listaEnc, int tipocliente, char cliente[30], int prioridade, int horarioMin)
{
    tipoNo *novoNo;
    if (listaEnc->inicio == NULL)
    {
        return insereListaVazia(listaEnc, tipocliente, cliente, prioridade, horarioMin);
    }
    else
    {
        novoNo = (tipoNo *)malloc(sizeof(tipoNo));
        if (novoNo == NULL)
        {
            return 0;
        }
        strcpy(novoNo->nome, cliente);
        novoNo->senha = tipocliente;
        novoNo->prioridade = prioridade;
        novoNo->tempo = horarioMin;

        novoNo->antNo = NULL;
        novoNo->proxNo = listaEnc->inicio;
        listaEnc->inicio->antNo = novoNo;
        listaEnc->inicio = novoNo;
        listaEnc->quant++;
        return 1;
    }
}

int insereNoFim(tipoLista *listaEnc, int tipocliente, char cliente[30], int prioridade, int horarioMin)
{
    tipoNo *novoNo;
    if (listaEnc->inicio == NULL)
    {
        return insereListaVazia(listaEnc, tipocliente, cliente, prioridade, horarioMin);
    }
    else
    {
        novoNo = (tipoNo *)malloc(sizeof(tipoNo));
        if (novoNo == NULL)
        {
            return 0;
        }
        strcpy(novoNo->nome, cliente); // novas atribuições
        novoNo->senha = tipocliente;
        novoNo->prioridade = prioridade;
        novoNo->tempo = horarioMin;

        novoNo->proxNo = NULL;
        novoNo->antNo = listaEnc->fim;
        listaEnc->fim->proxNo = novoNo;
        listaEnc->fim = novoNo;
        listaEnc->quant++;
        return 1;
    }
}

int insereOrdenado(tipoLista *listaEnc, int tipocliente, char cliente[30], int prioridade, int horarioMin)
{
    tipoNo *novoNo, *aux;
    novoNo = (tipoNo *)malloc(sizeof(tipoNo));

    if (novoNo == NULL)
        return 0;

    strcpy(novoNo->nome, cliente);
    novoNo->senha = tipocliente;
    novoNo->prioridade = prioridade;
    novoNo->tempo = horarioMin;

    if (listaEnc->quant == 0 || listaEnc->inicio->tempo <= horarioMin)
    {
        return insereNaFrente(listaEnc, tipocliente, cliente, prioridade, horarioMin);
    }
    else
    {
        aux = listaEnc->inicio;

        while (aux->proxNo != NULL && aux->proxNo->tempo > horarioMin)
        {
            aux = aux->proxNo;
        }
        if (aux->proxNo != NULL)
        {

            novoNo->proxNo = aux->proxNo;
            novoNo->antNo = aux;
            aux->proxNo->antNo = novoNo;
            aux->proxNo = novoNo;
        }
        else
        {
            aux->proxNo = novoNo;
            novoNo->antNo = aux;
            novoNo->proxNo = NULL;
            listaEnc->fim = novoNo;
        }
    }

    listaEnc->quant++;
    return 1;
}

int removerFim(tipoLista *listaEnc)
{
    if (listaEnc->inicio == NULL)
    {
        return 0;
    }
    else
    {
        tipoNo *novoNo = listaEnc;
        if (listaEnc->quant == 1)
        {
            free(listaEnc->inicio);
            listaEnc->quant = 0;
            listaEnc->inicio = NULL;
            listaEnc->fim = NULL;
            return 1;
        }
        // printf("\n%s\n", listaEnc->fim->nome);
        novoNo = listaEnc->fim->antNo;
        free(listaEnc->fim);
        listaEnc->fim = novoNo;
        novoNo->proxNo = NULL;
        listaEnc->quant--;
        return 1;
    }
}

int removerInicio(tipoLista *listaEnc)
{
    if (listaEnc->inicio == NULL)
    {
        return 0;
    }
    else
    {
        tipoNo *novoNo = listaEnc;
        if (listaEnc->quant == 1)
        {
            free(listaEnc->inicio);
            listaEnc->quant = 0;
            listaEnc->inicio = NULL;
            listaEnc->fim = NULL;
            return 1;
        }
        // printf("\n%s\n", listaEnc->fim->nome);
        novoNo = listaEnc->inicio->proxNo;
        free(listaEnc->inicio);
        listaEnc->inicio = novoNo;
        novoNo->antNo = NULL;
        listaEnc->quant--;

        return 1;
    }
}

int atendeCliente(tipoLista *listaEnc, int *contaPrioridade)
{
    if (listaEnc->inicio == NULL)
        return 0;
    tipoNo *atual = listaEnc->fim;

    if (*contaPrioridade < 3) // atenderá 3 com prioridade e alterna para sem prioridade
    {
        if (listaEnc->fim->prioridade == 1)
        {
            *contaPrioridade = *contaPrioridade + 1;
            return removerFim(listaEnc);
        }
        else
        {
            while (atual != NULL && atual->prioridade != 1)
            {
                atual = atual->antNo;
            }
            if (atual == NULL)
            {
                *contaPrioridade = 3;
            }
            else if (listaEnc->inicio == atual)
            {
                *contaPrioridade = *contaPrioridade + 1;
                return removerInicio(listaEnc);
            }
            else
            {
                atual->antNo->proxNo = atual->proxNo;
                atual->proxNo->antNo = atual->antNo;
                free(atual);
                listaEnc->quant--;
                *contaPrioridade = *contaPrioridade + 1;

                return 1;
            }
        }
    }
    if (*contaPrioridade == 3)
    {
        if (listaEnc->fim->prioridade == 0)
        {
            *contaPrioridade = 0;

            return removerFim(listaEnc);
        }
        else
        {
            while (atual != NULL && atual->prioridade != 0)
            {
                atual = atual->antNo;
            }
            if (atual == NULL)
                *contaPrioridade = *contaPrioridade - 1;
            else if (listaEnc->inicio == atual)
            {
                *contaPrioridade = 0;
                return removerInicio(listaEnc);
            }
            else
            {
                atual->antNo->proxNo = atual->proxNo;
                atual->proxNo->antNo = atual->antNo;
                free(atual);
                listaEnc->quant--;
                *contaPrioridade = 0;
            }
        }
    }
}

tipoLista unificar(tipoLista *lista1, tipoLista *lista2)
{
    tipoLista *listaResultante = (tipoLista *)malloc(sizeof(tipoLista));
    listaResultante->inicio = NULL;
    listaResultante->fim = NULL;
    listaResultante->quant = 0;

    tipoNo *aux1 = lista1->inicio;
    tipoNo *aux2 = lista2->inicio;

    while (aux1 != NULL && aux2 != NULL)
    {
        if (aux1->senha <= aux2->senha)
        {
            insereOrdenado(listaResultante, aux1->senha, aux1->nome, aux1->prioridade, aux1->tempo);
            aux1 = aux1->proxNo;
        }
        else
        {
            insereOrdenado(listaResultante, aux2->senha, aux2->nome, aux2->prioridade, aux2->tempo);
            aux2 = aux2->proxNo;
        }
    }

    while (aux1 != NULL)
    {
        insereOrdenado(listaResultante, aux1->senha, aux1->nome, aux1->prioridade, aux1->tempo);
        aux1 = aux1->proxNo;
    }

    while (aux2 != NULL)
    {
        insereOrdenado(listaResultante, aux2->senha, aux2->nome, aux2->prioridade, aux2->tempo);
        aux2 = aux2->proxNo;
    }

    exibeLista(listaResultante);
    return *listaResultante;
}

void previsaoAtendimento(tipoLista *listaEnc)
{
    int tempoCliente = 0;

    tipoNo *atual; /*Variável que será usada para percorrer a fila*/
    atual = listaEnc->fim;
    printf("------------Previsao em minutos------------\n");
    printf("O caixa esta atendendo %s", atual->nome);
    atual = atual->antNo;
    tempoCliente += 5;

    while (atual != NULL)
    {

        printf("Em %d minutos o caixa vai atender %s", tempoCliente, atual->nome);
        atual = atual->antNo;
        tempoCliente += 5;
    }
    printf("------------------------------------------\n ");
}

void exibeLista(tipoLista *listaEnc)
{
    tipoNo *atual; /*Variável que será usada para percorrer a fila*/
    atual = listaEnc->inicio;
    // printf("--------Dados do cliente--------\n");
    while (atual != NULL)
    {

        printf("\n--------Dados do cliente--------\n");

        printf("Nome: %s", atual->nome);
        if (atual->prioridade)
            printf("Tem prioridade\n");
        else
            printf("Sem prioridade\n");
        // printf("Prioridade: %d\n", atual->prioridade);

        if (atual->senha)
            printf("Pessoa juridica\n");
        else
            printf("Pessoa fisica\n");
        // printf("Tipo de cliente: %d\n", atual->senha);
        printf("Tempo total: %d minutos\n", atual->tempo);

        atual = atual->proxNo;
    }
    printf("-------------------------------\n ");
}

int buscaDado(tipoLista *listaEnc, int *procurado)
{
    tipoNo *atual;
    int cont = 1;
    atual = listaEnc->inicio;
    while (atual != NULL)
    {
        if (atual->senha == procurado)
            return cont;
        atual = atual->proxNo;
        cont++;
    }
    return 0;
}

void main()
{
    tipoLista fisica, juridica, FilasUnificadas;
    int op, tipocliente, prioridade, hora, min, escolheLista, contPrioriFIS = 0, contPrioriJUR = 0, contPrioriUNI = 0;
    char nomecliente[30];
    boolean testaUnificacao = 0;

    inicializa(&fisica);
    inicializa(&juridica);
    do
    {
        printf("\n-=-=-=-=-=-=-=-Menu-=-=-=-=-=-=-=-");
        printf("\n1 - Insere uma fila vazia");
        printf("\n2 - Insere na fila (ja ordenado)");
        printf("\n3 - Exibe fila detalhada");
        printf("\n4 - Atender cliente");
        printf("\n5 - Fechar um caixa (unifica as filas)");
        printf("\n6 - Exibe tempo do cliente para ser atendido");
        printf("\n0 - Encerrar programa");
        printf("\nDigite sua opcao: ");
        scanf("%d", &op);
        switch (op)
        {
        case 1: // printf("\n1 - Insere uma fila vazia");
            do
            {
                printf("\nDigite a senha (0 - Fisica|| 1 - Juridica): ");
                scanf("%d", &tipocliente);
            } while (tipocliente != 1 && tipocliente != 0);
            do
            {
                printf("\nDigite a prioridade (0 - Sem prioridade || 1 - Com prioridade): ");
                scanf("%d", &prioridade);
            } while (prioridade != 0 && prioridade != 1);
            fflush(stdin);
            printf("\nDigite o nome do cliente: ");
            fgets(nomecliente, 30, stdin);
            do
            {
                printf("\nDigite o horario de chegada\nA hora (FORMATO 24H): ");
                scanf("%d", &hora);
                printf("\nOs minutos(0-59): ");
                scanf("%d", &min);
            } while (!((hora <= 23 && hora >= 0) && (min >= 0 && min <= 59)));
            // clrscr(); //Limpa a tela para ter uma melhor visualização

            if (tipocliente == 0)
                if (insereListaVazia(&fisica, tipocliente, nomecliente, prioridade, (hora * 60) + min))
                    printf("\n[Dado inserido com sucesso]");
                else
                    printf("\n[Insercao nao efetuada]");
            else
            {
                if (insereListaVazia(&juridica, tipocliente, nomecliente, prioridade, (hora * 60) + min))
                    printf("\n[Dado inserido com sucesso]");
                else
                    printf("\n[Insercao nao efetuada]");
            }
            break;
        case 2: // Insere na fila (ja ordenado)
            do
            {
                printf("\nDigite a senha (0 - Fisica|| 1 - Juridica): ");
                scanf("%d", &tipocliente);
            } while (tipocliente != 1 && tipocliente != 0);
            do
            {
                printf("\nDigite a prioridade (0 - Sem prioridade || 1 - Com prioridade): ");
                scanf("%d", &prioridade);
            } while (prioridade != 0 && prioridade != 1);
            fflush(stdin);
            printf("\nDigite o nome do cliente: ");
            fgets(nomecliente, 30, stdin);
            do
            {
                printf("\nDigite o horario de chegada\nA hora (FORMATO 24H): ");
                scanf("%d", &hora);
                printf("\nOs minutos(0-59): ");
                scanf("%d", &min);
            } while (!((hora <= 23 && hora >= 0) && (min >= 0 && min <= 59)));
            if (!testaUnificacao)
            {
                if (tipocliente == 0)
                    if (insereOrdenado(&fisica, tipocliente, nomecliente, prioridade, (hora * 60) + min))
                        printf("\n[Dado inserido com sucesso]");
                    else
                        printf("\n[Insercao nao efetuada]");
                else
                {
                    if (insereOrdenado(&juridica, tipocliente, nomecliente, prioridade, (hora * 60) + min))
                        printf("\n[Dado inserido com sucesso]");
                    else
                        printf("\n[Insercao nao efetuada]");
                }
            }
            if (testaUnificacao)
            {
                if (insereOrdenado(&FilasUnificadas, tipocliente, nomecliente, prioridade, (hora * 60) + min))
                    printf("\n[Dado inserido com sucesso]");
                else
                    printf("\n[Insercao nao efetuada]");
            }
            break;
        case 3: // 3 - Exibe fila
            if (!testaUnificacao)
            {
                do
                {
                    printf("Qual fila deseja visualizar?(0 - Fisica || 1 - Juridica): ");
                    scanf("%d", &escolheLista);
                } while (escolheLista != 0 && escolheLista != 1);
                if (escolheLista == 0)
                    exibeLista(&fisica);
                else
                    exibeLista(&juridica);
            }
            if (testaUnificacao)
            {
                exibeLista(&FilasUnificadas);
            }
            break;
        case 4: // 4 - Atender cliente

            if (!testaUnificacao)
            {
                do
                {
                    printf("Qual fila vai atender o cliente? (0 - Fisica || 1 - Juridica): ");
                    scanf("%d", &escolheLista);
                } while (escolheLista != 0 && escolheLista != 1);

                if (escolheLista == 0)
                    if (atendeCliente(&fisica, &contPrioriFIS))
                        printf("\nCliente da fila fisica atendido (a)");
                    else
                        printf("\nNão foi possível atender o cliente da fila fisica");
                else
                {
                    if (atendeCliente(&juridica, &contPrioriJUR))
                        printf("\nCliente da fila fisica atendido (a)");
                    else
                        printf("\nNao foi possível atender o cliente da fila fisica");
                }
            }
            if (testaUnificacao)
            {
                if (atendeCliente(&FilasUnificadas, &contPrioriUNI))
                    printf("\nCliente da fila fisica atendido (a)");
                else
                    printf("\nNao foi possível atender o cliente da fila fisica");
            }
            break;
        case 5: //  Fecha um caixa (unifica as filas)
            printf("-------Filas Unificadas-------");
            testaUnificacao = 1;
            FilasUnificadas = unificar(&fisica, &juridica);
            break;
        case 6: // Exibe tempo do cliente para ser atendido
            do
            {
                printf("Qual fila deseja exibir? (0 - Fisica || 1 - Juridica): ");
                scanf("%d", &escolheLista);
            } while (escolheLista != 0 && escolheLista != 1);

            if (!testaUnificacao)
            {
                tipoLista *previaLista;
                if (tipocliente == 0)
                {
                    *previaLista = fisica;
                    previsaoAtendimento(previaLista);
                }
                else
                {
                    *previaLista = juridica;
                    previsaoAtendimento(previaLista);
                }
            }
            if (testaUnificacao)
            {
                previsaoAtendimento(&FilasUnificadas);
            }

            break;
        case 0:
            printf("\nEncerrando programa...");
            break;
        default:
            printf("\nOpcao invalida. Escolha outra opcao.");
            break;
        }
    } while (op != 0);
}
