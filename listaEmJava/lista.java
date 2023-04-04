package listaEmJava;
import java.util.Locale;
import java.util.Scanner;

import listaEmJava.util.List;

public class lista {
    public static void main(String[] args) {

        Locale.setDefault(Locale.US);
        Scanner ler = new Scanner(System.in);
        int op;
        List list = new List();

        do{

            showMenu();
            op = ler.nextInt();

            switch(op){
                case 1:{
                    System.out.println("Digite um elemento: ");
                    Double value = ler.nextDouble();
                    list.add(value);
                    break;
                }
                case 2:{
                    System.out.println(list.toString());
                    break;
                }
                case 3:{
                    System.out.println("Programa encerrado");
                    break;
                }
                default:{
                    System.out.println("Opção inválida");
                }
            }

        }while(op!=3);

        ler.close();
    }

    public static void showMenu(){
        System.out.println("1 - Inserir elemento na lista");
        System.out.println("2 - Mostrar lista");
        System.out.println("3 - Encerrar programa");
    }
}
