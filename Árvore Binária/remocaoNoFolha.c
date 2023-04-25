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
