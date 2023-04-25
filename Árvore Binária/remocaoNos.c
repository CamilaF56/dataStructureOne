#include <stdlib.h>
#include <stdio.h>

typedef struct no
{
    int dado;

    struct no *pai;
    struct no *filhoEsq;
    struct no *filhoDir;
} tipoNode;

tipoNode *removeNoFolhas(tipoNode *root, int n) // Verifica se a árvore está vazia ou se chegou ao fim
{
    if (root == NULL)
    {
        printf("Valor não encontrado\n");
        return NULL;
    }
    else
    {
        if (root->dado == n) // Verificação de valor
        {
            if (root->filhoEsq == NULL && root->filhoDir == NULL)
            {
                root->dado = NULL;
                return NULL;
            }
        }
        else if (n < root->dado) // decide se vai para a esquerda ou para a direita
        {
            root->filhoEsq = removeNo(root->filhoEsq, n);
        }
        else
        {
            root->filhoDir = removeNo(root->filhoDir, n);
        }
        return root;
    }
}

/* função auxiliar para encontrar o menor valor à direita do nó */
tipoNode *menorDir(tipoNode *root)
{
    tipoNode *aux = root->filhoDir; // começa pela fruta da direita
    while (aux->filhoEsq != NULL)
    { // vai para a esquerda até chegar ao fim
        aux = aux->filhoEsq;
    }
    return aux; // retorna o ponteiro para a fruta com o menor valor
}

/* função auxiliar para encontrar o maior valor à esquerda do nó */
tipoNode *maiorEsq(tipoNode *root)
{
    tipoNode *aux = root->filhoEsq; // começa pela fruta da esquerda
    while (aux->filhoDir != NULL)
    { // vai para a direita até chegar ao fim
        aux = aux->filhoDir;
    }
    return aux; // retorna o ponteiro para a fruta com o maior valor
}

tipoNode *removeNo(tipoNode *root, int n) // Remoção com nós folhas e com filhos
{
    if (root == NULL)
    { // verifica se a árvore está vazia ou se chegou ao fim
        printf("Valor nao encontrado!\n");
        return NULL;
    }
    else
    {
        // procura o nó a remover
        if (root->dado == n)
        { // verifica se encontrou o nó
            // remove nós folhas (nós sem filhos)
            if (root->filhoEsq == NULL && root->filhoDir == NULL)
            {
                free(root); // libera o espaço do nó
                printf("Elemento removido com sucesso!\n");
                return NULL;
            }
            else
            {
                if (root->filhoEsq == NULL || root->filhoDir == NULL)
                { // NÓ COM UM FILHO
                    tipoNode *aux;
                    if (root->filhoEsq != NULL)
                    {                         // verifica se tem filho à esquerda
                        aux = root->filhoEsq; // guarda o ponteiro do filho à esquerda
                    }
                    else
                    {                         // senão, tem filho à direita
                        aux = root->filhoDir; // guarda o ponteiro do filho à direita
                    }
                    free(root); // libera o espaço do nó
                    printf("Elemento removido com sucesso!\n");
                    return aux; // retorna o ponteiro do filho que substituiu o nó removido
                }
                else
                {
                    // remove nós com dois filhos (nós com filho à esquerda e à direita)
                    tipoNode *aux = menorDir(root);                      // encontra o sucessor do nó na árvore (menor valor à direita)
                    root->dado = aux->dado;                              // troca os valores dos nós
                    root->filhoDir = remover(root->filhoDir, aux->dado); // chama a função recursivamente
                }
            }
        }
    }
}