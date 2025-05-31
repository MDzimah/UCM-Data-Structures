#include <iostream>

class ListLinkedSingle {
private:
	struct Node {
		int value;
		Node* next;
	};
	Node* head;
public:
	ListLinkedSingle() : head(nullptr) {}
	void reverse();
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
	void read(std::istream& in) {
		int aux; in >> aux;
		if (aux != 0) {
			head = new Node();
			head->value = aux;

			Node* current = head;

			in >> aux;
			while (aux != 0) {
				current->next = new Node();
				current = current->next;
				current->value = aux;
				in >> aux;
			}
		}
	}
};

std::istream& operator>> (std::istream& in, ListLinkedSingle& l) {
	l.read(in);
	return in;
}

void ListLinkedSingle::reverse() {
	//O(n) donde n = tamaño lista
		Node* actual = head;
		Node* previo = nullptr;
		Node* next;
		while (actual != nullptr) {
			next = actual->next;
			actual->next = previo;
			previo = actual;
			actual = next;
		}
		head = previo;
}

void res() {
	ListLinkedSingle l;
	std::cin >> l;
	l.reverse();
	l.display();
}

int main() {
	int nc; std::cin >> nc;
	for (int i = 0; i < nc; ++i)
		res();
	return 0;
}