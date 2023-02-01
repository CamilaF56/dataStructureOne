public class quickSort1 {
    // Algoritmo de recursividade
    // Dividir e conquistar
    // Escolha de pivô

    public static void QSort(int vet[], int inicio, int fim) {
        int i, j, x, aux;
        i = inicio;
        j = fim;
        x = vet[(i + j) / 2];
        System.out.println("Inicio = " + i + " fim = " + j + " meio = " + x);
        do {
            while (vet[i] < x) {
                i++;
            }
            while (vet[j] > x) {
                j--;
            }
            if (i <= j) {
                aux = vet[i];
                vet[i] = vet[j];
                vet[j] = aux;
                i++;
                j--;
            }
        } while (i <= j);
        if (inicio < j)
            QSort(vet, inicio, j);
        if (i < fim)
            QSort(vet, i, fim);
    }

    public static void main(String[] args) {
        int x[] = { 7, 9, 23, 45, 12, 89 };

        QSort(x, 0, x.length - 1);

        for (int i = 0; i < x.length; i++) {
            System.out.println(" " + x[i]);
        }
    }
}
