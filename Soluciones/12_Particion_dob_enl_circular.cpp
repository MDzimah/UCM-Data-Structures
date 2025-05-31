/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 */

 /*
  * MUY IMPORTANTE: Solo se corregirán los comentarios y el código
  * contenidos entre las etiquetas <answer> y </answer>.
  * Toda modificación fuera de esas etiquetas no será corregida.
  */

  /*@ <answer>
    Estudiante 1: Nombre y Apellidos
    Estudiante 2: Nombre y Apellidos

    Dad una explicación de la solución y justificad el coste del
    nuevo método.

   *@ </answer> */

   /*
    * Implementa las operaciones pedidas en el ejercicio al final de
    * este fichero, entre las etiquetas.
    */

#include <cassert>
#include <iostream>
#include <fstream>

class ListLinkedDouble {
private:
    struct Node {
        int value;
        Node* next;
        Node* prev;
    };

public:
    ListLinkedDouble() : num_elems(0) {
        head = new Node;
        head->next = head;
        head->prev = head;
    }

    ListLinkedDouble(const ListLinkedDouble& other) : ListLinkedDouble() {
        copy_nodes_from(other);
        num_elems = other.num_elems;
    }

    ~ListLinkedDouble() { delete_nodes(); }

    void push_front(const int& elem) {
        Node* new_node = new Node{ elem, head->next, head };
        head->next->prev = new_node;
        head->next = new_node;
        num_elems++;
    }

    void push_back(const int& elem) {
        Node* new_node = new Node{ elem, head, head->prev };
        head->prev->next = new_node;
        head->prev = new_node;
        num_elems++;
    }

    void pop_front() {
        assert(num_elems > 0);
        Node* target = head->next;
        head->next = target->next;
        target->next->prev = head;
        delete target;
        num_elems--;
    }

    void pop_back() {
        assert(num_elems > 0);
        Node* target = head->prev;
        target->prev->next = head;
        head->prev = target->prev;
        delete target;
        num_elems--;
    }

    int size() const { return num_elems; }

    bool empty() const { return num_elems == 0; };

    const int& front() const {
        assert(num_elems > 0);
        return head->next->value;
    }

    int& front() {
        assert(num_elems > 0);
        return head->next->value;
    }

    const int& back() const {
        assert(num_elems > 0);
        return head->prev->value;
    }

    int& back() {
        assert(num_elems > 0);
        return head->prev->value;
    }

    const int& operator[](int index) const {
        assert(0 <= index && index < num_elems);
        Node* result_node = nth_node(index);
        return result_node->value;
    }

    int& operator[](int index) {
        assert(0 <= index && index < num_elems);
        Node* result_node = nth_node(index);
        return result_node->value;
    }

    ListLinkedDouble& operator=(const ListLinkedDouble& other) {
        if (this != &other) {
            delete_nodes();
            head = new Node;
            head->next = head->prev = head;
            copy_nodes_from(other);
            num_elems = other.num_elems;
        }
        return *this;
    }

    void display(std::ostream& out) const;

    void display() const {
        display(std::cout);
    }

    void display_reverse(std::ostream& out) const;

    void display_reverse() const {
        display_reverse(std::cout);
    }

    // Nuevo método. Debe implementarse abajo
    void partition(int pivot);

private:
    Node* head;
    int num_elems;

    Node* nth_node(int n) const;
    void delete_nodes();
    void copy_nodes_from(const ListLinkedDouble& other);
    void detach(Node* node);
    void attach(Node* node, Node* position);

};

ListLinkedDouble::Node* ListLinkedDouble::nth_node(int n) const {
    int current_index = 0;
    Node* current = head->next;

    while (current_index < n && current != head) {
        current_index++;
        current = current->next;
    }

    return current;
}

void ListLinkedDouble::delete_nodes() {
    Node* current = head->next;
    while (current != head) {
        Node* target = current;
        current = current->next;
        delete target;
    }

    delete head;
}

void ListLinkedDouble::copy_nodes_from(const ListLinkedDouble& other) {
    Node* current_other = other.head->next;
    Node* last = head;

    while (current_other != other.head) {
        Node* new_node = new Node{ current_other->value, head, last };
        last->next = new_node;
        last = new_node;
        current_other = current_other->next;
    }
    head->prev = last;
}

void ListLinkedDouble::display(std::ostream& out) const {
    out << "[";
    if (head->next != head) {
        out << head->next->value;
        Node* current = head->next->next;
        while (current != head) {
            out << ", " << current->value;
            current = current->next;
        }
    }
    out << "]";
}

void ListLinkedDouble::display_reverse(std::ostream& out) const {
    out << "[";
    if (head->prev != head) {
        out << head->prev->value;
        Node* current = head->prev->prev;
        while (current != head) {
            out << ", " << current->value;
            current = current->prev;
        }
    }
    out << "]";
}

std::ostream& operator<<(std::ostream& out, const ListLinkedDouble& l) {
    l.display(out);
    return out;
}

// ----------------------------------------------------------------
// ¡No modificar nada importante por encima de esta línea!

// Implementa a continuación los métodos pedidos.
//@ <answer>

void ListLinkedDouble::detach(Node* node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
    node->next = node;
    node->prev = node;
    --this->num_elems;
}

void ListLinkedDouble::attach(Node* node, Node* position) {
    position->prev->next = node;
    node->prev = position->prev;
    node->next = position;
    position->prev = node;
    ++this->num_elems;
}


void ListLinkedDouble::partition(int pivot) {
    //O(num_elems)
   
    Node* curr = this->head->next;
    Node* last_L_or_eq = this->head, *last_G = this->head;
   
    while (curr != this->head) {
        Node* next = curr->next;
        if (curr->value <= pivot) {  
            this->detach(curr);
            this->attach(curr, last_L_or_eq->next);
            last_L_or_eq = curr;
        }
        else {
            if (last_G != head) { 
                this->detach(curr);
                this->attach(curr, last_G->next);
            }
            last_G = curr;
        }
        curr = next;
    }

}

//@ </answer>
// ¡No modificar nada debajo de esta línea!
// ----------------------------------------------------------------

using namespace std;

ListLinkedDouble leerLista() {
    ListLinkedDouble lista;
    int num;
    std::cin >> num;
    while (num != 0) {
        lista.push_back(num);
        std::cin >> num;
    }
    return lista;
}

void resuelveCaso() {
    auto lista = leerLista();
    int pivot;
    cin >> pivot;

    lista.partition(pivot);

    cout << lista << '\n';

    lista.display_reverse(); cout << '\n';
}

int main() {
    int num_casos;
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    cin >> num_casos;

    while (num_casos > 0) {
        resuelveCaso();
        num_casos--;
    }

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    // Descomentar si se necesita
    // system("PAUSE");
#endif

    return 0;
}


