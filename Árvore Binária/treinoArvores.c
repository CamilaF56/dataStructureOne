#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    float dado;
    struct node *pai;
    struct node *dir;
    struct node *esq;
} tipoNode;

typedef struct volta // Struct que retorna valores
{
    tipoNode *paiOuFilho; // retorno de um ponteiro do tipoNode, que aponta para um nó da arvore que representa pai ou filho do nó atual. Usado para referenciar um nó em uma estrutura de dados, permitindo a manipulação do nó em questão e seus descendentes.
    char tipoFilho;       // retorno para saber se é filho da esquerda ou da direita
    int encontrou;        // indica se o nó espefifico foi encontrado na arvore, retornando 1 para sim e 0 pora não
} tipoVolta;

tipoNode* achou;

tipoNode *criaNo(float n, tipoNode *pai)
{
    tipoNode *novo = (tipoNode *)malloc(sizeof(tipoNode));
    if (novo == NULL)
    {
        return NULL;
    }
    novo->dado = n;
    novo->dir = NULL;
    novo->esq = NULL;
    novo->pai = pai;
    return novo;
}

tipoVolta *criaVolta(tipoNode *no, char tF, int seAchou)
{
    tipoVolta *aux = (tipoVolta *)malloc(sizeof(tipoVolta));
    if (aux == NULL)
    {
        return NULL;
    }
    aux->paiOuFilho = no;
    aux->tipoFilho = tF;
    aux->encontrou = seAchou;
    return aux;
}

void exibeInOrdem(tipoNode *root)
{
    if (root != NULL)
    {
        exibeInOrdem(root->esq);
        printf("%.2f ", root->dado);
        exibeInOrdem(root->dir);
    }
}

void exibePreOrdem(tipoNode *root)
{
    if (root != NULL)
    {
        printf("%.2f", root->dado);
        exibePreOrdem(root->esq);
        exibePreOrdem(root->dir);
    }
}

void exibePosOrdem(tipoNode *root)
{
    if (root != NULL)
    {
        exibePosOrdem(root->esq);
        exibePosOrdem(root->dir);
        printf("%.2f", root->dado);
    }
}

void metadeInOrdem(tipoNode *root)
{
    if (root != NULL)
    {
        metadeInOrdem(root->esq);
        printf("%.2f", root->dado / 2);
        metadeInOrdem(root->dir);
    }
}

tipoNode *busque(float n, tipoNode *root)
{
    if (root == NULL)
    {
        tipoVolta *retorno = criaVolta(NULL, 'p', 0);
        return retorno;
    }
    else
    {
        tipoNode *aux = root;
        while (root->dado != n)
        {
            if (n < aux->dado)
            { /*É menor que o nó visitado*/
                if (aux->esq == NULL)
                { /*É menor que o nó que não tem filho esquerdo. Retorna ele como pai*/
                    tipoVolta *retorno = criaVolta(aux, 'e', 0);
                    return retorno;
                }
                else
                    aux = aux->esq;
            }
            else
            {
                if (aux->dir == NULL)
                { /*É menor que o nó que não tem filho esquerdo. Retorna ele como pai*/
                    tipoVolta *retorno = criaVolta(aux, 'd', 0);
                    return retorno;
                }
                else
                    aux = aux->dir;
            }
        }
        tipoVolta *retorno = criaVolta(aux, 'p', 1); /*Se chegou aqui é porque o no já existe na árvore. Retorno seu endereço*/
        return retorno;
    }
}

void excluirArv(tipoNode* root){
    if(root != NULL){
        excluirArv(root->dir);
        excluirArv(root->esq);
        free(root);
    }
}

int temFilhoEsq(tipoNode* root){ // arvore Somente Binaria
    if(root!=NULL){
        if(root->esq!=NULL){
            return 1;
        }
    }
    return 0;
}

int temFilhoDir(tipoNode* root){ // Arvore somente Binaria
    if(root!=NULL){
        if(root->dir!=NULL){
            return 1;
        }
    }
    return 0;
}

tipoNode* buscaInOrdem(tipoNode* root, int n){ // Arvore Somente Binaria
    buscaInOrdem(root->esq, n); // primeiro o filho da esquerda
    if(root!=NULL){ // procurando
        if(root->dado==n){
            achou = root;
            return;        
        }
    }
    buscaInOrdem(root->dir, n);// depois filho da direita
}