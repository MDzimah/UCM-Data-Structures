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
	void duplicate();
	void display(){
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

void ListLinkedSingle::duplicate() {
	//O(n) donde n = tamaño lista
	if (head != nullptr) {
		Node* aux = head->next;
		head->next = new Node{ head->value,aux };
		while (aux != nullptr) {
			Node* old = aux;
			aux = aux->next;
			old->next = new Node{ old->value, aux };
		}
	}
}

void res() {
	ListLinkedSingle l;
	std::cin >> l;
	l.duplicate();
	l.display();
}

int main() {
	int nc; std::cin >> nc;
	for (int i = 0; i < nc; ++i)
		res();
	return 0;
}