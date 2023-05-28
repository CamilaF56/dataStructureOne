/*Código de árvore binária de busca - ABB*/
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    float dado;
    struct node *pai;
    struct node *filhoEsq;
    struct node *filhoDir;
} tipoNode;

typedef struct volta
{
    tipoNode *noOuPai;
    char tipoFilho;
    int encontrou; /*Se for 1 é porque a informação já existe na árvore*/
} tipoVolta;

tipoNode *achou; /*Variavel global*/

/*Função para criar uma estrutura de retorno*/
tipoVolta *criaVolta(tipoNode *no, char tF, int seAchou)
{
    tipoVolta *aux = (tipoVolta *)malloc(sizeof(tipoVolta));
    aux->noOuPai = no;
    aux->tipoFilho = tF;
    aux->encontrou = seAchou;
    return aux;
}

/*Função para criar um nó*/
tipoNode *criaNo(float n, tipoNode *noPai)
{
    tipoNode *novo;
    novo = (tipoNode *)malloc(sizeof(tipoNode));
    novo->dado = n;
    novo->filhoDir = NULL;
    novo->filhoEsq = NULL;
    novo->pai = noPai;
    return novo;
}

void exibeInOrdem(tipoNode *atual)
{
    if (atual != NULL)
    {
        exibeInOrdem(atual->filhoEsq);
        printf("  %8.2f", atual->dado);
        exibeInOrdem(atual->filhoDir);
    }
}

void metadeInOrdem(tipoNode *atual)
{
    if (atual != NULL)
    {
        metadeInOrdem(atual->filhoEsq);
        atual->dado = (atual->dado / 2);
        metadeInOrdem(atual->filhoDir);
    }
}

void buscaNo(tipoNode *atual, float n)
{
    if (atual != NULL)
    {
        if (atual->dado == n)
        {
            achou = atual;
            return;
        }
        buscaNo(atual->filhoEsq, n);
        buscaNo(atual->filhoDir, n);
    }
}

void exibePreOrdem(tipoNode *atual)
{
    if (atual != NULL)
    {
        printf("  %8.2f", atual->dado);
        exibePreOrdem(atual->filhoEsq);
        exibePreOrdem(atual->filhoDir);
    }
}

void exibePosOrdem(tipoNode *atual)
{
    if (atual != NULL)
    {
        exibePosOrdem(atual->filhoEsq);
        exibePosOrdem(atual->filhoDir);
        printf("  %8.2f", atual->dado);
    }
}

void excluirArv(tipoNode *raiz)
{
    if (raiz != NULL)
    {
        excluirArv(raiz->filhoEsq);
        excluirArv(raiz->filhoDir);
        free(raiz);
    }
}

char getPosNo(tipoNode *no)
{
    if (no->pai->filhoEsq == no)
        return 'e';
    else
        return 'd';
}

/*O retorno dessa função deve ser o endereço do filho que ocupou a posição do nó removido
para no caso da remoção da raiz a variável local ao programa principal poder ser atualizada*/
tipoNode *removeNo(tipoNode *no)
{
    if (no != NULL)
    {
        if (no->filhoEsq != NULL)
        { /*Tem filho esquerdo*/
            if (no->filhoDir != NULL)
            { /*Tem filho direito*/
                printf("\nErro! O nao pode ser removido por ter 2 filhos!\n");
                return NULL;
            }
            else
            { /*Situacao em que só tem filho esquerdo*/
                if (no->pai == NULL)
                { /*Se o né é a raiz*/
                    tipoNode *antigo = no;
                    no = no->filhoEsq;
                    no->pai = NULL;
                    free(antigo);
                    return no;
                }
                char posicao = getPosNo(no); /*Qual a posicao do nó em relção ao próprio pai*/
                if (posicao == 'e')
                    no->pai->filhoEsq = no->filhoEsq;
                else
                    no->pai->filhoDir = no->filhoEsq;
                no->filhoEsq->pai = no->pai;
                tipoNode *aux = no;
                free(no);
                return aux;
            }
        }
        else
        { /*Só tem filho da direita ou filho nenhum*/
            if (no->pai == NULL)
            {
                tipoNode *antigo = no;
                no = no->filhoDir;
                if (no != NULL)
                    no->pai = NULL;
                free(antigo);
                return no;
            }
            else
            {
                char posicao = getPosNo(no);
                if (posicao == 'e')
                {
                    no->pai->filhoEsq = no->filhoDir;
                }
                else
                    no->pai->filhoDir = no->filhoDir;
                if (no->filhoDir != NULL)
                    no->filhoDir->pai = no->pai;
                tipoNode *aux = no->filhoDir;
                free(no);
                return aux;
            }
        }
    }
    return NULL;
}

