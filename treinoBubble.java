public class treinoBubble {
    public static void main(String[] args) {
        int vetor[] = {3, 6, 2, 1, 8, 4};
        int aux;
        boolean controle;

        for(int i = 0; i < vetor.length; i++){
            controle = true;
            for(int j = 0; j < (vetor.length-1); j++){
                if(vetor[j] > vetor[j+1]){ //SWAP
                    aux = vetor[j]; 
                    vetor[j] = vetor[j+1];
                    vetor[j+1] = aux;
                    controle = false; //se não estiver ordenado recebe false e não entra no if abaixo
                }
            }
            if(controle){
                break; // quebrar pois ja está ordenado
            }
        }

        for(int i = 0; i < vetor.length; i++){
            System.out.println(vetor[i] + " ");
        }
    }
}
