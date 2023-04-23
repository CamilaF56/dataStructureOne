public class quickSort2 {
    // Algoritmo de recursividade
    // Dividir e conquistar
    // Escolha de pivô

    public static int particao(int vet[], int inicio, int fim) {
        int i, j, x, aux;
        i = inicio - 1;
        j = fim + 1;
        int div = (int) ((i + j) / 2);
        x = vet[div];
        System.out.println("Inicio = " + i + " fim = " + j + " meio = " + x);

        while (true) {
            do {
                i++;
            } while (vet[i] < x);

            do {
                j--;
            } while (vet[j] > x);

            if (i >= j) {
                return j;
            }

            aux = vet[i];
            vet[i] = vet[j];
            vet[j] = aux;
        }
    }

    public static void QSort(int vet[], int inicio, int fim) {
        if (inicio < fim) {
            int p = particao(vet, inicio, fim);
            QSort(vet, fim, p);
            QSort(vet, p + 1, fim);
        }
    }

    public static void main(String[] args) {
        int x[] = { 7, 9, 23, 45, 12, 89 };

        QSort(x, 0, x.length - 1);

        for (int i = 0; i < x.length; i++) {
            System.out.println(" " + x[i]);
        }
    }
}
