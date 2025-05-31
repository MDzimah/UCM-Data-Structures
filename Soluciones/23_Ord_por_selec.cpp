#include <cassert>
#include <iostream>
#include <fstream>

template <typename T>
class ListLinkedDouble
{
private:
    struct Node
    {
        T value;
        Node* next;
        Node* prev;
    };

public:
    ListLinkedDouble() : num_elems(0)
    {
        head = new Node;
        head->next = head;
        head->prev = head;
    }

    ListLinkedDouble(const ListLinkedDouble& other) : ListLinkedDouble()
    {
        copy_nodes_from(other);
        num_elems = other.num_elems;
    }

    ~ListLinkedDouble() { delete_nodes(); }

    void push_front(const T& elem)
    {
        Node* new_node = new Node{ elem, head->next, head };
        head->next->prev = new_node;
        head->next = new_node;
        num_elems++;
    }

    void push_back(const T& elem)
    {
        Node* new_node = new Node{ elem, head, head->prev };
        head->prev->next = new_node;
        head->prev = new_node;
        num_elems++;
    }

    void pop_front()
    {
        assert(num_elems > 0);
        Node* target = head->next;
        head->next = target->next;
        target->next->prev = head;
        delete target;
        num_elems--;
    }

    void pop_back()
    {
        assert(num_elems > 0);
        Node* target = head->prev;
        target->prev->next = head;
        head->prev = target->prev;
        delete target;
        num_elems--;
    }

    int size() const { return num_elems; }

    bool empty() const { return num_elems == 0; };

    const T& front() const
    {
        assert(num_elems > 0);
        return head->next->value;
    }

    T& front()
    {
        assert(num_elems > 0);
        return head->next->value;
    }

    const T& back() const
    {
        assert(num_elems > 0);
        return head->prev->value;
    }

    T& back()
    {
        assert(num_elems > 0);
        return head->prev->value;
    }

    const T& operator[](int index) const
    {
        assert(0 <= index && index < num_elems);
        Node* result_node = nth_node(index);
        return result_node->value;
    }

    T& operator[](int index)
    {
        assert(0 <= index && index < num_elems);
        Node* result_node = nth_node(index);
        return result_node->value;
    }

    ListLinkedDouble& operator=(const ListLinkedDouble& other)
    {
        if (this != &other)
        {
            delete_nodes();
            head = new Node;
            head->next = head->prev = head;
            copy_nodes_from(other);
            num_elems = other.num_elems;
        }
        return *this;
    }

    void display(std::ostream& out) const;

    void display() const { display(std::cout); }

    class iterator
    {
    public:
        iterator& operator++()
        {
            assert(current != head);
            current = current->next;
            return *this;
        }

        iterator& operator--() {
            assert(current != head->next);
            current = current->prev;
            return *this;
        }

        T& operator*() const
        {
            assert(current != head);
            return current->value;
        }

        bool operator==(const iterator& other) const
        {
            return (head == other.head) && (current == other.current);
        }

        bool operator!=(const iterator& other) const { return !(*this == other); }

        friend class ListLinkedDouble;

    private:
        iterator(Node* head, Node* current) : head(head), current(current) {}
        Node* head;
        Node* current;
    };

    iterator begin() { return iterator(head, head->next); }
    iterator end() { return iterator(head, head); }

    Node* minimum(Node* start, Node* end) const;
    void sort_and_dedup();

private:
    Node* head;
    int num_elems;

    Node* nth_node(int n) const;
    void delete_nodes();
    void copy_nodes_from(const ListLinkedDouble& other);
    void detach(Node* node);
    void attach(Node* node, Node* position);
};

template <typename T>
typename ListLinkedDouble<T>::Node* ListLinkedDouble<T>::nth_node(int n) const
{
    int current_index = 0;
    Node* current = head->next;

    while (current_index < n && current != head)
    {
        current_index++;
        current = current->next;
    }

    return current;
}

template <typename T>
void ListLinkedDouble<T>::delete_nodes()
{
    Node* current = head->next;
    while (current != head)
    {
        Node* target = current;
        current = current->next;
        delete target;
    }

    delete head;
}

