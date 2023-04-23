public class mergeSort {

    public static void mSort(int x[], int xTemp[], int esq, int dir) {
        if (esq < dir) {
            int medio = (esq + dir) / 2;
            mSort(x, xTemp, esq, medio);
            mSort(x, xTemp, medio + 1, dir);
            mesclar(x, xTemp, esq, medio + 1, dir);
        }
    }

    public static void mesclar(int x[], int xAux[], int posEsq, int posDir, int posFim) {
        int finIzq = posDir - 1;
        int posAux = posEsq;
        int numElements = (posFim - posEsq) + 1;
        while (posEsq <= finIzq && posDir <= posFim) {
            if (x[posEsq] < x[posDir])
                xAux[posAux++] = x[posEsq++];
            else
                xAux[posAux++] = x[posDir++];
        }

        while (posEsq <= finIzq) {
            xAux[posAux++] = x[posEsq++];
        }

        while (posDir <= posFim) {
            xAux[posAux++] = x[posDir++];
        }

        for (int i = 0; i < numElements; i++, posFim--) {
            x[posFim] = xAux[posFim];
        }

    }

    public static void main(String[] args) {
        int x[] = { 7,78,32,21,67};

        int xTemp[] = new int[x.length];

        mSort(x, xTemp, 0, x.length - 1);

        for (int i = 0; i < x.length; i++) {
            System.out.println(" " + x[i]);
        }
    }
}
