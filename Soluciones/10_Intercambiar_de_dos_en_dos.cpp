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

    int & at(int index) {
        assert(0 <= index && index < num_elems);
        Node* result_node = nth_node(index);
        return result_node->value;
    }

    void display(std::ostream& out) const;

    void display() const { display(std::cout); }

    void swap2by2();

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

void ListLinkedDouble::swap2by2() {
    //O(num_elems)
    Node* n1 = head->next, *n2 = head->next->next;
    int aux = num_elems;
    if (num_elems % 2 != 0) aux = num_elems - 1;

    for (int i = 0; i < aux; i += 2) {
        std::swap(n1->value, n2->value);
        n1 = n1->next->next;
        n2 = n2->next->next;
    }
}

bool res() {
    int N;
    std::cin >> N;
    if (N == 0) return false;

    ListLinkedDouble l;
    while (N--) {
        int aux;
        std::cin >> aux;
        l.push_back(aux);
    }
    l.swap2by2();
    l.display();
    std::cout << '\n';

    return true;
}


int main() {
    while (res());
    return 0;
}