#include <cassert>
#include <iostream>
#include <string>

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

    ListLinkedDouble(const ListLinkedDouble& other);
    ~ListLinkedDouble();

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

    const int& at(int index) const {
        assert(0 <= index && index < num_elems);
        Node* result_node = nth_node(index);
        return result_node->value;
    }

    int& at(int index) {
        assert(0 <= index && index < num_elems);
        Node* result_node = nth_node(index);
        return result_node->value;
    }

    void display(std::ostream& out) const;

    void display() const { display(std::cout); }

    void zip(ListLinkedDouble& other);

private:
    Node* head;
    int num_elems;

    Node* nth_node(int n) const;
};

ListLinkedDouble::ListLinkedDouble(const ListLinkedDouble& other)
    : ListLinkedDouble() {
    Node* current_other = other.head->next;
    Node* last = head;

    while (current_other != other.head) {
        Node* new_node = new Node{ current_other->value, head, last };
        last->next = new_node;
        last = new_node;
        current_other = current_other->next;
    }
    head->prev = last;
    num_elems = other.num_elems;
}

ListLinkedDouble::~ListLinkedDouble() {
    Node* current = head->next;
    while (current != head) {
        Node* target = current;
        current = current->next;
        delete target;
    }

    delete head;
}

ListLinkedDouble::Node* ListLinkedDouble::nth_node(int n) const {
    int current_index = 0;
    Node* current = head->next;

    while (current_index < n && current != head) {
        current_index++;
        current = current->next;
    }

    return current;
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

void ListLinkedDouble::zip(ListLinkedDouble& other) {
    //O(this.num_elems + other.num_elems)
    int least_size = std::min(this->num_elems, other.num_elems);
    int sumSizes = this->num_elems + other.num_elems;
   
    Node* curr = this->head->next;
    Node* oCurr = other.head->next; 
    Node* next_t = this->head->next->next;
    Node* next_o  = other.head->next->next;
   
    other.head->next = other.head; //Para asegurar que al final de todo se quede solo un nodo fantasma circular

    for (int i = 0; i < least_size; ++i) {
        curr->next = oCurr;
        oCurr->next = next_t;
        oCurr->prev = curr;
        next_t->prev = oCurr;

        curr = next_t;
        oCurr = next_o;
        next_t = next_t->next;
        next_o = next_o->next;
        ++this->num_elems;
    }

    //Han quedado elems. de other sin meter en this
    if (this->num_elems < sumSizes) {
        if (curr == this->head) curr = this->head->prev; //Buscamos conectar el final de this lista con la de other, luego curr tiene que ser el último nodo de this list
        curr->next = oCurr;
        oCurr->prev = curr;
        this->head->prev = other.head->prev;
        other.head->prev->next = this->head;
    }

    other.head->prev = other.head; //Ídem
    //Para cumplir el invariante hace falta que "other.num_elems = 0;"
}

void res() {
    int N,M;
    std::cin >> N;

    ListLinkedDouble l1;
    while (N--) {
        int aux;
        std::cin >> aux;
        l1.push_back(aux);
    }

    std::cin >> M;
    ListLinkedDouble l2;
    while (M--) {
        int aux;
        std::cin >> aux;
        l2.push_back(aux);
    }

    l1.zip(l2);
    l1.display();
    std::cout << '\n';
}


int main() {
    int nc; std::cin >> nc;
    while (nc--) 
        res();
    return 0;
}