tipoVolta *busque(tipoNode *raiz, float valor)
{
    if (raiz == NULL)
    {
        tipoVolta *retorno = criaVolta(NULL, 'p', 0);
        return retorno;
    }
    else
    {
        tipoNode *aux = raiz;
        while (valor != aux->dado)
        {
            if (valor < aux->dado)
            { /*É menor que o nó visitado*/
                if (aux->filhoEsq == NULL)
                { /*É menor que o nó que não tem filho esquerdo. Retorna ele como pai*/
                    tipoVolta *retorno = criaVolta(aux, 'e', 0);
                    return retorno;
                }
                else
                    aux = aux->filhoEsq;
            }
            else
            { /*É maior que o nó visitado*/
                if (aux->filhoDir == NULL)
                { /*Não tem filho na direita. Coloca aqui*/
                    tipoVolta *retorno = criaVolta(aux, 'd', 0);
                    return retorno;
                }
                else
                    aux = aux->filhoDir;
            }
        }
        tipoVolta *retorno = criaVolta(aux, 'p', 1); /*Se chegou aqui é porque o no já existe na árvore. Retorno seu endereço*/
        return retorno;
    }
}

/*Função para inserção de um nó na árvore*/
tipoNode *insereNo(tipoNode *pai, float n, char tipoFilho)
{
    tipoNode *novo;
    if (pai == NULL) /*Quer inserir na raiz*/
        return criaNo(n, NULL);

    if (tipoFilho == 'e')
    {
        if (pai->filhoEsq != NULL)
        {
            printf("\nImpossivel inserir. No ja tem filho na esquerda");
            return NULL;
        }
        pai->filhoEsq = criaNo(n, pai);
        return pai->filhoEsq;
    }
    else
    {
        if (pai->filhoDir != NULL)
        {
            printf("\nImpossivel inserir. No ja tem filho na direita");
            return NULL;
        }
        pai->filhoDir = criaNo(n, pai);
        return pai->filhoDir;
    }
}

tipoNode *insereBusca(tipoNode *raiz, float valor)
{
    if (raiz == NULL)
        return insereNo(NULL, valor, 'p');
    tipoVolta *resposta = busque(raiz, valor);
    if (resposta->encontrou)
    {
        printf("\nInformacao ja existe na arvore.\n");
        return NULL;
    }
    return insereNo(resposta->noOuPai, valor, resposta->tipoFilho);
}

tipoNode *removeEmABB(tipoNode *raiz, float valor)
{
    tipoVolta *retorno = busque(raiz, valor);
    tipoNode *aux;
    if (retorno->encontrou)
    { /*Caso o no tenha sido encontrado na arvore*/
        if (retorno->noOuPai->filhoDir != NULL && retorno->noOuPai->filhoEsq != NULL)
        {
            /*O no a ser apagado tem dois filhos*/
            aux = retorno->noOuPai->filhoEsq; /*Estamos olhando para a subarvore esquerda*/
            while (aux->filhoDir != NULL)     /*Procurando o maior valor da subarvore esquerda*/
                aux = aux->filhoDir;
            retorno->noOuPai->dado = aux->dado; /*Copiando o maior valor da subarvore esquerda no lugar do nó removido*/
            if (aux->pai == retorno->noOuPai)
                retorno->noOuPai->filhoEsq = removeNo(aux);
            else
                aux->pai->filhoDir = removeNo(aux);
            return raiz; // Como tinha dois filhos o endereço da raiz não muda, muda apenas seu conteúdo
        }
        else
            return removeNo(retorno->noOuPai);
    }
    else
        printf("\nNo não encontrado na arvore.");
    return NULL;
}

