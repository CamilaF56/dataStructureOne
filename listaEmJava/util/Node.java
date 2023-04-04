package listaEmJava.util;

public class Node {
    private Double value;
    private Node next; // ponteiro para o proximo nó

    // gerando getters e setters
    public Double getValue() {
        return value;
    }
    public void setValue(Double value) {
        this.value = value;
    }
    public Node getNext() {
        return next;
    }
    public void setNext(Node next) {
        this.next = next;
    }


}


