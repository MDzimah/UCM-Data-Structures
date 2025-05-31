/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 */

 /*
  * MUY IMPORTANTE: Para realizar este ejercicio solo podéis
  * modificar el código contenido entre las etiquetas <answer>
  * y </answer>. Toda modificación fuera de esas etiquetas está
  * prohibida, pues no será corregida.
  *
  * Tampoco está permitido modificar las líneas que contienen
  * las etiquetas <answer> y </answer>, obviamente :-)
  */

  //@ <answer>
  /*
   * Introduce el nombre y apellidos de los/as componentes del grupo:
   *
   * Estudiante 1:
   * Estudiante 2:
   *
   */
   //@ </answer>

#include <iostream>
#include <cassert>
#include <fstream>


class ListLinkedSingle {
private:
    struct Node {
        int value;
        Node* next;
    };

public:
    ListLinkedSingle() : head(nullptr) { }
    ~ListLinkedSingle() {
        delete_list(head);
    }

    ListLinkedSingle(const ListLinkedSingle& other)
        : head(copy_nodes(other.head)) { }

    void push_front(const int& elem) {
        Node* new_node = new Node{ elem, head };
        head = new_node;
    }

    void push_back(const int& elem);

    void pop_front() {
        assert(head != nullptr);
        Node* old_head = head;
        head = head->next;
        delete old_head;
    }

    void pop_back();

    int size() const;

    bool empty() const {
        return head == nullptr;
    };

    const int& front() const {
        assert(head != nullptr);
        return head->value;
    }

    int& front() {
        assert(head != nullptr);
        return head->value;
    }

    const int& back() const {
        return last_node()->value;
    }

    int& back() {
        return last_node()->value;
    }

    const int& at(int index) const {
        Node* result_node = nth_node(index);
        assert(result_node != nullptr);
        return result_node->value;
    }

    int& at(int index) {
        Node* result_node = nth_node(index);
        assert(result_node != nullptr);
        return result_node->value;
    }

    void display(std::ostream& out) const;
    void display() const {
        display(std::cout);
    }

    // Nuevo método. Debe implementarse abajo
    void intersect(const ListLinkedSingle& l2);

private:
    Node* head;

    void delete_list(Node* start_node);
    Node* last_node() const;
    Node* nth_node(int n) const;
    Node* copy_nodes(Node* start_node) const;

};

ListLinkedSingle::Node* ListLinkedSingle::copy_nodes(Node* start_node) const {
    if (start_node != nullptr) {
        Node* result = new Node{ start_node->value, copy_nodes(start_node->next) };
        return result;
    }
    else {
        return nullptr;
    }
}

void ListLinkedSingle::delete_list(Node* start_node) {
    if (start_node != nullptr) {
        delete_list(start_node->next);
        delete start_node;
    }
}

void ListLinkedSingle::push_back(const int& elem) {
    Node* new_node = new Node{ elem, nullptr };
    if (head == nullptr) {
        head = new_node;
    }
    else {
        last_node()->next = new_node;
    }
}

void ListLinkedSingle::pop_back() {
    assert(head != nullptr);
    if (head->next == nullptr) {
        delete head;
        head = nullptr;
    }
    else {
        Node* previous = head;
        Node* current = head->next;

        while (current->next != nullptr) {
            previous = current;
            current = current->next;
        }

        delete current;
        previous->next = nullptr;
    }
}

int ListLinkedSingle::size() const {
    int num_nodes = 0;

    Node* current = head;
    while (current != nullptr) {
        num_nodes++;
        current = current->next;
    }

    return num_nodes;
}


ListLinkedSingle::Node* ListLinkedSingle::last_node() const {
    assert(head != nullptr);
    Node* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }
    return current;
}

ListLinkedSingle::Node* ListLinkedSingle::nth_node(int n) const {
    assert(0 <= n);
    int current_index = 0;
    Node* current = head;

    while (current_index < n && current != nullptr) {
        current_index++;
        current = current->next;
    }

    return current;
}

void ListLinkedSingle::display(std::ostream& out) const {
    out << "[";
    if (head != nullptr) {
        out << head->value;
        Node* current = head->next;
        while (current != nullptr) {
            out << ", " << current->value;
            current = current->next;
        }
    }
    out << "]";
}

// ----------------------------------------------------------------
//@ <answer>

// Implementa a continuación el método pedido.

void ListLinkedSingle::intersect(const ListLinkedSingle& other) {
    Node* curr = head;
    Node* oCurr = other.head;
    Node* lastIntersec = nullptr;

    /*Los elems. de ambas listas solo pueden intersecar si
    el elemento curr es <= a oCurr para que la solución sea de coste lineal
    en los O(other.num_elems + this.num_elems))*/

    while (curr != nullptr && oCurr != nullptr) {
        if (curr->value < oCurr->value) {
            Node* aux = curr;
            curr = curr->next;
            delete aux;
        }
        else if (curr->value > oCurr->value) {
            oCurr = oCurr->next;
        }
        else {
            if (lastIntersec == nullptr) {
                this->head = curr;
                lastIntersec = curr;
            }
            else {
                lastIntersec->next = curr;
                lastIntersec = curr;
            }

            curr = curr->next;
            oCurr = oCurr->next;
        }
    }

    //Borrar la lista this para que no haya memory leaks
    if (curr != nullptr) {
        while (curr != nullptr) {
            Node* aux = curr;
            curr = curr->next;
            delete aux;
        }
    }

    if (lastIntersec != nullptr)
        lastIntersec->next = nullptr;
    else this->head = nullptr;
}

//@ </answer>

// ¡No modificar nada debajo de esta línea!
// ----------------------------------------------------------------

using namespace std;

ListLinkedSingle leer_lista() {
    int N;
    cin >> N;
    ListLinkedSingle lista;
    for (int i = 0; i < N; ++i) {
        int x; cin >> x;
        lista.push_back(x);
    }
    return lista;
}
void resuelveCaso() {
    ListLinkedSingle lista1 = leer_lista();
    ListLinkedSingle lista2 = leer_lista();

    lista1.intersect(lista2);
    lista1.display(); cout << '\n';
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    // Leemos el número de casos de prueba que vendrán a continuación
    int num_casos;
    cin >> num_casos;

    for (int i = 0; i < num_casos; i++) {
        resuelveCaso();
    }

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}
