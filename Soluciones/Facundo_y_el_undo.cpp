#include <iostream>
#include <stack>

void ctrlDelete(std::deque<std::string>& frase, std::stack<std::string>& deleted) {
	if (!frase.empty()) {
		deleted.push(frase.front());
		frase.pop_front();
	}
}

void ctrlZ(bool deleteAnterior, std::deque<std::string>& frase, std::stack<std::string>& deleted) {
	if (deleteAnterior) {
		frase.push_front(deleted.top());
		deleted.pop();
	}
	else ctrlDelete(frase, deleted);
}

void res() {
	std::deque<std::string> frase;
	std::stack<std::string> deleted;
	std::stack<bool> acciones; //"true" si ha hecho delete en ese momento, "false" si ha escrito una palabra

	std::string palabra;
	while (std::cin >> palabra) {
		if (palabra == "*") {
			ctrlDelete(frase, deleted);
			acciones.push(true);
		}
		else if (palabra == "+") {
			if (!acciones.empty()) {
				ctrlZ(acciones.top(), frase, deleted);
				acciones.pop();
			}
		}
		else {
			frase.push_front(palabra);
			acciones.push(false);
		}

		if (std::cin.peek() == '\n') break;
	}

	std::cin.ignore();

	while (frase.size() > 1) {
		std::cout << frase.back() << ' ';
		frase.pop_back();
	}
	std::cout << frase.back() << '\n';
}

int main() {
	int nc; std::cin >> nc;
	while (nc--) res();
}