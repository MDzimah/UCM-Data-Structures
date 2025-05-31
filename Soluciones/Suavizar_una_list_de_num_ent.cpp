#include <list>
#include <iostream>

using li = std::list<int>;

void insertarSuavizantes(li& l, li::iterator& e1, li::iterator& e2) {
	if (*e2 > *e1) {
		e2 = l.insert(e2, *e2 - 1);
		if (abs(*e2 - *e1) != 1) e1 = l.insert(e2, *e1 + 1);
		else e1 = e2;
	}
	else {
		e2 = l.insert(e2, *e2 + 1);
		if (abs(*e2 - *e1) != 1) e1 = l.insert(e2, *e1 - 1);
		else e1 = e2;
	}
}

void suavizar(li& l) {
	auto act = l.begin();
	auto next = ++l.begin();
	
	//Elimino elems repetidos
	while (next != l.end()) {
		if (*act == *next) next = l.erase(next);
		else {
			++act; 
			++next;
		}
	}

	//Suavizo
	act = l.begin();
	next = ++l.begin();

	while (next != l.end()) {
		if (abs(*act - *next) != 1) {
			auto aux = next; //Para poder después avanzar para suavizar la próxima pareja de números
			while (act != next && abs(*act - *next) != 1) {
				insertarSuavizantes(l, act, next);
			}
			act = aux;
			next = ++aux;
		}
		else {
			++act;
			++next;
		}
	}
}

bool res() {
	int tam; std::cin >> tam;
	if (!std::cin) return false;

	li l;
	while (tam--) {
		int aux; std::cin >> aux;
		l.push_back(aux);
	}

	suavizar(l);

	std::ostream_iterator<int> sal(std::cout, " ");
	for (int i : l) {
		*sal = i;
	}
	std::cout << '\n';

	return true;
}

int main() {
	while (res());
	return 0;
}