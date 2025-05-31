#include <iostream>

class ListLinkedSingle {
private:
	struct Node {
		int value;
		Node* next;
	};
	Node* head;
	Node* last_node() const {
		Node* current = head;
		while (current->next != nullptr) {
			current = current->next;
		}
		return current;
	}
public:
	void push_back(const int& elem) {
		Node* new_node = new Node{ elem, nullptr };
		if (head == nullptr) {
			head = new_node;
		}
		else {
			last_node()->next = new_node;
		}
	}
	ListLinkedSingle() : head(nullptr) {}
	void rev_seg(int a, int b);
	void display() {
		std::cout << '[';
		if (head != nullptr) {
			std::cout << head->value;
			Node* aux = head->next;
			while (aux != nullptr) {
				std::cout << ", " << aux->value;
				aux = aux->next;
			}
		}
		std::cout << "]\n";
	}
	void read(int N) {
		if (N > 0) {
			this->head = new Node();
			std::cin >> this->head->value;
			Node* current = new Node();
			this->head->next = current;
			for (int i = 1; i < N; ++i) {
				std::cin >> current->value;
				current->next = new Node();
				current = current->next;
			}
			current->next = nullptr;
		}
	}
};

void ListLinkedSingle::rev_seg(int a, int num_elems_inv) {
	//O(n) donde n = num_elems_inv
	Node* actual = head;
	Node* previo = nullptr;

	int cont = 0;
	while (cont < a) {
		previo = actual;
		actual = actual->next;
		++cont;
	}

	Node* previousToHead_a = previo;
	Node* head_a = actual;

	previo = actual;
	actual = actual->next;
	Node* next;

	cont = 1;
	while (cont < num_elems_inv) {
		next = actual->next;
		actual->next = previo;
		previo = actual;
		actual = next;
		++cont;
	}
	
	head_a->next = actual;
	if (previousToHead_a != nullptr) previousToHead_a->next = previo;
	else head = previo;
}

bool res() {
	ListLinkedSingle l;
	int N, a, num_el_inv;
	std::cin >> N >> a >> num_el_inv;
	if (!std::cin) return false;
	int elem;
	while (N--) {
		std::cin >> elem;
		l.push_back(elem);
	}
	l.rev_seg(a, num_el_inv);
	l.display();
	return true;
}

int main() {
	while (res());
		
	return 0;
}