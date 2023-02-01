public class insertionSort{

    public static void funcSort(int x[]){
        int aux, i, j;

        for(i=1; i < x.length;i++){
            aux = x[i];
            for(j=i; (j > 0) && (aux<x[j-1]); j--){
                x[j] = x[j-1];
            }
            x[j] = aux;
            }
        }
    public static void main(String[] args) {
        
        int x[] = {6,90,32,1,5,56};

        funcSort(x);

        for(int i = 0; i < x.length; i++){
            System.out.println(" " + x[i]);
        }
    }
}