template <typename T>
void ListLinkedDouble<T>::copy_nodes_from(const ListLinkedDouble& other)
{
    Node* current_other = other.head->next;
    Node* last = head;

    while (current_other != other.head)
    {
        Node* new_node = new Node{ current_other->value, head, last };
        last->next = new_node;
        last = new_node;
        current_other = current_other->next;
    }
    head->prev = last;
}

template <typename T>
void ListLinkedDouble<T>::display(std::ostream& out) const
{
    out << "[";
    if (head->next != head)
    {
        out << head->next->value;
        Node* current = head->next->next;
        while (current != head)
        {
            out << ", " << current->value;
            current = current->next;
        }
    }
    out << "]";
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const ListLinkedDouble<T>& l)
{
    l.display(out);
    return out;
}


/*
ANSWER

La función detach tiene coste constante porque se ejecutan un numero fijo (5 en concreto)
de instrucciones de coste constante. Lo mismo sucede con la funcion attach,

La funcion minimum tiene coste lineal en el tamaño del segmento tratado que es end - start donde
start es cerrado y end abierto

La funcion sort_and_dedup tiene coste lineal cuadratico, porque iterato sobre todos los elementos
de la lista una vez y en cada iteracion, ejecuta un numero fijo de instrucciones de coste constante
mas una vez la funcion minimum que tiene coste lineal. Luego, por la regla del producto, el coste
resultante es cuadratico en el numero de elementos de la lista.
Aunque fuera del bucle tenemos otro bucle while que elimina las repeticion, este tiene coste lineal
en el numero de elementos de la lista, y port tanto, se coge el maximo de ambos. Es decir, coste
cuadratico.

Las funciones attach, detach y minimum vienen explicadas en la especificacion.
En el caso de la funcion sort_and_dedup, se avanza un node current que itera sobre la lista
y avanza si es distinto del minimo econtrado en el segmento start-end.
En caso constrario, cogemos el minimo calculado y lo metemos antes que current.
El bucle acaba porque el ultimo es el minimo del segemento start end de longitud 1 y por tanto
avanza a end.
Al final, eleminamos las repeticiones con un bucle while.

*/

template <typename T>
void ListLinkedDouble<T>::detach(ListLinkedDouble<T>::Node* node)
{
    node->prev->next = node->next;
    node->next->prev = node->prev;
    node->next = nullptr;
    node->prev = nullptr;
    num_elems--;
}

// añade un nodo antes del nodo apuntado por position
template <typename T>
void ListLinkedDouble<T>::attach(ListLinkedDouble<T>::Node* node, ListLinkedDouble<T>::Node* position)
{
    node->next = position;
    node->prev = position->prev;
    position->prev->next = node;
    position->prev = node;
    num_elems++;
}

template <typename T>
typename ListLinkedDouble<T>::Node* ListLinkedDouble<T>::minimum(ListLinkedDouble<T>::Node* start, ListLinkedDouble<T>::Node* end) const {
    Node* min = start;
    start = start->next;
    while (start != end) {
        if (start->value < min->value) {
            min = start;
        }
        start = start->next;
    }
    return min;
}

template <typename T>
void ListLinkedDouble<T>::sort_and_dedup() {
    if (num_elems > 1) {
        Node* curr = head->next;
        while (curr != head) {
            Node* next = curr->next;
            Node* min = minimum(curr, head);
            if (min != curr) {
                detach(min);
                attach(min, curr);
            }
            else {
                curr = next;
            }
        }
        curr = head->next->next;
        while (curr != head) {
            if (curr->prev->value == curr->value) {
                Node* aux = curr->prev;
                detach(curr->prev);
                delete aux;
            }
            curr = curr->next;
        }
    }
}


using namespace std;

void resuelveCaso()
{
    ListLinkedDouble<int> lista;
    int v;
    cin >> v;
    while (v != -1)
    {
        lista.push_back(v);
        cin >> v;
    }

    lista.sort_and_dedup();

    std::cout << lista << "\n";

}

int main()
{
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    int casos;
    cin >> casos;

    while (casos--)
    {
        resuelveCaso();
    }

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    // Descomentar si se trabaja en Visual Studio
    // system("PAUSE");
#endif
    return 0;
}
