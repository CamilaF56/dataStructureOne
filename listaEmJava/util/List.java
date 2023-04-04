package listaEmJava.util;

public class List {

    private Node head; // Primeiro nó da lista

    public void add(Double value) {
        Node node = new Node(); // Instanciando novo nó
        node.setValue(value);
        node.setNext(head); // cabeça anterior sendo ligada para o proximo nó
        head = node; // head sendo atualizado para o novo nó feito(atualizando nó principal com o
                     // novo valor inserido)
    }

    @Override
    public String toString() {
        StringBuffer sb = new StringBuffer();
        sb.append("[");

        Node p = head;
        while (p != null) {
            sb.append(p.getValue() + " ");
            p = p.getNext();
        }

        sb.append("]");
        return sb.toString();
    }

}
