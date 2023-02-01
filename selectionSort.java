public class selectionSort {

        public static void funcSort(int x[]){
            int aux, iMenor;
            for(int i=0; i < x.length-1; i++){ //esq
                iMenor = i;
                for(int j=i+1; j < x.length; j++){ //dir
                    if(x[j] < x[iMenor]){
                        iMenor = j;
                    }
                }
                if(iMenor != i){
                    aux = x[iMenor]; 
                    x[iMenor] = x[i];
                    x[i] = aux;
                }
            }
        }
    public static void main(String[] args) {     
            int x[] = {5,9,2,45,32,23};
            
            funcSort(x);

            for(int i=0; i<x.length;i++){
                System.out.println(" "+x[i]);
            }
        }
    
}
