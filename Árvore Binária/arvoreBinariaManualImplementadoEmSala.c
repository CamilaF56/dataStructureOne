#include <stdio.h>
#include <stdlib.h>

typedef struct no
{
    int dado;
    
    struct no *pai;
    struct no *filhoEsq;
    struct no *filhoDir;
} tipoNode;

tipoNode *achou;

tipoNode *criaNo(int n, tipoNode *pai)
{
    tipoNode *novo;
    novo = (tipoNode *)malloc(sizeof(tipoNode));
    if (novo == NULL)
        return NULL;
    novo->dado = n;
    novo->filhoDir = NULL;
    novo->filhoEsq = NULL;
    novo->pai = pai;
    return novo;
}

int temFilhoEsq(tipoNode *no)
{
    if (no->filhoEsq != NULL)
        return 1;
    else
        return 0;
}

int temFilhoDir(tipoNode *no)
{
    if (no->filhoDir != NULL)
        return 1;
    else
        return 0;
}

void exibeInOrdem(tipoNode *atual)
{
    if (atual != NULL)
    {
        exibeInOrdem(atual->filhoEsq);
        printf("%8d", atual->dado);
        exibeInOrdem(atual->filhoDir);
    }
}

void exibePosOrdem(tipoNode *atual)
{
    if (atual != NULL)
    {
        exibePosOrdem(atual->filhoEsq);
        exibePosOrdem(atual->filhoDir);
        printf("%8d", atual->dado);
    }
}

void exibePreOrdem(tipoNode *atual)
{
    if (atual != NULL)
    {
        printf("%8d", atual->dado);
        exibePreOrdem(atual->filhoEsq);
        exibePreOrdem(atual->filhoDir);
    }
}

tipoNode *buscaInOrdem(tipoNode *atual, int n)
{
    if (atual == NULL)
        return NULL;
    buscaInOrdem(atual->filhoEsq, n);
    if (achou != NULL)
        return achou;
    if (atual->dado == n)
    {
        achou = atual;
        return atual;
    }
    buscaInOrdem(atual->filhoDir, n);
    return achou;
}

int main()
{
    int num;
    tipoNode *novoNo;

    // Criando a raiz
    printf("\nDigite um numero inteiro PARA RAIZ: ");
    scanf("%d", &num);
    novoNo = criaNo(num, NULL);
    if (novoNo != NULL)
        printf("\nNo(raiz) criado com sucesso: dado = %d", novoNo->dado);

    // Colocando manualmente um nó como filho da esquerda
    printf("\n\nDigite outro numero inteiro PARA O FILHO DA ESQUERDA: ");
    scanf("%d", &num);
    if (!temFilhoEsq(novoNo))
        novoNo->filhoEsq = criaNo(num, novoNo);

    // Colocando manualmente um nó como filho da direita
    printf("\nDigite outro numero inteiro PARA O FILHO DA DIREITA: ");
    scanf("%d", &num);    
    if (!temFilhoDir(novoNo))
        novoNo->filhoDir = criaNo(num, novoNo);

    //Exibições
    printf("\nExibicao da arvore pre-ordem: \n");
    exibePreOrdem(novoNo);
    printf("\n\nExibicao da arvore in ordem:\n");
    exibeInOrdem(novoNo);
    printf("\nExibicao da arvore pos-ordem: \n");
    exibePosOrdem(novoNo);
}