void main()
{
    tipoNode *raiz = NULL, *resposta;
    int op;
    float valor, valorPai;
    char filhoEouD;

    do
    {
        printf("\n Escolha sua opcao");
        printf("\n 1 - Insere um no na arvore");
        printf("\n 2 - Exibe a arvore em ordem simetrica");
        printf("\n 3 - Exibe a arvore em pre ordem");
        printf("\n 4 - Exibe a arvore em pos ordem");
        printf("\n 5 - Mostra se um no existe na arvore");
        printf("\n 6 - Remove no (folha ou com um filho apenas)");
        printf("\n 7 - Insere em ABB");
        printf("\n 8 - Remove no de ABB");
        printf("\n 9 - Coloca valores pela metade");
        printf("\n 0 - Encerra o programa");
        printf("\nDigite sua opcao:");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            printf("\nDigite o dado que deseja incluir: ");
            scanf("%f", &valor);
            if (raiz == NULL) /*Esta sendo criado o primeiro valor da arvore*/
                if (raiz = insereNo(NULL, valor, 'r'))
                    printf("\nRaiz inserida com sucesso!");
                else
                    printf("\nRaiz nao inserida!");
            else
            {
                printf("\nDigite o pai do no:");
                scanf("%f", &valorPai);
                achou = NULL;
                buscaNo(raiz, valorPai);
                if (achou == NULL)
                    printf("\nPai nao encontrado. Insercao nao feita");
                else
                {
                    printf("\nDigite se o no sera filho da esquerda <e> ou da direita <d> : ");
                    fflush(stdin);
                    scanf("%c", &filhoEouD);
                    if (insereNo(achou, valor, filhoEouD))
                        printf("\nNo inserido com sucesso!");
                    else
                        printf("\nNo nao inserido!");
                }
            }
            break;
        case 2:
            printf("\nExibindo a arvore in-ordem:\n");
            exibeInOrdem(raiz);
            break;
        case 3:
            printf("\n\n\nExibindo a arvore pre-ordem\n:");
            exibePreOrdem(raiz);
            break;
        case 4:
            printf("\n\n\nExibindo a arvore pos-ordem\n");
            exibePosOrdem(raiz);
            break;
        case 5:
            printf("\nDigite que dado deseja procurar na arvore: ");
            scanf("%d", &valor);
            achou = NULL;
            buscaNo(raiz, valor);
            if (achou)
                printf("\nNo encontrado com sucesso");
            else
                printf("\nNo nao encontrado na arvore");
            break;
        case 6:
            printf("\nDigite o dado que deseja remover: ");
            scanf("%d", &valor);
            achou = NULL;
            buscaNo(raiz, valor);
            if (achou == NULL)
                printf("\n No nao encontrado.");
            else
            {
                if (achou == raiz)
                {
                    raiz = removeNo(achou);
                    printf("\nNo removido com sucesso!");
                }
                else if (removeNo(achou) != NULL)
                    printf("\nNo removido com sucesso!");
            }
            break;
        case 7:
            printf("\nDigite o dado que deseja incluir: ");
            scanf("%f", &valor);
            if (raiz == NULL)
                raiz = insereBusca(raiz, valor);
            else
            {
                if (insereBusca(raiz, valor))
                    printf("\nNo inserido com sucesso");
                else
                    printf("\nNo nao inserido");
            }
            break;
        case 8:
            printf("\nDigite o dado que deseja remover: ");
            scanf("%f", &valor);
            int eraRaiz = 0;
            if (valor == raiz->dado)
                eraRaiz = 1;
            tipoNode *retornado = removeEmABB(raiz, valor);
            if (eraRaiz)
                raiz = retornado;
            if (retornado || (!retornado && eraRaiz))
                printf("\nNo removido com sucesso!\n");
            else
                printf("\nNo nao removido.\n");
            break;
        case 9:
            printf("\nColocando valores da arvore pela metade");
            metadeInOrdem(raiz);
            break;
        case 0:
            printf("\nEncerrando programa...");
            excluirArv(raiz);
            raiz = NULL;
            break;
        default:
            printf("\nOpcao invalida! Escolha uma nova opcao: ");
        }
    } while (op != 0);
}
