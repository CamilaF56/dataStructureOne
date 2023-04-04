import java.util.Scanner;

class listaSequencial {

    static Scanner ler = new Scanner(System.in);

    static int quantElem = 0;
    static int maximo = 30;

    /*
     * Função que cria uma lista vazia com 30 elementos e retorna um ponteiro para a
     * lista criada
     */
    public static int[] criaLista() {
        int[] vetor = new int[maximo];
        return vetor;
    }

    /* Função que faz inserção não ordenada no vetor */
    public static boolean insereNaoOrd(int vetor[]) {
        if (quantElem < maximo) {
            System.out.print("\nDigite um número inteiro: ");
            vetor[quantElem++] = ler.nextInt();
            return true;
        } else {
            return false;
        }
    }

    /* Função que faz pesquisa sequencial */
    public static int pesqSeq(int vetor[], int elemento) {
        for (int x = 0; x < quantElem; x++)
            if (elemento == vetor[x])
                return x;
        return -1;
    }

    /* Função que exibe os elementos do vetor */
    public static void mostraVetor(int vetor[]) {
        System.out.println("\nConteudo do vetor:");
        for (int x = 0; x < quantElem; x++)
            System.out.printf("%5d", vetor[x]);
    }

    public static void main(String[] args) {

        int lista[], aux, resp, op;
        lista = criaLista();

        do {
            System.out.println("\n\n\nEscolha uma opcao\n1 - Inserção nao ordenada\n2 - Pesquisa sequencial");
            System.out.println("\n8 - Exibir lista \n0 - Sair do programa");
            System.out.println("\nDigite sua opcao: ");
            op = ler.nextInt();

            switch (op) {
                case 1:
                    if (!insereNaoOrd(lista))
                        System.out.println("\nLista cheia. Insercao nao realizada.");
                    else
                        System.out.println("\nElemento inserido com sucesso");
                    break;

                case 2:
                    System.out.println("\nDigite o elemento que deseja procurar:");
                    aux = ler.nextInt();
                    resp = pesqSeq(lista, aux);
                    if (resp == -1)
                        System.out.println("\nElemento nao encontrado");
                    else
                        System.out.printf("\nElemento encontrado na posicao %d do vetor.", resp);
                    break;

                case 8:
                    mostraVetor(lista);
                    break;

                case 0:
                    System.out.println("\nEncerrando programa.");
                    break;

                default:
                    System.out.println("\n\nOpcao indisponivel. Selecione uma nova opcao.");
            }
        } while (op != 0);

        ler.close();

    }
}